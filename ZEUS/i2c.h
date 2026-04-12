/* 			|																																											|
				|                                                                                     |
				|    AUTHOR:                TOM GONCIN                                                |
				|																																											|
				|    FILE DECSCRIPTION:     I2C Header File														                |
				|_____________________________________________________________________________________| */
				
				
				

							#ifndef I2C_H
							#define I2C_H


													#include "stm32f10x.h"
													#include <stdint.h>


// 																				I2C Functions			( Low-Level )
					
																									void i2c_init(void);
																									void i2c_waitForReady(void);
																									void i2c_sendStart(void);
																									void i2c_sendStop(void);
																									
																									uint8_t i2c_sendAddrForWrite(uint8_t addr);
																									uint8_t i2c_sendData(uint8_t data);
									#endif