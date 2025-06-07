/*
This example uses FreeRTOS softwaretimers as there is no built-in Ticker library
*/

#include <WiFi.h>
extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}
#include <AsyncMqttClient.h>

#define WIFI_SSID "yourSSID"
#define WIFI_PASSWORD "yourpass"

#define MQTT_HOST IPAddress(192, 168, 1, 10)
#define MQTT_PORT 1883

AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

// 连接wifi
void connectToWifi()
{
  Serial.println("连接到Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

// 连接mqtt
void connectToMqtt()
{
  Serial.println("连接到MQTT...");
  mqttClient.connect();
}

// wifi事件
void WiFiEvent(WiFiEvent_t event)
{
  Serial.printf("[WiFi-event] event: %d\n", event);
  switch (event)
  {
  case SYSTEM_EVENT_STA_GOT_IP:
    Serial.println("WiFi已连接");
    Serial.println("IP 地址: ");
    Serial.println(WiFi.localIP());
    connectToMqtt();
    break;
  case SYSTEM_EVENT_STA_DISCONNECTED:
    Serial.println("WiFi连接中断");
    xTimerStop(mqttReconnectTimer, 0); // 确保在重新连接到Wi-Fi时不会重新连接到MQTT
    xTimerStart(wifiReconnectTimer, 0);
    break;
  }
}

void onMqttConnect(bool sessionPresent)
{
  Serial.println("已连接到MQTT.");
  Serial.print("当前会话: ");
  Serial.println(sessionPresent);
  uint16_t packetIdSub = mqttClient.subscribe("test/lol", 2);
  Serial.print("订阅QoS 2，packeId: ");
  Serial.println(packetIdSub);
  mqttClient.publish("test/lol", 0, true, "test 1");
  Serial.println("以QoS 0发布");
  uint16_t packetIdPub1 = mqttClient.publish("test/lol", 1, true, "test 2");
  Serial.print("以QoS 1发布，packetId: ");
  Serial.println(packetIdPub1);
  uint16_t packetIdPub2 = mqttClient.publish("test/lol", 2, true, "test 3");
  Serial.print("以QoS 2发布，packeId: ");
  Serial.println(packetIdPub2);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println("已断开与MQTT的连接.");

  if (WiFi.isConnected())
  {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
  Serial.println("已确认订阅.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId)
{
  Serial.println("已确认取消订阅.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  Serial.println("已收到发布.");
  Serial.print("  topic 主题: ");
  Serial.println(topic);
  Serial.print("  qos: ");
  Serial.println(properties.qos);
  Serial.print("  dup: ");
  Serial.println(properties.dup);
  Serial.print("  retain 保持: ");
  Serial.println(properties.retain);
  Serial.print("  len 长度: ");
  Serial.println(len);
  Serial.print("  index 索引: ");
  Serial.println(index);
  Serial.print("  total 总: ");
  Serial.println(total);
}

void onMqttPublish(uint16_t packetId)
{
  Serial.println("已确认发布.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // 定时器创建
  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));

  // 添加wifi事件
  WiFi.onEvent(WiFiEvent);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);

  connectToWifi();
}

void loop()
{
}
