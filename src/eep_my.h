enum
{
    page_jitterSet = 0,    // 抖动设置界面
    page_acc,              // 加速度界面
    page_clock,            // 时钟界面
    page_mainSet,          // 主设置界面
    page_networkConfig,    // 配网界面
    page_clockManualCal,   // 时钟手动校准界面
    page_clockSet,         // 时钟设置
    page_air,              // 空气质量界面
    page_uartAir,          // 串口空气质量界面
    page_alarmClock,       // 闹钟界面
    page_alarmClockEdit,   // 闹钟编辑界面
    page_buzzerSet,        // 蜂鸣器设置界面
    page_fileExplorer,     // 文件管理器主页
    page_fileExplorerMenu, // 文件管理器菜单
    page_batSOC,           // 电量计
    page_locateInfo,       // 定位
    page_stopwatch,        // 码表
    page_keyADCCali,       // 按键ADC校准
    page_picture,          // 图片查看
    page_memoSet,          // 备忘录设置界面
    page_memo,             // 备忘录界面
    page_frontLightSet,    // 前置光设置界面
    page_sleepSet,         // 休眠设置
    page_checkUpdate,      // 检查更新界面
    page_wifiSelect,       // wifi选择
    page_wifiSelectMenu,   // wifi选择菜单
    page_wanNianLi,        // 万年历界面
};

//****** EEPROM地址和定义 ******
#include <Preferences.h>
Preferences eep;
bool eep_init = 0;
uint8_t eep_disPage = page_jitterSet; // 显示哪个界面
bool eep_language = 0;                // 0-中文 1-英文
bool eep_doudong = 0;                 // 是否开启抖动
// String eep_sta_ssid = "Xiaomi 15";        // wifi名称
// String eep_sta_password = "112233445566"; // wifi密码
String eep_sta_ssid = F("Jones_ZTE");          // wifi名称
String eep_sta_password = F("J326513988.0.0"); // wifi密码
int8_t eep_timeZone = 8.0;                     // 时区
String eep_ntpAdd;                             // 自定义ntp地址
uint16_t eep_clockLWJG = 0;                    // 时钟联网校准间隔，0为不联网校准 ，单位分钟
float eep_fyxs = FYXS;                         // 电池分压系数

uint8_t eep_accDispMod = 1;       // 加速度计显示模式 0-原始数据 1-角度数据 2-原始滤波数据
uint8_t eep_clockSleep = 5;       // 时钟界面休眠时间 单位秒
uint8_t eep_otherSleep = 255;     // 其他界面休眠时间 单位秒
uint8_t eep_airSleep = 30;        // 空气质量界面休眠时间 单位分钟
bool eep_WU_TaiShou = 0;          // 抬手唤醒
bool eep_WU_AnDong = 1;           // 按动唤醒
bool eep_otherSleepOffScreen = 0; // 其他界面休眠息屏
bool eep_clockSleepOffScreen = 0; // 时钟界面休眠息屏
bool eep_sleepPicEn = 0;          // 休眠壁纸使能
bool eep_batSleepPicEn = 0;       // 低电休眠壁纸使能

#define LCD_COM_TIME 102 // lcd反转信号的占空比 0 - 1023
#define LCD_COM_FRE 60   // lcd反转信号频率 1-140 hz

bool eepSaveState = 0; // eeprom定时检查状态 0-不需要保存 1-需要保存

bool eep_buzzerEn = 1;        // 蜂鸣器使能
uint8_t eep_buzzerNote = 0;   // 音符
uint8_t eep_buzzerOctave = 8; // 音程
uint8_t eep_buzzerVolume = 5; // 音量

uint16_t eep_keyADCUp = 5000;   // 向上拨的ADC值
uint16_t eep_keyADCDown = 5000; // 向下拨的ADC值

String eep_sleepPic;    // 自定义休眠图片
String eep_batSleepPic; // 自定义低电量休眠图片
String eep_alarmSound;  // 自定义闹铃

String eep_inAWord = F("路漫漫其修远兮吾将上下而求索"); // 备忘录句子
uint8_t eep_memoBg = 5;   // 备忘录背景颜色
uint8_t eep_memoFC = 6;   // 备忘录字体颜色
bool eep_memoClockEn = 0; // 时钟显示备忘录 交替显示方式 1开启 0关闭
bool eep_memoSleepEn = 0; // 休眠时显示 1开启 0关闭

uint8_t eep_ledPwm = 50; // 前置光LEDPWM 0-1024
uint8_t eep_ledFre = 90; // 前置光LED频率
bool eep_ledEn = 0;      // 前置光LED使能
bool eep_ledAuto = 0;    // 前置光LED自动打开使能

String eep_mqttHost = F("homeassistant.local"); // mqtt主机
uint16_t eep_mqttPort = 1883;                   // mqtt端口
String eep_mqttUserName = F("gcsbs");           // mqtt服务器用户名
String eep_mqttPassword = F("123456");          // mqtt服务器密码
String eep_AQHA_DP = F("gc");                   // 空气质量HA的发现前缀

void eepSave();

void eeprom_init()
{
    // 名词不能超过14个字符
    eep.begin("eepUser", false);

    eep_init = eep.getBool("eep_init", 0); // 获取初始化状态 1-已初始化 0-未初始化

    if (eep_init == 0)
    {
        Serial.println("eepromPut");
        String xreep = F("正在写入EEPROM");
        Serial.println(xreep);

        eep.clear(); // 清除空间

        eepSave(); // 保存eeprom
        eep.putUChar("disPage", eep_disPage);            // 显示哪个界面
        eep.putBool("language", eep_language);           // 语言选择 0-中文 1-英文
        eep.putBool("doudong", eep_doudong);             // 是否开启抖动
        eep.putString("sta_ssid", eep_sta_ssid);         // wifi名称
        eep.putString("sta_password", eep_sta_password); // wifi密码
        eep.putChar("timeZone", eep_timeZone);           // 时区
        eep.putString("ntpAdd", eep_ntpAdd);             // 自定义ntp地址
        eep.putUInt("clockLWJG", eep_clockLWJG);         // 时钟联网校准间隔，0为不联网校准 ，单位分钟
        eep.putString("inAWord", eep_inAWord);           // 自定义句子

        eep.putUInt("keyADCUp", eep_keyADCUp);         // 向上拨的ADC值
        eep.putUInt("keyADCDown", eep_keyADCDown);     // 向下拨的ADC值
        eep.putString("batSleepPic", eep_batSleepPic); // 自定义低电休眠图片
        eep.putString("sleepPic", eep_sleepPic);       // 自定义休眠图片
        eep.putString("alarmSound", eep_alarmSound);   // 自定义闹铃

        eep.putString("mqttHost", eep_mqttHost);         // mqtt主机
        eep.putUShort("mqttPort", eep_mqttPort);         // mqtt端口
        eep.putString("mqttUserName", eep_mqttUserName); // mqtt服务器用户名
        eep.putString("mqttPassword", eep_mqttPassword); // mqtt服务器密码
        eep.putString("AQHA_DP", eep_AQHA_DP);           // 空气质量HA的发现前缀

        eep_init = 1; // 初始化成功

        eep.putBool("eep_init", eep_init);

        ESP.restart();
    }
    else
    {
        Serial.println("eepromGet");
        eep_disPage = eep.getUChar("disPage", eep_disPage);                         // 显示哪个界面
        eep_language = eep.getBool("language", eep_language);                       // 语言选择 0-中文 1-英文
        eep_sta_ssid = eep.getString("sta_ssid", eep_sta_ssid);                     // wifi名称
        eep_sta_password = eep.getString("sta_password", eep_sta_password);         // wifi密码
        eep_timeZone = eep.getChar("timeZone", eep_timeZone);                       // 时区
        eep_ntpAdd = eep.getString("ntpAdd", eep_ntpAdd);                           // 自定义ntp地址
        eep_clockLWJG = eep.getUInt("clockLWJG", eep_clockLWJG);                    // 时钟联网校准间隔，0为不联网校准 ，单位小时
        eep_accDispMod = eep.getUChar("accDispMod", eep_accDispMod);                // 加速度计显示模式 0-原始数据 1-角度数据 2-原始滤波
        eep_clockSleep = eep.getUChar("clockSleep", eep_clockSleep);                // 时钟界面休眠时间 单位秒
        eep_otherSleep = eep.getUChar("otherSleep", eep_otherSleep);                // 其他界面休眠时间 单位秒
        eep_airSleep = eep.getUChar("airSleep", eep_airSleep);                      // 空气质量界面休眠时间 单位分钟
        eep_WU_TaiShou = eep.getBool("WU_TaiShou", eep_WU_TaiShou);                 // 抬手唤醒
        eep_WU_AnDong = eep.getBool("WU_AnDong", eep_WU_AnDong);                    // 按动唤醒
        eep_otherSleepOffScreen = eep.getBool("otherSOS", eep_otherSleepOffScreen); // 其他界面休眠息屏
        eep_clockSleepOffScreen = eep.getBool("clockSOS", eep_clockSleepOffScreen); // 时钟界面休眠息屏
        eep_sleepPicEn = eep.getBool("sleepPicEn", eep_sleepPicEn);                 // 休眠壁纸使能
        eep_batSleepPicEn = eep.getBool("batSleepPicEn", eep_batSleepPicEn);        // 低电休眠壁纸使能

        eep_inAWord = eep.getString("inAWord", eep_inAWord); // 自定义句子

        eep_buzzerEn = eep.getBool("buzzerEn", eep_buzzerEn);              // 蜂鸣器使能
        eep_buzzerNote = eep.getUChar("buzzerNote", eep_buzzerNote);       // 音符
        eep_buzzerOctave = eep.getUChar("buzzerOctave", eep_buzzerOctave); // 音程
        eep_buzzerVolume = eep.getUChar("buzzerVolume", eep_buzzerVolume); // 音量

        eep_keyADCUp = eep.getUInt("keyADCUp", eep_keyADCUp);
        eep_keyADCDown = eep.getUInt("keyADCDown", eep_keyADCDown);

        eep_batSleepPic = eep.getString("batSleepPic", eep_batSleepPic); // 自定义低电休眠图片
        eep_sleepPic = eep.getString("sleepPic", eep_sleepPic);          // 自定义休眠图片
        eep_alarmSound = eep.getString("alarmSound", eep_alarmSound);    // 自定义闹铃

        eep_memoBg = eep.getUChar("memoBg", eep_memoBg);               // 备忘录背景颜色
        eep_memoFC = eep.getUChar("memoFC", eep_memoFC);               // 备忘录字体颜色
        eep_memoClockEn = eep.getBool("memoClockEn", eep_memoClockEn); // 时钟显示备忘录 交替显示方式
        eep_memoSleepEn = eep.getBool("memoSleepEn", eep_memoSleepEn); // 休眠时显示 1开启 0关闭

        eep_ledPwm = eep.getUChar("ledPwm", eep_ledPwm);   // 前置光LEDPWM 0-255
        eep_ledFre = eep.getUChar("ledFre", eep_ledFre);   // 前置光LED频率
        eep_ledEn = eep.getBool("ledEn", eep_ledEn);       // 前置光LED使能
        eep_ledAuto = eep.getBool("ledAuto", eep_ledAuto); // 前置光自动打开使能

        eep_mqttHost = eep.getString("mqttHost", eep_mqttHost);             // mqtt主机
        eep_mqttPort = eep.getUShort("mqttPort", eep_mqttPort);             // mqtt端口
        eep_mqttUserName = eep.getString("mqttUserName", eep_mqttUserName); // mqtt服务器用户名
        eep_mqttPassword = eep.getString("mqttPassword", eep_mqttPassword); // mqtt服务器密码
        eep_AQHA_DP = eep.getString("AQHA_DP", eep_AQHA_DP);                // 空气质量HA的发现前缀

        eep.end();
    }
}

void eepSave() // 保存eeprom
{
    // 写入数据 注意：命名空间名称限制为15个字符。
    if (eep_disPage == page_frontLightSet || eep_init == 0)
    {
        eep.putUChar("accDispMod", eep_accDispMod); // 加速度计显示模式 0-原始数据 1-角度数据 2-原始滤波
    }
    if (eep_disPage == page_sleepSet || eep_init == 0)
    {
        eep.putUChar("clockSleep", eep_clockSleep);       // 时钟界面休眠时间 单位秒
        eep.putUChar("otherSleep", eep_otherSleep);       // 其他界面休眠时间 单位秒
        eep.putUChar("airSleep", eep_airSleep);           // 空气质量界面休眠时间 单位分钟
        eep.putBool("WU_TaiShou", eep_WU_TaiShou);        // 抬手唤醒
        eep.putBool("WU_AnDong", eep_WU_AnDong);          // 按动唤醒
        eep.putBool("otherSOS", eep_otherSleepOffScreen); // 其他界面休眠息屏
        eep.putBool("clockSOS", eep_clockSleepOffScreen); // 时钟界面休眠息屏
        eep.putBool("sleepPicEn", eep_sleepPicEn);        // 休眠壁纸使能
        eep.putBool("batSleepPicEn", eep_batSleepPicEn);  // 低电休眠壁纸使能
    }
    if (eep_disPage == page_buzzerSet || eep_init == 0)
    {
        eep.putBool("buzzerEn", eep_buzzerEn);          // 蜂鸣器使能
        eep.putUChar("buzzerNote", eep_buzzerNote);     // 音符
        eep.putUChar("buzzerOctave", eep_buzzerOctave); // 音程
        eep.putUChar("buzzerVolume", eep_buzzerVolume); // 音量
    }
    if (eep_disPage == page_memoSet || eep_init == 0)
    {
        eep.putUChar("memoBg", eep_memoBg);           // 备忘录背景颜色
        eep.putUChar("memoFC", eep_memoFC);           // 备忘录字体颜色
        eep.putUChar("memoClockEn", eep_memoClockEn); // 时钟显示备忘录 交替显示方式
        eep.putBool("memoSleepEn", eep_memoSleepEn);  // 休眠时显示 1开启 0关闭
    }
    if (eep_disPage == page_frontLightSet || eep_init == 0)
    {
        eep.putUChar("ledPwm", eep_ledPwm);  // 前置光LEDPWM 0-255
        eep.putUChar("ledFre", eep_ledFre);  // 前置光LED频率
        eep.putBool("ledEn", eep_ledEn);     // 前置光LED使能
        eep.putBool("ledAuto", eep_ledAuto); // 前置光自动打开使能
    }
}

void eepSave_fixedTime() // 定时检查eeprom是否需要保存
{
    if (eepSaveState == 0) return;
    eepSaveState = 0;
    eep.begin("eepUser", false);
    eepSave();
    eep.end();
    Serial.println("保存eeprom");
}

void eepSavePage(uint8_t page, bool save) // 保存界面位置
{
    RTC_disPage_old = eep_disPage; // 保存现在的界面到存储
    eep_disPage = page;
    if (save)
    {
        eep.begin("eepUser", false);
        eep.putUChar("disPage", eep_disPage); // 显示哪个界面
        eep.end();
    }
}