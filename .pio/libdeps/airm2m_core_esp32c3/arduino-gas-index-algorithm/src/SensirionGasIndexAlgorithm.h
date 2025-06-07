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

#ifndef SENSIRIONGASINDEXALGORITHM_H
#define SENSIRIONGASINDEXALGORITHM_H

extern "C" {
#include "algorithm/sensirion_gas_index_algorithm.h"
}

class SensirionGasIndexAlgorithm {

  public:
    SensirionGasIndexAlgorithm(const SensirionGasIndexAlgorithm&) = delete;
    SensirionGasIndexAlgorithm&
    operator=(const SensirionGasIndexAlgorithm&) = delete;

    explicit SensirionGasIndexAlgorithm(int32_t algorithm_type);
    explicit SensirionGasIndexAlgorithm(int32_t algorithm_type,
                                        float sampling_interval);
    ~SensirionGasIndexAlgorithm();

    /**
     * 设置参数以自定义气体指数算法。如果需要，在创建GasIndexAlgorithm的新实例后调用一次。
     * 否则，将使用默认值。
     *
     * @param index_offset 代表典型（平均）条件的气体指数。范围1..250，VOC默认为100，NOx默认为1
     * @param learning_time_offset_hours  偏移长期估计量的时间常数。大约两倍的学习时间后，过去的事件将被遗忘。
     * 范围1..1000[小时]，默认值12[小时]
     * @param learning_time_gain_hours    增益长期估计器的时间常数。大约两倍的学习时间后，过去的事件将被遗忘。
     * 范围1..1000[小时]，默认12[小时]注意：此值与NOx算法类型无关
     * @param gating_max_duration_minutes 门控的最大持续时间（高气体指数信号期间估计器冻结）。
     * 0（无门控）或范围1..3000[分钟]，VOC默认180[分钟]和NOx默认720[分钟]
     * @param std_initial 标准偏差的初步估计。较低的值会在初始学习期间增强事件，
     * 但可能会导致较大的设备间差异。范围10..5000，默认值50
     * NOTE: 该值与NOx算法类型无关
     * @param gain_factor 计算气体指数时用于缩放应用增益值的因子。范围1..1000，默认值230
     */
    void set_tuning_parameters(int32_t index_offset,
                               int32_t learning_time_offset_hours,
                               int32_t learning_time_gain_hours,
                               int32_t gating_max_duration_minutes,
                               int32_t std_initial, int32_t gain_factor);

    /**
     * 获取当前参数以自定义气体指数算法。
     * 有关参数的说明，请参阅set_tuning_parameters（）。
     */
    void get_tuning_parameters(int32_t& index_offset,
                               int32_t& learning_time_offset_hours,
                               int32_t& learning_time_gain_hours,
                               int32_t& gating_max_duration_minutes,
                               int32_t& std_initial, int32_t& gain_factor);

    /**
     * 获取算法使用的采样间隔
     */
    float get_sampling_interval();

    /**
     * 根据原始传感器值计算气体指数值。
     *
     * @param sraw        SGP4x传感器的原始值
     * @return            根据原始传感器值计算出的气体指数值。初始停电期间为零，之后为1-500
     */
    int32_t process(int32_t sraw);

    /**
     * 重置气体指数算法的内部状态。保留以前设置的调整参数。在测量中断后恢复操作时调用此命令。
     */
    void reset();

    static const int32_t ALGORITHM_TYPE_VOC = GasIndexAlgorithm_ALGORITHM_TYPE_VOC;
    static const int32_t ALGORITHM_TYPE_NOX = GasIndexAlgorithm_ALGORITHM_TYPE_NOX;

  protected:
    GasIndexAlgorithmParams* params = nullptr;
};

#endif /* SENSIRIONGASINDEXALGORITHM_H */
