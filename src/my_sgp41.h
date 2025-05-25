#include <NOxGasIndexAlgorithm.h>
#include <SensirionI2CSgp41.h>
#include <VOCGasIndexAlgorithm.h>
SensirionI2CSgp41 sgp41;
VOCGasIndexAlgorithm voc_algorithm;
NOxGasIndexAlgorithm nox_algorithm;

/*struct AIR_ALGORITHM 
{
    int32_t index_offset;                // 索引偏移量
    int32_t learning_time_offset_hours;  // 学习时间偏移小时数
    int32_t learning_time_gain_hours;    // 学习时间增加小时数
    int32_t gating_max_duration_minutes; // 门控最长持续时间分钟
    int32_t std_initial;                 // 标准初始值
    int32_t gain_factor;                 // 增益系数
    uint16_t sraw = 0;                   // 原始值
    int32_t index = 0;                   // 指数
};
AIR_ALGORITHM voc;
AIR_ALGORITHM nox;
*/

uint16_t sgp41_error;
#define SGP41_Rh 0x8000
#define SGP41_Temp 0x6666
uint16_t vocSraw = 0;      // 原始数值
uint16_t noxSraw = 0;      // 原始数值
uint16_t vocIndex = 0;      // 指数
uint16_t noxIndex = 0;      // 指数
uint32_t sgp41_runTime = 0; // 运行时间

void sgp41_init()
{
    char errorMessage[256];

    digitalWrite(AIR_POWER_PIN, 1);
    delay(10);

    sgp41.begin(Wire);

    uint8_t serialNumberSize = 3;
    uint16_t serialNumber[serialNumberSize];

    sgp41_error = sgp41.getSerialNumber(serialNumber);

    if (sgp41_error)
    {
        // Serial.print("尝试执行 getSerialNumber() 时出错： ");
        // errorToString(sgp41_error, errorMessage, 256);
        // Serial.println(errorMessage);
    }
    else
    {
        /*Serial.print("序列号:");
        Serial.print("0x");
        for (size_t i = 0; i < serialNumberSize; i++)
        {
            uint16_t value = serialNumber[i];
            Serial.print(value < 4096 ? "0" : "");
            Serial.print(value < 256 ? "0" : "");
            Serial.print(value < 16 ? "0" : "");
            Serial.print(value, HEX);
        }
        Serial.println();*/

        uint16_t testResult;
        sgp41_error = sgp41.executeSelfTest(testResult);
        if (sgp41_error)
        {
            //Serial.print("尝试执行 executeSelfTest() 时出错：");
            //errorToString(sgp41_error, errorMessage, 256);
            //Serial.println(errorMessage);
            my_msgbox_send(F("空气错误"), F("自检错误"), 0, F("退出\n返回\n"), backPage_mainSet);
        }
        /*else if (testResult != 0xD400)
        {
            Serial.print("executeSelfTest 失败，错误如下：");
            Serial.println(testResult);
        }*/
        // spg41_get_tuning_parameters();
    }
}

void sgp41_readSRAW()
{
    if (millis() - sgp41_runTime < 9)
    {
        // 在氮氧化物调节期间（10秒），SRAW氮氧化物将保持为0
        sgp41_error = sgp41.executeConditioning(SGP41_Rh, SGP41_Temp, vocSraw);
        Serial.println("SGP41等待");
    }
    else
    {
        // 读取测量值
        sgp41_error = sgp41.measureRawSignals(SGP41_Rh, SGP41_Temp, vocSraw, noxIndex);
    }

    if (sgp41_error)
    {
        char errorMessage[256];
        Serial.print("尝试执行measureRawSignals()时出错:");
        errorToString(sgp41_error, errorMessage, 256);
        Serial.println(errorMessage);
    }
    else
    {
        Serial.print("SRAW_VOC:");
        Serial.print(vocSraw);
        Serial.print("\t");
        Serial.print("SRAW_NOx:");
        Serial.println(noxSraw);
    }
}

//获取当前参数以自定义气体指数算法。
void spg41_get_tuning_parameters()
{
    int32_t index_offset;
    int32_t learning_time_offset_hours;
    int32_t learning_time_gain_hours;
    int32_t gating_max_duration_minutes;
    int32_t std_initial;
    int32_t gain_factor;
    // 获取当前参数以自定义气体指数算法。
    voc_algorithm.get_tuning_parameters(
        index_offset, learning_time_offset_hours, learning_time_gain_hours,
        gating_max_duration_minutes, std_initial, gain_factor);

    Serial.println("\nVOC气体指数算法参数");
    Serial.print("指数偏移量:\t");
    Serial.println(index_offset);
    Serial.print("学习时间偏移小时数：\t");
    Serial.println(learning_time_offset_hours);
    Serial.print("学习时间增加小时数：\t");
    Serial.println(learning_time_gain_hours);
    Serial.print("门控最长持续时间分钟：\t");
    Serial.println(gating_max_duration_minutes);
    Serial.print("标准初始值：\t");
    Serial.println(std_initial);
    Serial.print("增益系数：\t");
    Serial.println(gain_factor);

    // 获取当前参数以自定义气体指数算法。
    nox_algorithm.get_tuning_parameters(
        index_offset, learning_time_offset_hours, learning_time_gain_hours,
        gating_max_duration_minutes, std_initial, gain_factor);

    Serial.println("\nNOx气体指数算法参数");
    Serial.print("指数偏移量:\t");
    Serial.println(index_offset);
    Serial.print("学习时间偏移小时数:\t");
    Serial.println(learning_time_offset_hours);
    Serial.print("门控最大持续时间分钟:\t");
    Serial.println(gating_max_duration_minutes);
    Serial.print("增益因子:\t");
    Serial.println(gain_factor);
    Serial.println("");
}

// 输入原始值计算指数
void sgp41_readIndex()
{
    // 以SGP41定义的刻度为单位
    uint16_t defaultCompenstaionRh = 0x8000; // 湿度默认配置
    uint16_t defaultCompenstaionT = 0x6666;  // 温度默认配置

    // 1. 睡眠：根据气体指数算法的定义，每秒测量一次（1Hz）前提
    //delay(1000);

    //int32_t temp = ((cpuTemp - cpuTemp / 4) + 45) * 65535 / 175;
    //if (temp < 0) temp = 0x6666;

    // 2. 测量SGP4x信号
    if (sgp41_runTime < 9)
    {
        // 在氮氧化物调节期间（10秒），SR0W氮氧化物将保持为0
        sgp41_error = sgp41.executeConditioning(SGP41_Rh, SGP41_Temp, vocSraw);
        Serial.println("SGP41等待voc");
    }
    else
    {
        // 读取测量值
        sgp41_error = sgp41.measureRawSignals(SGP41_Rh, SGP41_Temp, vocSraw, noxIndex);
    }

    // 3. 通过气体指数算法处理原始信号，得到VOC和NOx指数值
    if (sgp41_error)
    {
        char errorMessage[256];
        Serial.print("SGP41-尝试执行measureRawSignals()时出错：");
        errorToString(sgp41_error, errorMessage, 256);
        Serial.println(errorMessage);
    }
    else
    {
        vocIndex = voc_algorithm.process(vocSraw);
        noxIndex = nox_algorithm.process(noxSraw);
        /*Serial.print("VOC 指数: ");
        Serial.print(vocIndex);
        Serial.print("\t");
        Serial.print("NOx 指数: ");
        Serial.println(noxIndex);

        Serial.print("VOC sraw: ");
        Serial.print(vocSraw);
        Serial.print("\t");
        Serial.print("NOx sraw: ");
        Serial.println(noxSraw);

        Serial.println();*/
    }
}

void airRead_rtos_init() // 创建空气质量读取任务
{
  i2c_begin();
  xTaskCreatePinnedToCore(
      airRead_rtos, /* 任务指针，创建任务用的那个函数名 */
      "airRead",    /* 任务名称 */
      4 * 1024,     /* 任务栈大小，根据需要自行设置*/
      NULL,         /* 可选参数，一般不填*/
      2,            /* 优先级 */
      &TH_airRead,  /* 任务句柄，用于后续挂起或恢复运行*/
      0             /* 核ID */
  );
}

void airRead_rtos(void *param)
{
    sgp41_init(); //传感器初始化
    voc_algorithm.reset();
    nox_algorithm.reset();
    if (sgp41_error != 0)
    {
        delay(GRADUAL_ANIM_TIME);
        bitWrite(backgroundTask, BGT_AIR_READ, 0);
        my_msgbox_send(F("空气错误"), F("不存在"), 0, F("退出\n返回\n"), backPage_mainSet);
    }
    for (;;)
    {
        if (!bitRead(backgroundTask, BGT_AIR_READ))
        {
            sgp41.turnHeaterOff(); // 关闭测量进入待机模式
            sgp41_runTime = 0;
            digitalWrite(AIR_POWER_PIN, 0);

            Serial.println("删除TH_airRead");
            TH_airRead = NULL;
            vTaskDelete(NULL);
        }
        sgp41_readIndex();
        sgp41_runTime++;
        delay(1000); // 1000 / 15
    }
}