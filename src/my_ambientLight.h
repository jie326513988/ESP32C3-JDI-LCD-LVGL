#include <ClosedCube_OPT3001.h>
ClosedCube_OPT3001 opt3001;

void ambientLight_rtos(void *param);

void printError(String text, OPT3001_ErrorCode error)
{
  Serial.print(text);
  Serial.print(": [ERROR] Code #");
  Serial.println(error);
}

void printResult(String text, OPT3001 result)
{
  if (result.error == NO_ERROR)
  {
    Serial.print(text);
    Serial.print(": ");
    Serial.print(result.lux);
    Serial.println(" lux");
  }
  else
  {
    printError(text, result.error);
  }
}

void configureSensor()
{
  OPT3001_Config newConfig;

  newConfig.RangeNumber = B1100;
  newConfig.ConvertionTime = B0;
  newConfig.Latch = B1;
  newConfig.ModeOfConversionOperation = B11;

  OPT3001_ErrorCode errorConfig = opt3001.writeConfig(newConfig);
  if (errorConfig != NO_ERROR) printError("OPT3001配置", errorConfig);
  else
  {
    OPT3001_Config sensorConfig = opt3001.readConfig();
    Serial.println("OPT3001当前配置:");
    Serial.println("------------------------------");

    Serial.print("转换就绪 (R):");
    Serial.println(sensorConfig.ConversionReady, HEX);

    Serial.print("转换时间 (R/W):");
    Serial.println(sensorConfig.ConvertionTime, HEX);

    Serial.print("故障计数字段 (R/W):");
    Serial.println(sensorConfig.FaultCount, HEX);

    Serial.print("Flag high field (R-only):");
    Serial.println(sensorConfig.FlagHigh, HEX);

    Serial.print("Flag low field (R-only):");
    Serial.println(sensorConfig.FlagLow, HEX);

    Serial.print("Latch field (R/W):");
    Serial.println(sensorConfig.Latch, HEX);

    Serial.print("掩码指数字段 (R/W):");
    Serial.println(sensorConfig.MaskExponent, HEX);

    Serial.print("转换操作模式 (R/W):");
    Serial.println(sensorConfig.ModeOfConversionOperation, HEX);

    Serial.print("极性场 (R/W):");
    Serial.println(sensorConfig.Polarity, HEX);

    Serial.print("溢出标志 (R-only):");
    Serial.println(sensorConfig.OverflowFlag, HEX);

    Serial.print("范围编号 (R/W):");
    Serial.println(sensorConfig.RangeNumber, HEX);

    Serial.println("------------------------------");
  }
}

void ambientLight_init()
{
  opt3001.begin(AMBIENT_LIGHT_I2C_ADDR);
  //Serial.print("OPT3001 Manufacturer ID");
  //Serial.println(opt3001.readManufacturerID());
  //Serial.print("OPT3001 Device ID");
  //Serial.println(opt3001.readDeviceID());

  configureSensor(); //配置传感器
  //printResult("High-Limit", opt3001.readHighLimit());
  //printResult("Low-Limit", opt3001.readLowLimit());
  //Serial.println("----");
}

// 创建环境光读取任务
void ambientLight_rtos_init()
{
  xTaskCreatePinnedToCore(
      ambientLight_rtos, /* 任务指针，创建任务用的那个函数名 */
      "ambientLight",    /* 任务名称 */
      2 * 1024,          /* 任务栈大小，根据需要自行设置*/
      NULL,              /* 可选参数，一般不填*/
      1,                 /* 优先级 */
      &TH_ambientLigh,   /* 任务句柄，用于后续挂起或恢复运行*/
      0                  /* 核ID */
  );
}
// 环境光读取任务
void ambientLight_rtos(void *param)
{
  // 检查芯片是否存在
  bool ok = i2cChipExist(AMBIENT_LIGHT_I2C_ADDR);
  // 标记关闭环境光读取任务
  if (ok == 0)
    bitWrite(backgroundTask, BGT_AMBIENT_LIGHT, 0);

  Serial.printf("OPT3001 ok:%d\n",ok);

  ambientLight_init();
  
  for (;;)
  {
    // 检查是否需要删除
    if (!bitRead(backgroundTask, BGT_AMBIENT_LIGHT))
    {
      Serial.println("删除TH_ambientLigh");
      TH_ambientLigh = NULL;
      vTaskDelete(NULL);
    }

    OPT3001 result = opt3001.readResult();
    //printResult("OPT3001", result);
    shareNum_f[0] = result.lux;
    delay(1000);
  }
}
