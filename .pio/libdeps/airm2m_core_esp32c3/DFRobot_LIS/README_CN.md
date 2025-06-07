# DFRobot_LIS

* [English Version](./README.md)
  
H3LIS200DL是一款低功耗、高性能的3轴线性加速度计
属于“纳米”家族，具有数字I2C/SPI
串行接口标准输出。
该设备具有超低功耗运行特点
模式允许先进的节能和
智能sleep-to-wakeup功能。
H3LIS200DL有动态用户可选择的全量程±100g/±200g，是
能够测量加速度与输出
数据速率从0.5 Hz到1 kHz。
H3LIS200DL有一个小薄型
塑料地网阵列包(LGA)，是
保证在较长的时间内运行
温度范围:-40℃~ +85℃。

LIS331HH是一种超低功耗的高功率
性能高全尺寸三轴线性
加速度计属于“纳米”家族，具有
数字I2C/SPI串行接口标准输出。
该设备具有超低功耗运行特点
模式允许先进的节能和
智能睡眠唤醒功能。
LIS331HH具有动态用户选择功能
全量程±6g/±12g/±24g
测量加速度与输出数据速率
从0.5 Hz到1 kHz。自测能力
允许用户检查功能

IIS2DLPC是一款超低功耗高性能产品
带有数字I²C/SPI的三轴线性加速度计
输出接口，利用了健壮的和
已采用成熟的制造工艺
微机械加速度计的生产。
IIS2DLPC具有用户可选择的完整规模
±2g/±4g/±8g/±16g，可测量
输出数据速率从1.6 Hz到
1600 Hz。

LIS2DW12是一款超低功率高性能三轴线性
加速度计属于“femto”家族，利用了强大的和
成熟的制造工艺已用于生产微加工
加速度计。
LIS2DW12有用户可选择的±2g/±4g/±8g/±16g的全刻度，并能够
测量输出数据速率从1.6 Hz到1600hz的加速度。

LIS2DH12是一款超低功率高性能三轴线性
加速度计属于“femto”家族，利用了强大的和
成熟的制造工艺已用于生产微加工
加速度计。
LIS2DH12有用户可选择的±2g/±4g/±8g/±16g的全刻度

CHIP                | Work Well    | Work Wrong  | Remarks
------------------  | :----------: | :---------- | -----
H3LIS200DL          |      √       |              |             
LIS331HH            |      √       |              |  
LIS2DW12            |      √       |              |             
IIS2DLPC            |      √       |              |        
IIS2DH12            |      √       |              |              

![产品效果图片](./resources/images/SEN0405_TOP.jpg)
![产品效果图片](./resources/images/SEN0407_TOP.jpg)
![产品效果图片](./resources/images/SEN0408_TOP.jpg)
![产品效果图片](./resources/images/SEN0409_TOP.jpg)
![产品效果图片](./resources/images/SEN0411_TOP.jpg)
![产品效果图片](./resources/images/SEN0412_TOP.jpg)

## 产品链接(https://www.dfrobot.com)
    SKU:SEN0405
    SKU:SEN0407
    SKU:SEN0408
    SKU:SEN0409
    SKU:SEN0411
    SKU:SEN0412
    SKU:SEN0224

## 目录

  * [概述](#概述)
  * [库安装](#库安装)
  * [Method_H3LIS200DL_LIS331HH](#Method_H3LIS200DL_LIS331HH)
  * [Method_LIS2DW12_IIS2DLPC](#Method_LIS2DW12_IIS2DLPC)
  * [Method_LIS2DH12](#Method_LIS2DH12)
  * [兼容性](#兼容性)
  * [历史](#历史)
  * [创作者](#创作者)

## 概述

提供一个Arduino库，通过读取LIS数据获得三轴加速度。

## 库安装

使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。

## Method_H3LIS200DL_LIS331HH 
```C++
  DFRobot_LIS();
  /**
   * @fn begin
   * @brief 初始化函数
   * @return 返回初始化状态
   */
  bool begin(void);
 
  /**
   * @fn getID
   * @brief 获取芯片ID
   * @return 8 位连续数据
   */
  uint8_t getID();
  
  /**
   * @fn enableInterruptEvent
   * @brief 使能中断
   * @param source 中断引脚选择
   * @n          eINT1 = 0,/<int1>/
   * @n          eINT2,/<int2>/
   * @param event Interrupt event selection
   * @n           eXLowerThanTh ,/<x方向上的加速度小于阈值>/
   * @n           eXHigherThanTh ,/<x方向上的加速度大于阈值>/
   * @n           eYLowerThanTh,/<y方向上的加速度小于阈值>/
   * @n           eYHigherThanTh,/<y方向上的加速度大于阈值>/
   * @n           eZLowerThanTh,/<z方向上的加速度小于阈值>/
   * @n           eZHigherThanTh,/<z方向上的加速度大于阈值>/
   */
  void enableInterruptEvent(eInterruptSource_t source, eInterruptEvent_t event);
  
  /**
   * @fn setRange
   * @brief 设置测量范围
   * @param range 范围(g)
   * @n               eH3lis200dl_100g, //±100g
   * @n               eH3lis200dl_200g, //±200g
   *        
   * @n               eLis331hh_6g = 6,//±6g
   * @n               eLis331hh_12g = 12 //±12g
   * @n               eLis331hh_24g = 24 //±24g  
   * @return true(设置成功)/false(设置失败)
   */
  bool setRange(eRange_t range);
  
  /**
   * @fn setAcquireRate
   * @brief 设置数据测量速率
   * @param rate rate(HZ)
   * @n          ePowerDown_0HZ  
   * @n          eLowPower_halfHZ
   * @n          eLowPower_1HZ
   * @n          eLowPower_2HZ
   * @n          eLowPower_5HZ
   * @n          eLowPower_10HZ
   * @n          eNormal_50HZ
   * @n          eNormal_100HZ
   * @n          eNormal_400HZ
   * @n          eNormal_1000HZ
   */
  void setAcquireRate(ePowerMode_t rate);
  
  /**
   * @fn setHFilterMode
   * @brief 设置数据过滤模式
   * @param mode Four modes
   * @n              eCutOffMode1 = 0,
   * @n              eCutOffMode2,
   * @n              eCutOffMode3,
   * @n              eCutOffMode4,
   * @n              eShutDown,
   * @n  eg: 选择50HZ的“eCutOffMode1”，过滤频率为1HZ
   * @n|---------------------------选择50HZ的“eCutOffMode1”，过滤频率为1HZ--------------------------------------|
   * @n|--------------------------------------------------------------------------------------------------------|
   * @n|                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
   * @n|   mode         |Data rate = 50 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 1000 Hz |
   * @n|--------------------------------------------------------------------------------------------------------|
   * @n|  eCutOffMode1  |     1           |         2            |            8         |             20        |
   * @n|--------------------------------------------------------------------------------------------------------|
   * @n|  eCutOffMode2  |    0.5          |         1            |            4         |             10        |
   * @n|--------------------------------------------------------------------------------------------------------|
   * @n|  eCutOffMode3  |    0.25         |         0.5          |            2         |             5         |
   * @n|--------------------------------------------------------------------------------------------------------|
   * @n|  eCutOffMode4  |    0.125        |         0.25         |            1         |             2.5       |
   * @n|--------------------------------------------------------------------------------------------------------|
   */
  void setHFilterMode(eHighPassFilter_t mode);

  /**
   * @fn setInt1Th
   * @brief 设置中断源1中断的阈值
   * @param threshold 我们之前设置的阈值在测量范围内(unit:g)
   */
  void setInt1Th(uint8_t threshold);

  /**
   * @fn setInt2Th
   * @brief 设置“中断源2”的中断产生阈值
   * @param threshold 我们之前设置的阈值在测量范围内(unit:g）
   */
  void setInt2Th(uint8_t threshold);

  /**
   * @fn enableSleep 
   * @brief 开启睡眠唤醒功能
   * @param enable true(使能)\false(禁用)
   * @return false启用失败/true启用成功
   */
  bool enableSleep(bool enable);
  
  /**
   * @fn getInt1Event
   * @brief 检查中断1中是否产生中断事件'event'
   * @param event 中断事件
   * @n           eXLowerThanTh ,/<x方向上的加速度小于阈值>/
   * @n           eXHigherThanTh ,/<x方向上的加速度大于阈值>/
   * @n           eYLowerThanTh,/<y方向上的加速度小于阈值>/
   * @n           eYHigherThanTh,/<y方向上的加速度大于阈值>/
   * @n           eZLowerThanTh,/<z方向上的加速度小于阈值>/
   * @n           eZHigherThanTh,/<z方向上的加速度大于阈值>/
   * @return true产生该事件/false不产生该事件
   */
  bool getInt1Event(eInterruptEvent_t event);

  /**
   * @fn getInt2Event
   * @brief 检查中断2中是否产生中断事件'event'
   * @param event 中断事件
   * @n           eXLowerThanTh ,/<x方向上的加速度小于阈值>/
   * @n           eXHigherThanTh ,/<x方向上的加速度大于阈值>/
   * @n           eYLowerThanTh,/<y方向上的加速度小于阈值>/
   * @n           eYHigherThanTh,/<y方向上的加速度大于阈值>/
   * @n           eZLowerThanTh,/<z方向上的加速度小于阈值>/
   * @n           eZHigherThanTh,/<z方向上的加速度大于阈值>/
   * @return true产生该事件/false不产生该事件
   */
  bool getInt2Event(eInterruptEvent_t event);
  
  /**
   * @fn readAccX
   * @brief 得到x方向上的加速度
   * @return x方向加速度 
   */
  int32_t readAccX();
  
  /**
   * @fn readAccY
   * @brief 得到y方向上的加速度
   * @return y方向加速度
   */
  int32_t readAccY();
  
  /**
   * @fn readAccZ
   * @brief 得到z方向上的加速度
   * @return z方向加速度
   */
  int32_t readAccZ();
  
  /**
   * @fn getAcceFromXYZ
   * @brief 求xyz三个方向上的加速度
   * @param accx 存储x方向上的加速度变量
   * @param accy 存储y方向上的加速度变量
   * @param accz 存储z方向上的加速度变量
   * @return true(获取数据成功)/false(数据无法读取)
   */
  bool getAcceFromXYZ(int32_t &accx,int32_t &accy,int32_t &accz);

  /**
   * @fn getSleepState 
   * @brief 获取传感器是否处于睡眠模式
   * @return true(在睡眠模式下)/false(在正常模式下)
   */
  bool getSleepState();
  
  /**
   * @fn setSleepFlag
   * @brief 设置休眠状态标志
   * @param into true(将当前模式标记为睡眠模式)/false(将当前模式标记为普通模式)
   */
  void setSleepFlag(bool into);
```
## Method_LIS2DW12_IIS2DLPC
```C++
  /**
   * @fn begin
   * @brief 初始化函数
   * @return true(初始化成功)/fasle(初始化失败)
   */
  bool begin(void);
 
  /**
   * @fn getID
   * @brief 获取芯片ID
   * @return 8 bit serial number
   */
  uint8_t getID();
 
  /**
   * @fn softReset
   * @brief 软件复位将所有寄存器的值恢复为默认值
   */
  void softReset();
  
  /**
   * @fn continRefresh
   * @brief 使芯片能够连续采集数据
   * @param enable  true(持续的更新)/false(输出寄存器直到读取MSB和LSB时才更新)
   */
  void continRefresh(bool enable);
  
  /**
   * @fn setFilterPath
   * @brief 设置过滤处理模式
   * @param path 滤波通道
   * @n          eLPF   = 0x00,/<选择低通滤波路径>/
   * @n          eHPF   = 0x10,/<高通滤波路径选择>/
   */
  void setFilterPath(ePath_t path);

  /**
   * @fn setFilterBandwidth
   * @brief 设置数据带宽
   * @param bw 带宽
   * @n        eRateDiv_2  
   * @n        eRateDiv_4  
   * @n        eRateDiv_10 
   * @n        eRateDiv_20 
   */
  void setFilterBandwidth(eBWFilter_t bw);
  
  /**
   * @fn setPowerMode
   * @brief 设置功率模式后，传感器有两种模式来测量加速度
   * @n       1.连续测量在这种模式下，传感器将连续测量并将数据存储在其寄存器中
   * @n       2.单数据转换按需模式在这种模式下，传感器除非收到外部请求，否则不会进行测量
   * @param mode  电源模式可供选择
   * @n           eHighPerformance_14bit         /<高性能模式,14-bit决议>/
   * @n           eContLowPwr4_14bit             /<连续测量，低功耗模式4(14位分辨率)>/
   * @n           eContLowPwr3_14bit             /<连续测量，低功耗模式3(14位分辨率)>/
   * @n           eContLowPwr2_14bit             /<连续测量，低功耗模式2(14位分辨率)/
   * @n           eContLowPwr1_12bit             /<连续测量，低功耗模式1(12位分辨率)>/
   * @n           eSingleLowPwr4_14bit           /<单数据按需转换模式，低功耗模式4(14位分辨率)>/
   * @n           eSingleLowPwr3_14bit           /<单数据按需转换模式，低功耗模式3(14位分辨率)>/
   * @n           eSingleLowPwr2_14bit           /<单数据按需转换模式，低功耗模式2(14位分辨率)>/
   * @n           eSingleLowPwr1_12bit           /<单数据按需转换模式，低功耗模式1(12位分辨率)>/
   * @n           eHighPerformanceLowNoise_14bit /<高性能模式，低噪音，14位分辨率>/
   * @n           eContLowPwrLowNoise4_14bit     /<连续测量，低功耗模式4(14位分辨率，低噪声启用)>/
   * @n           eContLowPwrLowNoise3_14bit     /<连续测量，低功耗模式3(14位分辨率，低噪声启用)>/
   * @n           eContLowPwrLowNoise2_14bit     /<连续测量，低功耗模式2(14位分辨率，低噪声启用)>/
   * @n           eContLowPwrLowNoise1_12bit     /<连续测量，低功耗模式1(12位分辨率，低噪声启用)>/
   * @n           eSingleLowPwrLowNoise4_14bit   /<单数据转换按需模式，低功耗模式4(14位分辨率)，低噪音启用>/
   * @n           eSingleLowPwrLowNoise3_14bit   /<单数据转换按需模式，低功耗模式3(14位分辨率)，低噪音启用>/
   * @n           eSingleLowPwrLowNoise2_14bit   /<单数据转换按需模式，低功耗模式2(14位分辨率)，低噪音启用>/
   * @n           eSingleLowPwrLowNoise1_12bit   /<单数据转换按需模式，低功耗模式1(12位分辨率)，低噪音启用>/
   */
  void setPowerMode(ePowerMode_t mode);
  
  /**
   * @fn setDataRate
   * @brief 芯片数据采集速率设置
   * @param rate  Accelerometer frequency, 0-1600hz selection
   * @n           eRate_0hz            
   * @n           eRate_1hz6           
   * @n           eRate_12hz5          
   * @n           eRate_25hz        
   * @n           eRate_50hz        
   * @n           eRate_100hz       
   * @n           eRate_200hz       
   * @n           eRate_400hz         
   * @n           eRate_800hz         
   * @n           eRate_1k6hz         
   * @n           eSetSwTrig          
   */
  void setDataRate(eRate_t rate);
  
  /**
   * @fn setFreeFallDur
   * @brief 设置自由落体时间，或自由落体样品的数量。在测量中，除非样品足够多，否则不能将其确定为自由落体事件。
   * @param dur 自由落体样本,范围:0 ~ 31
   * @n time = dur * (1/rate)(unit:s)
   * @n  |                            这是一个参数和时间之间线性关系的例子                            |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   * @n  |                |                     |                          |                          |                           |
   * @n  |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   * @n  |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   */
  void setFreeFallDur(uint8_t dur);
  
  /**
   * @fn setInt1Event
   * @brief 选择在int1引脚上生成的中断事件
   * @param event  中断事件，当它发生时，将在int1引脚上生成一个级别跳转
   * @n            eDoubleTap    = 0x08,/<双击事件>/
   * @n            eFreeFall     = 0x10,/<自由落体的事件>/
   * @n            eWakeUp       = 0x20,/<唤醒事件>/
   * @n            eSingleTap    = 0x40,/<单一的点击事件>/
   * @n            e6D           = 0x80,/<改变面朝上/下/左/右/前/后状态的事件>/
   */
  void setInt1Event(eInt1Event_t event);
  
  /**
   * @fn setInt2Event
   * @brief 选择在int2引脚上生成的中断事件
   * @param event 中断事件，当它发生时，将在int2引脚上生成一个级别跳转
   * @n           eSleepChange = 0x40,/<睡眠改变状态路由到INT2 pad>/
   * @n           eSleepState  = 0x80,/<在INT2 pad上开启SLEEP_STATE路由>/
   */
  void setInt2Event(eInt2Event_t event);
  
  /**
   * @fn setWakeUpDur
   * @brief 设置唤醒时间，在setActMode()函数中使用eDetectAct的检测方式时，会以正常速率采集数据
   * @n     芯片被唤醒后。然后在一段时间后，芯片将继续休眠，以12.5hz的频率收集数据。
   * @param dur 时间范围:0 ~ 3
   * @n time = dur * (1/rate)(unit:s)
   * @n  |                           这是一个参数和时间之间线性关系的例子                             |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   * @n  |                |                     |                          |                          |                           |
   * @n  |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   * @n  |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   */
  void setWakeUpDur(uint8_t dur);

  /**
   * @fn setWakeUpThreshold
   * @brief 设置唤醒阈值，当某一方向的加速度大于该值时，触发唤醒事件
   * @param th 阈值，单位:mg，数值在测量范围内
   */
  void setWakeUpThreshold(float th);
  
  /**
   * @fn setActMode
   * @brief 设置运动检测模式，第一模式不会检测模块是否在运动;第二种方法一旦设定，测量的数据就会更低
   * @n 频率节省消耗，检测运动后恢复正常;第三种只能检测模块是否处于睡眠状态。
   * @param mode 运动检测模式
   * @n          eNoDetection         /<没有检测>/
   * @n          eDetectAct           /<检测移动，芯片在低功耗模式下自动切换到12.5 Hz频率>/
   * @n          eDetectStatMotion    /<检测运动，芯片检测加速度低于固定阈值，但不会改变速率或工作模式>/
   */
  void setActMode(eActDetect_t mode);
  
  /**
   * @fn setRange
   * @brief 设置范围
   * @param range 量程
   * @n     eLIS2DH12_2g /<±2g>/
   * @n     eLIS2DH12_4g /<±4g>/
   * @n     eLIS2DH12_8g /<±8g>/
   * @n     eLIS2DH12_16g /<±16g>/
   */
  void setRange(eRange_t range);
  
  /**
   * @fn enableTapDetectionOnZ
   * @brief 启用Z方向的侦测轻击事件
   * @param enable ture(启动成功)\false(启动失败)
   */
  void enableTapDetectionOnZ(bool enable);
  
  /**
   * @fn enableTapDetectionOnY
   * @brief 启用Y方向的侦测轻击事件
   * @param enable ture(启动成功)\false(启动失败)
   */
  void enableTapDetectionOnY(bool enable);

  /**
   * @fn enableTapDetectionOnX
   * @brief 启用X方向的侦测轻击事件
   * @param enable ture(启动成功)\false(启动失败)
   */
  void enableTapDetectionOnX(bool enable);

  /**
   * @fn setTapThresholdOnX
   * @brief 设置X方向的点击阈值
   * @param th 阈值(mg)，只能在0~2g范围内使用
   */
  void setTapThresholdOnX(float th);
  
  /**
   * @fn setTapThresholdOnY
   * @brief 设置Y方向的点击阈值
   * @param th 阈值(mg)，只能在0~2g范围内使用
   */
  void setTapThresholdOnY(float th);

  /**
   * @fn setTapThresholdOnZ
   * @brief 设置Z方向的点击阈值
   * @param th 阈值(mg)，只能在0~2g范围内使用
   */
  void setTapThresholdOnZ(float th);
  
  /**
   * @fn setTapDur
   * @brief 双点识别的最大时间间隔的持续时间。当双击
   * @n 识别被启用，这个寄存器表示两个之间的最大时间 
   * @n 连续检测轻击以确定双轻击事件。
   * @param dur 时间范围:0 ~ 15
   * @n time = dur * (1/rate)(unit:s)
   * @n  |                        这是一个参数和时间之间线性关系的例子                                |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   * @n  |                |                     |                          |                          |                           |
   * @n  |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   * @n  |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   */
  void setTapDur(uint8_t dur);
  
  /**
   * @fn setTapMode
   * @brief 设置点击检测模式，检测单点或单点、双点同时检测 
   * @param mode 利用检测模式
   * @n          eOnlySingle   /<检测单一的水龙头>/
   * @n          eBothSingleDouble /<检测单点和双点>/
   */
  void setTapMode(eTapMode_t mode);

  /**
   * @fn set6DThreshold
   * @brief 设置4D/6D的Thresholds，当旋转阈值超过指定的角度时，就会发生方向改变事件。
   * @param degree   eDegrees80   /<80°>/
   * @n              eDegrees70   /<70°>/
   * @n              eDegrees60   /<60°>/
   * @n              eDegrees50   /<50°>/
   */
  void set6DThreshold(e6DTh_t degree);

  /**
   * @fn readAccX
   * @brief 读取x方向上的加速度
   * @return  加速度数据来自x(mg)，测量范围为±2g，±4g，±8g或±16g，由setRange()函数设置。
   */
  int16_t readAccX();
  
  /**
   * @fn readAccY
   * @brief 读取y方向上的加速度
   * @return  加速度数据来自y(mg)，测量范围为±2g，±4g，±8g或±16g，由setRange()函数设置。
   */
  int16_t readAccY();
  
  /**
   * @fn readAccZ
   * @brief 读取y方向上的加速度
   * @return  加速度数据来自z(mg)，测量范围为±2g，±4g，±8g或±16g，由setRange()函数设置。
   */
  int16_t readAccZ();
  
  /**
   * @fn actDetected
   * @brief 检测运动
   * @return true(运动产生)/false(没有产生)
   */
  bool actDetected();
  
  /**
   * @fn freeFallDetected
   * @brief 检测自由落体 
   * @return true(自由落体)/false(没有自由落体)
   */
  bool freeFallDetected();
  
  /**
   * @fn oriChangeDetected
   * @brief 当芯片面朝上/下/左/右/前/后(即6D)时，检测芯片方向是否改变
   * @return true(检测到位置变化)/false(没有检测到事件)
   */
  bool oriChangeDetected();
  
  /**
   * @fn getOrientation
   * @brief 只有在6D(朝上/朝下/左/右/向前/向后)状态下，函数才能得到传感器相对于正z轴的方向。
   * @return    eXDown  /<X现在是向下的>/
   * @n         eXUp    /<X现在是向上的>/
   * @n         eYDown  /<Y现在是向下的>/
   * @n         eYUp    /<Y现在是向上的>/
   * @n         eZDown  /<Z现在是向下的>/
   * @n         eZUp    /<Z现在是向上的>/
   */
  eOrient_t getOrientation();
  
  /**
   * @fn tapDetect
   * @brief 轻拍检测，可以检测是双拍还是单拍
   * @return   eSTap       
   * @n        eDTap       
   * @n        eNoTap,     
   */
  eTap_t tapDetect();
  
  /**
   * @fn getTapDirection
   * @brief 抽头方向源检测
   * @return   eDirXUp   /<在X的正方向检测到Tap>/
   * @n        eDirXDown /<在X的负方向检测到Tap>/
   * @n        eDirYUp   /<在Y的正方向检测到Tap>/
   * @n        eDirYDown /<在Y的负方向检测到Tap>/
   * @n        eDirZUp   /<在Z的正方向检测到Tap>/
   * @n        eDirZDown /<在Z的负方向检测到Tap>/
   */
  eTapDir_t getTapDirection();
  
  /**
   * @fn getWakeUpDir
   * @brief 唤醒运动方向检测
   * @return   eDirX    /<芯片被X方向的运动唤醒>/
   * @n        eDirY    /<芯片被Y方向的运动唤醒>/
   * @n        eDirZ    /<芯片被Z方向的运动唤醒>/
   * @n        eDirError,/<检测到错误>/
   */
  eWakeUpDir_t getWakeUpDir();
  
  /**
   * @fn demandData
   * @brief 在单数据转换按需模式下，请求测量。
   */
  void demandData();
```
## Method_LIS2DH12
```C++
  /**
   * @fn begin
   * @brief 初始化函数
   * @return true(成功)/false(失败)
   */
  bool begin(void);

  /**
   * @fn setRange
   * @brief 设置测量范围
   * @param range 范围(g)
   * @n           eLIS2DH12_2g, //±2g
   * @n           eLIS2DH12_4g, //4g
   * @n           eLIS2DH12_8g, //8g
   * @n           eLIS2DH12_16g, //16g
   */
  void setRange(eRange_t range);

  /**
   * @fn setAcquireRate
   * @brief 设置数据测量速率
   * @param rate 速度(HZ)
   * @n          ePowerDown_0Hz 
   * @n          eLowPower_1Hz 
   * @n          eLowPower_10Hz 
   * @n          eLowPower_25Hz 
   * @n          eLowPower_50Hz 
   * @n          eLowPower_100Hz
   * @n          eLowPower_200Hz
   * @n          eLowPower_400Hz
   */
  void setAcquireRate(ePowerMode_t rate);

  /**
   * @fn setAcquireRate
   * @brief 获取芯片ID
   * @return 8连续数据
   */
  uint8_t getID();

  /**
   * @fn readAccX
   * @brief 获取x方向上的加速度
   * @return 加速度为x(单位:g)，测量范围为±100g或±200g，由setRange()函数设定。
   */
  int32_t readAccX();

  /**
   * @fn readAccY
   * @brief 获取y方向的加速度
   * @return 加速度为y(单位:g)，测量范围为±100g或±200g，由setRange()函数设定。
   */
  int32_t readAccY();

  /**
   * @fn readAccZ
   * @brief 获取z方向的加速度
   * @return 加速度从z开始(单位:g)，测量范围为±100g或±200g，由setRange()函数设定。
   */
  int32_t readAccZ();
  
  /**
   * @fn setInt1Th
   * @brief 设置中断源1中断的阈值
   * @param threshold 告警阈值在测量范围内，单位:g
   */
  void setInt1Th(uint8_t threshold);

  /**
   * @fn setInt2Th
   * @brief 设置“中断源2”的中断产生阈值
   * @param threshold 告警阈值在测量范围内，单位:g
   */
  void setInt2Th(uint8_t threshold);

  /**
   * @fn enableInterruptEvent
   * @brief 启用中断
   * @param source 中断引脚选择
   * @n           eINT1 = 0,/<int1 >/
   * @n           eINT2,/<int2>/
   * @param event 中断事件选择
   * @n            eXLowerThanTh ,/<x方向上的加速度小于阈值>/
   * @n            eXHigherThanTh ,/<x方向上的加速度大于阈值>/
   * @n            eYLowerThanTh,/<y方向上的加速度小于阈值>/
   * @n            eYHigherThanTh,/<y方向上的加速度大于阈值>/
   * @n            eZLowerThanTh,/<z方向的加速度小于阈值>/
   * @n            eZHigherThanTh,/<z方向的加速度大于阈值>/
   */
  void enableInterruptEvent(eInterruptSource_t source, eInterruptEvent_t event);

  /**
   * @fn getInt1Event
   * @brief 检查中断1中是否产生中断事件'event'  
   * @param event Interrupt event
   * @n            eXLowerThanTh ,/<x方向上的加速度小于阈值>/
   * @n            eXHigherThanTh ,/<x方向上的加速度大于阈值>/
   * @n            eYLowerThanTh,/<y方向上的加速度小于阈值>/
   * @n            eYHigherThanTh,/<y方向上的加速度大于阈值>/
   * @n            eZLowerThanTh,/<z方向的加速度小于阈值>/
   * @n            eZHigherThanTh,/<z方向的加速度大于阈值>/
   * @return true 产生/false 没有产生
   */
  bool getInt1Event(eInterruptEvent_t event);

  /**
   * @fn getInt2Event
   * @brief 检查中断2中是否产生中断事件'event'  
   * @param event Interrupt event
   * @n            eXLowerThanTh ,/<x方向上的加速度小于阈值>/
   * @n            eXHigherThanTh ,/<x方向上的加速度大于阈值>/
   * @n            eYLowerThanTh,/<y方向上的加速度小于阈值>/
   * @n            eYHigherThanTh,/<y方向上的加速度大于阈值>/
   * @n            eZLowerThanTh,/<z方向的加速度小于阈值>/
   * @n            eZHigherThanTh,/<z方向的加速度大于阈值>/
   * @return true 产生/false 没有产生
   */
  bool getInt2Event(eInterruptEvent_t event);
```
## 兼容性

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
FireBeetle-ESP8266 |      √       |              |             | 
FireBeetle-ESP32   |      √       |              |             | 
Arduino MEGA2560   |      √       |              |             | 
Arduino Leonardo   |      √       |              |             | 
Micro:bit          |      √       |              |             | 
FireBeetle-M0      |      √       |              |             | 
Raspberry Pi       |      √       |              |             | 

## 历史

- 2021/2/1 -1.0.0 版本
- 2021/1/6 -1.0.1 版本

## 创作者

Written by(li.feng@dfrobot.com,jie.tang@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))
