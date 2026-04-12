/* 			|																																											|
				|                                                                                     |
				|    AUTHOR:                TOM GONCIN                                                |
				|																																											|
				|    FILE DECSCRIPTION:     LCD Header File																						|
				|_____________________________________________________________________________________| */
				
				
				

								#ifndef LCD_H
								#define LCD_H


											#include "stm32f10x.h"
											#include <stdint.h>
														
											#include "i2c.h"
											
// 													Base 7-bit address for the PCF8574 LCD Backpack
															#define LCD_ADDR 0x27

//								 													LCD Functions 	( High-Level )																					
																					void LCD_Init(void)	;
																					
																					void LCD_SetCursor(uint8_t row, uint8_t col);
																					void LCD_SendString(char *str);
																					void LCD_Clear(void);
								#endif
								
								

