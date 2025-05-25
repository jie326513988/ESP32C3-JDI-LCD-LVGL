note_t note[12] = {NOTE_C, NOTE_Cs, NOTE_D, NOTE_Eb, NOTE_E, NOTE_F, NOTE_Fs, NOTE_G, NOTE_Gs, NOTE_A, NOTE_Bb, NOTE_B};
const uint16_t noteFrequencyBase[12] = {
    4186, // C
    4435, // C#
    4699, // D
    4978, // Eb
    5274, // E
    5588, // F
    5920, // F#
    6272, // G
    6645, // G#
    7040, // A
    7459, // Bb
    7902, // B
};

bool buzzerSending = 0; // 发送中
bool buzzerRun = 0;     // 运行中
int16_t buzzerTime = 0; // 发声时长
uint16_t buzzerNum = 0; // 循环数量

void buzzer_init()
{
    // 蜂鸣器初始化
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, 0);
    uint32_t noteFreq = (uint32_t)noteFrequencyBase[eep_buzzerNote] / (uint32_t)(1 << (8 - eep_buzzerOctave));
    ledcSetup(BUZZER_CHANNEL, noteFreq, 10);   // 通道，频率，分辨率
    ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL); // 映射引脚，通道
    ledcWrite(BUZZER_CHANNEL, 0);              // 占空比
}

void buzzer_rtos_init() // 
{
  xTaskCreatePinnedToCore(
      buzzer_rtos, /* 任务指针，创建任务用的那个函数名 */
      "buzzer",    /* 任务名称 */
      4 * 1024,    /* 任务栈大小，根据需要自行设置*/
      NULL,        /* 可选参数，一般不填*/
      2,           /* 优先级 */
      &TH_buzzer,  /* 任务句柄，用于后续挂起或恢复运行*/
      0            /* 核ID */
  );
}

uint32_t btime1;
void buzzer_rtos(void *param) // 
{
  buzzer_init();
  for(;;)
  {
    if (!bitRead(backgroundTask, BGT_BUZZER))
    {
      ledcWrite(BUZZER_CHANNEL, 0);
      ledcDetachPin(BUZZER_CHANNEL); // 卸载引脚
      Serial.println("删除TH_buzzer");
      TH_buzzer = NULL;
      vTaskDelete(NULL);
    }

    if (buzzerSending == 1)
    {
      buzzerRun = 1; // 标记运行中
      //btime1 = micros();
      //ledcWriteNote(BUZZER_CHANNEL, NOTE_F, 6);
      //Serial.printf("耗时：%d\n", micros() - btime1);
      static uint16_t volume[5] = {150, 200, 250, 300, 400};
      //Serial.print("volume["+String(eep_buzzerVolume - 1)+"]:");
      //Serial.println(volume[eep_buzzerVolume - 1]);
      ledcWrite(BUZZER_CHANNEL, volume[eep_buzzerVolume - 1]); // eep_buzzerVolume
      buzzerSending = 0; //发送结束
    }

    // 发声时间计算
    if (buzzerTime > 0)
    {
      buzzerTime -= 5;
      if (buzzerTime <= 0)
      { 
        ledcWrite(BUZZER_CHANNEL, 0);
        buzzerTime = 0;
        buzzerRun = 0; // 运行中结束
      }
    }

    delay(5);
  }
}

uint32_t bTime = 0;
void buzzerSen(int16_t time)
{
  if(midi.run == 1)     return;
  if(eep_buzzerEn == 0) return;
  if(buzzerRun == 1)    return;
  //if(millis() - bTime < 200) return;
  //bTime = millis();
  buzzerSending = 1;
  buzzerTime = time; // 时间
}
void buzzer_setNote(int8_t note_in, int8_t octave_in)
{
  if(midi.run == 1)     return;
  if(buzzerRun == 1)    return;

  uint8_t note,octave;
  if (note_in > -1) note = note_in;
  else note = eep_buzzerNote;

  if (octave_in > -1) octave = octave_in;
  else octave = eep_buzzerOctave;

  uint32_t noteFreq = (uint32_t)noteFrequencyBase[note] / (uint32_t)(1 << (8 - octave));
  ledcSetup(BUZZER_CHANNEL, noteFreq, 10); // 通道，频率，分辨率
  // Serial.printf("noteFreq:%d\n", noteFreq);
}

//********** 音乐队列 输入格式为 频率，时长，延时，0为结束符
//定义一个蜂鸣器回调
typedef void (*BuzzerCallback)(void);
// 参数结构体
typedef struct
{
  uint16_t *music;         // 音乐队列
  BuzzerCallback callback; // 播放完成的回调函数
} BuzzerTaskParams;

BaseType_t buzzer_music_rtos_init(uint16_t *music, BuzzerCallback callback = NULL);

BaseType_t buzzer_music_rtos_init(uint16_t *music, BuzzerCallback callback)
{
  // 分配任务参数
  BuzzerTaskParams *params = (BuzzerTaskParams *)malloc(sizeof(BuzzerTaskParams));
  if (params == NULL)
  {
    return pdFAIL; // 内存分配失败
  }

  params->music = music;
  params->callback = callback;

  // 创建蜂鸣器音乐任务
  return xTaskCreate(
      buzzer_music_rtos, // 任务入口函数
      "buzzer_music",    // 任务名称
      4 * 1024,          // 任务栈大小
      params,            // 任务参数
      3,                 // 优先级
      NULL               // 不需要任务句柄
  );
}
void buzzer_music_rtos(void *p)
{
  // 获取任务参数
  BuzzerTaskParams *params = (BuzzerTaskParams *)p;
  uint16_t *music = params->music;
  BuzzerCallback callback = params->callback;
  uint16_t index = 0;

  buzzer_init();

  for (;;)
  {
    if (music[index] == 0) // 检测结束符
    {
      free(music);      // 释放动态内存
      buzzer_setNote(); // 恢复默认蜂鸣器状态

      if (callback != NULL)
      {
        callback(); // 调用播放完成回调函数
      }

      free(params);      // 释放参数内存
      vTaskDelete(NULL); // 删除当前任务
    }

    // 配置蜂鸣器频率和时长
    if (music[index] != 1)
    {
      ledcSetup(BUZZER_CHANNEL, music[index], 10);
      buzzerSen(music[index + 1]);
    }
    // 延时播放
    delay(music[index + 1] + music[index + 2]);

    index += 3; // 跳转到下一个音符
  }
}

void buzzer_active() // 积极
{
  uint16_t *melody = (uint16_t *)malloc(7 * sizeof(uint16_t));
  melody[0] = 4400; melody[1] = 100; melody[2] = 50;  // C4 262
  melody[3] = 4700; melody[4] = 100; melody[5] = 50;  // D4 294
  melody[6] = 0; 
  buzzer_music_rtos_init(melody);
}
void buzzer_negative() // 消极
{
  uint16_t *melody = (uint16_t *)malloc(7 * sizeof(uint16_t));
  melody[0] = 4700; melody[1] = 100; melody[2] = 50;  // C4 262
  melody[3] = 4400; melody[4] = 100; melody[5] = 50;  // D4 294
  melody[6] = 0; 
  buzzer_music_rtos_init(melody);
}
/*void buzzer_negative() // 备忘录进入
{
  uint16_t *melody = (uint16_t *)malloc(7 * sizeof(uint16_t));
  melody[0] = 4700; melody[1] = 100; melody[2] = 50;  // C4 262
  melody[3] = 4400; melody[4] = 100; melody[5] = 50;  // D4 294
  melody[6] = 0; 
  buzzer_music_rtos_init(melody);
}*/