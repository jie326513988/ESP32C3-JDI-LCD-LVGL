struct LOCATEINFO // 定位信息结构体
{
    //****** RMC (时间、日期、位置、速度) ****** 
    String UTCTime;        // UTC时间 hhmmss.sss
    String state;          // 状态 A=数据有效；V=数据无效
    String latitude;       // 纬度 ddmm.mmmm
    String NS;             // N/S 指示 N=北，S=南
    String longitude;      // 经度 dddmm.mmmm
    String EW;             // E/W 指示 W=西，E=东
    String groundSpeed;    // 地面速度 Knot（节）
    String azimuthAngle;   // 方位角 度
    String UTCDate;        // UTC日期
    String magneticDec;    // 磁偏角 (000-180)度（前导位数不足则补0）
    String magneticDecDir; // 磁偏角方向，E=东 W=西
    String modeInd;        // 模式指示(仅NMEA01833.00版本输出，A=自主定位，D=差分，E=估算，N=数据无效)
    
    //****** GGA (时间、位置、定位类型) ****** 
    String satelliteNum;   // 卫星数量
    String HDOP;           // 水平精度
    String MSL;            // 平均海平面高度

    // 校验和 $和*之间所有字符 ASCII 码的校验和 将这些字符逐个按位进行异或（XOR）运算。
    String checksum;
};
LOCATEINFO locateInfo;

bool NMEA0183(String in); // 解析总协议
bool analysisRMC(String in, LOCATEINFO *info); // 解析RMC 消息 (时间、日期、位置、速度) 12个
bool analysisGGA(String in, LOCATEINFO *info); // 解析GGA 消息 (时间、位置、定位类型) 13个
bool analysisVTG(String in, LOCATEINFO *info);
/**
 * @brief    接收数据
 * @param    rxCmd   : 接收到的数据缓存在该数组
 * @param    rxCount : 接收到的数据长度
 * @param    rxMax   : 接收数据的最大长度
 * @retval   无
 */

/*void receive_Data(uint8_t *rxCmd, uint8_t *rxCount, uint8_t rxMax)
{
    int i = 0;
    const unsigned long TIMEOUT = 100; // 超时时间
    unsigned long lastTime = millis(); // 上一时刻的时间

    // 开始接收数据
    while (true)
    {
        if (Serial0.available() > 0) // 串口有数据
        {
            int data = Serial0.read(); // 读取数据
            if (data == -1) continue; // 读取失败时跳过
            rxCmd[i++] = (uint8_t)data; // 将数据存入数组
            lastTime = millis();        // 更新上一时刻的时间
            if (i >= rxMax) break; // 达到最大接收长度，退出循环
        }
        else // 串口没有数据
        {
            unsigned long currentTime = millis(); // 当前时间
            delay(10);
            if ((currentTime - lastTime) > TIMEOUT) // 超时检测
            {
                break; // 超时退出
            }
        }
    }
    *rxCount = i; // 设置数据长度
}*/

String receive_Data(HardwareSerial &my_Serial)
{
    int i = 0;
    uint8_t TIMEOUT = 100; // 超时时间
    uint32_t lastTime = millis(); // 上一时刻的时间
    uint16_t rxMax = 255;
    String out;
    // 开始接收数据
    for (;;)
    {
        if (my_Serial.available() > 0) // 串口有数据
        {
            char data = my_Serial.read(); // 读取数据
            //if (data == -1) continue; // 读取失败时跳过
            out += data; // 将数据存入数组
            lastTime = millis(); // 更新上一时刻的时间
            i++;
            if (i >= rxMax) break; // 达到最大接收长度，退出循环
        }
        else // 串口没有数据
        {
            uint32_t currentTime = millis(); // 当前时间
            if ((currentTime - lastTime) > TIMEOUT) // 超时检测
                break; // 超时退出
            vTaskDelay(1);
        }
    }
    return out;
}

void locateInfo_rtos_init() // 创建北斗读取任务
{
    xTaskCreatePinnedToCore(
        locateInfoRead_rtos, /* 任务指针，创建任务用的那个函数名 */
        "locateInfo",        /* 任务名称 */
        4 * 1024,            /* 任务栈大小，根据需要自行设置*/
        NULL,                /* 可选参数，一般不填*/
        2,                   /* 优先级 */
        &TH_locateInfo,      /* 任务句柄，用于后续挂起或恢复运行*/
        0                    /* 核ID */
    );
}
void locateInfoRead_rtos(void *param)
{
    // 关闭虚拟USB串口
    Serial0.flush();
    Serial0.end();
    delay(100);
    // 重新设置串口
    Serial1.begin(9600, SERIAL_8N1, UART1_RX, UART1_TX);
    Serial1.setTimeout(100);
    delay(100);
    Serial1.flush();
    delay(100);
    bool state = 0;
    uint8_t buzzerTime = 0;
    uint8_t stop_count = 0;
    for (;;)
    {
        if (!bitRead(backgroundTask, BGT_LOCATE_INFO_READ))
        {
            Serial1.flush();
            Serial1.end();
            //Serial.println("删除TH_locateInfo");
            TH_locateInfo = NULL;
            vTaskDelete(NULL);
        }

        String str;
        str = receive_Data(Serial1);

        /*while (Serial1.available() > 0) // 串口有数据进来
        {
            str += char(Serial1.read()); // 接收数据
        }*/

        if (NMEA0183(str) == 0)
        {
            // 无消息一定次数清空结构体
            stop_count++;
            if (stop_count > 10)
                structClear((unsigned char *)&locateInfo, sizeof(locateInfo)); // 清空结构体
            locateInfo.state = "V"; //标记数据无效
        }
        else stop_count = 0;

        delay(500);

        // 状态
        if(locateInfo.state) 
        {
            if(locateInfo.state[0] == 'A') state = 1;
            else                           state = 0;
        }

        buzzerTime++;
        if (state == 1 && buzzerTime >= 3) // 数据有效3次响一下
        {
            buzzerSen(30);
            buzzerTime = 0;
        }
        else if (state == 0 && buzzerTime >= 1)  // 数据无效1次响一下
        {
            buzzerSen(30);
            buzzerTime = 0;
        }
    }
}

// 解析RMC 消息 (时间、日期、位置、速度) 12个
bool analysisRMC(String in, LOCATEINFO *info)
{
    uint8_t pos = 0;
    //structClear((unsigned char *)info, sizeof(*info)); // 清空结构体

    //************ 检查检验和
    char checksum = in[0]; // 需要计算的校验和
    bool checksumEn = 1;   // 校验和计算使能
    bool checksumOk = 0;   // 校验结果
    for (uint16_t i = 0; i < in.length(); i++)
    {
        char c = in[i];
        // 校验和 每位异或
        if (c == '*') checksumEn = 0;
        else if(checksumEn)
        {
            // Serial.print("i:");Serial.print(i);Serial.print(" c:");Serial.print(c);
            if(i > 0) checksum ^= c;
            // Serial.print(" checksum:");  Serial.println(checksum, HEX);
        }
        if      (c == ',')  pos++;
        else if (pos == 13) info->checksum += c; // 校验和 $和*之间所有字符 ASCII 码的校验和
    }
    // 检验结果
    String in_checksum; // 提取*后面的字符
    bool en = 0;
    for (uint8_t i; i < info->checksum.length(); i++)
    {
        char c = info->checksum[i];
        if (c == '*') en = 1;
        else if (en) in_checksum += c;
    }
    //String转换为char
    char converted_checksum = (char)strtol(in_checksum.c_str(), NULL, 16);
    if (converted_checksum != checksum)
    {
        //Serial.println("校验失败");
        return 0; //校验失败返回
    }

    info->UTCTime.clear();
    info->state.clear();
    info->latitude.clear();
    info->NS.clear();
    info->longitude.clear();
    info->EW.clear();
    info->groundSpeed.clear();
    info->azimuthAngle.clear();
    info->UTCDate.clear();
    info->magneticDec.clear();
    info->magneticDecDir.clear();
    info->modeInd.clear();
    info->checksum.clear();
    pos = 0;
    for (uint16_t i = 0; i < in.length(); i++)
    {
        char c = in[i];
        // 解析
        if      (c == ',')  pos++;
        else if (pos == 1)  info->UTCTime += c;        // UTC时间
        else if (pos == 2)  info->state += c;          // 状态 A=数据有效 V=数据无效
        else if (pos == 3)  info->latitude += c;       // 纬度 ddmm.mmmm
        else if (pos == 4)  info->NS += c;             // N/S 指示 N=北，S=南
        else if (pos == 5)  info->longitude += c;      // 经度 dddmm.mmmm
        else if (pos == 6)  info->EW += c;             // E/W 指示 W=西，E=东
        else if (pos == 7)  info->groundSpeed += c;    // 地面速度 Knot（节）
        else if (pos == 8)  info->azimuthAngle += c;   // 方位角 度
        else if (pos == 9)  info->UTCDate += c;        // UTC日期
        else if (pos == 10) info->magneticDec += c;    // 磁偏角 (000-180)度（前导位数不足则补0）
        else if (pos == 11) info->magneticDecDir += c; // 磁偏角方向，E=东 W=西
        else if (pos == 12) info->modeInd += c;        // 模式指示(仅NMEA01833.00版本输出，A=自主定位，D=差分，E=估算，N=数据无效)
        else if (pos == 13) break; // 提前退出
    }

    //转换成公里
    float speed = atof(info->groundSpeed.c_str());
    speed = speed * 1.85;
    info->groundSpeed = String(speed, 1);

    return 1;
    //Serial.print("info->state:");Serial.println(info->state);
    //Serial.print("checksum:");Serial.println(checksum,HEX); // 计算的校验和
    //Serial.print("in_checksum:");Serial.println(in_checksum);  // 接收的检验和 去掉*号
    //Serial.print("converted_checksum:");Serial.println(converted_checksum,HEX);//  接收的检验和 char格式
    //Serial.println();
}
// 解析GGA 消息 (时间、位置、定位类型) 13个
bool analysisGGA(String in, LOCATEINFO *info)
{
    uint8_t pos = 0;
    //************ 检查检验和
    char checksum = in[0]; // 需要计算的校验和
    bool checksumEn = 1;   // 校验和计算使能
    for (uint16_t i = 0; i < in.length(); i++)
    {
        char c = in[i];
        // 校验和 每位异或
        if (c == '*') checksumEn = 0;
        else if(checksumEn)
        {
            // Serial.print("i:");Serial.print(i);Serial.print(" c:");Serial.print(c);
            if(i > 0) checksum ^= c;
            // Serial.print(" checksum:");  Serial.println(checksum, HEX);
        }
        if      (c == ',')  pos++;
        else if (pos == 14) info->checksum += c;       // 校验和 $和*之间所有字符 ASCII 码的校验和
    }
    // 检验结果
    String in_checksum; // 提取*后面的字符
    bool en = 0;
    for (uint8_t i; i < info->checksum.length(); i++)
    {
        char c = info->checksum[i];
        if (c == '*') en = 1;
        else if (en) in_checksum += c;
    }
    //String转换为char
    char converted_checksum = (char)strtol(in_checksum.c_str(), NULL, 16);
    if (converted_checksum != checksum)
    {
        //Serial.println("校验失败");
        return 0; //校验失败返回
    }

    info->satelliteNum.clear();
    info->HDOP.clear();
    info->MSL.clear();
    info->checksum.clear();
    pos = 0;
    for (uint16_t i = 0; i < in.length(); i++)
    {
        char c = in[i];
        if      (c == ',')  pos++;
        //else if (pos == 1) // UTC时间
        //else if (pos == 2)  // 纬度 ddmm.mmmm
        //else if (pos == 3)  // N/S 指示 N=北，S=南
        //else if (pos == 4)  // 经度 dddmm.mmmm
        //else if (pos == 5)  // E/W 指示 W=西，E=东
        //else if (pos == 6)  // 定位指示
        else if (pos == 7) info->satelliteNum += c; // 卫星数目
        else if (pos == 8) info->HDOP += c;         // HDOP 水平精度
        else if (pos == 9) info->MSL += c;          // MSL 幅度 平均海平面高度
        else if (pos == 10)  break;  // 提前退出
        //else if (pos == 10)  // 单位  M 米 单位：米
        //else if (pos == 11) // 大地 0.0 米 平均海平面
        //else if (pos == 12) // 单位 M 单位：米
    }

    return 1;
    //Serial.print("checksum:");Serial.println(checksum,HEX); // 计算的校验和
    //Serial.print("in_checksum:");Serial.println(in_checksum);  // 接收的检验和 去掉*号
    //Serial.print("converted_checksum:");Serial.println(converted_checksum);//  接收的检验和 char格式
    //Serial.println();
}
// 解析VTG 消息 (地面速度信息) 8个
bool analysisVTG(String in, LOCATEINFO *info)
{
    uint8_t pos = 0;
     //************ 检查检验和
    char checksum = in[0]; // 需要计算的校验和
    bool checksumEn = 1;   // 校验和计算使能
    for (uint16_t i = 0; i < in.length(); i++)
    {
        char c = in[i];
        // 校验和 每位异或
        if (c == '*') checksumEn = 0;
        else if(checksumEn)
        {
            // Serial.print("i:");Serial.print(i);Serial.print(" c:");Serial.print(c);
            if(i > 0) checksum ^= c;
            // Serial.print(" checksum:");  Serial.println(checksum, HEX);
        }
        if      (c == ',')  pos++;
        else if (pos == 14) info->checksum += c;       // 校验和 $和*之间所有字符 ASCII 码的校验和
    }
    // 检验结果
    String in_checksum; // 提取*后面的字符
    bool en = 0;
    for (uint8_t i; i < info->checksum.length(); i++)
    {
        char c = info->checksum[i];
        if (c == '*') en = 1;
        else if (en) in_checksum += c;
    }
    //String转换为char
    char converted_checksum = (char)strtol(in_checksum.c_str(), NULL, 16);
    if (converted_checksum != checksum)
    {
        //Serial.println("校验失败");
        return 0; //校验失败返回
    }

    info->groundSpeed.clear();
    pos = 0;
    for (uint16_t i = 0; i < in.length(); i++)
    {
        char c = in[i];
        if      (c == ',') pos++;
        else if (pos == 7) info->groundSpeed += c;// 地面速率(0000.0~1851.8公里/小时，前面的0也将被传输)
        else if (pos == 8) break;
    }
    return 1;
    // Serial.print("state:");Serial.println(rmc->state);
    // Serial.print("modeInd:");Serial.println(rmc->modeInd);
}
// 解析总协议
bool NMEA0183(String in)
{
    //Serial.print("in.length():");Serial.println(in.length());

    if(in.length() < 10) return 0; 

    uint8_t stage = 0;
    String content; // 内容
    for (uint16_t i = 0; i < in.length(); i++)
    {
        char c = in[i];
        if (c == '$') // 检测标头
        {
            stage = 1;
            content.clear();
            if (in.length() - i < 10)  return 0; // 长度不足退出

            content += in[++i];  // B i = 1 跳过
            content += in[++i];  // D i = 2 跳过
            content += in[++i];  // R i = 3
            content += in[++i]; // M i = 4
            content += in[++i]; // C i = 5
            content += in[++i]; // , i = 6
        }
        else if (stage == 1) // 提取内容
        {
            if (c != '\r' && c != '\n') content += c;
            else stage = 2;
        }

        //处理内容
        if (stage == 2)
        {
            //buzzerSen(30);
            stage = 0;
            //Serial.print("content:");Serial.println(content);
            // 解析RMC (推荐最小定位信息)
            if (content[2] == 'R' && content[3] == 'M' && content[4] == 'C') 
                analysisRMC(content, &locateInfo);
            // 解析GGA (时间、位置、定位类型)
            else if (content[2] == 'G' && content[3] == 'G' && content[4] == 'A') 
                analysisGGA(content, &locateInfo);
            // 解析VTG (地面速度信息)
            //else if (content[2] == 'V' && content[3] == 'T' && content[4] == 'G') 
                //analysisVTG(content, &locateInfo);
        }
    }

    return 1; 
}