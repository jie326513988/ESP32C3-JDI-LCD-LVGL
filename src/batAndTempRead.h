// 采集电池电压电量变化率和cpu温度

// 时间平均滤波
float bat_adc_new = 0.0;
uint8_t bat_vcc_count = 0; // 采样计数
#define bat_vcc_cycs 3     // 采样次数
#define bat_vcc_cyjg 1000  // 采样时间间隔，ms
#define adc_xfvcc  3.3 / 4095.0 //adc每级电压

// 获取电池电量，经过曲线拟合的
void get_bat_soc()
{
  double soc = lipo.getSOC();

  if (soc > 100)
  {
    bat_soc = 100;
    return;
  }
  else if (soc <= 0)
  {
    bat_soc = 0;
    return;
  }

  uint32_t time1 = micros();
  //Serial.printf("soc:%.2f\n", soc);
  /*bat_soc = (0.000000000000326192902311649) * soc * soc * soc * soc * soc * soc * soc * soc * soc +
            (-0.000000000151720516464633) * soc * soc * soc * soc * soc * soc * soc * soc +
            (0.000000029615625177305) * soc * soc * soc * soc * soc * soc * soc +
            (-0.00000315114343497038) * soc * soc * soc * soc * soc * soc +
            (0.000198801015420025) * soc * soc * soc * soc * soc +
            (-0.00758784512642473) * soc * soc * soc * soc +
            (0.1717269546223) * soc * soc * soc +
            (-2.16861244407924) * soc * soc +
            (14.1966113326299) * soc +
            (7.51403684098412);*/

  /*bat_soc = (0.0000000000001467) * soc * soc * soc * soc * soc * soc * soc * soc * soc +
            (-0.00000000007075) * soc * soc * soc * soc * soc * soc * soc * soc +
            (0.000000014406911) * soc * soc * soc * soc * soc * soc * soc +
            (-0.00000161520491) * soc * soc * soc * soc * soc * soc +
            (0.000109022874489) * soc * soc * soc * soc * soc +
            (-0.00455687591174) * soc * soc * soc * soc +
            (0.116837457227518) * soc * soc * soc +
            (-1.74700272574817) * soc * soc +
            (14.1349969995013) * soc +
            (0.492074280664809);*/

  /*bat_soc = (4.68475567744579) +
            ((9.79343033419428) * soc) +
            ((-0.754374995460575) * soc * soc) +
            ((0.0267247706120589) * soc * soc * soc) +
            ((-0.000455374213679642) * soc * soc * soc * soc) +
            ((3.6916477512004E-06) * soc * soc * soc * soc * soc) +
            ((-1.14462310470767E-08) * soc * soc * soc * soc * soc * soc);*/

  bat_soc = (2.4991111281042) +
            ((11.7512066550343) * soc) +
            ((-1.10779279356962) * soc * soc) +
            ((0.0503255772673454) * soc * soc * soc) +
            ((-0.00118667900045202) * soc * soc * soc * soc) +
            ((1.51032234931541E-05) * soc * soc * soc * soc * soc) +
            ((-9.85709679141557E-08) * soc * soc * soc * soc * soc * soc) +
            ((2.58825941651094E-10) * soc * soc * soc * soc * soc * soc * soc);

  //Serial.printf("bat_soc:%.2f\n", bat_soc);
  //Serial.printf("耗时:%d\n", micros() - time1);
  //Serial.println();
  
  if (bat_soc > 100)    bat_soc = 100.0;
  else if (bat_soc < 0) bat_soc = 0;
}

void get_bat_vcc_rtos_init() // 获取电池电压-rtos初始化
{
  xTaskCreateUniversal(
      get_bat_vcc_rtos, /* 任务指针，创建任务用的那个函数名 */
      "get_bat_vcc",    /* 任务名称 */
      2 * 1024,          /* 任务栈大小，根据需要自行设置*/
      NULL,             /* 可选参数，一般不填*/
      2,                /* 优先级 */
      &TH_batRead,      /* 任务句柄，用于后续挂起或恢复运行*/
      0                 /* 核ID */
  );
}

void get_bat_vcc_rtos(void *param) // 获取电池电压-rtos
{
  // 每秒采样一次，采样3次后取平均值输出
  for (;;)
  {
    overTime++;
    bat_vcc_count++;

#if FUEL_GAUGE_TYPE == 0
    uint16_t adc = 0;
    for (uint8_t i = 0; i < 5; i++)
    {
      adc += analogRead(BAT_PIN);
      vTaskDelay(1);
    }
    bat_adc_new += adc / 5;
    if (bat_vcc_count >= bat_vcc_cycs)
    {
      bat_vcc = ((bat_adc_new / bat_vcc_cycs) * (adc_xfvcc)) / eep_fyxs; // 电池电压系数
      bat_adc_new = 0.0;
      bat_vcc_count = 0;
      // 读取转换为摄氏度的温度传感器数据。
      temp_sensor_read_celsius(&cpuTemp);
      //Serial.print("内置温度:");Serial.println(cpuTemp);
      //Serial.print("bat_vcc:");Serial.println(bat_vcc);
      eepSave_fixedTime(); // 检查eeprom是否需要保存
    }
#else
    if (bat_vcc_count > bat_vcc_cycs)
    {
      bat_vcc_count = 0;
      temp_sensor_read_celsius(&cpuTemp); // 读取转换为摄氏度的温度传感器数据。
      eepSave_fixedTime();                // 检查eeprom是否需要保存
      bat_vcc = lipo.getVoltage();

      // 温度补偿,每分钟计算一次
      batTempComp++;
      if (batTempComp == 1 || batTempComp > 60)
      {
        batTempComp = 0;
        max17048_Compensation();
      }
      // bat_soc = lipo.getSOC();
      // Serial.print("bat_vcc:");Serial.println(bat_vcc);
      // Serial.print("百分比: ");
      // Serial.print(lipo.getSOC(), 2);
      // Serial.print("%");
    }
#endif
    buzzerMonitor();
    delay(1000);
  }
}

float batVccToPer(float batVcc) //电池电压转换百分比
{
  if(batVcc >= 4.0)           return 100.0;
  else if(batVcc < BAT_LOW1)  return 0.0;
  double bfb = 44.68296 * batVcc * batVcc * batVcc * batVcc * batVcc -
               195.46225 * batVcc * batVcc * batVcc * batVcc -
               3218.55651 * batVcc * batVcc * batVcc +
               28908.23111 * batVcc * batVcc -
               83885.31360 * batVcc +
               83380.92869;
  return bfb;
}

void cupTempInit() //cpu温度初始化
{
  // 2.定义对象 设定其值为默认值，即
  // temp_sensor 的 dac_offset = TSENS_DAC_L2
  // temp_sensor 的 clk_div = 6

  temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
  // DEFAULT: range:-10℃ ~  80℃, error < 1℃.
  // TSENS_DAC_DEFAULT	默认偏置，即TSENS_DAC_L2
  // TSENS_DAC_L2	offset = 0, measure range:-10℃ ~ 80℃, error < 1℃.

  // 其中temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
  // 这句也可以写为如下/* xxxx */所示，二选一即可
  /*
   temp_sensor_config_t temp_sensor = {
      .dac_offset = TSENS_DAC_L2,
      .clk_div = 6,
    };
  */

  temp_sensor_set_config(temp_sensor); // 3.设定配置
  temp_sensor_start();                 // 4.传感器启用
}

float getBatVolNew() //即时的电压
{
#if FUEL_GAUGE_TYPE == 0
  float vcc_cache = 0.0;
  for (uint8_t i = 0; i < 50; i++)
  {
    vcc_cache += analogRead(BAT_PIN);
  }
  vcc_cache = (vcc_cache / 50.0) * adc_xfvcc / eep_fyxs;
  //Serial.print("BAT ADC:");Serial.println(analogRead(BAT_PIN));
  //Serial.printf("vcc_cache:%.2f\n",vcc_cache);
  return (vcc_cache);
  #else
  return lipo.getVoltage();
#endif
}