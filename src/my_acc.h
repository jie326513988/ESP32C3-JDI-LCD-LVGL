#include <DFRobot_LIS2DW12.h>
// When using I2C communication, use the following program to construct an object by DFRobot_LIS2DW12_I2C
/*!
 * @brief Constructor
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
struct ACC
{
  int16_t x = 0.0;
  int16_t y = 0.0;
  int16_t z = 0.0;
};
ACC acc;
DFRobot_LIS2DW12_I2C acce(&Wire, ACC_I2C_ADDR);

void accInterrupt()
{
  Serial.print("加速度计中断唤醒：");
  Serial.println(digitalRead(ACCINT_PIN));
}

//6D方向检测模式
bool acc_6d()
{
  uint8_t count = 0;
  while (!acce.begin())
  {
    Serial.println("通信失败，使用I2C通信时检查连接和I2C地址设置.");
    delay(20);
    count++;
    if (count > 10) return 0;
  }
  //Serial.printf("加速度计id:%d\n",acce.getID());
  // 芯片软复位
  acce.softReset();
  // 设置带宽
  //acce.setFilterBandwidth(DFRobot_LIS2DW12::eRateDiv_4);
  // 设置传感器数据采集速率
  acce.setDataRate(DFRobot_LIS2DW12::eRate_50hz);
  // 设置传感器测量范围
  acce.setRange(DFRobot_LIS2DW12::e16_g);
  // 过滤器设置
  acce.setFilterPath(DFRobot_LIS2DW12::eLPF);
  // 设置电源模式
  acce.setPowerMode(DFRobot_LIS2DW12::eContLowPwrLowNoise1_12bit);
  // 设置转弯时角度的阈值：
  acce.set6DThreshold(DFRobot_LIS2DW12::eDegrees80);

  /*
  设置 int1 引脚的中断事件：
  eDoubleTap（双击）
  eFreeFall（自由落体）
  eWakeUp（唤醒）
  eSingleTap（单击）
  e6D（方向变化检查）
  */
  acce.setInt1Event(DFRobot_LIS2DW12::e6D);
  //acce.setInt2Event(DFRobot_LIS2DW12::eSleepState);

  // 上拉 INPUT_PULLUP，下拉 INPUT_PULLDOWN
  // pinMode(ACCINT_PIN, INPUT);
  // FALLING 下降，RISING 上升，CHANGE 改变
  // attachInterrupt(digitalPinToInterrupt(ACCINT_PIN), accInterrupt, RISING);

  //Serial.println("加速度计，6D方向检测模式，启动");
  return 1;
}
//使用休眠唤醒模式
bool acc_wakeUp()
{
  uint8_t count = 0;
  while (!acce.begin())
  {
    Serial.println("通信失败，使用I2C通信时检查连接和I2C地址设置.");
    delay(10);
    count++;
    if (count > 10) return 0;
  }
  Serial.printf("加速度计id:%d\n",acce.getID());
  // 芯片软复位
  acce.softReset();
  // 设置传感器数据采集速率
  acce.setDataRate(DFRobot_LIS2DW12::eRate_50hz);
  // 设置传感器测量范围
  acce.setRange(DFRobot_LIS2DW12::e2_g);
  // 过滤器设置
  acce.setFilterPath(DFRobot_LIS2DW12::eLPF);
  // 设置电源模式
  acce.setPowerMode(DFRobot_LIS2DW12::eContLowPwrLowNoise1_12bit);
  // 设置唤醒时长 – 芯片被唤醒后，会持续一段时间，然后进入休眠状态
  acce.setWakeUpDur(1); //0-3 持续时间 = dur * (1000 / hz) 毫秒
  // 设置唤醒阈值，当加速度变化超过此值时，会触发eWakeUp事件，单位：mg
  acce.setWakeUpThreshold(0.5);
  /*
  设置 int1 引脚的中断事件：
  eDoubleTap（双击）
  eFreeFall（自由落体）
  eWakeUp（唤醒）
  eSingleTap（单击）
  e6D（方向变化检查）
  */
  acce.setInt1Event(DFRobot_LIS2DW12::eWakeUp);
  //acce.setInt2Event(DFRobot_LIS2DW12::eSleepBOOT);

  // 上拉 INPUT_PULLUP，下拉 INPUT_PULLDOWN
  //pinMode(ACCINT_PIN, INPUT);
  // FALLING 下降，RISING 上升，CHANGE 改变
  //attachInterrupt(digitalPinToInterrupt(ACCINT_PIN), accInterrupt, RISING);

  Serial.println("加速度计，休眠唤醒模式，启动");
  return 1;
}
//使用连续采集模式
bool acc_continRefresh()
{
  uint8_t count = 0;
  while (!acce.begin())
  {
    Serial.println("通信失败，使用I2C通信时检查连接和I2C地址设置.");
    delay(10);
    count++;
    if (count > 10) return 0;
  }
  Serial.printf("加速度计id:%d\n",acce.getID());
  // 芯片软复位
  acce.softReset();
  // 设置是否连续收集数据
  acce.continRefresh(true);

  /*
    设置传感器数据采集速率:
    eRate_0hz           /<测量关闭>/
    eRate_1hz6          /<1.6hz，仅在低功率模式下使用>/
    eRate_12hz5         /<12.5hz>/
    eRate_25hz
    eRate_50hz
    eRate_100hz
    eRate_200hz
    eRate_400hz       /<仅在高性能模式下使用>/
    eRate_800hz       /<仅在高性能模式下使用>/
    eRate_1k6hz       /<仅在高性能模式下使用>/
    eSetSwTrig        /<该软件触发单次测量>/
  */
  acce.setDataRate(DFRobot_LIS2DW12::eRate_200hz);

  /*
    设置传感器测量范围:
    e2_g   /<±2g>/
    e4_g   /<±4g>/
    e8_g   /<±8g>/
    e16_g  /< ±16g>/
  */
  acce.setRange(DFRobot_LIS2DW12::e2_g);

  /*
    过滤器设置:
    eLPF (低通滤波器)
    eHPF (高通滤波器)
  */
  acce.setFilterPath(DFRobot_LIS2DW12::eLPF);

  /*
    设置带宽：
    eRateDiv_2 /<Rate/2（最高速率 = 800 Hz，速率 = 1600 Hz 时为 400 Hz）>/
    eRateDiv_4 /<Rate/4（高功率/低功率）>*
    eRateDiv_10 /<Rate/10 (HP/LP)>/
    eRateDiv_20 /<Rate/20 (HP/LP)>/
  */
  acce.setFilterBandwidth(DFRobot_LIS2DW12::eRateDiv_4);

  /*
    设置电源模式：
    eHighPerformance_14bit /<高性能模式，14 位分辨率>/
    eContLowPwr4_14bit /<连续测量，低功耗模式 4（14 位分辨率）>/
    eContLowPwr3_14bit /<连续测量，低功耗模式 3（14 位分辨率）>/
    eContLowPwr2_14bit /<连续测量，低功耗模式 2（14 位分辨率）/
    eContLowPwr1_12bit /<连续测量，低功耗模式 1（12 位分辨率）>/
    eSingleLowPwr4_14bit /<按需单次数据转换模式，低功耗模式 4（14 位分辨率）>/
    eSingleLowPwr3_14bit /<按需单次数据转换模式，低功耗模式3(14 位分辨率)>/
    eSingleLowPwr2_14bit /<单次数据转换按需模式，低功耗模式 2(14 位分辨率)>/
    eSingleLowPwr1_12bit /<单次数据转换按需模式，低功耗模式 1(12 位分辨率)>/
    eHighPerformanceLowNoise_14bit /<高性能模式，低噪声启用，14 位分辨率>/
    eContLowPwrLowNoise4_14bit /<连续测量，低功耗模式 4(14 位分辨率，低噪声启用)>/
    eContLowPwrLowNoise3_14bit /<连续测量，低功耗模式 3(14 位分辨率，低噪声启用)>/
    eContLowPwrLowNoise2_14bit     /<连续测量，低功率模式2（14位分辨率，启用低噪声）>/
    eContLowPwrLowNoise1_12bit     /<连续测量，低功率模式1（12位分辨率，启用低噪声）>/
    eSingleLowPwrLowNoise4_14bit  /<按需单数据转换模式，低功率模式4（14位分辨率），低噪声启用>/
    eSingleLowPwrLowNoise3_14bit  /<按需单数据转换模式，低功率模式3（14位分辨率），低噪声启用>/
    eSingleLowPwrLowNoise2_14bit  /<按需单数据转换模式，低功率模式2（14位分辨率），低噪声启用>/
    eSingleLowPwrLowNoise1_12bit  /<按需单数据转换模式，低功率模式1（12位分辨率），低噪声启用>/
  */
  acce.setPowerMode(DFRobot_LIS2DW12::eContLowPwrLowNoise2_14bit);

  Serial.println("加速度计，连续采集模式，启动");
  return 1;
}
//双击唤醒

void acc_test_loop()
{
  // 在按需单数据转换模式下请求测量
  // 访问需求数据（）；
  // 测量范围为±2g、±4g、±8g或±16g，由setRange（）函数设置。
  /*Serial.print("x: ");
  // 读取x方向的加速度
  Serial.print(acce.readAccX());
  Serial.print(" mg \ty: ");
  // 读取y方向的加速度
  Serial.print(acce.readAccY());
  Serial.print(" mg \tz: ");
  // 读取z方向的加速度
  Serial.print(acce.readAccZ());
  Serial.println(" mg");
  delay(300);*/
  Serial.print(acce.readAccX());
  Serial.print(",");
  Serial.print(acce.readAccY());
  Serial.print(",");
  Serial.print(acce.readAccZ());
  Serial.println();
}

// 动态调参一阶滤波算法
#define Threshold_1 20  // 阈值1用于一阶带参滤波器，变化值大于此值时，计数增加，越大越稳定也越慢
#define Threshold_2 15 // 阈值2用于一阶带参滤波器，计数值大于此值时，减少参数，增强滤波跟随

struct FILTER
{
  float k = 0.0; // 滤波系数
  float dataNew = 0.0;
  float dataOld = 0.0;
  float dataOld1 = 0.0;
  uint8_t count = 0; // 滤波计数器
  uint8_t flag = 0;  // 数据变化方向0无 1越来越大 2-越来越小
};
FILTER filter_x;
FILTER filter_y;
FILTER filter_z;

struct FILTER2
{
  int16_t data[10] = {0};
  uint8_t i = 0;
};
FILTER2 filter2_acc;

float filter_acc(float in , FILTER *f)
{
  // 获取新的数据
  f->dataNew = in;

  // 判断数据变化方向
  if (f->dataNew > f->dataOld && f->dataOld > f->dataOld1) // 连续3次同向
  {
    f->flag = 1; // 标记同向
  }
  else if (f->dataNew < f->dataOld && f->dataOld < f->dataOld1)  // 连续3次同向
  { 
    f->flag = 1;  // 标记同向
  }
  else
  {
    f->flag = 0;  // 标记反向
  }

  f->dataOld1 = f->dataOld; // 保存起来

  if (f->flag) // 如果变化方向一致
  { 
    f->count++;
    if (abs(f->dataNew - f->dataOld) > Threshold_1) // 新数据减旧数据大于阈值再加1
    {
      f->count++;
    }
    if (f->count > Threshold_2)  // 阈值大于设定值
    {
      f->k += 0.25; // 增加滤波系数，增强跟随性
      f->count = 0;
    }
  }
  else
  {
    f->count = 0;
    f->k = 0.02; // 重置滤波系数，增强平滑性
  }

  if ( f->k > 1)  f->k = 1;

  // 应用一阶滤波器公式
  f->dataOld = ((1.0 - f->k) * f->dataOld) + (f->k * f->dataNew);

  return f->dataOld;
}

float filter_acc2(float in , FILTER2 *f)
{
  if (f->i == 10) f->i = 0;
  f->data[f->i] = in;
  float out = 0.0;
  //int16_t min = 10000;
  //int16_t max = -10000;
  for (uint8_t i = 0; i < 10; i++)
  {
    //if (f->data[i] < min) min = f->data[i];
    //v else if (f->data[i] > max) max = f->data[i];
    out += f->data[i];
  }
  f->i++;
  //Serial.printf("min:%d\n",min);
  //Serial.printf("max:%d\n",max);
  return out = out/ 10.0;
  //return out = (out - min - max) / 8.0;
}

void accRead_rtos_init() // 创建加速度计读取任务
{
  i2c_begin();
  xTaskCreatePinnedToCore(
      accRead_rtos, /* 任务指针，创建任务用的那个函数名 */
      "accRead",    /* 任务名称 */
      4 * 1024,     /* 任务栈大小，根据需要自行设置*/
      NULL,         /* 可选参数，一般不填*/
      2,            /* 优先级 */
      &TH_accRead,  /* 任务句柄，用于后续挂起或恢复运行*/
      0             /* 核ID */
  );
}

void accRead_rtos(void *param)
{
  // 设置加速度计模式
  bool ok = acc_continRefresh();
  // 标记加速度芯片的状态
  bitWrite(ic_state, IC_ACC, ok);
  // 标记关闭加速度读取任务
  if (ok == 0)
    bitWrite(backgroundTask, BGT_ACC_READ, 0); 

  for (;;)
  {
    if (!bitRead(backgroundTask, BGT_ACC_READ))
    {
      Serial.println("删除TH_accRead");
      TH_accRead = NULL;
      vTaskDelete(NULL);
    }

    if (eep_accDispMod == 0) // 输出原始数据
    {
      acc.x = acce.readAccX();
      acc.y = acce.readAccY();
      acc.z = acce.readAccZ();
      /*Serial.print(acc.x);
      Serial.print(",");
      Serial.print(acc.y);
      Serial.print(",");
      Serial.println(acc.z);*/
    }
    else  // 输出滤波数据
    {
      acc.x = filter_acc(acce.readAccX(), &filter_x);
      acc.y = filter_acc(acce.readAccY(), &filter_y);
      acc.z = filter_acc(acce.readAccZ(), &filter_z);
    }
    delay(15); // 1000 / 15 
    /*Serial.println("11111111");
    lv_obj_send_event(label_acc[0], LV_EVENT_REFRESH, NULL);
    Serial.println("22222222");*/
    // lv_obj_send_event(label_acc[1], LV_EVENT_REFRESH, NULL);
    // lv_obj_send_event(label_acc[2], LV_EVENT_REFRESH, NULL);
  }
}

