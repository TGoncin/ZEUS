	/* _______________________________________________________________________________________________________________________________________
		|																																																																			  |
		|																																																																			  |
		|			AUTHOR:												TOM GONCIN																																													|
		|																																																																			  |
		| 		DATE FILE LAST EDITED:				MARCH 13, 2026 - 23:22 CST																																					|
		|																																																																			  |
		| 		FILE DECSCRIPTION:						Soil Moisture Sensor Source File 																																		|
		|																																																																			  |															
		|_______________________________________________________________________________________________________________________________________| */


				#include "soilSensor.h"




//<---- Sensor Initialization ---->



						void SoilSensor_Init(void)
							{
														
// 								Enable clock for GPIOA, GPIOB, and ADC1
								
										RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_ADC1EN;
																	
								
// 								Configure PB0 as General Purpose Output Push-Pull (Max speed 2 MHz) for Sensor Power	
								
										GPIOB->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0); 	
										GPIOB->CRL |= GPIO_CRL_MODE0_1; 

								
// 								Configure PA0 as Analog Input for Sensor Signal	
								
										GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);			
															
								
								
// 					Configure ADC1	
								
								
// 								Wake up ADC
								
										ADC1->CR2 |= ADC_CR2_ADON;
								
// 								Wait for ADC to stabilize (approx 1us)

										for(volatile int i = 0; i < 1000; i++);
																
// 								Start Calibration

										ADC1->CR2 |= ADC_CR2_CAL; 
										
// 								Wait for calibration to finish

										while(ADC1->CR2 & ADC_CR2_CAL);
							}

				
							
							
							
							
//---->	POWER ON :		Soil Moisture Sensor <----
							
						void SoilSensor_PowerOn(void)			{		GPIOB->BSRR = GPIO_BSRR_BS0;		}		//	Set PB0 HIGH (Logic 1)
						
						
//----> POWER OFF :	Soil Moisture Sensor<----
						
						void SoilSensor_PowerOff(void)		{		GPIOB->BSRR = GPIO_BSRR_BR0;		}		//  Set PB0 LOW (Logic 0)

				
						
						
						
//----> READ Soil Moisture Sensor <----
						
						
						
						uint16_t SoilSensor_Read(void)
							{
								
// 								Channel 0 (PA0)
								
										ADC1->SQR3 = 0;
								
// 								Start conversion
								
										ADC1->CR2 |= ADC_CR2_ADON;
								
// 								Wait for End Of Conversion
								
										while(!(ADC1->SR & ADC_SR_EOC))
											{
														__NOP();
											};
										
// 								Return Data Register value
											
										return ADC1->DR;
							}
							
							
							