// I2S初始化 BUZZER_PIN
void i2s_init()
{
    i2s = new AudioOutputI2SNoDAC(); // 软件DACS
    i2s->SetOutputModeMono(true);              // 单声道
    i2s->SetGain(.8);                           // 设置音量
    //i2s->SetOversampling(64);
    sf2 = new AudioFileSourceLittleFS("/Piano.sf2");

    //i2s->SetOversampling(256);
    /*i2s = new AudioOutputI2S(0, 0, 128, 0); // 使用外置DAC芯片
    i2s->SetMclk(false);                    // 无Mclk
    i2s->SetPinout(-1, -1, BUZZER_PIN);
    i2s->SetGain(1);*/
}

// 释放音频内存
void releaseAudioMemory()
{
  // 停止播放
  if (audioOut && audioOut->isRunning())
  {
    //out->flush();
    audioOut->stop();
    delete audioOut;
    audioOut = NULL;
  }
  if (musicFile)
  {
    musicFile->close();
    delete musicFile;
    musicFile = NULL;
  }

}

// 播放文件，输入文件的路径
void i2s_playSpecified(String in)
{
    releaseAudioMemory(); // 释放音频内存

    musicFile = new AudioFileSourceLittleFS(in.c_str());
    bool f = musicFile->open(in.c_str());
    if (!f)
    {
        musicFile->close();
        Serial.print("打开错误：");
        Serial.println(in);
        Serial.println();
    }
    else
    {
        Serial.print("打开成功：");
        Serial.println(in);
        Serial.println();
    }
    // audioOut = new AudioGeneratoraudioOut();
    //audioOut = new AudioGeneratorMP3();
    audioOut = new AudioGeneratorMIDI();
    audioOut->SetSoundfont(sf2);
    audioOut->SetSampleRate(24000); //11025 22050 24000 44100 48000
    // id3 = new AudioFileSourceID3(musicFile);
    audioOut->begin(musicFile, i2s);
}

// I2S音频任务初始化
void i2s_music_rtos_init() //
{
    xTaskCreatePinnedToCore(
        i2s_music_rtos, /* 任务指针，创建任务用的那个函数名 */
        "i2s_music",    /* 任务名称 */
        8 * 1024,       /* 任务栈大小，根据需要自行设置 */
        NULL,           /* 可选参数，一般不填 */
        1,              /* 优先级 */
        NULL,           /* 任务句柄，用于后续挂起或恢复运行 */
        0               /* 核ID */
    );
}

//I2S音频任务循环
void i2s_music_rtos(void *param)
{
    i2s_init();
    for (;;)
    {
        // 检查任务
        if (audioOut && audioOut->isRunning())
        {
            if (!audioOut->loop())
            {
                audioOut->stop();
                delete audioOut;
                audioOut = NULL;
            }
        }
        vTaskDelay(1);
    }
}