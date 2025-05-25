// 实时解析midi文件，使用蜂鸣器播放

// 文件头信息以MThd开始4D 54 68 64，紧接4位为长度信息，如00 00 00 06表示再这之后有6字节数据需要读取
// 轨道信息以MTrk开始4D 54 72 6B，紧接4位为长度信息，如00 00 00 0C表示再这之后有12字节数据需要读取，末尾00 FF 2F 00结束
// 1个tick = speed/quarterNoteTime ，单位us


// 大端模式，是指数据的低位保存在内存的高地址中，而数据的高位，保存在内存的低地址中
// 小端模式，是指数据的低位保存在内存的低地址中，而数 据的高位保存在内存的高地址中

//****** MIDI ******
#define MThd 0x4D546864
#define MTrk 0x4D54726B
struct MIDI
{
    bool run = 0;         // 运行状态 0未运行 1已运行
    //****** MThd（4D 54 68 64 文件头）
    uint8_t type = 0;     // 文件类型（2字节） 0 1 2
    uint8_t trackNum = 0; // 音轨数量（2字节） 0 1 2....
    // 时间类型和数量（2字节） 如00 60
    bool timeType = 0;            // 时间类型，第15位，0-按音符 1-按帧
    uint16_t quarterNoteTime = 0; // 0:第0-14位四分音符的Tick数，1:14-8SMPTE格式 7-0每帧Tick数

    //****** 第1条MTrk一般为元事件信息（4D 54 72 6B 轨道信息）
    // 拍号（00 FF 58 04 4字节），如04 02 18 08
    // 04-拍号分子
    // 02-拍号分母，2的X次方，这里2的2次方
    // 18-拍号分子，每个midi时钟包含的tick数
    // 08-拍号分子，每24个midi时钟，对应的32分音符的数目
    uint32_t timeSignature = 0;

    //****** 第2条开始的MTrk一般是正式的音乐数据（4D 54 72 6B 轨道信息）
    uint32_t speed = 0; // 速度（4字节），00 FF 51 LL开始，紧接LL位为实际数据
    String trackName;   // 轨道名称，00 FF 03 LL开始，紧接LL位为实际数据
    // 轨道的数据，乐器，时间，指令，音符，力度等
    uint32_t tickNum = 0;    // 音乐的时间，使用可变长度，读取2个字节后最高位为1则需再读取后2个字节，为0表不需要继续读取
    uint8_t instruct = 0;    // 音乐的指令（1字节）9x开，8x关，其他ax、bx、cx、dx、fx,不清楚
    uint8_t note = 0;        // 音乐的音符（1字节）
    uint8_t strength = 0;    // 音乐的力度（1字节）
    uint32_t frequency = 0;  // 音符的频率
    uint8_t instructOld = 0; // 上一次音乐的指令
    uint8_t noteOld = 0;     // 上一次开的音符
    uint8_t strengthOld = 0; // 上一次开音符的力度
    uint32_t oneTick = 0;
    uint64_t temp = 0; // 临时存储
};
MIDI midi;

void midiAnalysis(File &f, MIDI &midi);

BaseType_t midi_rtos_init(void *p)
{
    return xTaskCreate(
        midiTask,   /* 任务指针，创建任务用的那个函数名 */
        "midiTask", /* 任务名称 */
        6 * 1024,   /* 任务栈大小，根据需要自行设置*/
        p,          /* 可选参数，一般不填*/
        1,          /* 优先级 */
        &HT_midi    /* 任务句柄，用于后续挂起或恢复运行*/
    );
}
void midiTask(void *p)
{
    for (;;)
    {
        midi.run = 1;
        // char *midiName = (char *)p; //这个写法会导致赋值失败，勿用！
        char * midiName;
        midiName = (char *)p;
        // Serial.print("(char *)p:");Serial.println((char *)p);
        // Serial.print("midiName:");Serial.println(midiName);
        // 手动复制，否者会传入失败
        String name;
        uint8_t length = strlen(midiName);
        for (uint8_t i = 0; i < length; i++)
        {
            name += midiName[i];
            //Serial.print("midiName[" + String(i) + "]:");
            //Serial.println(midiName[i]);
        }
        delay(500);
        midiRun(name);
        free(midiName);
    }
}

uint16_t read16_B(File& f)
{
  uint16_t result;
  ((uint8_t *)&result)[1] = f.read(); // MSB 最高有效位 最左侧
  ((uint8_t *)&result)[0] = f.read(); // LSB 最低有效位 最右侧
  return result;
}

uint32_t read32_B(File& f)
{
  uint32_t result;
  ((uint8_t *)&result)[3] = f.read(); // MSB 最高有效位 最左侧
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[0] = f.read(); // LSB 最低有效位 最右侧
  return result;
}

// 加多一个字节到低位
void addByte(File &f, uint64_t &in)
{
    in = in << 8;
    ((uint8_t *)&in)[0] = f.read();
}

// 音符映射，输入midi的音符，输出音调和音符
/*void noteMap(uint8_t in, uint8_t &tone, uint8_t &note)
{
    // tone 音调0-7
    // note 音符0-11
    double in_f = 0.0;   // 浮点数
    double in_dec = 0.0; // 浮点数后的小数
    in = in - 12;
    in_f = in / 12.0;
    tone = in_f; //音调0-7
    in_dec = in_f - tone;
    note = 12.0 * in_dec + 0.5; //音符0-11 4省5入
}*/

// 将MIDI音符转换为频率
float midiNoteToFrequency(uint16_t note) {
  return 440.0 * pow(2.0, (note - 69) / 12.0);
}

// midi解析
void midiAnalysis(File &f, MIDI &midi)
{
    uint64_t delayAccumulate = 0;
    Serial.begin(115200);
    for (;;)
    {
        //Serial.println();
        overTime = 0;
        //delay(500);
        uint8_t variable = 0; // 可变长度增加了几次
        bool reduce = 0;      // 是否有缩减指令
        midi.temp = read32_B(f);

        // 音乐数据
        if (((uint8_t *)&midi.temp)[2] != 0xFF)
        {
            // 检测为可变长度的时间量
            while (((uint8_t *)&midi.temp)[3] > 0x80)
            {
                variable += 1; //标记可变长度
                addByte(f, midi.temp);
                Serial.println("可变长度加" + String(variable));
            }

            // 获取时间长度
            uint64_t reality_length;
            if(variable == 0) reality_length = ((uint8_t *)&midi.temp)[3];
            else// 可变长度
            {
                uint64_t temp = midi.temp;
                // 最高字节最高位清零
                bitWrite(((uint8_t *)&temp)[variable + 3], 7, 0);
                for (uint8_t i = variable; i > 0; i--)
                {
                    // 高字节的0位给到低1字节的7位
                    bitWrite(((uint8_t *)&temp)[i + 2], 7, bitRead(((uint8_t *)&temp)[i + 3], 0));
                    // 高字节右移1位
                    uint8_t temp1 = ((uint8_t *)&temp)[i + 3]; // 使用新的临时变量中转，不然会影响到其他字节
                    ((uint8_t *)&temp)[i + 3] = temp1 >> 1;
                }
                for (int8_t i = 0; i <= variable; i++)
                {
                    ((uint8_t *)&reality_length)[i] = ((uint8_t *)&temp)[i + 3];
                }
            }
            midi.tickNum = reality_length * midi.oneTick; // 计算发声时间

            if (((uint8_t *)&midi.temp)[2] < 0x80) // 音乐指令不存在
            {
                //Serial.println("缩减指令");
                reduce = 1;  // 标记缩减指令
                midi.temp = midi.temp >> 8; // 缓存区右移8位挤掉最后的字节
                f.seek(f.position() - 1);   // 退回1个字节
            }
            //Serial.print("midi.temp0:");Serial.println(midi.temp, HEX);

            // 获取音乐指令，如果没有则使用上一次的指令
            // 0x8x 9x ax bx cx dx ex f0
            if (reduce == 0) // 音乐指令存在
                midi.instruct = ((uint8_t *)&midi.temp)[2];

            // 音乐指令C0长度只要3，需要退回
            if ((midi.instruct & 0xF0) == 0xC0)
            {
                //Serial.println("C3指令 跳过");
                f.seek(f.position() - 1); //退回1个字节
                continue;
            }

            // 驱动蜂鸣器
            // 只能处理单音所以，只有在开指令时才更新音符和力度
            // 发声指令为开
            int64_t delay1 = midi.tickNum;
            // 是开指令
            if ((midi.instruct & 0xF0) == 0x90)
            {
                // 当有连续的无时间的开指令时，表示需要同时发出多个音符
                // 但蜂鸣器只有一个，所以让每个音符只出声2ms
                // 然后累积delayAccumulate，在下一次有时间的指令，抵消掉delayAccumulate的值
                if (midi.tickNum == 0 && (midi.instructOld & 0xF0) == 0x90)
                {
                    delay1 = 2000; // 延时2ms
                    delayAccumulate += 2000;
                }
            }

            if (midi.tickNum > 0) //只要存在时间就补偿和清空累积
            {
                delay1 = int64_t(midi.tickNum) - int64_t(delayAccumulate);
                if (delay1 < 0) delay1 = 2000; //至少响2ms
                delayAccumulate = 0;
            }

            //Serial.print("midi.tickNum:");Serial.println(midi.tickNum);
            //Serial.print("delay1:");Serial.println(delay1);
            //Serial.print("delayAccumulate:");Serial.println(delayAccumulate);

            // (力度大于0 && 大于1.2秒使用声音衰减算法) && (关指令 && 这次音符等于上一次开的音符)
            if (delay1 > 1200 * 1000 && midi.strengthOld > 0)
            {
                int64_t delay2 = delay1;
                //double dutyCycle = midi.strengthOld;
                for (uint8_t i = 0; i < 50; i++) // 衰减10次
                {
                    if (delay2 - 60000 >= 60000) // 还能衰减
                    {
                        delay2 -= 60000;
                        midi.strengthOld = midi.strengthOld * exp(-0.0025 * i); // 衰减曲线
                        uint16_t strength = map(midi.strengthOld, 0, 255, 0, 1023);
                        ledcWrite(BUZZER_CHANNEL, strength);
                        //delay(60); // 迭代时间
                        delayMicroseconds(60000); // 迭代时间
                    }
                    else // 时间不足以继续衰减
                    {
                        delayMicroseconds(delay2);
                        break;
                    } 
                }
            }
            else delayMicroseconds(delay1);

            // 更新音符和力度
            midi.note = ((uint8_t *)&midi.temp)[1];     // 音符
            midi.strength = ((uint8_t *)&midi.temp)[0]; // 力度
            // 打开时用这一次的音符
            if ((midi.instruct & 0xF0) == 0x90)
            {
                //Serial.println("打开");
                // 设置-通道，频率
                midi.frequency = midiNoteToFrequency(midi.note);
                ledcWriteTone(BUZZER_CHANNEL, midi.frequency);// 通道，频率
                // 输出-通道，占空比
                uint16_t strength = map(midi.strength, 0, 255, 0, 1023);
                ledcWrite(BUZZER_CHANNEL, strength);
                midi.noteOld = midi.note; // 更新上一次开的音符
                midi.strengthOld = midi.strength;
            }
            // 关闭时 要和上一次的打开的音符一致才关闭
            else if ((midi.instruct & 0xF0) == 0x80 && midi.note == midi.noteOld)
            {
                // Serial.println("关闭");
                ledcWrite(BUZZER_CHANNEL, 0); // 关闭
            }

            midi.instructOld = midi.instruct; // 更新上一次指令

            //Serial.print("指令-midi.instruct:");Serial.println(midi.instruct,HEX); // midi音乐指令
            //Serial.print("本次音符-midi.note:");Serial.println(midi.note);         // midi本次音符
            //Serial.print("上次打开音符:");Serial.println(midi.noteOld);            // midi上次打开的音符
            //Serial.print("频率-midi.frequency:");Serial.println(midi.frequency);  // midi音符的频率
            //Serial.print("力度-midi.strength:");Serial.println(midi.strength);    // midi音符的力度，即占空比
            //Serial.print("reality_length:");Serial.println(reality_length,HEX);   // midi音乐时间长度
            //Serial.print("midi.tickNum:");Serial.println(midi.tickNum);           // midi音乐实际延时   
        }
        // 系统指令 ((uint8_t *)&midi.temp)[3] == 0x00 && ((uint8_t *)&midi.temp)[2] == 0xFF
        else
        {
            //Serial.print("midi.temp1:");Serial.println(midi.temp, HEX);
            // 拍号 0x00FF5804
            uint8_t code = ((uint8_t *)&midi.temp)[1];
            if (code == 0x58) 
            {
                midi.timeSignature = read32_B(f); // 继续读取
                //Serial.print("midi.timeSignature:");Serial.println(midi.timeSignature,HEX);
            }
            // 速度 0x00FF51LL,LL表示需要读取多少个字节
            else if(code == 0x51)
            {
                uint16_t length = ((uint8_t *)&midi.temp)[0];
                //Serial.print("speedLength:");Serial.println(length);
                for (uint16_t i = 0; i < length; i++)  // 继续读取
                    ((uint8_t *)&midi.speed)[length - 1 - i] = f.read();
                midi.oneTick = midi.speed / midi.quarterNoteTime; // 计算一个滴答的时间
                //Serial.print("midi.oneTick:");Serial.println(midi.oneTick);
                //Serial.print("midi.speed:");Serial.println(midi.speed, HEX);
            }
            // 轨道名称 0x00FF03LL,LL表示需要读取多少个字节
            else if(code == 0x03)
            {
                uint16_t length = ((uint8_t *)&midi.temp)[0];
                //Serial.print("trackNameLength:");Serial.println(length);
                for (uint16_t i = 0; i < length; i++)  // 继续读取
                    midi.trackName += char(f.read());
                //Serial.print("midi.trackName:");Serial.println(midi.trackName);
            }
            else if (code == 0x2F) // 退出
            {
                //Serial.println("退出");
                ledcWrite(BUZZER_CHANNEL, 0); // 关闭
                return;
            }
            else // 其他未做处理，跳过
            {
                uint16_t length = ((uint8_t *)&midi.temp)[0];
                //Serial.println("跳过：" + String(length) + "字节");
                for (uint16_t i = 0; i < length; i++)
                    f.read();
            }

            // 继续检测，防止系统指令存在不正规的数据扰乱
            bool retreat = 0; // 0：未后退 1：已后退
            for (uint16_t i = 0; i < 8; i++)
            {
                if (f.read() == 0xFF)
                {
                    f.seek(f.position() - 2); // 退回到系统指令开头
                    retreat = 1;              // 标记已后退
                    break;
                }
            }
            if (retreat == 0) f.seek(f.position() - 8); // 退回到检测前

        }//系统指令 END
    }//for END
}

//midi运行
void midiRun(String midPath)
{
    uint8_t trackCount = 0;  // 轨道计数，用于记录再第几条轨道时发生错误
    uint32_t infoType = 0;   // 信息类型MThd或MTrk
    uint32_t infoLength = 0; // 信息长度
    uint32_t systemCode = 0; // 系统码
    uint16_t time;
    String ts = F("播放结束");
    File file, fileL;
    Serial.print("输入的midi:");Serial.println(midPath);

    // LittleFS播放
    file = LittleFS.open(midPath, "r");
    if (!file)
    {
        ts = F("打开midi文件失败");
        Serial.println(ts);
        goto tuichu;
    }
    infoType = read32_B(file);
    if(infoType != MThd)
    {
        ts = F("不是midi文件");
        Serial.println(ts);
        goto tuichu;
    }

    Serial.print("infoType:");Serial.println(infoType, HEX);

    //for (uint8_t i = 0; i < 8; i++) Serial.print(bitRead(infoType, i));

    // 读取类型
    file.seek(8);
    midi.type = read16_B(file);
    Serial.print("文件类型-midi.type:");Serial.println(midi.type);
    // 读取轨道数量
    midi.trackNum = read16_B(file);
    Serial.print("轨道数量-midi.trackNum:");Serial.println(midi.trackNum);
    // 读取时间类型和时间量
    time = read16_B(file);
    Serial.print("时间信息原-time—DEC:");Serial.println(time);
    Serial.print("时间信息原-time—HEX:");Serial.println(time, HEX);
    Serial.println();
    midi.timeType = bitRead(time, 15); // 提取类型
    bitWrite(time, 15, 0);
    midi.quarterNoteTime = time; // 提取一个四分音符的时间
    Serial.print("时间类型-midi.timeType:");Serial.println(midi.timeType);
    Serial.print("时间量-midi.quarterNoteTime:");Serial.println(midi.quarterNoteTime);
    Serial.println();

    for (uint8_t i = 0; i < midi.trackNum; i++)
    {
        infoType = read32_B(file);
        trackCount++;
        if (infoType != MTrk)
        {
            ts = "第" + String(trackCount) + "Mtrk读取错误";
            Serial.println(ts);
            goto tuichu;
        }
        infoLength = read32_B(file);
        Serial.print("infoLength:");
        Serial.println(infoLength);
        Serial.println("第" + String(trackCount) + "Mtrk长度:" + String(infoLength));
        midiAnalysis(file, midi);
    }

// 退出
tuichu:
    //Serial.println("退出midi");
    structClear((unsigned char *)&midi, sizeof(midi));   // 清空结构体
    file.close();      // 关闭文件
    midi.run = 0;      // 标记运行结束
    buzzer_setNote();
    
    //Serial.printf("AC_timeTarget_midi:%d\n", AC_timeTarget);

    // 是闹钟启动的播放再更新一次
    if (AC_timeTarget == -100004) updatealarmClockDifference();
        
    vTaskDelete(NULL); // 删除自己
}

// 停止midi播放
void stopMidi()
{
    if (midi.run)
    {
        //循环检查直至删除
        do
        {
            vTaskDelete(HT_midi);
            vTaskDelay(2);
        } while (eTaskGetState(HT_midi) != eDeleted);
        Serial.println("关闭midi任务成功");
        ledcWrite(BUZZER_CHANNEL, 0);                      // 关闭蜂鸣器
        structClear((unsigned char *)&midi, sizeof(midi)); // 清空结构体

        //设置回按键的声音
        buzzer_setNote();
    }
}