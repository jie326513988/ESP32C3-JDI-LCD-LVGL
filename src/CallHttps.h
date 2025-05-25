// https请求
String callHttps(String url, int *httpsCode)
{
  *httpsCode = 0;
  String out;
  String payload;
  // Serial.print("requesting URL: ");
  // Serial.println(url);
  // std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  WiFiClientSecure *client = new WiFiClientSecure;
  client->setInsecure(); // 不检验
  HTTPClient https;
  //https.setReuse(3);
  if (https.begin(*client, url))
  {
    *httpsCode = https.GET();
    //Serial.printf("httpsCode:%d\n",httpsCode);
    if (*httpsCode > 0) // 判断有无返回值
    {
      out = https.getString();
      // Serial.println(" ");
      // Serial.println("https.GET");
      // Serial.println(payload);
      // Serial.println(" ");
    }
    else out =  F("服务器无响应");
  }
  else out = F("服务器连接失败");
  return out;
  https.end();
}


/*void update_started()
{
  Serial.println("回调:HTTP更新过程已开始");
}*/
/*void update_error(int err)
{
  Serial.printf("回调:HTTP更新致命错误代码 %d\n", err);
}*/

/*
void update_finished()
{
  //Serial.println("回调:HTTP更新过程已完成");
  String str = F("HTTP更新成功\n即将重启");
  Serial.println(str);
  promptBox(str);
  delay(3000);
}
void update_progress(int cur, int total)
{
  //Serial.printf("回调:  HTTP更新进程 %d/%d\n", cur, total);
  uint16_t percentage = float(cur) / float(total) * 100.0;
  if (percentage >= 10 && percentage % 10 == 0)
    promptBox(String(percentage) + "%", 36);
  else if (percentage >= 1 && percentage < 2)
    promptBox(String(percentage) + "%", 36);
}
void myHttpUpdate(String address, uint32_t fileSize)
{
  WiFiClientSecure *client = new WiFiClientSecure;
  client->setInsecure(); // 不检验

  // 下面的行是可选的。可用于在闪烁过程中闪烁板上的LED
  // 在从网络下载一个数据缓冲区时，LED将亮起。在将该缓冲区写入闪存时，LED将熄灭
  // 连接良好时，LED应定期闪烁。在连接不良的情况下，LED的亮起时间会比熄灭时间长得多。
  // 可以使用LED_BUILTIN以外的其他引脚。第二个值用于点亮LED。如果LED以高电平点亮，则应传递该值
  //httpUpdate.setLedPin(LED_BUILTIN, LOW);
  httpUpdate.setFileSize(fileSize); // 设置文件大小，当HTTP标头没有定义大小时使用
 // httpUpdate.onStart(update_started);
  httpUpdate.onEnd(update_finished);
  httpUpdate.onProgress(update_progress);
  //httpUpdate.onError(update_error);
  //Serial.printf("address:%s\n", address.c_str());
  //Serial.printf("fileSize:%d\n", fileSize);
  t_httpUpdate_return ret = httpUpdate.update(*client, address);

  //HTTPClient https;
  //t_httpUpdate_return ret = httpUpdate.update(https, address);
  // t_httpUpdate_return ret = httpUpdate.update(client, "server", 80, "/file.bin");

  String out;
  switch (ret)
  {
  case HTTP_UPDATE_FAILED:
    Serial.printf("HTTP更新错误 (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
    promptBox("HTTP更新错误" + String(httpUpdate.getLastError()));
    break;

  case HTTP_UPDATE_NO_UPDATES:
    out = F("HTTP没有更新");
    Serial.println(out);
    promptBox(out);
    break;

  case HTTP_UPDATE_OK:
    out = F("HTTP更新成功");
    Serial.println(out);
    promptBox(out);
    break;
  }
  delay(1000);
}*/