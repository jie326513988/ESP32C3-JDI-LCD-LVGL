#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>
SFE_MAX1704X lipo(MAX1704X_MAX17048); // Create a MAX17048
void max17048_init()
{
  // 检查电量计是否存在
  bool ok = i2cChipExist(BATSOC_I2C_ADDR);

  if (ok == 0 || lipo.begin() == 0)
  {
    Serial.println(F("未检测到MAX17048。"));
  }
  else
  {
    // lipo.reset();
    // delay(100);
    //  读取并打印高压阈值
    /*Serial.print(F("当前高电压阈值: "));
    float highVoltage = ((float)lipo.getVALRTMax()) * 0.02; // 1 LSb为20mV。转换为伏特。
    Serial.print(highVoltage, 2);
    Serial.println(F("V"));
    // 设置高压阈值
    //lipo.setVALRTMax((float)4.25); // 设置高电压阈值（伏特）
    // 读取并打印高压阈值
    Serial.print(F("设置后高电压阈值: "));
    highVoltage = ((float)lipo.getVALRTMax()) * 0.02; // 1 LSb为20mV。转换为伏特。
    Serial.print(highVoltage, 2);
    Serial.println(F("V"));

    // 读取并打印低电压阈值
    Serial.print(F("当前低电压阈值: "));
    float lowVoltage = ((float)lipo.getVALRTMin()) * 0.02; // 1 LSb为20mV。转换为伏特。
    Serial.print(lowVoltage, 2);
    Serial.println(F("V"));
    // 设置低电压阈值
    //lipo.setVALRTMin((float)3.2); // 设置低电压阈值（伏特）
    // 读取并打印低电压阈值
    Serial.print(F("设置后低电压阈值: "));
    lowVoltage = ((float)lipo.getVALRTMin()) * 0.02; // 1 LSb为20mV。转换为伏特。
    Serial.print(lowVoltage, 2);
    Serial.println(F("V"));*/

    max17048_Compensation(); //温度补偿
  }
}

// 温度补偿
void max17048_Compensation()
{
  //float RCOMP0 = lipo.getCompensation();
  //Serial.print("RCOMP0:"); Serial.println(RCOMP0);
  float RCOMP0 = 0x97;
  uint8_t RCOMP = 0;
  float TempCoUp = -0.5;
  float TempCoDown = 5.0;
  if (cpuTemp > 20)
    RCOMP = RCOMP0 + (cpuTemp - 20.0) * TempCoUp;
  else
    RCOMP = RCOMP0 + (cpuTemp - 20.0) * TempCoDown;
  // Serial.print("RCOMP:"); Serial.println(RCOMP);
  // bool no = lipo.setCompensation(RCOMP);
  // Serial.print("no:"); Serial.println(no);

  lipo.setCompensation(RCOMP);
}

void max17048_init2()
{
    if (lipo.begin() == false) // 使用默认接线端口连接到MAX17048
    {
        Serial.println(F("未检测到MAX17048。请检查线路。冻结."));
        while (1)
            delay(5);
    }

  // 就因为我们可以，让我们重置MAX17048
  Serial.println(F("重置MAX17048..."));
  delay(1000); // 给它时间重新振作起来

  // 读取并打印重置指示器
  Serial.print(F("重置指示器: "));
  bool RI = lipo.isReset(true); // 读取RI标志，如果已设置，则自动清除
  Serial.println(RI); // 打印RI
  // 如果已设置RI，请检查是否已清除
  if (RI)
  {
    Serial.print(F("重置指示器现在: "));
    RI = lipo.isReset(); // 读取RI标志
    Serial.println(RI); // 打印RI
  }

  // 快速启动还是不快速启动？这就是问题所在！
  // 阅读以下内容，然后决定是否要快速启动燃油表。
  // 大多数系统不应使用快速启动，因为IC可以透明地处理大多数启动问题，
  // 例如插入过程中的间歇性电池端子连接。如果电池电压稳定在17ms以上，
  // 则不要使用快速启动。快速启动命令以与IC初始加电相同的方式重新启动燃油表计算。
  // 如果系统加电顺序太嘈杂，导致SOC的初始估计存在不可接受的误差，
  // 系统微控制器可能能够通过使用快速启动来减少误差
  //  如果你仍然想尝试快速开始，那么取消注释下一行:
  // lipo.quickStart();

  // 读取并打印设备ID
  Serial.print(F("设备 ID: 0x"));
  uint8_t id = lipo.getID(); // 读取设备ID
  if (id < 0x10) Serial.print(F("0")); // 如果需要，打印前导零
  Serial.println(id, HEX); // 以十六进制打印ID

  // 读取并打印设备版本
  Serial.print(F("设备版本: 0x"));
  uint8_t ver = lipo.getVersion(); // 读取设备版本
  if (ver < 0x10) Serial.print(F("0")); // 如果需要，打印前导零
  Serial.println(ver, HEX); // 以十六进制打印ID

  // 读取并打印电池阈值
  Serial.print(F("电池空阈值当前为: "));
  Serial.print(lipo.getThreshold());
  Serial.println(F("%"));

  // 我们可以设置一个中断，以便在电池SoC电量过低时发出警报。
  // 我们可以在1%到32%之间的任何地方发出警报：
  //lipo.setThreshold(20); // 将警报阈值设置为20%。

  // 读取并打印电池电量阈值
  Serial.print(F("电池空阈值现在为: "));
  Serial.print(lipo.getThreshold());
  Serial.println(F("%"));

  // 读取并打印高压阈值
  Serial.print(F("当前为高电压阈值: "));
  float highVoltage = ((float)lipo.getVALRTMax()) * 0.02; // 1 LSb为20mV。转换为伏特。
  Serial.print(highVoltage, 2);
  Serial.println(F("V"));

  // 设置高压阈值
  //lipo.setVALRTMax((float)4.2); // 设置高电压阈值（伏特）

  // 读取并打印高压阈值
  Serial.print(F("高电压阈值现在: "));
  highVoltage = ((float)lipo.getVALRTMax()) * 0.02; // 1 LSb为20mV。转换为伏特。
  Serial.print(highVoltage, 2);
  Serial.println(F("V"));

  // 读取并打印低电压阈值
  Serial.print(F("低电压阈值目前: "));
  float lowVoltage = ((float)lipo.getVALRTMin()) * 0.02; // 1 LSb为20mV。转换为伏特。
  Serial.print(lowVoltage, 2);
  Serial.println(F("V"));

  // 设置低电压阈值
  //lipo.setVALRTMin((float)3.9); // 设置低电压阈值（伏特）

  // 读取并打印低电压阈值
  Serial.print(F("低电压阈值现已: "));
  lowVoltage = ((float)lipo.getVALRTMin()) * 0.02; // 1 LSb为20mV。转换为伏特。
  Serial.print(lowVoltage, 2);
  Serial.println(F("V"));

  // 启用状态变化警报
  /*Serial.print(F("启用1%变化状态警报: "));
  if (lipo.enableSOCAlert())
  {
    Serial.println(F("成功."));
  }
  else
  {
    Serial.println(F("失败!"));
  }*/
  
  // 读取并打印HIBRT活动阈值
  Serial.print(F("休眠的活动阈值为: "));
  float actThr = ((float)lipo.getHIBRTActThr()) * 0.00125; // 1 LSb为1.25mV。转换为伏特。
  Serial.print(actThr, 5);
  Serial.println(F("V"));

  // 读取并打印HIBRT休眠阈值
  Serial.print(F("休眠的休眠阈值是: "));
  float hibThr = ((float)lipo.getHIBRTHibThr()) * 0.208; // 1 LSb为0.208%/hr。转换为%/hr。
  Serial.print(hibThr, 3);
  Serial.println(F("%/h"));
}