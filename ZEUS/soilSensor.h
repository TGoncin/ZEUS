	/* _______________________________________________________________________________________________________________________________________
		|																																																																			  |
		|																																																																			  |
		|			AUTHOR:												TOM GONCIN																																													|
		|																																																																			  |
		| 		DATE FILE LAST EDITED:				MARCH 13, 2026 - 23:14 CST																																					|
		|																																																																			  |
		| 		FILE DECSCRIPTION:						Soil Moisture Sensor Header File																																		|
		|																																																																			  |
		|																																																																				|																		
		|_______________________________________________________________________________________________________________________________________| */



			#ifndef SOIL_SENSOR_H
			#define SOIL_SENSOR_H
															#include "stm32f10x.h"


																										void SoilSensor_Init(void);
																																			
																										void SoilSensor_PowerOn(void);
																										void SoilSensor_PowerOff(void);
																																			
																										uint16_t SoilSensor_Read(void);
			#endif