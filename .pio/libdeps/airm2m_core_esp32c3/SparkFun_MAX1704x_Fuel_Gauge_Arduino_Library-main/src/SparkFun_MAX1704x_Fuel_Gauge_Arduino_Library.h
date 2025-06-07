/******************************************************************************
SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h
By: Paul Clark
October 23rd 2020

Based extensively on:
SparkFunMAX17043.h
SparkFun MAX17043 Library Header File
Jim Lindblom @ SparkFun Electronics
Original Creation Date: June 22, 2015
https://github.com/sparkfun/SparkFun_MAX17043_Particle_Library

This file implements all functions of the MAX17043 class. Functions here range
from higher level stuff, like reading/writing MAX17043 registers to low-level,
hardware reads and writes.

This code is released under the MIT license.

Distributed as-is; no warranty is given.
******************************************************************************/
#ifndef MAX1704X_ARDUINO_LIBRARY_H
#define MAX1704X_ARDUINO_LIBRARY_H

// Uncomment the next #define to EXclude any debug logging from the code, by default debug logging code will be included

// #define MAX1704X_ENABLE_DEBUGLOG 0 // OFF/disabled/excluded on demand

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

// Enable/disable including debug log (to allow saving some space)
#ifndef MAX1704X_ENABLE_DEBUGLOG
#if defined(LIBRARIES_NO_LOG) && LIBRARIES_NO_LOG
#define MAX1704X_ENABLE_DEBUGLOG 0 // OFF/disabled/excluded on demand
#else
#define MAX1704X_ENABLE_DEBUGLOG 1 // ON/enabled/included by default
#endif
#endif

// #include "application.h"

//////////////////////////
// MAX1704x Device Enum //
//////////////////////////

typedef enum
{
  MAX1704X_MAX17043 = 0,
  MAX1704X_MAX17044, // 2-cell version of the MAX17043 (full-scale range of 10V)
  MAX1704X_MAX17048,
  MAX1704X_MAX17049 // 2-cell version of the MAX17048
} sfe_max1704x_devices_e;

///////////////////////////////////
// MAX1704x Register Definitions //
///////////////////////////////////
// All registers contain two bytes of data and span two addresses.
// Registers which are present on the MAX17048/49 only are prefixed with MAX17048_
#define MAX17043_VCELL 0x02     // R - 12-bit A/D measurement of battery voltage
#define MAX17043_SOC 0x04       // R - 16-bit state of charge (SOC)
#define MAX17043_MODE 0x06      // W - Sends special commands to IC
#define MAX17043_VERSION 0x08   // R - Returns IC version
#define MAX17048_HIBRT 0x0A     // R/W - (MAX17048/49) Thresholds for entering hibernate
#define MAX17043_CONFIG 0x0C    // R/W - Battery compensation (default 0x971C)
#define MAX17048_CVALRT 0x14    // R/W - (MAX17048/49) Configures vcell range to generate alerts (default 0x00FF)
#define MAX17048_CRATE 0x16     // R - (MAX17048/49) Charge rate 0.208%/hr
#define MAX17048_VRESET_ID 0x18 // R/W - (MAX17048/49) Reset voltage and ID (default 0x96__)
#define MAX17048_STATUS 0x1A    // R/W - (MAX17048/49) Status of ID (default 0x01__)
#define MAX17043_COMMAND 0xFE   // W - Sends special comands to IC

///////////////////////////////////
// MAX17043 Config Register Bits //
///////////////////////////////////
#define MAX17043_CONFIG_SLEEP (1 << 7)
#define MAX17043_CONFIG_ALSC 0x0040 // MAX17048/49 only
#define MAX17043_CONFIG_ALERT (1 << 5)
#define MAX17043_CONFIG_THRESHOLD 0

/////////////////////////////////////
// MAX17043 Mode Register Commands //
/////////////////////////////////////
#define MAX17043_MODE_QUICKSTART 0x4000 // On the MAX17048/49 this also clears the EnSleep bit

/////////////////////////////////
// MAX17048 Mode Register Bits //
/////////////////////////////////
#define MAX17048_MODE_ENSLEEP 0x2000 // W - _Enables_ sleep mode (the SLEEP bit in the CONFIG reg engages sleep)
#define MAX17048_MODE_HIBSTAT 0x1000 // R - indicates when the IC is in hibernate mode

/////////////////////////////////////
// MAX17048/9 Status Register Bits //
/////////////////////////////////////
#define MAX1704x_STATUS_RI (1 << 0)    // Assumes the MSB has been shifted >> 8
#define MAX1704x_STATUS_VH (1 << 1)    // Assumes the MSB has been shifted >> 8
#define MAX1704x_STATUS_VL (1 << 2)    // Assumes the MSB has been shifted >> 8
#define MAX1704x_STATUS_VR (1 << 3)    // Assumes the MSB has been shifted >> 8
#define MAX1704x_STATUS_HD (1 << 4)    // Assumes the MSB has been shifted >> 8
#define MAX1704x_STATUS_SC (1 << 5)    // Assumes the MSB has been shifted >> 8
#define MAX1704x_STATUS_EnVR (1 << 14) // ** Unshifted **

////////////////////////////////////////
// MAX17043 Command Register Commands //
////////////////////////////////////////
#define MAX17043_COMMAND_POR 0x5400

///////////////////////////////////////
// MAX17048 Hibernate Enable/Disable //
///////////////////////////////////////
#define MAX17048_HIBRT_ENHIB 0xFFFF  // always use hibernate mode
#define MAX17048_HIBRT_DISHIB 0x0000 // disable hibernate mode

////////////////////////////////
// MAX1704x 7-Bit I2C Address //
////////////////////////////////
#define MAX1704x_ADDRESS 0x36 // Unshifted I2C address. Becomes 0x6C for write and 0x6D for read.

// Generic error:
// Wire.endTransmission will return:
// 0:success
// 1:data too long to fit in transmit buffer
// 2:received NACK on transmit of address
// 3:received NACK on transmit of data
// 4:other error
// So, let's use "5" as a generic error value
#define MAX17043_GENERIC_ERROR 5

class SFE_MAX1704X
{
public:
  SFE_MAX1704X(sfe_max1704x_devices_e device = MAX1704X_MAX17043); // Default to the 5V MAX17043

  // 如果需要，更改设备类型。在实例化之后但在 .begin 之前执行此操作
  void setDevice(sfe_max1704x_devices_e device);

  // 允许手动设置 _i2CPort，以便可以在需要时在 .begin 之前调用 isConnected
  void setWirePort(TwoWire &wirePort);

  // begin() - 初始化 MAX17043。
  bool begin(TwoWire &wirePort = Wire); // Returns true if module is detected

  // 如果设备存在则返回 true
  bool isConnected(void);

  // Debug
  void enableDebugging(Stream &debugPort = Serial); // enable debug messages
  void disableDebugging();                          // disable debug messages

  // quickStart() - 重新启动 MAX17043，使其能够重新“猜测”进入其 SoC 算法的参数。
  // 在 setup() 中调用此函数通常可获得更准确的 SoC 读数。
  // 输出：成功时为 0，失败时为正整数。
  uint8_t quickStart();

  // getVoltage() - 获取 MAX17043 的电压读数。
  // 输出：0-5V 之间的浮点值，增量为 1.25mV。
  float getVoltage();

  // getSOC() - 获取 MAX17043 的充电状态 (SOC) 读数，由 IC 的“ModelGauge”算法计算得出。
  // 第一次更新在 IC POR 后约 1 秒可用。
  // 输出：0-100 之间的浮点值，表示
  // 满电量的百分比。
  float getSOC();

  // getVersion() - 获取 MAX17043 的生产版本号。
  // 输出：成功时为 3
  uint16_t getVersion();

  // getThreshold() - 获取将触发警报的 MAX17043 当前百分比阈值。
  // 输出：1 到 32 之间的整数值，表示将触发警报中断的百分比。
  uint8_t getThreshold();

  // setThreshold([percent]) - 设置将触发警报的 MAX17043 百分比阈值。
  // 输入：[percent] - 将触发警报中断的百分比值。
  // 1 到 32 之间的任何值均有效。默认值为 0x1C == 4%
  // 输出：成功时为 0，失败时为正整数。
  uint8_t setThreshold(uint8_t percent = 4);

  // sleep() - 将 MAX17043 设置为睡眠模式。
  // 输出：成功时为 0，失败时为正整数。
  // 在睡眠模式下，IC 停止所有操作，将电流
  // 消耗降至 1μA 以下。退出睡眠模式后，
  // IC 继续正常运行。在睡眠模式下，IC 不会检测自放电。
  // 如果电池在 IC 睡眠时改变状态，IC 无法检测到，从而导致 SOC 错误。
  // 在充电或放电之前唤醒 IC。
  uint8_t sleep();

  // wake() - 将 MAX17043 从睡眠状态唤醒。
  // 输出：成功时为 0，失败时为正整数。
  uint8_t wake();

  // reset() - 向 MAX17043 发出上电复位命令。该函数将 MAX17043 中的每个寄存器复位为其默认值。
  // 输出：成功时为正整数，失败时为 0。
  uint8_t reset();

  // getConfigRegister() - 读取 CONFIG 寄存器的 16 位值。
  // 输出：表示 CONFIG 寄存器的 msb 和 lsb 字节的 16 位整数值。
  // 输出：表示 CONFIG 寄存器的 msb 和 lsb 字节的 16 位整数值。
  uint16_t getConfigRegister();

  // getCompensation() - 获取 ModelGauge 补偿值 - 一个模糊的 8 位值，默认设置为 0x97。
  // 输出：从 CONFIG 寄存器的 MSB 读取的 8 位值。
  uint8_t getCompensation();

  // setCompensation（[newCompensation]）-设置8位补偿值. 
  // 这是一个模糊的8位值，对Maxim的ModelGauge算法有一定影响. The POR value of RCOMP is 0x97.
  // From the datasheet: "Contact Maxim for instructions for optimization."
  // 为获得最佳性能，微控制器主机必须定期测量电池温度，
  // 并相应地补偿RCOMP ModelGauge参数， 至少每分钟一次。
  // 每个定制模型定义常数RCOMP0 (默认值为0x97)、
  //TempCoUp (默认值为-0.5)和TempCoDown (默认值为-5.0)。
  // 按照以下方法计算新CONFIG.RCOMP值：
  // // T是电池温度（摄氏度）
  // if (T > 20) {
  // RCOMP = RCOMP0 + (T - 20) x TempCoUp;
  // }
  // else {
  // RCOMP = RCOMP0 + (T - 20) x TempCoDown;
  // }
  // Input: [newCompensation]-应为0-255之间的值。
  // Output: 0表示成功，正整数表示失败。
  uint8_t setCompensation(uint8_t newCompensation = 0x97);

  // getID() - (MAX17048/49) 返回工厂设置的 8 位 OTP 位。可用于“区分生产中的多种单元类型”。
  // 对这些位的写入将被忽略。
  uint8_t getID(void);

  // setResetVoltage([threshold]) - (MAX17048/49) 设置 7 位 VRESET 值。
  // 一个 7 位值，用于控制比较器，以检测电池何时断开和重新连接。每位 40mV。默认值为 3.0V。
  // 对于内置电池，设置为 2.5V。对于可拆卸电池，根据应用所需的复位阈值，将其设置为至少低于应用空电压 300mV。
  // 输入：[threshold] - 应为 0-127 之间的值。
  // 输出：成功时为 0，失败时为正整数。
  uint8_t setResetVoltage(uint8_t threshold = (0x96 >> 1));
  uint8_t setResetVoltage(float threshold = 3.0); // 辅助功能：设置阈值（单位：伏）

  // getResetVoltage() - (MAX17048/49) 获取 7 位 VRESET 值
  // 输出：从 VRESET/ID 寄存器的 MSB 读取的 7 位值。
  // 返回值为每位 40mV。
  uint8_t getResetVoltage(void);

  // enableComparator() - (MAX17048/49) 设置 VRESET/ID reg 中的位，默认情况下启用比较器。（重新）启用模拟比较器，使用 0.5uA。
  // 输出：成功时为 0，失败时为正整数。
  uint8_t enableComparator(void);

  // disableComparator() - （MAX17048/49）清除 VRESET/ID 寄存器中的位禁用模拟比较器，在休眠模式下节省 0.5uA。
  // 输出：成功时为 0，失败时为正整数。
  uint8_t disableComparator(void);

  // getChangeRate() - (MAX17048/49) 获取每小时变化率（百分比）
  // 输出：（有符号）浮点数（即 0.208% * CRATE 寄存器值）
  // 正变化率表示充电，负变化率表示放电。
  float getChangeRate();

// getStatus() - (MAX17048/49) 获取状态寄存器的 7 位
// 输出：7 位表示各种警报
  uint8_t getStatus();

  //(MAX17048/49) 各种辅助函数用于检查状态寄存器输入中的位：
  // [clear] - 如果 [clear] 为真，则警报标志（如果已设置）将被清除。
  bool isReset(bool clear = false);       // POR 后为真
  bool isVoltageHigh(bool clear = false); // 当 VCELL 高于 VALRTMAX 时为真（参见 setVALRTMax）
  bool isVoltageLow(bool clear = false);  // 当 VCELL 低于 VALRTMIN 时为真（参见 setVALRTMin）
  bool isVoltageReset(bool clear = false);
  bool isLow(bool clear = false);    // 当 SOC 超过 ATHD 中的值时为真（参见 setThreshold）
  bool isChange(bool clear = false); // 当 SOC 变化至少 1% 且启用了 SOCAlert 时为真

  // getAlert([clear]) - 检查 MAX1704X 的 ALRT 警报中断是否已触发。
  // 输入：[clear] - 如果 [clear] 为真，则警报标志（如果已设置）将被清除。
  // 输出：如果中断已触发，则返回 1，否则返回 0。
  uint8_t getAlert(bool clear = false);

// clearAlert() - 清除 MAX1704X 的 ALRT 警报标志。
// 输出：成功时为 0，失败时为正整数。
  uint8_t clearAlert();

  // enableSOCAlert() - (MAX17048/49) 启用 SOC 变化警报
  // 如果 SOC 变化警报已成功启用，则返回 true
  bool enableSOCAlert();

  // disableSOCAlert() - （MAX17048/49）禁用 SOC 变化警报
  // 如果 SOC 变化警报已成功禁用，则返回 true
  bool disableSOCAlert();

  // 启用或禁用 MAX17048/49 VRESET 警报：
  // EnVr（启用电压复位警报）设置为 1 时，在 VRESET/ID 寄存器描述的条件下发生电压复位事件时，将置位 ALRT 引脚。
  // enableAlert() - 设置 STATUS 寄存器 0x​​1A 中的 ENvR 位，
  // 输出：成功时为 0，失败时为正整数。
  uint8_t enableAlert();

  // disableAlert() - 清除 STATUS 寄存器 0x​​1A 中的 ENvR 位
  // 输出：成功时为 0，失败时为正整数。
  uint8_t disableAlert();

  // 读取并返回 MAX17048/49 VALRT 最大阈值
  // LSb = 20mV
  uint8_t getVALRTMax();

  // 读取并返回 MAX17048/49 VALRT 最小阈值
  // LSb = 20mV
  uint8_t getVALRTMin();

  // 设置 MAX17048/49 VALRT 最大阈值
  // 输出：成功时为 0，失败时为正整数。
  // 注意：这将设置每个电池的阈值电压（MAX17049 监控两个电池）
  uint8_t setVALRTMax(uint8_t threshold = 0xFF); // LSb = 20mV
  uint8_t setVALRTMax(float threshold = 5.1);    // 阈值以伏特为单位

  // 设置 MAX17048/49 VALRT 最小阈值
  // 输出：成功时为 0，失败时为正整数。
  // 注意：这将设置每个电池的阈值电压（MAX17049 监控两个电池）
  uint8_t setVALRTMin(uint8_t threshold = 0x00); // LSb = 20mV
  uint8_t setVALRTMin(float threshold = 0.0);    // threshold is defined in Volts

  // 读取并返回 MAX17048/49 休眠状态标志
  bool isHibernating();

  // 读取并返回 MAX17048/49 HIBRT 有效阈值
  // LSb = 1.25mV
  uint8_t getHIBRTActThr();

  // 设置 MAX17048/49 HIBRT 激活阈值
  // Output: 0 on success, positive integer on fail.
  uint8_t setHIBRTActThr(uint8_t threshold); // LSb = 1.25mV
  uint8_t setHIBRTActThr(float threshold);   // Helper function: set threshold in Volts

  // 读取并返回 MAX17048/49 HIBRT 休眠阈值
  // LSb = 0.208%/hr
  uint8_t getHIBRTHibThr();

  //设置 MAX17048/49 HIBRT 休眠阈值
  // 输出：成功时为 0，失败时为正整数。
  uint8_t setHIBRTHibThr(uint8_t threshold); // LSb = 0.208%/hr
  uint8_t setHIBRTHibThr(float threshold);   // Helper function: set threshold in percent

// 将 MAX17048/49 置于休眠状态
// 将 HIBRT 寄存器设置为 0xFFFF
// 输出：成功时为 0，失败时为正整数。
  uint8_t enableHibernate();

// 禁用 MAX17048/49 上的休眠模式
// 将 HIBRT 寄存器设置为 0x0000
// 输出：成功时为 0，失败时为正整数。
  uint8_t disableHibernate();

  // Lower level functions but exposed incase user wants them

  // write16([data], [address]) - Write 16 bits to the requested address. After
  // writing the address to be written, two sequential 8-bit writes will occur.
  // the msb is written first, then lsb.
  // Input: [data] - A 16-bit integer to be written to the device.
  //        [address] - An 8-bit address to be written to.
  // Output: 0 on success, positive integer on fail.
  uint8_t write16(uint16_t data, uint8_t address);

  // read16([address]) - Read 16-bits from the requested address of a device.
  // Input: [address] - An 8-bit address to be read from.
  // Output: A 16-bit value read from the device's address will be returned.
  uint16_t read16(uint8_t address);

private:
  // Variables
  TwoWire *_i2cPort; // The generic connection to user's chosen I2C hardware

#if MAX1704X_ENABLE_DEBUGLOG
  Stream *_debugPort;       // The stream to send debug messages to if enabled. Usually Serial.
  bool _printDebug = false; // Flag to print debugging variables
#endif                      // if MAX1704X_ENABLE_DEBUGLOG

  // Clear the specified bit(s) in the MAX17048/49 status register
  // This requires the bits in mask to be correctly aligned.
  // MAX1704x_STATUS_RI etc. will need to be shifted left by 8 bits to become aligned.
  // Output: 0 on success, positive integer on fail.
  uint8_t clearStatusRegBits(uint16_t mask);

  int _device = MAX1704X_MAX17043; // Default to MAX17043
  float _full_scale = 5.12;        // Default: full-scale for the MAX17043
};

#endif
