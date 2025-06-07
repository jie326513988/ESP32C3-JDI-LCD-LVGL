/*
 * Copyright (c) 2022, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <Wire.h>

#include <Arduino.h>
#include <SensirionI2CSgp40.h>
#include <SensirionI2CSht4x.h>
#include <VOCGasIndexAlgorithm.h>

SensirionI2CSht4x sht4x;
SensirionI2CSgp40 sgp40;

// 采样间隔（秒）
// 此代码使用约200毫秒的固定加热脉冲进行测量，因此采样间隔定义了占空比
float sampling_interval = 1.f;

VOCGasIndexAlgorithm voc_algorithm(sampling_interval);

char errorMessage[32];

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }

    Wire.begin();

    sht4x.begin(Wire);
    sgp40.begin(Wire);

    delay(1000);  // 某些Arduino板需要串行就绪

    Serial.print("采样间隔（秒）：\t");
    Serial.println(voc_algorithm.get_sampling_interval());
    Serial.println("");
}

//sgp40测量原始信号低功率
void sgp40MeasureRawSignalLowPower(uint16_t compensationRh,
                                   uint16_t compensationT, uint16_t* error) {
    uint16_t srawVoc = 0;
    int32_t voc_index = 0;
    // 请求第一次测量以加热板材（忽略结果）
    *error = sgp40.measureRawSignal(compensationRh, compensationT, srawVoc);
    if (*error) {
        return;
    }

    // 延迟170毫秒，让盘子加热。
    // 请记住，测量命令已经包含30ms的延迟
    delay(140);

    // 请求测量值
    *error = sgp40.measureRawSignal(compensationRh, compensationT, srawVoc);
    if (*error) {
        return;
    }

    Serial.print("\t");
    Serial.print("srawVOC: ");
    Serial.println(srawVoc);

    // Turn heater off
    *error = sgp40.turnHeaterOff();
    if (*error) {
        return;
    }

    // 通过气体指数算法处理原始信号以获得VOC指数值
    voc_index = voc_algorithm.process(srawVoc);
    Serial.print("\t");
    Serial.print("VOC 指数: ");
    Serial.println(voc_index);
}

//从SHT4x获取补偿值
void getCompensationValuesFromSHT4x(uint16_t* compensationRh,
                                    uint16_t* compensationT, uint16_t* error) {
    float humidity = 0;     // %RH
    float temperature = 0;  // degreeC
    *error = sht4x.measureHighPrecision(temperature, humidity);
    if (*error) {
        return;
    }
    Serial.print("T:");
    Serial.print(temperature);
    Serial.print("\t");
    Serial.print("RH:");
    Serial.print(humidity);

    //将温度和湿度转换为SGP40接口定义的滴答声
    //注意：如果您读取RH和T原始信号，请查看数据表中的刻度规格，因为不同传感器的刻度规格可能不同
    *compensationT = static_cast<uint16_t>((temperature + 45) * 65535 / 175);
    *compensationRh = static_cast<uint16_t>(humidity * 65535 / 100);
}

void loop() {
    uint16_t error;
    uint16_t compensationRh =
        0x8000;  // 初始化为SGP40定义的默认值
    uint16_t compensationT =
        0x6666;  // 初始化为SGP40定义的默认值

    //1.睡眠：我们需要延迟来匹配所需的采样间隔
    // 在低功耗模式下，SGP40需要200毫秒来获取值。
    // SHT4X还包括10ms的延迟
    delay(int(sampling_interval) * 1000 - 210);

    // 2. 测量SGP内部补偿的温度和湿度
    getCompensationValuesFromSHT4x(&compensationRh, &compensationT, &error);
    if (error) {
        Serial.print(
            "SHT4x - Error trying to execute measureHighPrecision(): ");
        errorToString(error, errorMessage, sizeof(errorMessage));
        Serial.println(errorMessage);
        Serial.println("Fallback to use default values for humidity and "
                       "temperature compensation for SGP40");
    }

    // 3. Measure SGP40 signals using low power mode
    sgp40MeasureRawSignalLowPower(compensationRh, compensationT, &error);
    if (error) {
        Serial.print(
            "SGP40 - Error trying to acquire data in low power mode: ");
        errorToString(error, errorMessage, sizeof(errorMessage));
        Serial.println(errorMessage);
    }
}
