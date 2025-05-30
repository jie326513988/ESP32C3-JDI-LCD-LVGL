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

#define DISPLAY_WIDTH 0 // 72 Display width in pixel
#define DISPLAY_HEIGHT 0 //144 Display height in pixel

//=================================================================
// Wiring details: https://github.com/Gbertaz/JDI_MIP_Display#wiring
//=================================================================

//===============================
//esp32c3自己画板
#define PIN_SCS 7         // SPI芯片选择信号引脚
#define PIN_DISP 6        // 显示器ON/OFF开关信号引脚
#define PIN_FRONTLIGHT -1 // 前灯针脚。可选，具体取决于显示器型号

//esp32c3开发板
/*#define PIN_SCS 10        // SPI芯片选择信号引脚
#define PIN_DISP 3        // 显示器ON/OFF开关信号引脚
#define PIN_FRONTLIGHT -1 // 前灯针脚。可选，具体取决于显示器型号*/
