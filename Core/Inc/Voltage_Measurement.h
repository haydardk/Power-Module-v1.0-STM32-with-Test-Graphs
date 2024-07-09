/*
 * Voltage_Measurement.h
 *
 *  Created on: Jul 9, 2024
 *      Author: HAYDAR DENİZ KORKMAZ
 */

#ifndef INC_VOLTAGE_MEASUREMENT_H_
#define INC_VOLTAGE_MEASUREMENT_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_adc.h"
#include <stdio.h>

extern ADC_HandleTypeDef hadc1;

// Voltaj değerleri için sabitler
#define V_12_60 99.50
#define V_12_55 97.74
#define V_12_50 95.93
#define V_12_45 94.07
#define V_12_40 92.17
#define V_12_35 90.22
#define V_12_30 88.22
#define V_12_25 86.16
#define V_12_20 84.03
#define V_12_15 81.85
#define V_12_10 79.59
#define V_12_05 77.25
#define V_12_00 74.83
#define V_11_95 72.31
#define V_11_90 69.70
#define V_11_85 66.98
#define V_11_80 64.13
#define V_11_75 61.14
#define V_11_70 58.00
#define V_11_65 54.69
#define V_11_60 51.18
#define V_11_55 47.43
#define V_11_50 43.42
#define V_11_45 39.08
#define V_11_40 34.35
#define V_11_35 29.14
#define V_11_30 23.31
#define V_11_25 16.68
#define V_11_20 8.94
#define V_11_15 0.0

void Process_Voltage( double *battery_percentage);
void Read_Voltage();
void Voltage_ADC_Init();

#endif /* INC_VOLTAGE_MEASUREMENT_H_ */
