// 创建颜色
// r:0-31,g:0-63,b:0-31
uint16_t create_rgb565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r << 11) | (g << 5) | b);
}

uint16_t create_rgb565(float f_r, float f_g, float f_b)
{
  uint8_t r;
  uint8_t g;
  uint8_t b;

  if (f_r > 0) r = f_r + 0.5;
  else         r = 0;
  if (f_g > 0) g = f_g + 0.5;
  else         g = 0;
  if (f_b > 0) b = f_b + 0.5;
  else         b = 0;
  
  return ((r << 11) | (g << 5) | b);
}
// 创建颜色
// r:0-7,g:0-7,b:0-3
uint8_t create_rgb332(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r << 5) | (g << 2) | b);
}
//修改内存里面的颜色
void modify_pixel_color(uint8_t *color_p, int16_t x, int16_t y, uint16_t new_color)
{
  //printf("color_p address1: %p\n", (void *)color_p);
  int32_t pixel_offset = (y * TFT_HOR_RES + x) * 2; // 计算要修改像素在缓冲区中的偏移量
  uint8_t high_byte = (new_color >> 8) & 0xFF;      // 获取高8位
  uint8_t low_byte = new_color & 0xFF;              // 获取低8位
  uint8_t *pixel_addr = color_p + pixel_offset;     // 获取要修改像素颜色值的内存地址
  // 修改像素颜色值
  *pixel_addr = low_byte;
  pixel_addr++;
  *pixel_addr = high_byte;
}

//修改内存里面的颜色
void modify_pixel_color(uint8_t *color_p, uint32_t pixel_offset, uint16_t new_color)
{
  //printf("color_p address1: %p\n", (void *)color_p);
  uint8_t high_byte = (new_color >> 8) & 0xFF;      // 获取高8位
  uint8_t low_byte = new_color & 0xFF;              // 获取低8位
  uint8_t *pixel_addr = color_p + pixel_offset;     // 获取要修改像素颜色值的内存地址
  // 修改像素颜色值
  *pixel_addr = low_byte;
  pixel_addr+=1;
  *pixel_addr = high_byte;
}

//获取颜色的位置（索引）
uint32_t getPixelIdx(int32_t x, int32_t y)
{
  return (y * TFT_HOR_RES + x) * 2;
}

// 颜色阈值限制
//val1附近的像素，val2误差
uint8_t colorThresholdLimit(uint8_t val1, int8_t val2,uint8_t max) 
{
  int16_t val1_int = val1;
  int16_t val2_int = val2;
  int16_t tmp = val1_int + val2_int;
  //Serial.print("val1_int:" + String(val1_int)); Serial.print(" val2_int:" + String(val2_int)); Serial.println(" tmp:" + String(tmp));
  if (tmp > max) return max;
  else if (tmp < 0) return 0;
  else return tmp;
  return 0;
}

void saveSaveScreenCache(uint16_t x, uint16_t y, uint16_t piexl)
{
  uint16_t pos = y * TFT_VER_RES + x;
}
