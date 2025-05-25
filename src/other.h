//****** 获取文件内指定行数的行所包含的字符 mode = 1 跳过头部空白行
String getlineNumStr(fs::FS &fs, String dir, uint16_t line, bool mode)
{
  File file = fs.open(dir, "r");
  uint16_t line_count = 0;       // 行计数
  uint16_t previousLine_pos = 0; // 上一个'\n'的位置
  while (file.available())
  {
    if (char(file.read()) != '\n' && file.available())
      continue; // 不是换行符 并 还有字节没读完，跳过

    if (mode == 1 && file.position() == 1)
      continue; // 跳过头部空白行

    line_count++;           // 行计数加
    //Serial.print("line_count:"); Serial.println(line_count);
    if (line_count == line) // 寻找到行
    {
      String out = "";                // 要输出的字符串
      uint16_t pos = file.position(); // 记录 当前的'\n' 的位置
      file.seek(previousLine_pos);    // 退回上一行的位置
      // 获取 上一个'\n' 到 当前的'\n' 之间的字符
      //uint16_t endPos = pos - 1;
      //if(file.available() == 0) endPos = pos;
      //Serial.print("previousLine_pos:"); Serial.println(previousLine_pos);
      //Serial.print("pos:"); Serial.println(pos);
      for (uint16_t i = previousLine_pos; i < pos; i++)
      {
        //read:
        char c = file.read();
        if (c != '\r' && c != '\n') // 过滤\r\n
        {
          out += c;
        }
        //if(file.available() == 1) goto read; // 防止最后一位是\n 读取进去
      }
      file.close();
      return out;
    }
    else
      previousLine_pos = file.position(); // 记录下位置，下次就是 上一个'\n' 的位置
  }
  file.close();
  return "";
}

uint32_t getEspChipId() //获取芯片ID
{
  uint32_t chipId = 0;
  for (int i = 0; i < 17; i = i + 8)
  {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  return chipId;
}
String getEspChipId_str() //获取芯片ID
{
  return String(getEspChipId());
}

//整合文件名和路径
String integrationPath(String dir,String name)
{
  String out;
  if (dir.charAt(dir.length() - 1) == '/') out = dir + name;
  else                                     out = dir + "/" + name;
  return out;
}

/*
一、indexOf()
indexOf("\\")：返回"\\"字符在此实例中第一个出现的索引位置，实例的下标是从0开始，如果未找到则返回-1.
indexOf("\\", 7)：返回在此实例中从下标7开始的，第一次出现"\\"的位置，如果未找到返回-1.
二、lastIndexOf()
lastIndexOf("\\")：返回"\\"在此实例中最后一个出现的索引位置。即从右向左搜索，第一次出现的"\\"的位置，如果未找到则返回-1.
lastIndexOf("\\", 7)：返回在此实例中从下标0开始到下标7结束的这一段子串中，最后一次出现"\\"的位置 。即从右向左搜索，第一次出现的"/"的位置，如果未找到则返回-1.
三、subString()
substring：截取字符串。Substring(7,2)表示从下标7开始，截取长度为2的字符串，Substring(7)表示从下标7开始，一直截取到字符串末尾。
*/

// 结构体清零
void structClear(unsigned char *pta, int size)
{
  while (size > 0)
  {
    *pta++ = 0;
    size--;
  }
}

// 检查i2c芯片是否存在 0不存在 1存在
bool i2cChipExist(uint8_t add)
{
    bool ok = 0;
    Wire.beginTransmission(add); // 从指定的地址开始向I2C从设备进行传输
    if (Wire.endTransmission() == 0) ok = 1;

    // 标记状态
    if     (add == CLOCK_I2C_ADDR)  bitWrite(ic_state, IC_CLOCK, ok);
    else if(add == ACC_I2C_ADDR)    bitWrite(ic_state, IC_ACC, ok);
    else if(add == BATSOC_I2C_ADDR) bitWrite(ic_state, IC_BATSOC, ok);

    return ok;

    // Wire.endTransmission()返回结果：
    // 0: 成功
    // 1: 数据量超过传送缓存容纳限制
    // 2: 传送地址时收到 NACK
    // 3: 传送数据时收到 NACK
    // 4: 其它错误
}

// 获取文件类型 ,能识别大小写
// 1txt 2bmp 3jpg 4ttf 5bin 6mp3 7flac
enum 
{
  FILE_TXT = 1,
  FILE_BMP,
  FILE_JPG,
  FILE_BIN,
  FILE_WATCH,
  FILE_EPUB,
  FILE_MID,
  FILE_TTF
};

uint8_t fileFormat(String Name)
{
  //uint32_t time1 = micros();
  if (Name.length() < 1) return 0;

  String suffix;
  uint16_t length = Name.length();
  uint16_t dianPos = length; // 最后一个点的位置
  // 获取最后一个点的位置
  for (uint16_t i = length; i > 0; i--)
  {
    if (Name[i] == '.')
    {
      dianPos = i;
      break;
    }
  }
  //Serial.print("Name：");Serial.println(Name);
  //Serial.print("耗时：");Serial.println(micros()-time1);

  if (dianPos < 0) return 0;// 点不能是最后

  // 提取点之后的后缀名称
  for (uint16_t i = dianPos + 1; i < length; i++)
  {
    if (Name[i] >= 65 && Name[i] <= 91) // 转换为小写
      Name[i] = Name[i] + 32;
    suffix += Name[i];
  }

  // Serial.println(suffix);
  if      (suffix == "txt")   return FILE_TXT;
  else if (suffix == "epub")  return FILE_EPUB;
  else if (suffix == "jpg")   return FILE_JPG;
  else if (suffix == "bmp")   return FILE_BMP;
  else if (suffix == "bin")   return FILE_BIN;
  else if (suffix == "ttf")   return FILE_TTF;
  else if (suffix == "watch") return FILE_WATCH;
  else if (suffix == "mid")   return FILE_MID;
  return 0;
}

//去除文件名称前的目录路径 如: /mp3/周杰伦/回到过去.mp3  =  回到过去.mp3
String removeDirectoryName(String z)
{
  int16_t pos = z.lastIndexOf('/'); // 获取最后一个 '/'
  if (pos < 0) return "";
  return z.substring(pos + 1);
}
 //去除文件名称前的目录路径 如: /mp3/周杰伦/回到过去.mp3  =  回到过去.mp3
String removeDirectoryName(const char* z)
{
  String z_str = String(z);
  return removeDirectoryName(z_str);
}

//提取路径 如: /mp3/周杰伦/回到过去.mp3  =  /mp3/周杰伦/
String extractPath(String z)
{
  int16_t pos = z.lastIndexOf('/'); // 获取最后一个 '/'
  if (z.length() == 1 && z == "/") return "/";
  else if (pos < 0) return "";
  else if (pos == 0) return "/";
  /*Serial.print("z:"); Serial.println(z);
  Serial.print("z.length():"); Serial.println(z.length());
  Serial.print("pos:"); Serial.println(pos);*/
  return z.substring(0, pos);
}
String qchz(String in) //去除后缀
{
  uint8_t in_length = in.length();
  if (in_length == 0) return F("");
  uint8_t pos = 0; //点的位置
  String out;
  for (int16_t i = in_length; i > 0; i--)
    if (in[i] == '.') pos = i;
  for (uint8_t i = 0; i < pos; i++) out += in[i];
  return out;
}

String byteConversion(size_t bytes) //字节换算
{
  String bytes_str;
  if (bytes <= 1024)
    bytes_str = String(bytes) + " B"; //1024.0
  else if (bytes <= 1048576)
    bytes_str = String(bytes * 0.0009765625) + " KB"; //1024.0
  else if (bytes <= 1073741824)
    bytes_str = String(bytes * 0.0009765625 * 0.0009765625) + " MB"; //1024.0
  else bytes_str = String(bytes * 0.0009765625 * 0.0009765625 * 0.0009765625) + "GB";
  return bytes_str;
}

String byteConversion2(size_t bytes) //字节换算成字符串
{
  String bytes_str;
  if (bytes <= 1000000)
    bytes_str = String(bytes * 0.1) + "KB"; 
  else if (bytes <= 10000000)
    bytes_str = String(bytes * 0.0001) + " MB";
  else if (bytes <= 100000000)
    bytes_str = String(bytes * 0.0000001) + " GB";
  else if (bytes <= 1000000000)
    bytes_str = String(bytes * 0.0000001) + " GB"; 
  return bytes_str;
}

//日期增减
void dateAddSub(int16_t &year, int8_t &month, int8_t &day, int8_t dayAdd)
{
  if(dayAdd == 0) return;

  day += dayAdd;
  uint8_t dayMax = monthHowManyDay(year, month);

  if (day > dayMax) // 天数满，进入下一个月
  {
    day = 1;
    month++;  // 月加1
    if (month > 12)
    {
      month = 1;
      year++;// 年加1
    } 
  }
  else if (day <= 0)  // 天数负，进入上一个月
  {
    month--;
    if (month <= 0)
    {
      month = 12;
      year--;
    }
    day = monthHowManyDay(year, month);
  }
}

//自动换行，二分法
String autoLineFeed(const char *inAWord, uint16_t pixelValue, const lv_font_t *font, uint8_t *line)
{
  String out;
  size_t len = strlen(inAWord);
  size_t start = 0;
  while (start < len)
  {
    size_t left = start;
    size_t right = len;
    size_t best_fit = start;

    // 二分法查找最长不超宽度的子字符串
    while (left <= right)
    {
      size_t mid = (left + right) / 2;
      uint16_t width = lv_text_get_width(inAWord + start, mid - start, font, 0);
      if (width <= pixelValue)
      {
        best_fit = mid; // 找到可行的断点
        left = mid + 1; // 尝试更长的
      }
      else
      {
        right = mid - 1; // 缩短范围
      }
    }
    // 将当前行添加到结果中
    out += String(inAWord).substring(start, best_fit);
    if (best_fit < len)
    {
      out += "\n"; // 添加换行符
      *line+=1;
    }
    // 移动到下一部分
    start = best_fit;
  }

  return out;
}

// 函数：从文件中提取指定行数的密码
const char *extractPasswordFromFile(const char *filePath, int targetLine)
{
  static char password[64]; // 存储提取的密码（静态数组，避免动态分配）
  password[0] = '\0';       // 初始化为空字符串

  File file = LittleFS.open(filePath, "r"); // 打开文件
  if (!file)
  {
    Serial.println("Failed to open file!");
    return password; // 返回空字符串
  }

  char buffer[128];    // 假设每行最大长度为128字节
  int currentLine = 1; // 当前行号

  while (file.available())
  {
    int len = file.readBytesUntil('\n', buffer, sizeof(buffer) - 1); // 读取一行
    buffer[len] = '\0';                                              // 添加字符串结束符

    if (currentLine == targetLine)
    {                                         // 如果当前行是目标行
      char *separator = strstr(buffer, "隔"); // 查找“隔”字
      if (separator)
      {
        char *passwordStart = separator + 3; // 跳过“隔”字（UTF-8 中“隔”占3字节）
        // 过滤掉 \r
        char *passwordEnd = strchr(passwordStart, '\r');
        if (passwordEnd)
        {
          *passwordEnd = '\0'; // 截断字符串
        }
        strncpy(password, passwordStart, sizeof(password) - 1); // 复制密码到静态数组
        password[sizeof(password) - 1] = '\0';                  // 确保字符串以 \0 结尾
        break;                                                  // 找到密码后退出循环
      }
    }
    currentLine++; // 增加行号
  }

  file.close();    // 关闭文件
  return password; // 返回提取的密码
}
/*
  r 以只读方式操作文件，读位置在文件的开始位置，文件不存在返回空对象；
  r+ 以可读可写方式打开文件，读写位置在文件的开始位置，文件不存在返回空对象；
  w 截取文件长度到0或者创建新文件，只能写操作，写位置在文件的开始位置；
  w+ 截取文件长度到0或者创建新文件，可读可写操作，写位置在文件的开始位置；
  a 在文件末尾追加内容或者文件不存在就创建新文件，追加位置在当前文件的末尾，只能写操作；
  a+ 在文件末尾追加内容或者文件不存在就创建新文件，追加位置在当前文件的末尾，可读写操作；
  如果模式值是 SeekSet，则从文件开头移动指定的偏移量。
  如果模式值是 SeekCur，则从目前的文件位置移动指定的偏移量。
  如果模式值是 SeekEnd，则从文件结尾处移动指定的偏移量。

  O_CREAT:在文件打开过程中创建新文件
  O_RDONLY：以只读方式打开文件。
  O_WRONLY：以只写方式打开文件。
  O_RDWR：以读写方式打开文件。
  O_APPEND：在文件末尾追加数据，而不是覆盖现有内容。
  O_TRUNC：如果文件已经存在，将其截断为空文件。
  O_EXCL：与 O_CREAT 一起使用时，如果文件已经存在，则 open() 调用将失败。
  O_SYNC：使文件写操作变为同步写入，即将数据立即写入磁盘。
  O_NONBLOCK：以非阻塞方式打开文件，即使无法立即进行读写操作也不会被阻塞。
*/