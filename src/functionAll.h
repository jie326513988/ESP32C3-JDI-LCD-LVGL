void jdi_init();
void lvgl_init();

// imageProcessing.c
uint16_t create_rgb565(uint8_t r, uint8_t g, uint8_t b);
uint16_t create_rgb565(float f_r, float f_g, float f_b);
void modify_pixel_color(uint8_t *color_p, int16_t x, int16_t y, uint16_t new_color);
void modify_pixel_color(uint8_t *color_p, uint32_t pixel_offset, uint16_t new_color);
uint32_t getPixelIdx(int32_t x, int32_t y);
uint8_t colorThresholdLimit(uint8_t val1, int8_t val2,uint8_t max); // 颜色阈值限制
