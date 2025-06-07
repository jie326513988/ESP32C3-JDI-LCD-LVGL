/*
 * Copyright (c) 2021, Sensirion AG
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
#include <NOxGasIndexAlgorithm.h>
#include <SensirionI2CSgp41.h>
#include <SensirionI2CSht4x.h>
#include <VOCGasIndexAlgorithm.h>

SensirionI2CSht4x sht4x;
SensirionI2CSgp41 sgp41;

VOCGasIndexAlgorithm voc_algorithm;
NOxGasIndexAlgorithm nox_algorithm;

// 氮氧化物调节所需的时间（秒）
uint16_t conditioning_s = 10;

char errorMessage[64];

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }

    Wire.begin();

    sht4x.begin(Wire);
    sgp41.begin(Wire);

    delay(1000);  // 某些Arduino板需要串行就绪

    int32_t index_offset;
    int32_t learning_time_offset_hours;
    int32_t learning_time_gain_hours;
    int32_t gating_max_duration_minutes;
    int32_t std_initial;
    int32_t gain_factor;
    // 获取当前参数以自定义气体指数算法。
    voc_algorithm.get_tuning_parameters(
        index_offset, learning_time_offset_hours, learning_time_gain_hours,
        gating_max_duration_minutes, std_initial, gain_factor);

    Serial.println("\nVOC气体指数算法参数");
    Serial.print("索引偏移量:\t");
    Serial.println(index_offset);
    Serial.print("学习时间偏移小时数：\t");
    Serial.println(learning_time_offset_hours);
    Serial.print("学习时间增加小时数：\t");
    Serial.println(learning_time_gain_hours);
    Serial.print("门控最长持续时间分钟：\t");
    Serial.println(gating_max_duration_minutes);
    Serial.print("标准初始值：\t");
    Serial.println(std_initial);
    Serial.print("增益系数：\t");
    Serial.println(gain_factor);

    // 获取当前参数以自定义气体指数算法。
    nox_algorithm.get_tuning_parameters(
        index_offset, learning_time_offset_hours, learning_time_gain_hours,
        gating_max_duration_minutes, std_initial, gain_factor);

    Serial.println("\nNOx气体指数算法参数");
    Serial.print("索引偏移量:\t");
    Serial.println(index_offset);
    Serial.print("学习时间偏移小时数:\t");
    Serial.println(learning_time_offset_hours);
    Serial.print("门控最大持续时间分钟:\t");
    Serial.println(gating_max_duration_minutes);
    Serial.print("增益因子:\t");
    Serial.println(gain_factor);
    Serial.println("");
}

void loop() {
    uint16_t error;
    float humidity = 0;     // %RH
    float temperature = 0;  // degreeC
    uint16_t srawVoc = 0;
    uint16_t srawNox = 0;
    // 以SGP41定义的刻度为单位
    uint16_t defaultCompenstaionRh = 0x8000;  // 湿度默认配置
    uint16_t defaultCompenstaionT = 0x6666;   // 温度默认配置
    uint16_t compensationRh = 0;              // 湿度补偿
    uint16_t compensationT = 0;               // 温度补偿

    // 1. 睡眠：根据气体指数算法的定义，每秒测量一次（1Hz）前提
    delay(1000);

    // 2. 测量SGP内部补偿的温度和湿度
    error = sht4x.measureHighPrecision(temperature, humidity);
    if (error) {
        Serial.print(
            "SHT4x-尝试执行measureHighPrecision()时出错: ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
        Serial.println("回退到使用SGP41湿度和“”温度补偿的默认值");
        compensationRh = defaultCompenstaionRh;
        compensationT = defaultCompenstaionT;
    } else {
        Serial.print("T:");
        Serial.print(temperature);
        Serial.print("\t");
        Serial.print("RH:");
        Serial.println(humidity);

        //将温度和湿度转换为SGP41接口定义的滴答声
        //注意：如果您读取RH和T原始信号，请查看数据表中的刻度规格，因为不同传感器的刻度规格可能不同
        compensationT = static_cast<uint16_t>((temperature + 45) * 65535 / 175);
        compensationRh = static_cast<uint16_t>(humidity * 65535 / 100);
    }

    // 3. 测量SGP4x信号
    if (conditioning_s > 0) {
        // 在氮氧化物调节期间（10秒），SRAW氮氧化物将保持为0
        error =
            sgp41.executeConditioning(compensationRh, compensationT, srawVoc);
        conditioning_s--;
    } else {
        error = sgp41.measureRawSignals(compensationRh, compensationT, srawVoc,
                                        srawNox);
    }

    // 4. 通过气体指数算法处理原始信号，得到VOC和NOx指数值
    if (error) {
        Serial.print("SGP41-尝试执行measureRawSignals（）时出错：");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        int32_t voc_index = voc_algorithm.process(srawVoc);
        int32_t nox_index = nox_algorithm.process(srawNox);
        Serial.print("VOC 指数: ");
        Serial.print(voc_index);
        Serial.print("\t");
        Serial.print("NOx 指数: ");
        Serial.println(nox_index);
    }
}
