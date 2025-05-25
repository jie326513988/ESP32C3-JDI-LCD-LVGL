
// 串口空气质量
void read_airQuality_rtos(void *param);
int16_t read_airQuality();

union
{
    float data;
    uint8_t array[4];
} UART_CO2; // 二氧化碳浓度 400.0-2000.0PPM
union
{
    float data;
    uint8_t array[4];
} UART_TVOC; // 有机挥发物 0-9.99mg/m3
union
{
    float data;
    uint8_t array[4];
} UART_HCHO; // 甲醛 0-9.99mg/m3

int8_t UART_TEMP = 0.0;
int8_t UART_HUMI = 0.0;

uint8_t uartState = 0;
void read_airQuality_rtos_init()
{
    xTaskCreatePinnedToCore(
        read_airQuality_rtos, /* 任务指针，创建任务用的那个函数名 */
        "read_airQuality",    /* 任务名称 */
        4 * 1024,             /* 任务栈大小，根据需要自行设置*/
        NULL,                 /* 可选参数，一般不填*/
        1,                    /* 优先级 */
        &TH_airRead,          /* 任务句柄，用于后续挂起或恢复运行*/
        0                     /* 核ID */
    );
}

void read_airQuality_rtos(void *param)
{
    // 关闭虚拟USB串口
    Serial0.flush();
    Serial0.end();
    delay(100);
    // 重新设置串口
    Serial1.begin(115200, SERIAL_8N1, UART1_RX, UART1_TX);
    Serial1.setTimeout(100);
    delay(100);
    Serial1.flush();
    delay(100);
    //pinMode(UART1_RX, INPUT);
    //pinMode(UART1_TX, INPUT);
    for (;;)
    {
        if (!bitRead(backgroundTask, BGT_AIR_READ))
        {
            Serial1.flush();
            Serial1.end();
            //Serial.println("删除TH_airRead");
            /*uint8_t i = 0;
            uint16_t *melody = (uint16_t *)malloc((3 * 6 + 1) * sizeof(uint16_t)); // 频率，时长，延时
            melody[i++] = 1;  melody[i++] = 1;  melody[i++] = 500;
            melody[i++] = 659;melody[i++] = 150;melody[i++] = 75;
            melody[i++] = 659;melody[i++] = 75; melody[i++] = 187;
            melody[i++] = 523;melody[i++] = 75; melody[i++] = 37;
            melody[i++] = 659;melody[i++] = 150;melody[i++] = 75;
            melody[i++] = 784;melody[i++] = 300;melody[i++] = 50;
            melody[i] = 0;
            buzzer_music_rtos_init(melody);*/
            TH_airRead = NULL;
            vTaskDelete(NULL);
        }

        int8_t err = read_airQuality();
        if (err < -1)
        {
            err *= -1; // 转为正数
            uint8_t i = 0;
            uint16_t *melody = (uint16_t *)malloc((3 * err + 1) * sizeof(uint16_t)); //频率，时长，延时
            for (uint8_t j = 0; j < err; j++)
            {
                melody[i++] = 4300; melody[i++] = 30; melody[i++] = 80; 
            }
            melody[i] = 0;
            buzzer_music_rtos_init(melody);
        }
        delay(100);
    }
}

int16_t read_airQuality()
{
    if (Serial1.available() <= 0) return 1;
    
    int err = 0;
    uint8_t dataMax = 255;
    uint8_t *out = (uint8_t *)calloc(dataMax, sizeof(uint8_t));
    uint8_t pos = 0;
    uint32_t timeout = millis();
    // 开始接收数据
    for (;;)
    {
        //buzzerSen(30);
        if (Serial1.available() > 0)
        {
            out[pos++] = Serial1.read();
            if (pos >= dataMax)
            {
                Serial1.flush();
                err = -4;
                break;
            }
        }
        else // 接收完毕
        {
            if (pos > 16)
            { 
                Serial1.flush();
                err = -1;
                break;
            }

            //****** 标头不对
            if (out[0] != 0XA0)
            {
                err = -2;
                break;
            }

            //****** 数据异或校验
            uint8_t result = out[0] ^ out[1] ^ out[2] ^ out[3] ^ out[4] ^
                             out[5] ^ out[6] ^ out[7] ^ out[8] ^ out[9] ^
                             out[10] ^ out[11] ^ out[12] ^ out[13] ^ out[14];
            // 校验失败
            if (result != out[15])
            {
                err = -3;
                break;
            }

            //****** 数据赋值
            UART_TEMP = out[1] - 30; // 温度
            UART_HUMI = out[2];      // 湿度
            // CO2
            UART_CO2.array[0] = out[3];
            UART_CO2.array[1] = out[4];
            UART_CO2.array[2] = out[5];
            UART_CO2.array[3] = out[6];
            // TVOC
            UART_TVOC.array[0] = out[7];
            UART_TVOC.array[1] = out[8];
            UART_TVOC.array[2] = out[9];
            UART_TVOC.array[3] = out[10];
            // HCHO
            UART_HCHO.array[0] = out[11];
            UART_HCHO.array[1] = out[12];
            UART_HCHO.array[2] = out[13];
            UART_HCHO.array[3] = out[14];
            break;
        }
        //超时
        if (millis() - timeout > 100)
        {
            err = -5;
            break;
        }
    }

    free(out);
    return err;
}