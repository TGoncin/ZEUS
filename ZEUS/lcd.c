

	/* _______________________________________________________________________________________________________________________________________________________
		|																																																																			  								|
		|																																																																			  								|
		|			AUTHOR:																				TOM GONCIN																																													|			
		|																																																																			  								|
		|			FILE LAST EDITED DATE:												MARCH 13, 2026 - 00:24 CST																																					|
		|																																																																    				 						|
		| 		FILE DECSCRIPTION:														LCD Source File  																																										|
		|																											-> Bare-metal LCD processing																																			|
		|																											-> Uses I2C Configuration 																																				|
		|																											-> High Level							 																																				|
		|_______________________________________________________________________________________________________________________________________________________| */




#include "lcd.h"
#include "i2c.h"
#include "delay.h"



			static void LCD_Write_Nibble(uint8_t nibble, uint8_t rs)
				{
							uint8_t data = nibble | rs | 0x08; // BL ON
					
							i2c_waitForReady();
							i2c_sendStart();
					
							if (i2c_sendAddrForWrite(LCD_ADDR) == 0) 
								{
										i2c_sendData(data | 0x04); // EN High
										delay_us(10);
										i2c_sendData(data & ~0x04); // EN Low
								}
								
							i2c_sendStop();
							delay_us(50);
				}

			
			
			
			
			
// ( MUST BE ABOVE INIT )			
				
		void LCD_SendCmd(uint8_t cmd)
			{
						LCD_Write_Nibble(cmd & 0xF0, 0);
						LCD_Write_Nibble((cmd << 4) & 0xF0, 0);
			}			


		
		
		
		void LCD_Init(void)
			{
						i2c_init();
						delay_ms(100);
				
				
// 			waking up sequence ( 4-bit ) from your working profile
				
						LCD_Write_Nibble(0x30, 0); delay_ms(5);
						LCD_Write_Nibble(0x30, 0); delay_us(150);
						LCD_Write_Nibble(0x30, 0); delay_us(150);
						LCD_Write_Nibble(0x20, 0); 
						
				
				
						LCD_SendCmd(0x28); // 4-bit, 2 lines
						LCD_SendCmd(0x0C); // Display ON
						LCD_SendCmd(0x06); // Auto-inc
						LCD_Clear();
			}


		
		

			void LCD_SendData(uint8_t data)
				{
							LCD_Write_Nibble(data & 0xF0, 1);
							LCD_Write_Nibble((data << 4) & 0xF0, 1);
				}
			
		
		
		

			void LCD_SendString(char *str)		{				while (*str) LCD_SendData(*str++);		}

		
		
			
		
		
			void LCD_SetCursor(uint8_t row, uint8_t col)
				{
							uint8_t off[] = {0x00, 0x40, 0x14, 0x54};
							LCD_SendCmd(0x80 | (col + off[row > 3 ? 3 : row]));
				}
			
		

				
				
				

			void LCD_Clear(void)
				{
							LCD_SendCmd(0x01);
							delay_ms(2);
				}