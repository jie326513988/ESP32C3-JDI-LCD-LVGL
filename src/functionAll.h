void jdi_init();
void lvgl_init();
void i2c_begin();
void backstageManagement();
void backstageManagement_rtos_init();
void backstageManagement_rtos(void *param);

//****** eep_my.h
void eeprom_init();
void eepSave();           // 保存eeprom
void eepSave_fixedTime(); // 定时检查eeprom是否需要保存
void eepSavePage(uint8_t page, bool save = 1);

//****** imageProcessing.h
uint16_t create_rgb565(uint8_t r, uint8_t g, uint8_t b);
uint16_t create_rgb565(float f_r, float f_g, float f_b);
uint8_t create_rgb332(uint8_t r, uint8_t g, uint8_t b);
void modify_pixel_color(uint8_t *color_p, int16_t x, int16_t y, uint16_t new_color);
void modify_pixel_color(uint8_t *color_p, uint32_t pixel_offset, uint16_t new_color);
uint32_t getPixelIdx(int32_t x, int32_t y);
uint8_t colorThresholdLimit(uint8_t val1, int8_t val2,uint8_t max); // 颜色阈值限制

//****** acc.h
bool acc_6d();
bool acc_continRefresh(); // 连续采集模式
bool acc_wakeUp();        // 休眠唤醒模式
void acc_test_loop();
void accRead_rtos_init();
void accRead_rtos(void *param);
void accInterrupt();

//****** my_sgp41.h
void sgp41_init();
void sgp41_readSRAW();
void spg41_get_tuning_parameters();
void sgp41_readIndex();
void airRead_rtos_init();
void airRead_rtos(void *param);


//****** buzzer.h
void buzzer_init();
void buzzer_rtos_init();
void buzzer_rtos(void *param);
void buzzerSen(int16_t time);
void buzzer_setNote(int8_t note_in = -1, int8_t octave_in = -1);

//BaseType_t buzzer_music_rtos_init(void *p);
//BaseType_t buzzer_music_rtos_init(uint16_t *music, BuzzerCallback callback = NULL);
void buzzer_music_rtos(void *p);
void buzzer_active();   // 积极
void buzzer_negative(); // 消极

//****** key.h
uint8_t getKey();

//****** clock8010.h
void clock_read();                                        // 读取时钟芯片的时间
bool clockChipReadCheck();                                // 读取时钟数据是否正常 0错误 1正常
bool clockChipPowerDown();                                // 检查是否掉电了 0错误 1正常
bool ntpConnect();                                        // ntp连接程序 0-失败 1-成功
bool ntpToClockChip();                                    // 将NTP数据写入时钟芯片内
void getNTPDate(uint32_t timeStamp, struct ntpDate *jgt); // 获取NTP的日期
bool isLeapYear(uint16_t year);                           // 判断是否闰年
String weekDigitalToChinese(uint8_t digital);             // 星期数字1234567转中文
uint8_t monthHowManyDay(uint16_t year, uint16_t month);   // 获取月有多少天
void clockAutoCali_rtos_init();       // 创建时钟自动校准任务
void clockAutoCali_rtos(void *param); // 时钟自动校准任务
void clockRead_rtos_init();           // 创建时钟读取任务
void clockRead_rtos(void *param);     // 时钟读取任务

//****** STA_AT_OTA.h
bool connectToWifi(); // 连接wifi
void initApSTA();
void initApSTANoBegin();
void initAp();
bool scanNetworks(String currentSSID);

//****** batAndTempRead.h
void get_bat_vcc_rtos_init();
void get_bat_vcc_rtos(void *param);
float batVccToPer(float batVcc); // 电池电压转换百分比
void cupTempInit();              // cpu温度初始化

//****** networkConfig.h
void networkConfig_rtos_init();
void networkConfig_rtos(void *param);
void display_networkConfig_init();

//****** WEBServer1.h
void initWebServer();
void webNotFound();             // 设置处理404情况的函数'webUserRequest'
void webRoot();                 // 处理网站根目录"/"的访问请求
void webFileUpload();           // 上传至文件系统
void webRead_fileSync();        // 文件系统剩余内存
void webRootPost();             // WIFI保存
void webRead_scanWifi();        // 扫描周边wifi
void webRead_scanWifiHistory(); // 发送历史扫描记录
void webInAWord();
void webReadInAWord(); // 读取多能能输入框状态和内容

void web_submit_MQTT_port();
void web_get_MQTT_port(); 

void web_submit_MQTT_host();
void web_get_MQTT_host(); 

void web_submit_MQTT_userName();
void web_get_MQTT_userName(); 

void web_submit_MQTT_password();
void web_get_MQTT_password(); 

void web_submit_AQHA_DP();
void web_get_AQHA_DP(); 

void webRead_staNameIp();
void webRead_updataAddress();
void webRead_info();
void webRESET();
void reset_peiwang();
String sendHTML_main();
String getContentType(String filename);
bool getSystemFile(String fileName);

void replyOK();
void replyOKWithMsg(String msg);
void replyNotFound(String msg);
void replyBadRequest(String msg);
void replyServerError(String msg);
bool existsEdit(String path);
bool exists(fs::FS &fs, String path);

void handleStatus();
void handleFileList();
bool handleFileRead(String path);
String lastExistingParent(String path);
void handleFileCreate();
// void deleteRecursive(String path);
void handleFileDelete();
void handleFileUpload();
void handleGetEdit();
bool serverFlieSDInit(); // 网页文件管理器文件挂载

//****** other.h
String getlineNumStr(fs::FS &fs, String dir, uint16_t line, bool mode = 0);
uint32_t getEspChipId(); // 获取芯片ID
String getEspChipId_str();
String integrationPath(String dir, String name);
void structClear(unsigned char *pta, int size);
bool i2cChipExist(uint8_t add);
uint8_t fileFormat(String Name);
String removeDirectoryName(String z);
String removeDirectoryName(const char *z);
String extractPath(String z);
String qchz(String in);               // 去除后缀
String byteConversion(size_t bytes);  // 字节换算
String byteConversion2(size_t bytes); // 字节换算
//日期增减
void dateAddSub(int16_t &year, int8_t &month, int8_t &day, int8_t dayAdd);
String autoLineFeed(const char *inAWord, uint16_t pixelValue, const lv_font_t *font, uint8_t *line);
const char *extractPasswordFromFile(const char *filePath, int targetLine);

//****** PowerManagement.h
void esp_sleep(unsigned long minutes, bool skip = 1); // 默认跳过闹钟
void gpio_hold(bool en);
uint8_t print_wakeup_reason();
void dormantTimeoutDecision();

//****** myLVGLDemo.h
void demo_label();
void demo_img();
void demo_gif();

// 在事件内添加动画，动画不会重叠
bool addAnimation_event(lv_obj_t *obj1, void (*animFunctions)(lv_obj_t *obj2), lv_anim_exec_xcb_t exec_cb = NULL);

//弹窗动画
void my_msgbox_exit(uint32_t delay_ms);
void my_msgbox_forceSend(String title_in, String text_in, uint16_t time = 0,
                         String button = "", lv_event_cb_t event_cb = NULL);
void my_msgbox_send(String title_in, String text_in, uint16_t time = 0,
                    String button = "", lv_event_cb_t event_cb = NULL);
void my_msgbox(String title, String text, uint16_t time = 0,
               String button = "", lv_event_cb_t event_cb = NULL);
void my_msgbox_loop();

uint8_t pageInit(bool key, bool first);
void pageStartupEnters(); // 开机时进入哪个界面
void exitToMainSet();
void backPage_mainSet(lv_event_t *e);
void backPage_mainSet_event(lv_event_t *e);
void button_width_shrink_anim_init(lv_obj_t *obj);      // 按键横向向内收缩初始化
void button_width_shrink_anim_cb(void *var, int32_t v); // 按钮横向收缩动画
void markAnimIdle(lv_anim_t *a);                        // 标记动画空闲
void button_width_shrink_anim_end_cb(lv_anim_t *a);     // 按钮横向收缩动画结束回调
void onGlobalJitter(uint16_t time = 0);                 // 定时开启全局抖动
void offGlobalJitter_anim_cb(lv_anim_t *a);             // 关闭全局抖动
void offGlobalJitter_timer_cb(lv_timer_t *e);           // 关闭全局抖动
void offGlobalJitter_event_cb(lv_event_t *e);           // 关闭全局抖动
void buttonFocus_anim_event(lv_event_t *e);             // 按钮按下播放动画的事件
void label_x_bounce_anim_init(lv_obj_t *obj, int16_t val);
void label_x_bounce_anim_cb(void *var, int32_t v);
void label_y_bounce_anim_init(lv_obj_t *obj, int16_t val);
void label_y_bounce_anim_cb(void *var, int32_t v);

void focusPosOld_return();                              // 获取上一个界面的焦点索引值
void focusPosOld_save();                                // 保存上一个界面的焦点索引值

void display_jitterSet_event(lv_event_t *e);
void display_jitterSet_init();

void display_screenSaver_init();

void display_mainSet_init();

void display_acc_event(lv_event_t *e);
void display_acc_init();

void clockTimedWakeUp_time_cb(lv_timer_t *t);
void sleep_zero_time_cb(lv_timer_t *a);

void display_clock_event(lv_event_t *e);
void display_clock_init();
void display_clockManualCal_init();
void display_clockSet_init();

void display_air_event_msgbox(lv_event_t *e);
void display_air_init();

uint8_t getAlarmClockNumber(); // 获取闹钟的数量
void display_alarmClock_init();
void display_alarmClock_edit_init();
void buzzerMonitor_end_cb(lv_event_t *e); //  闹钟监测 弹窗退出

void display_buzzerSet_init();

void fileManagerInit(bool ergodic);
void display_fileExplorer_init();

void display_fileExplorerMenu_init();

void display_batSOC_init();

void display_locateInfo_init();

void display_stopwatch_init();

void display_keyADC_cali_init();

void display_memoSet_init();

void display_memo_init();

void display_frontLightSet_init();

void display_sleepSet_init();



void display_wifiSelect_init(String content);
void display_wifiSelectMenu_init();
//文件编辑 删除指定行 从0开始
bool fileEdit_deleteRow(fs::FS &fs, const char *record, uint8_t row);
//文件编辑 置顶指定行 从0开始
bool fileEdit_moveToTop(fs::FS &fs, const char *record, uint8_t row);
void box2d_world_init();

lv_point_precise_t *my_draw_rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

//****** alarmClock.h
void updatealarmClockDifference(bool mod = false); // 更新闹钟时间差
// 闹钟计寻找最小的时间差, mod 0返回最小的正值 1返回绝对值最小的值
int32_t alarmClockTimeDifference(bool mod);
void buzzerMonitor(); // 闹钟监测

//****** my_audio.h
void i2s_init();
void releaseAudioMemory();
void i2s_playSpecified(String in);
void i2s_music_rtos_init();
void i2s_music_rtos(void *param);

//****** my_ens160.h
bool ens160_init();
void ens160_init2();
void read_ens160_rtos_init();
void read_ens160_rtos(void *param);

//****** midiToBuzzer.h
BaseType_t midi_rtos_init(void *p);
void midiTask(void *p);
uint16_t read16_B(File& f); // 大端模式，读取数据由高到低
uint32_t read32_B(File& f); // 大端模式，读取数据由高到低
// 音符映射，输入midi的音符，输出音调和音符
void noteMap(uint8_t in, uint8_t &tone, uint8_t &note);
//midi运行
void midiRun(String midName);
// midi解析
//void midiAnalysis(File &f, MIDI &midi);
void stopMidi();//停止

//****** my_max17048.h
void max17048_init();
void max17048_Compensation();

//****** navigationSystem.h
//void NMEA0183(String in);              // 解析总协议
//void analysisRMC(String in, RMC *rmc); // 解析RMC消息 (推荐最小定位信息)
void locateInfo_rtos_init();
void locateInfoRead_rtos(void *param);

//****** my_ambientLight.h
void ambientLight_rtos_init();

void display_checkUpdate_init(String version, String content);
void checkUpdate_rtos_init();

//****** my_airQuality.h
void display_uartAir_init();

//******* my_mqtt.h
void mqtt_rtos_init();