#include <AsyncMqttClient.h>

#define MQTT_HOST IPAddress(172, 1, 7, 177)
#define MQTT_PORT 1883

AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;
uint8_t mqtt_connect = 0;    // mqtt连接状态 0-未连接未初始化 1-已初始化但未连接 2-已连接
bool mqtt_deviceRelease = 0; // mqtt设备发布 0-未发布 1-已发布
bool mqtt_send = 0;          // 发送 0-不发送 1-发送

void MQTT_airQualityReleaseDevice() //发布设备
{
  if (eep_AQHA_DP.length() == 0) return;
  String topic; // 发现的主题
  String esp32Id = getEspChipId_str();
  String output;
  
  JsonDocument doc;
  doc["name"] = F("温度");
  doc["state_topic"] = F("airQuality/data");
  doc["device_class"] = F("temperature");
  doc["unit_of_measurement"] = F("°C");
  doc["value_template"] = F("{{value_json.temperature}}");
  doc["unique_id"] = esp32Id + "_t";
  JsonObject device = doc["device"].to<JsonObject>();
  device["name"] = F("空气质量(5合1)");
  device["model"] = F("SYS02");
  device["model_id"] = F("saiya(赛亚)");
  device["manufacturer"] = F("甘草酸不酸");
  device["identifiers"][0] = esp32Id;
  doc.shrinkToFit();
  serializeJson(doc, output);
  topic = eep_AQHA_DP;
  topic += F("/sensor/airQuality_t/config");
  mqttClient.publish(topic.c_str(), 0, true, output.c_str());
   //Serial.println("发布温度");
  //Serial.println(output);
  //Serial.println();
  delay(500);
  device.clear();
  doc.clear();
  output.clear();

  doc["name"] = F("湿度");
  doc["state_topic"] = F("airQuality/data");
  doc["device_class"] = F("humidity");
  doc["unit_of_measurement"] = F("%");
  doc["value_template"] = F("{{value_json.humidity}}");
  doc["unique_id"] = esp32Id + "_h";
  device = doc["device"].to<JsonObject>();
  device["identifiers"][0] = esp32Id;
  doc.shrinkToFit();
  serializeJson(doc, output);
  topic = eep_AQHA_DP;
  topic += F("/sensor/airQuality_h/config");
  mqttClient.publish(topic.c_str(), 0, true, output.c_str());
  //Serial.println("发布湿度");
  //Serial.println(output);
  //Serial.println();
  delay(500);
  device.clear();
  doc.clear();
  output.clear();

  doc["name"] = F("CO2");
  doc["state_topic"] = F("airQuality/data");
  doc["device_class"] = F("carbon_dioxide");
  doc["suggested_display_precision"] = 0;
  doc["unit_of_measurement"] = F("ppm");
  doc["value_template"] = F("{{value_json.co2}}");
  doc["unique_id"] = esp32Id + "_co2";
  device = doc["device"].to<JsonObject>();
  device["identifiers"][0] = esp32Id;
  doc.shrinkToFit();
  serializeJson(doc, output);
  topic = eep_AQHA_DP;
  topic += F("/sensor/airQuality_co2/config");
  mqttClient.publish(topic.c_str(), 0, true, output.c_str());
  //Serial.println("发布CO2");
  //Serial.println(output);
  //Serial.println();
  delay(500);
  device.clear();
  doc.clear();
  output.clear();

  doc["name"] = F("TVOC");
  doc["state_topic"] = F("airQuality/data");
  doc["device_class"] = F("aqi");
  doc["suggested_display_precision"] = 2;
  doc["unit_of_measurement"] = F("mg/m³");
  doc["value_template"] = F("{{value_json.tvoc}}");
  doc["unique_id"] = esp32Id + "_tvoc";
  device = doc["device"].to<JsonObject>();
  device["identifiers"][0] = esp32Id;
  doc.shrinkToFit();
  serializeJson(doc, output);
  topic = eep_AQHA_DP;
  topic += F("/sensor/airQuality_tvoc/config");
  mqttClient.publish(topic.c_str(), 0, true, output.c_str());
  //Serial.println("发布TVOC");
  //Serial.println(output);
  //Serial.println();
  delay(500);
  device.clear();
  doc.clear();
  output.clear();

  doc["name"] = F("甲醛");
  doc["state_topic"] = F("airQuality/data");
  doc["device_class"] = F("aqi");
  doc["suggested_display_precision"] = 2;
  doc["unit_of_measurement"] = F("mg/m³");
  doc["value_template"] = F("{{value_json.hcho}}");
  doc["unique_id"] = esp32Id + "_hcho";
  device = doc["device"].to<JsonObject>();
  device["identifiers"][0] = esp32Id;
  doc.shrinkToFit();
  serializeJson(doc, output);
  topic = eep_AQHA_DP;
  topic += F("/sensor/airQuality_hcho/config");
  mqttClient.publish(topic.c_str(), 0, true, output.c_str());
  //Serial.println("发布甲醛");
  //Serial.println(output);
  //Serial.println();
  delay(500);
  device.clear();
  doc.clear();
  output.clear();

  mqtt_deviceRelease = 1; // 标记设备已发布完成
}

// 连接mqtt
void connectToMqtt()
{
  Serial.println("连接到MQTT...");
  mqttClient.connect();
}

// WiFi事件
void WiFiEvent(WiFiEvent_t event)
{
  Serial.printf("[WiFi-event] 事件: %d\n", event);
  switch (event)
  {
  case SYSTEM_EVENT_STA_GOT_IP: //ESP32站从连接的AP获得IP
    Serial.println("WiFi已连接");
    Serial.println("IP 地址: ");
    Serial.println(WiFi.localIP());
    connectToMqtt();
    break;
  case SYSTEM_EVENT_STA_DISCONNECTED: //ESP32站与AP断开连接
    Serial.println("WiFi连接中断");
    xTimerStop(mqttReconnectTimer, 0); // 确保在重新连接到Wi-Fi时不会重新连接到MQTT
    xTimerStart(wifiReconnectTimer, 0);
    break;
  }
}

// MQTT 连接成功回调
void onMqttConnect(bool sessionPresent)
{
  Serial.println("已连接到MQTT.");
  Serial.print("当前会话: ");
  Serial.println(sessionPresent);
  mqtt_connect = 2;

  /*
  uint16_t packetIdSub = mqttClient.subscribe("hand_punch/sz", 0);
  Serial.print("订阅QoS 0, packeId: ");
  Serial.println(packetIdSub);
  Serial.println();
  Serial.println("-----------------------");
  */

  //mqttClient.publish("hand_punch/sz", 0, true, "test 1");
  //Serial.println("以QoS 0发布");

  /*uint16_t packetIdPub1 = mqttClient.publish("test/lol", 1, true, "test 2");
  Serial.print("以QoS 1发布, packetId: ");
  Serial.println(packetIdPub1);
  uint16_t packetIdPub2 = mqttClient.publish("test/lol", 2, true, "test 3");
  Serial.print("以QoS 2发布, packeId: ");
  Serial.println(packetIdPub2);*/
}

// MQTT 断开回调
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println("已断开与MQTT的连接.");
  mqtt_connect = 1;
  Serial.println();
  Serial.println("-----------------------");
}

// MQTT 确认订阅回调
void onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
  Serial.println("已确认订阅.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
  Serial.println();
  Serial.println("-----------------------");
}

// MQTT 取消订阅回调
void onMqttUnsubscribe(uint16_t packetId)
{
  Serial.println("已确认取消订阅.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.println();
  Serial.println("-----------------------");
}

// MQTT 收到发布回调
void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  Serial.println("已收到发布.");
  Serial.print("  topic 主题: ");
  Serial.println(topic);
  Serial.print("  qos 服务质量: ");
  Serial.println(properties.qos);
  Serial.print("  dup 重复: ");
  Serial.println(properties.dup);
  Serial.print("  retain 保持: ");
  Serial.println(properties.retain);
  Serial.print("  len 长度: ");
  Serial.println(len);
  Serial.print("  index 索引: ");
  Serial.println(index);
  Serial.print("  total 总: ");
  Serial.println(total);
  Serial.print("Message 消息:");

  for (int i = 0; i < len; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

// MQTT 确认发布回调
void onMqttPublish(uint16_t packetId)
{
  Serial.println("已确认发布.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.println();
  Serial.println("-----------------------");
}

void mtqq_init()
{
  // 添加wifi事件
  // WiFi.onEvent(WiFiEvent);

  mqttClient.onConnect(onMqttConnect);          // 回调 开启mqtt连接
  mqttClient.onDisconnect(onMqttDisconnect);    // 回调 mqtt连接已断开
  mqttClient.onSubscribe(onMqttSubscribe);      // 回调 已确认订阅
  mqttClient.onUnsubscribe(onMqttUnsubscribe);  // 回调 已确认取消订阅
  mqttClient.onMessage(onMqttMessage);          // 回调 收到发布
  mqttClient.onPublish(onMqttPublish);          // 回调 确认发布

  // 解析IP还是地址
  uint8_t drop = 0;
  String ip[4];
  for (uint8_t i = 0; i < eep_mqttHost.length(); i++)
  {
    char c = eep_mqttHost[i];
    if (c == '.') drop++;
    else ip[drop] += c;
  }
  if (drop == 4)
  {
    uint8_t ip_i[4];
    ip_i[0] = atoi(ip[0].c_str());
    ip_i[1] = atoi(ip[1].c_str());
    ip_i[2] = atoi(ip[2].c_str());
    ip_i[3] = atoi(ip[3].c_str());
    mqttClient.setServer(IPAddress(ip_i[0], ip_i[1], ip_i[2], ip_i[3]), eep_mqttPort);
    //Serial.println("ip");
  }
  else
  {
    mqttClient.setServer(eep_mqttHost.c_str(), eep_mqttPort);
    //Serial.println("host");
  }

  if (eep_mqttUserName.length() > 0)
    mqttClient.setCredentials(eep_mqttUserName.c_str(), eep_mqttPassword.c_str());
  
  //Serial.printf("eep_mqttHost:%s\n", eep_mqttHost.c_str());
  //Serial.printf("eep_mqttUserName:%s\n", eep_mqttUserName.c_str());
  //Serial.printf("eep_mqttPassword:%s\n", eep_mqttPassword.c_str());

  //Serial.println("连接到MQTT...");
  mqttClient.connect();
}

void mqtt_airQuality_proCount()
{
  // 检查WIFI状态
  bool wifi_ok = WiFi.isConnected();
  if (wifi_ok == 0) // wifi断开了
  {
    my_msgbox_send(F("连接WIFI"), eep_sta_ssid);
    delay(500);
    WiFi.mode(WIFI_OFF);
    wifi_ok = connectToWifi();
    if (wifi_ok == 1) //wifi连接成功
    {
      /*if (bitRead(ic_state, IC_CLOCK) == 1 && !ntpConnect()) // 连接NTP服务器
      {
        ntpToClockChip(); // 写入时钟芯片
      }*/
    }
    else if (wifi_ok == 0) //wifi连接失败
    {
      //Serial.println("连接失败");
      my_msgbox_send(F("连接失败"), eep_sta_ssid, 1000);
      WiFi.mode(WIFI_OFF);
      return;
    }
  }

  // 检查MQTT状态
  if (wifi_ok == 1 && mqtt_connect != 2)
  {
    my_msgbox_send(F("连接MQTT"), eep_mqttHost, 2000);
    if      (mqtt_connect == 0) mtqq_init();
    else if (mqtt_connect == 1) mqttClient.connect();
  }

  uint8_t count = 0;
  while (mqtt_connect == 0)
  {
    delay(100);
    count++;
    if (count > 80)
    {
      //Serial.println("连接MQTT失败");
      my_msgbox_send(F("连接MQTT"), F("失败"), 1500);
      return;
    }
  }

  if (mqtt_connect == 2 && mqtt_deviceRelease == 0)
  {
    MQTT_airQualityReleaseDevice(); // 发布设备
    my_msgbox_forceSend(F("发布设备"), LV_SYMBOL_LAUGH "\n成功", 1500);
  }

    // Serial.print("startingUpTime:");Serial.println(startingUpTime);

    JsonDocument my_doc; // JSON文档对象
    String output;
    my_doc["temperature"] = UART_TEMP;
    my_doc["humidity"] = UART_HUMI;
    my_doc["co2"] = UART_CO2.data;
    my_doc["tvoc"] = UART_TVOC.data;
    my_doc["hcho"] = UART_HCHO.data;
    my_doc.shrinkToFit();          // 可选,减少内存池的容量以匹配当前的使用情况
    serializeJson(my_doc, output); // 生成一个缩小的JSON文档

    // 查看上传的内容
    // Serial.print("output:");Serial.println(output);Serial.println();

    mqttClient.publish("airQuality/data", 0, true, output.c_str());
    //Serial.println("以QoS 0发布");
    //my_msgbox_exit(5);
    //delay(MSGBOX_ANIM_TIME2);
    //my_msgbox_send(F("发布成功"), LV_SYMBOL_LAUGH, 1000);
  }

void mqtt_rtos(void *param);
// mqtt任务
void mqtt_rtos_init()
{
  xTaskCreatePinnedToCore(
      mqtt_rtos, /* 任务指针，创建任务用的那个函数名 */
      "mqtt",    /* 任务名称 */
      8 * 1024,  /* 任务栈大小，根据需要自行设置*/
      NULL,      /* 可选参数，一般不填*/
      1,         /* 优先级 */
      &TH_mqtt,  /* 任务句柄，用于后续挂起或恢复运行*/
      0          /* 核ID */
  );
}
void mqtt_rtos(void *param)
{
  uint32_t time1 = 0;
  for (;;)
  {
    if (!bitRead(backgroundTask, BGT_MQTT))
    {
      TH_mqtt = NULL;
      vTaskDelete(NULL);
    }

    // 每10秒发布一次
    if (mqtt_send == 1 && millis() - time1 > 10 * 1000)
    {
      mqtt_airQuality_proCount();
      time1 = millis();
      // mqtt_send = 0;
    }
    vTaskDelay(1);
  }
}