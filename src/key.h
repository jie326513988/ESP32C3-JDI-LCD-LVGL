#define TRIGGER 4000  //触发值
#define RANGE 200
uint32_t keyTime = 0;
//返回 1按下 2左 3右
uint8_t getKey()
{
  //if(millis() - keyTime < 30 || millis() < 1000) return 0;
  //keyTime = millis();

  if (millis() < 1000) return 0;

  uint8_t state = 0;

  uint16_t adc = analogRead(KEY_ADC_PIN);
  if (adc < TRIGGER)
  {
    //Serial.printf("间隔:%d\n", millis() - keyTime);
    //keyTime = millis();

    overTime = 0;

    /*adc = 0;
    for (uint8_t i = 0; i < 3; i++)
    {
      delay(1);
      adc += analogRead(KEY_ADC_PIN);
    }
    adc = adc / 3;*/

    //Serial.print("按键adc:"); Serial.println(adc);

      /*if      (adc >= 0 && adc < 100)    return 1;
      else if (adc > 2000 && adc < 2400) return 2;
      else if (adc > 2800 && adc < 3200) return 3;*/
    // 按下
    if (adc < 100) state = 1;
    // 上拨
    else if (adc >= (eep_keyADCUp - RANGE) && adc <= (eep_keyADCUp + RANGE))
      state = 2;
    // 下拨
    else if (adc >= (eep_keyADCDown - RANGE) && adc <= (eep_keyADCDown + RANGE))
      state = 3;
    // 无
    else state = 100;
    //Serial.printf("返回:%d\n\n",state);
  }
  return state;
}