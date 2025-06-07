/******************************************************************************
Example4: test all the things on the MAX17048
By: Paul Clark, SparkFun Electronics
Date: October 23rd 2020

This example is an everything-but-the-kitchen-sink test of the MAX17048.

This code is released under the MIT license.

Distributed as-is; no warranty is given.
******************************************************************************/

#include <Wire.h> // Needed for I2C

#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library

SFE_MAX1704X lipo(MAX1704X_MAX17048); // Create a MAX17048

void setup()
{
	Serial.begin(115200); // Start serial, to output debug data
  while (!Serial)
    ; //Wait for user to open terminal
  Serial.println(F("MAX17048示例"));

  Wire.begin();

  lipo.enableDebugging(); // 取消注释此行以在串行上启用有用的调试消息

  // Set up the MAX17048 LiPo fuel gauge: 设置MAX17048 LiPo燃油表：
  if (lipo.begin() == false) // 使用默认接线端口连接到MAX17048
  {
    Serial.println(F("未检测到MAX17048。请检查线路。冻结."));
    while (1)
      ;
  }

  // 就因为我们可以，让我们重置MAX17048
  Serial.println(F("Resetting the MAX17048..."));
  delay(1000); // 给它时间重新振作起来

  // 读取并打印重置指示器
  Serial.print(F("Reset Indicator was: "));
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
  Serial.print(F("Device ID: 0x"));
  uint8_t id = lipo.getID(); // 读取设备ID
  if (id < 0x10) Serial.print(F("0")); // 如果需要，打印前导零
  Serial.println(id, HEX); // 以十六进制打印ID

  // 读取并打印设备版本
  Serial.print(F("Device version: 0x"));
  uint8_t ver = lipo.getVersion(); // Read the device version
  if (ver < 0x10) Serial.print(F("0")); // Print the leading zero if required
  Serial.println(ver, HEX); // Print the version as hexadecimal

  // 读取并打印电池阈值
  Serial.print(F("电池空阈值当前为: "));
  Serial.print(lipo.getThreshold());
  Serial.println(F("%"));

  // 我们可以设置一个中断，以便在电池SoC电量过低时发出警报。
  // 我们可以在1%到32%之间的任何地方发出警报：
  lipo.setThreshold(20); // 将警报阈值设置为20%。

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
  lipo.setVALRTMax((float)4.1); // 设置高电压阈值（伏特）

  // Read and print the high voltage threshold
  Serial.print(F("High voltage threshold is now: "));
  highVoltage = ((float)lipo.getVALRTMax()) * 0.02; // 1 LSb为20mV。转换为伏特。
  Serial.print(highVoltage, 2);
  Serial.println(F("V"));

  // 读取并打印低电压阈值
  Serial.print(F("Low voltage threshold is currently: "));
  float lowVoltage = ((float)lipo.getVALRTMin()) * 0.02; // 1 LSb为20mV。转换为伏特。
  Serial.print(lowVoltage, 2);
  Serial.println(F("V"));

  // 设置低电压阈值
  lipo.setVALRTMin((float)3.9); // 设置低电压阈值（伏特）

  // 读取并打印低电压阈值
  Serial.print(F("Low voltage threshold is now: "));
  lowVoltage = ((float)lipo.getVALRTMin()) * 0.02; // 1 LSb为20mV。转换为伏特。
  Serial.print(lowVoltage, 2);
  Serial.println(F("V"));

  // 启用状态变化警报
  Serial.print(F("启用1%变化状态警报: "));
  if (lipo.enableSOCAlert())
  {
    Serial.println(F("成功."));
  }
  else
  {
    Serial.println(F("失败!"));
  }
  
  // 读取并打印HIBRT活动阈值
  Serial.print(F("休眠活动阈值为: "));
  float actThr = ((float)lipo.getHIBRTActThr()) * 0.00125; // 1 LSb为1.25mV。转换为伏特。
  Serial.print(actThr, 5);
  Serial.println(F("V"));

  // 读取并打印HIBRT休眠阈值
  Serial.print(F("Hibernate hibernate threshold is: "));
  float hibThr = ((float)lipo.getHIBRTHibThr()) * 0.208; // 1 LSb为0.208%/hr。转换为%/hr。
  Serial.print(hibThr, 3);
  Serial.println(F("%/h"));
}

void loop()
{
  // 打印变量：
  Serial.print("电压: ");
  Serial.print(lipo.getVoltage());  // Print the battery voltage
  Serial.print("V");

  Serial.print(" 百分比: ");
  Serial.print(lipo.getSOC(), 2); // Print the battery state of charge with 2 decimal places
  Serial.print("%");

  Serial.print(" 变化率: ");
  Serial.print(lipo.getChangeRate(), 2); // Print the battery change rate with 2 decimal places
  Serial.print("%/hr");

  Serial.print(" 警惕的: ");
  Serial.print(lipo.getAlert()); // 打印通用警报标志

  Serial.print(" 电压过高警报: ");
  Serial.print(lipo.isVoltageHigh()); // 打印警报标志

  Serial.print(" 电压低警报: ");
  Serial.print(lipo.isVoltageLow()); // Print the alert flag

  Serial.print(" 空警报: ");
  Serial.print(lipo.isLow()); // Print the alert flag

  Serial.print(" SOC 1%变化警报: ");
  Serial.print(lipo.isChange()); // Print the alert flag
  
  Serial.print(" 冬眠: ");
  Serial.print(lipo.isHibernating()); // Print the alert flag
  
  Serial.println();

  delay(500);
}
