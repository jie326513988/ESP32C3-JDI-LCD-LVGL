#include <WiFi.h>
#include <SPI.h>
#include <FS.h>
#include "functionAll.h"

//****** 屏幕驱动
#define SPI_SCLK 2
#define SPI_MISO -1
#define SPI_MOSI 6
#define SPI_CS 10
#include <JDI_MIP_Display.h>
#define NUMBER_COLORS 8
const uint16_t colors[NUMBER_COLORS] = {COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN, COLOR_RED, COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE};
JDI_MIP_Display jdi_display;
bool doudong = 1; // 是否开启抖动

#include <lvgl.h>
#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif
//#include <maomao.c>
/*要使用LVGL的内置示例和演示，请分别取消对以下includes的注释。
 *您还需要将`lvgl/examples'复制到`lvgl/src/examples`。类似于演示“lvgl/demos”到“lvgl/src/demos”。
 *请注意，“lv_examples”库适用于LVGL v7，您不应该为此版本安装它（因为LVGL v8），因为示例和演示现在是主LVGL库的一部分。
 */

// #include <examples/lv_examples.h>
// #include <demos/lv_demos.h>

/*设置为您的屏幕分辨率*/
#define TFT_HOR_RES 72   //水平
#define TFT_VER_RES 144  //垂直
//#define BUF_HOR_NUM  TFT_HOR_RES + 4
//uint8_t buf_HOR[BUF_HOR_NUM];

/*LVGL绘制到这个缓冲区，1/10的屏幕大小通常工作得很好。大小以字节为单位*/
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 1 * (LV_COLOR_DEPTH / 8))
uint16_t draw_buf[DRAW_BUF_SIZE / 2];

#if LV_USE_LOG != 0
void my_print(lv_log_level_t level, const char *buf)
{
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}
#endif

#include "imageProcessing.h"
#include "myLVGLDemo.h"

// LVGL渲染函数，调用自带drawBufferedPixel绘制，可旋转，但会牺牲一点帧率
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *color_p)
{
  for (lv_coord_t y = area->y1; y <= area->y2; y++)
  {
    for (lv_coord_t x = area->x1; x <= area->x2; x++)
    {
      // jdi由4个位控制颜色
      // 0  1  2  3  
      // 黑 蓝 绿 红 

      //****** 24位颜色转换 ******
      /*uint8_t jdi_color = 0;
      if (color_p[2] >= 127) bitWrite(jdi_color, 3, 1); // 红色
      if (color_p[1] >= 127) bitWrite(jdi_color, 2, 1); // 绿色
      if (color_p[0] >= 127) bitWrite(jdi_color, 1, 1); // 蓝色
      jdi_display.drawBufferedPixel(x, y, jdi_color);
      color_p += 3;*/

      //******  16位颜色转换 ****** 
      uint8_t jdi_color = 0;
      uint16_t r, g, b;
      uint16_t color = color_p[1] << 8 | color_p[0];
      r = (color >> 11) & 0x1F;
      g = (color >> 5) & 0x3F;
      b = color & 0x1F;
      //Serial.print("color_p[0]:");Serial.println(color_p[0],HEX);
      //Serial.print("color_p[1]:");Serial.println(color_p[1],HEX);
      //Serial.print("color:");Serial.println(color,HEX);
      //Serial.print("r:");Serial.println(r);
      //Serial.print("g:");Serial.println(g);
      //Serial.print("b:");Serial.println(b);
      //Serial.println();
      if (r > 31 / 2) bitWrite(jdi_color, 3, 1); // 红色
      if (g > 63 / 2) bitWrite(jdi_color, 2, 1); // 绿色
      if (b > 31 / 2) bitWrite(jdi_color, 1, 1); // 蓝色
      jdi_display.drawBufferedPixel(x, y, jdi_color);
      color_p += 2;

      //******  8位颜色转换,lvgl暂无效 ****** 
      /*uint8_t jdi_color = 0;
      uint8_t r, g, b;
      r = (color_p[0] >> 5) & 0x07;
      g = (color_p[0] >> 2) & 0x07;
      b = color_p[0] & 0x03;
      if (r > 7 / 2) bitWrite(jdi_color, 3, 1); // 红色
      if (g > 7 / 2) bitWrite(jdi_color, 2, 1); // 绿色
      if (b > 3 / 2) bitWrite(jdi_color, 1, 1); // 蓝色
      //Serial.print(color_p[0], HEX); Serial.print(" ");
      //Serial.print("color_p[0]:");Serial.println(color_p[0],HEX);
      //Serial.print("r:");Serial.println(r);
      //Serial.print("g:");Serial.println(g);
      //Serial.print("b:");Serial.println(b);
      //Serial.println();
      jdi_display.drawBufferedPixel(x, y, jdi_color);
      color_p++;*/
    }
    //Serial.println();
  }
  //Serial.println();
  
  //uint32_t time1 = micros();
  jdi_display.refresh(); // 使用refresh()刷新显示内容 耗时最长
  //Serial.print("耗时:");Serial.println(micros() - time1);
  lv_disp_flush_ready(disp);
}

// LVGL渲染函数，使用pushPixelsDMA绘制，速度快，暂未实现旋转
void my_disp_flush2(lv_display_t *disp, const lv_area_t *area, uint8_t *color_p)
{
  /*Serial.println();
  Serial.print("area->x1:");Serial.println(area->x1);
  Serial.print("area->x2:");Serial.println(area->x2);
  Serial.print("area->y1:");Serial.println(area->y1);
  Serial.print("area->y2:");Serial.println(area->y2);
  Serial.println();
  delay(1000);*/

  //*** DMA发送缓冲区
  // 1个字节存储两个像素的颜色所以只需要屏幕的一半
  // 头指令2个+末尾结束指令2个所以+4
  // 因为DMA有BUG，需要发送多4个字节才能正常
  uint16_t BUF_HOR_NUM = TFT_HOR_RES / 2 + 4 + 4;
  uint8_t buf_HOR[BUF_HOR_NUM];
  memset(&buf_HOR, 0, sizeof(buf_HOR));
  //*** 当前颜色
  uint16_t color_cur;          // 当前像素的颜色
  uint8_t r_cur, g_cur, b_cur; // 旧的颜色 量化的颜色
  int8_t r_err, g_err, b_err;  // 颜色误差
  //*** 像素抖动参数
  uint32_t pixel_offset_d;
  uint8_t *pixel_d;
  uint16_t color_d;
  uint8_t r_d;
  uint8_t g_d;
  uint8_t b_d;

  for (lv_coord_t y = area->y1; y <= area->y2; y++) // area->y1 area->y2
  {
    //Serial.print(y);Serial.print(": ");
    // 行开头添加开始命令
    buf_HOR[0] = CMD_UPDATE;
    buf_HOR[1] = y + 1;
    for (lv_coord_t x = area->x1; x <= area->x2; x++) //area->x1 area->x2
    {
      // 获取当前地址的颜色，从rgb565拆成rgb分量
      color_cur = color_p[1] << 8 | color_p[0];
      r_cur, g_cur, b_cur; // 旧的颜色 量化的颜色
      r_err, g_err, b_err;  // 颜色误差
      r_cur = (color_cur >> 11) & 0x1F;
      g_cur = (color_cur >> 5) & 0x3F;
      b_cur = color_cur & 0x1F;

      // 量化颜色 将16位颜色转换为8位
      if (r_cur > 31 / 2) {r_err = r_cur - 31; r_cur = 31;}
      else                {r_err = r_cur - 0;  r_cur = 0;}
      if (g_cur > 63 / 2) {g_err = g_cur - 63; g_cur = 63;}
      else                {g_err = g_cur - 0;  g_cur = 0;}
      if (b_cur > 31 / 2) {b_err = b_cur - 31; b_cur = 31;}
      else                {b_err = b_cur - 0;  b_cur = 0;}

      if (doudong) // 抖动开启
      {
        modify_pixel_color(color_p, 0, create_rgb565(r_cur, g_cur, b_cur));
        // 进行误差扩散
        if (x != TFT_HOR_RES - 1)
        {
          //pixel_offset_d = getPixelIdx(1, 0);
          pixel_offset_d = 2;
          pixel_d = color_p + pixel_offset_d;
          color_d = pixel_d[1] << 8 | pixel_d[0];
          r_d = (color_d >> 11) & 0x1F;
          g_d = (color_d >> 5) & 0x3F;
          b_d = color_d & 0x1F;
          r_d = colorThresholdLimit(r_d, (r_err * 7) / 16, 31);
          g_d = colorThresholdLimit(g_d, (g_err * 7) / 16, 63);
          b_d = colorThresholdLimit(b_d, (b_err * 7) / 16, 31);
          color_d = create_rgb565(r_d, g_d, b_d);
          modify_pixel_color(color_p, pixel_offset_d, color_d);
        }
        if (x != 0 && y != TFT_VER_RES - 1)
        {
          //pixel_offset_d = getPixelIdx(-1, 1);
          pixel_offset_d = 142;
          pixel_d = color_p + pixel_offset_d;
          color_d = pixel_d[1] << 8 | pixel_d[0];
          r_d = (color_d >> 11) & 0x1F;
          g_d = (color_d >> 5) & 0x3F;
          b_d = color_d & 0x1F;
          r_d = colorThresholdLimit(r_d, (r_err * 5) / 16, 31);
          g_d = colorThresholdLimit(g_d, (g_err * 5) / 16, 63);
          b_d = colorThresholdLimit(b_d, (b_err * 5) / 16, 31);
          color_d = create_rgb565(r_d, g_d, b_d);
          modify_pixel_color(color_p, pixel_offset_d, color_d);
        }
        if (y != TFT_VER_RES - 1)
        {
          //pixel_offset_d = getPixelIdx(0, 1);
          pixel_offset_d = 144;
          pixel_d = color_p + pixel_offset_d;
          color_d = pixel_d[1] << 8 | pixel_d[0];
          r_d = (color_d >> 11) & 0x1F;
          g_d = (color_d >> 5) & 0x3F;
          b_d = color_d & 0x1F;
          r_d = colorThresholdLimit(r_d, (r_err * 3) / 16, 31);
          g_d = colorThresholdLimit(g_d, (g_err * 3) / 16, 63);
          b_d = colorThresholdLimit(b_d, (b_err * 3) / 16, 31);
          color_d = create_rgb565(r_d, g_d, b_d);
          modify_pixel_color(color_p, pixel_offset_d, color_d);
        }
        if (x != TFT_HOR_RES - 1 && y != TFT_VER_RES - 1)
        {
          //pixel_offset_d = getPixelIdx(1, 1);
          pixel_offset_d = 146;
          pixel_d = color_p + pixel_offset_d;
          color_d = pixel_d[1] << 8 | pixel_d[0];
          r_d = (color_d >> 11) & 0x1F;
          g_d = (color_d >> 5) & 0x3F;
          b_d = color_d & 0x1F;
          r_d = colorThresholdLimit(r_d, (r_err * 1) / 16, 31);
          g_d = colorThresholdLimit(g_d, (g_err * 1) / 16, 63);
          b_d = colorThresholdLimit(b_d, (b_err * 1) / 16, 31);
          color_d = create_rgb565(r_d, g_d, b_d);
          modify_pixel_color(color_p, pixel_offset_d, color_d);
        }
      }
      
      uint8_t jdi_color = 0;
      if(r_cur == 31) bitWrite(jdi_color, 3, 1);
      if(g_cur == 63) bitWrite(jdi_color, 2, 1);
      if(b_cur == 31) bitWrite(jdi_color, 1, 1);

      color_p += 2; //16位颜色占用两个字节，移动到下一个地址

      //****** 一个字节存储两个像素的颜色
      int pixelIdx1 = (x / 2);
      if (x % 2 == 0)
      {
        buf_HOR[pixelIdx1 + 2] &= 0x0F;
        buf_HOR[pixelIdx1 + 2] |= (jdi_color & 0x0F) << 4;
      }
      else
      {
        buf_HOR[pixelIdx1 + 2] &= 0xF0;
        buf_HOR[pixelIdx1 + 2] |= jdi_color & 0x0F;
      }
      //Serial.print(draw_buf[x + y * TFT_HOR_RES]);
      //Serial.print(" ");
    }
    // 行结尾添加结束命令
    buf_HOR[area->x2 + 3] = 0x00;
    buf_HOR[area->x2 + 4] = 0x00;
    buf_HOR[area->x2 + 5] = 0x00;
    buf_HOR[area->x2 + 6] = 0x00;
    buf_HOR[area->x2 + 7] = 0x00;
    buf_HOR[area->x2 + 8] = 0x00;
    //推送一行
    jdi_display.pushPixelsDMA(buf_HOR, BUF_HOR_NUM);
    //delay(500);
    //Serial.println();
  }
  // delay(1000);
  lv_disp_flush_ready(disp);
}

void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("开始");
  jdi_init();
  lvgl_init();
  demo_gif();
  //demo_label();
  //demo_img();
}
uint32_t time11 = 0;

void loop()
{
  long last_time = millis();

  yield();
  
  lv_task_handler(); /* 让 GUI 去做它该做的事 */

  lv_tick_inc(int(millis() - last_time));

  /*if (millis() - time11 > 3000)
  {
    time11 = millis();
    doudong = !doudong;
  }*/
}

void jdi_init()
{
  //SPI.setFrequency(8000000);
  //SPI.begin(SPI_SCLK, SPI_MISO, SPI_MOSI, SPI_CS); // sck,miso,mosi,cs
  jdi_display.begin(SPI_SCLK, SPI_MISO, SPI_MOSI, SPI_CS, 12000000, 1);
  // jdi_display.begin();
  jdi_display.displayOn();
  // jdi_display.setRotation(3); // 无效
  // jdi_display.frontlightOn(); // 前灯打开 可选，具体取决于显示器型号
  jdi_display.clearScreen(); // 清除屏幕
}

void lvgl_init()
{
  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.println(LVGL_Arduino);
  lv_init();

  /*设置一个时间戳源，以便 LVGL 知道经过了多少时间. */
  lv_tick_set_cb(millis);

  /* 用于调试的寄存器打印功能 */
#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print);
#endif

  lv_display_t *disp;

  /*创建一个显示*/
  disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
  lv_display_set_flush_cb(disp, my_disp_flush2);
  lv_display_set_buffers(disp, draw_buf, NULL, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_0); // 设置显示器旋转方向，可以是LV_DISP_ROT_NONE, LV_DISP_ROT_90, LV_DISP_ROT_180, LV_DISP_ROT_270

  /*初始化（伪）输入设备驱动程序*/
  /*lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); //触摸板应具有POINTER类型
  lv_indev_set_read_cb(indev, my_touchpad_read);*/

  /* 创建一个简单的标签
   * ---------------------
   lv_obj_t *label = lv_label_create( lv_scr_act() );
   lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
   lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );

   * 举个例子。查看所有示例
   *  - Online: https://docs.lvgl.io/master/examples.html
   *  - Source codes: https://github.com/lvgl/lvgl/tree/master/examples
   * ----------------------------------------------------------------

   lv_example_btn_1();

   * 或者尝试一个演示。不要忘记在lv_conf.h中启用演示。例如，lv_USE_demos_WIDGETS
   * -------------------------------------------------------------------------------------------
   lv_demo_widgets();
   */

    Serial.println("Setup done");
}