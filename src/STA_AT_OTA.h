/*** 初始化STA配置 ***/
bool connectToWifi() // 连接wifi
{
  // WiFi.persistent(true);
  // WiFi.disconnect();      //断开WIFI连接,清掉之前最近一个连接点信息
  // WiFi.mode(WIFI_OFF);    //设置工作模式
  WiFi.setAutoConnect(1); // 设置自动连接wifi
  WiFi.mode(WIFI_STA);    // 设置工作模式
  WiFi.begin(eep_sta_ssid, eep_sta_password); // 要连接的WiFi名称和密码
  uint8_t count = 0;
  //wifiConnectSkip = wifi跳过 由按键中断控制clockSkip()
  while (!WiFi.isConnected()) // 尝试连接 
  {
    overTime = 0;
    delay(800);
    count++;
    if (count == 6)
    {
      WiFi.mode(WIFI_OFF);
      delay(800);
      WiFi.mode(WIFI_STA);
      WiFi.begin(eep_sta_ssid, eep_sta_password);
    }
    else if (count > 12) return 0; // 连接失败
  } 
  if (WiFi.isConnected()) return 1; //连接成功
  return 0;
}

/*** 初始化AP配置 ***/
void initApSTA()
{
  // WiFi.persistent(true);
  WiFi.mode(WIFI_AP_STA);                                 // 设置工作模式
  WiFi.softAPConfig(local_IP, gateway, subnet);           // ap的网络参数
  WiFi.softAP(ap_ssid, ap_password, random(1, 14), 0, 1); // ap的名称、密码、信道、是否隐藏、同时连接数
  char ssid[32];
  char password[64];
  strcpy(ssid, eep_sta_ssid.c_str());
  strcpy(password, eep_sta_password.c_str());
  //strcpy(ssid, String("ACE 2").c_str());
  //strcpy(password, String("112233445566").c_str());
  WiFi.begin(ssid, password); // 要连接的WiFi名称和密码
}
void initApSTANoBegin()
{
  // WiFi.persistent(true);
  WiFi.mode(WIFI_AP_STA);                                 // 设置工作模式
  WiFi.softAPConfig(local_IP, gateway, subnet);           // ap的网络参数
  WiFi.softAP(ap_ssid, ap_password, random(1, 14), 0, 2); // ap的名称、密码、信道、是否隐藏、同时连接数
}
void initAp()
{
  // WiFi.persistent(true);
  // WiFi.mode(WIFI_OFF);   //设置工作模式
  WiFi.softAPConfig(local_IP, gateway, subnet);           // ap的网络参数
  WiFi.softAP(ap_ssid, ap_password, random(1, 14), 0, 2); // ap的名称、密码、信道、是否隐藏、同时连接数
  WiFi.mode(WIFI_AP);                                     // 设置工作模式
}

//********* 扫描周边网络 0-扫描到 1-无
bool scanNetworks(String currentSSID)
{
  bool scanState = 0;           // 扫描状态，0-扫描到 1-无
  uint8_t n = WiFi.scanNetworks(); // 扫描wifi
  if (n == 0)
    scanState = 0; // 扫描不到开启ap模式
  else
  {
    for (uint8_t i = 0; i < n; i++)
    {
      // Serial.println(WiFi.SSID(i));
      if (strcmp(currentSSID.c_str(), WiFi.SSID(i).c_str()) == 0)
        scanState = 1;
      else if (scanState != 1 && strcmp(currentSSID.c_str(), WiFi.SSID(i).c_str()) != 0)
        scanState = 0;
    }
  }
  WiFi.setAutoConnect(1); // 调回自动连接
  WiFi.scanDelete();      // 删除扫描的结果
  return scanState;
}

// WiFi.mode(); WIFI_AP /WIFI_STA /WIFI_AP_STA /WIFI_OFF

//****** OTA设置并启动 ******
// ArduinoOTA.handle();
/*void initOTA()
  {
  ArduinoOTA.setHostname("esp8266");
  ArduinoOTA.setPassword("333333");
  ArduinoOTA.begin();
  }*/
