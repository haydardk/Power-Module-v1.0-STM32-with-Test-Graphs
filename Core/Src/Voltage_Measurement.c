/*
 * Voltage_Measurement.c
 *
 *  Created on: Jul 9, 2024
 *      Author: CASPER
 */

#include "Voltage_Measurement.h"

float voltage_value;
uint16_t raw_value_v;
int veri;
int ADC_MAX_VALUE= 4095;
int Voltage_Divider = 10;
float Ref_Voltage = 3.07; // STM32F411VET Kartı için Geçerli !
float ADC_read_delay = 0.5 ;// Saniye
float battery_percentage;
float voltage_buffer[20];
float avg_voltage;

void Process_Voltage( double *battery_percentage) {

    if (avg_voltage >= 12.575) {
        *battery_percentage = V_12_60;
    }
    else if (avg_voltage >= 12.525 && avg_voltage < 12.575) {
        *battery_percentage = V_12_55;
    }
    else if (avg_voltage >= 12.475 && avg_voltage < 12.525) {
        *battery_percentage = V_12_50;
    }
    else if (avg_voltage >= 12.425 && avg_voltage < 12.475) {
        *battery_percentage = V_12_45;
    }
    else if (avg_voltage >= 12.375 && avg_voltage < 12.425) {
        *battery_percentage = V_12_40;
    }
    else if (avg_voltage >= 12.325 && avg_voltage < 12.375) {
        *battery_percentage = V_12_35;
    }
    else if (avg_voltage >= 12.275 && avg_voltage < 12.325) {
        *battery_percentage = V_12_30;
    }
    else if (avg_voltage >= 12.225 && avg_voltage < 12.275) {
        *battery_percentage = V_12_25;
    }
    else if (avg_voltage >= 12.175 && avg_voltage < 12.225) {
        *battery_percentage = V_12_20;
    }
    else if (avg_voltage >= 12.125 && avg_voltage < 12.175) {
        *battery_percentage = V_12_15;
    }
    else if (avg_voltage >= 12.075 && avg_voltage < 12.125) {
        *battery_percentage = V_12_10;
    }
    else if (avg_voltage >= 12.025 && avg_voltage < 12.075) {
        *battery_percentage = V_12_05;
    }
    else if (avg_voltage >= 11.975 && avg_voltage < 12.025) {
        *battery_percentage = V_12_00;
    }
    else if (avg_voltage >= 11.925 && avg_voltage < 11.975) {
        *battery_percentage = V_11_95;
    }
    else if (avg_voltage >= 11.875 && avg_voltage < 11.925) {
        *battery_percentage = V_11_90;
    }
    else if (avg_voltage >= 11.825 && avg_voltage < 11.875) {
        *battery_percentage = V_11_85;
    }
    else if (avg_voltage >= 11.775 && avg_voltage < 11.825) {
        *battery_percentage = V_11_80;
    }
    else if (avg_voltage >= 11.725 && avg_voltage < 11.775) {
        *battery_percentage = V_11_75;
    }
    else if (avg_voltage >= 11.675 && avg_voltage < 11.725) {
        *battery_percentage = V_11_70;
    }
    else if (avg_voltage >= 11.625 && avg_voltage < 11.675) {
        *battery_percentage = V_11_65;
    }
    else if (avg_voltage >= 11.575 && avg_voltage < 11.625) {
        *battery_percentage = V_11_60;
    }
    else if (avg_voltage >= 11.525 && avg_voltage < 11.575) {
        *battery_percentage = V_11_55;
    }
    else if (avg_voltage >= 11.475 && avg_voltage < 11.525) {
        *battery_percentage = V_11_50;
    }
    else if (avg_voltage >= 11.425 && avg_voltage < 11.475) {
        *battery_percentage = V_11_45;
    }
    else if (avg_voltage >= 11.375 && avg_voltage < 11.425) {
        *battery_percentage = V_11_40;
    }
    else if (avg_voltage >= 11.325 && avg_voltage < 11.375) {
        *battery_percentage = V_11_35;
    }
    else if (avg_voltage >= 11.275 && avg_voltage < 11.325) {
        *battery_percentage = V_11_30;
    }
    else if (avg_voltage >= 11.225 && avg_voltage < 11.275) {
        *battery_percentage = V_11_25;
    }
    else if (avg_voltage >= 11.175 && avg_voltage < 11.225) {
        *battery_percentage = V_11_20;
    }
    else if (avg_voltage >= 11.125 && avg_voltage < 11.175) {
        *battery_percentage = V_11_15;
    }
    else {
        *battery_percentage = 0.0; // 11.15 voltajı ve altı için yüzde 0 kabul edildi.
    }
}

void Read_Voltage(){
	float temp_v;
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_4;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	HAL_ADC_Start(&hadc1);

	if( HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) == HAL_OK ){
		raw_value_v = HAL_ADC_GetValue(&hadc1);
		veri++;
	}
	voltage_value =  0.5 + (raw_value_v *(Ref_Voltage) * Voltage_Divider) / (ADC_MAX_VALUE);
	HAL_ADC_Stop(&hadc1);
	int i;
	if ((veri-1)>= 20 ){
		voltage_buffer[(veri-1)%20] = voltage_value;
		for (i=0;i<20;i++){
			temp_v = temp_v + voltage_buffer[i];
		}
		avg_voltage = temp_v/20;
	}else{
		for (i=0;i<veri;i++){
			temp_v = temp_v + voltage_buffer[i];
		}
		avg_voltage = temp_v/veri;
	}
}

void Voltage_ADC_Init(){
	/* USER CODE BEGIN ADC1_Init 0 */

	  /* USER CODE END ADC1_Init 0 */

	  ADC_ChannelConfTypeDef sConfig = {0};

	  /* USER CODE BEGIN ADC1_Init 1 */

	  /* USER CODE END ADC1_Init 1 */

	  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	  */
	  hadc1.Instance = ADC1;
	  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	  hadc1.Init.ScanConvMode = DISABLE;
	  hadc1.Init.ContinuousConvMode = DISABLE;
	  hadc1.Init.DiscontinuousConvMode = DISABLE;
	  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	  hadc1.Init.NbrOfConversion = 1;
	  hadc1.Init.DMAContinuousRequests = DISABLE;
	  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	  if (HAL_ADC_Init(&hadc1) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	  */
	  sConfig.Channel = ADC_CHANNEL_4;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  /* USER CODE BEGIN ADC1_Init 2 */

	  /* USER CODE END ADC1_Init 2 */


}
