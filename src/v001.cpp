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
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 8 * (LV_COLOR_DEPTH / 8))
uint8_t draw_buf[DRAW_BUF_SIZE / 1];

#if LV_USE_LOG != 0
void my_print(lv_log_level_t level, const char *buf)
{
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}
#endif

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
  Serial.println();*/

  // 每个字节表示两个像素，所以只需要屏幕宽度的一半就能存储一行的颜色
  // 加4是因为每行的头尾都有2个命令
  uint16_t BUF_HOR_NUM = TFT_HOR_RES / 2 + 4;
  uint8_t buf_HOR[BUF_HOR_NUM];
  memset(&buf_HOR, 0, sizeof(buf_HOR));
  for (lv_coord_t y = area->y1; y <= area->y2; y++)
  {
    //Serial.print(y);Serial.print(": ");
    // 行开头添加开始命令
    buf_HOR[0] = CMD_UPDATE;
    buf_HOR[1] = y + 1;
    for (lv_coord_t x = area->x1; x <= area->x2; x++)
    {
      uint8_t jdi_color = 0;
      uint16_t r, g, b;

      //******  16位颜色转换 ****** 
      uint16_t color = color_p[1] << 8 | color_p[0];
      r = (color >> 11) & 0x1F;
      g = (color >> 5) & 0x3F;
      b = color & 0x1F;
      if (r > 31 / 2) bitWrite(jdi_color, 3, 1); // 红色
      if (g > 63 / 2) bitWrite(jdi_color, 2, 1); // 绿色
      if (b > 31 / 2) bitWrite(jdi_color, 1, 1); // 蓝色
      color_p += 2;

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
    }
    // 行结尾添加结束命令
    buf_HOR[area->x2 + 3] = 0x00;
    buf_HOR[area->x2 + 4] = 0x00;
    //推送一行
    jdi_display.pushPixelsDMA(buf_HOR, BUF_HOR_NUM);
    //delay(500);
    //Serial.println();
  }
  // delay(1000);
  lv_disp_flush_ready(disp);
}

void demo_label()
{
  /*更改活动屏幕的背景色*/
  // lv_obj_set_style_bg_color(lv_screen_active(), lv_color_make(255, 0, 255), LV_PART_MAIN);

  /*Create a white label, set its text and align it to the center*/
  // lv_obj_t * label = lv_label_create(lv_screen_active());
  // lv_label_set_text(label, "Hello world");
  // lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
  // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

  /*lv_obj_t *ta1 = lv_textarea_create(lv_scr_act());
  lv_obj_set_size(ta1, 70, 30);
  lv_obj_align(ta1, LV_ALIGN_CENTER, 0, -25);
  lv_obj_set_style_bg_color(ta1, lv_color_make(255, 0, 0), LV_STATE_DEFAULT);*/

  // 设置文本框的大小和位置
  /*
  lv_obj_t *ta1 = lv_textarea_create(lv_scr_act());
  lv_obj_set_size(ta1, 70, 30);
  lv_obj_align(ta1, LV_ALIGN_CENTER, 0, 30);
  lv_obj_set_style_bg_color(ta1, lv_color_make(255, 0, 0), LV_STATE_DEFAULT); // rgb
  */

  // 设置文本框的大小和位置
  lv_obj_t *ta2 = lv_textarea_create(lv_scr_act());
  lv_obj_set_size(ta2, 70, 30);
  lv_obj_align(ta2, LV_ALIGN_CENTER, 0, -25);
  lv_obj_set_style_bg_color(ta2, lv_color_make(0, 0, 255), LV_STATE_DEFAULT); // rgb

  lv_obj_t *label2 = lv_label_create(lv_scr_act());
  //lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL);
  //lv_obj_set_width(label2, 70 - 4);
  lv_obj_align(label2, LV_ALIGN_CENTER, 0, -25);
  lv_obj_set_style_text_color(label2, lv_color_make(255, 255, 255), LV_PART_MAIN); // 设置字体颜色
  //lv_label_set_text_fmt(label2, "%d", 123);
  lv_label_set_text(label2, "a ba a ba");

  // 设置文本框的大小和位置
  lv_obj_t *ta = lv_textarea_create(lv_scr_act());
  lv_obj_set_size(ta, 124, 30);
  lv_obj_align(ta, LV_ALIGN_CENTER, 0, -56);
  lv_obj_set_style_bg_color(ta, lv_color_make(0, 255, 0), LV_STATE_DEFAULT); // rgb

  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
  lv_obj_set_width(label, 124 - 4);
  lv_label_set_text(label, "Hello Arduino, I'm LVGL! -V9.1.0");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, -56);
}

void demo_img()
{
  // 1.准备一张图片
  LV_IMG_DECLARE(maomao);
  // 2.创建一个lv_img对象
  lv_obj_t *img1 = lv_image_create(lv_screen_active());
  // 3.给对象设置图片
  lv_image_set_src(img1, &maomao);
  // 4.设置图片位置
  lv_obj_align(img1, LV_ALIGN_BOTTOM_MID, 0, 0);
}

void demo_gif()
{
  /*LV_IMG_DECLARE(yqs);
  lv_obj_t *gif2 = lv_gif_create(lv_screen_active());
  lv_gif_set_src(gif2, &yqs);
  lv_obj_align(gif2, LV_ALIGN_TOP_MID, 0, 0);*/

  // 1.准备一张图片
  LV_IMG_DECLARE(qft);
  // 2.创建一个lv_img对象
  lv_obj_t *gif1 = lv_gif_create(lv_screen_active());
  // 3.给对象设置图片
  lv_gif_set_src(gif1, &qft);
  // 4.设置图片位置
  lv_obj_align(gif1, LV_ALIGN_BOTTOM_MID, 0, 0);
}

void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("1111");
  jdi_init();
  lvgl_init();
  demo_label();
  //demo_img();
  demo_gif();
}
uint32_t time11 = 0;

void loop()
{
  long last_time = millis();

  yield();
  
  lv_task_handler(); /* 让 GUI 去做它该做的事 */

  lv_tick_inc(int(millis() - last_time));
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