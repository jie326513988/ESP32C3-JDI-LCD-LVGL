// MIT License
//
// Copyright(c) 2021 Giovanni Bertazzoni <nottheworstdev@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef JDI_MIP_Display_h
#define JDI_MIP_Display_h

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Display_cfg.h>

#if defined(ESP32)
#include "driver/spi_master.h"
#endif

// #define DIFF_LINE_UPDATE   // 差异行更新
#define HALF_WIDTH (DISPLAY_WIDTH / 2)

#define COLOR_BLACK 0x00
#define COLOR_BLUE 0x02
#define COLOR_GREEN 0x04
#define COLOR_CYAN 0x06
#define COLOR_RED 0x08
#define COLOR_MAGENTA 0x0a
#define COLOR_YELLOW 0x0c
#define COLOR_WHITE 0x0e

#define CMD_NO_UPDATE 0x00
#define CMD_BLINKING_BLACK 0x10
#define CMD_BLINKING_INVERSION 0x14
#define CMD_BLINKING_WHITE 0x18
#define CMD_ALL_CLEAR 0x20
#define CMD_VCOM 0x40
#define CMD_UPDATE 0x90

class JDI_MIP_Display : public Adafruit_GFX
{
public:
        JDI_MIP_Display();
        // 设置引脚、频率、是否开启DMA传输
        void begin(int sck = -1, int miso = -1, int mosi = -1, int ss = -1,
                   int fre = -1, bool dmaEN = 0, bool end_cb = 0);
        void refresh();
        void displayOn();
        void displayOff();
        void clearScreen();
        void noUpdate();
        void frontlightOn();
        void frontlightOff();
        void setBackgroundColor(uint16_t color);
        void drawBufferedPixel(int16_t x, int16_t y, uint16_t color);

        void pushPixelsDMA(uint8_t *image, uint32_t len);
        void deInitDMA(void);
        void registerDMACallback(void (*callback)(void));       // 注册DMA回调函数
        static void (*dma_callback)(void);                      // 静态DMA完成回调函数指针
        static void spi_dma_callback(spi_transaction_t *trans); // 静态SPI DMA回调函数

private:
        uint8_t _scs;                     // 芯片选择信号 Chip selection signal
        uint8_t _disp;                    // 显示ON/OFF开关信号 Display ON/OFF switch signal
        uint8_t _frontlight;              // 前置灯 Front lights
        uint16_t _background;             // 背景 background

        char _backBuffer[(DISPLAY_WIDTH / 2) * DISPLAY_HEIGHT];
#ifdef DIFF_LINE_UPDATE
        char _dispBuffer[(DISPLAY_WIDTH / 2) * DISPLAY_HEIGHT];
#endif
        void sendLineCommand(char *line_cmd, int line);
        void drawPixel(int16_t x, int16_t y, uint16_t color);
        bool compareBuffersLine(int lineIndex);

        // 检查DMA是否已完成-使用while（tft.dmaBusy）；等待阻塞
        // Check if DMA has been completed - use while (tft. dmaBusy); Waiting for blocking
        bool DMA_Enabled = false; // DMA启用状态的标志 Flag for DMA enabled status
        uint8_t spiBusyCheck = 0; // 要检查的ESP32传输缓冲区的数量 The number of ESP32 transmission buffers to be checked
        bool dmaBusy(void);       // 如果DMA仍在进行中，则返回true If DMA is still in progress, return true
        void dmaWait(void);       // 等待DMA完成 Waiting for DMA completion
        void _pushPixelsDMA(uint8_t *image, uint32_t len);
        bool initDMA(int sck, int miso, int mosi, int ss, int fre, bool end_cb = 0);
        void _deInitDMA(void);
};
#endif