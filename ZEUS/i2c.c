

	/* _______________________________________________________________________________________________________________________________________________________
		|																																																																			  								|
		|																																																																			  								|
		|			AUTHOR:																				TOM GONCIN																																													|			
		|																																																																			  								|
		|			FILE LAST EDITED DATE:												MARCH 13, 2026 - 00:24 CST																																					|
		|																																																																    				 						|
		| 		FILE DECSCRIPTION:														I2C Source File  																																										|
		|																											-> Bare-metal Driver for LCD																																			|
		|																											-> Low Level I2C1																																									|
		|_______________________________________________________________________________________________________________________________________________________| */
				
			#include "stm32f10x.h"
			#include "i2c.h"
			
			
			

			void i2c_init(void)
				{
					
// 					enable clocks for I2C related GPIOs
					
							RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
							RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

// 					PB6/PB7 as Alternate Function Open-Drain
					
							GPIOB->CRL &= ~((0xF << 24) | (0xF << 28)); 		// Clearing first (Combine & invert)
							GPIOB->CRL |=  ((0xF << 24) | (0xF << 28)); 		// Setting

//					Must clean/force to reset state
					
							I2C1->CR1 |= I2C_CR1_SWRST;
							for(volatile int i=0; i<100; i++); 	//volatile to execute loop WITHOUT optimizing away since its doing nothing (Reset) [ COMPILER DELETED EMPTY LOOPS ]
							I2C1->CR1 &= ~I2C_CR1_SWRST;

// 					36MHz APB1 @ 100kHz Standard Mode
					
							I2C1->CR2 = 36;   
							I2C1->CCR = 180;  
							I2C1->TRISE = 37; 

							I2C1->CR1 |= I2C_CR1_PE;
					}
				
					
					
					
					
					

		void i2c_waitForReady(void)
			{
						uint32_t timeout = 50000;
						while(((I2C1->SR2 & I2C_SR2_BUSY) != 0) && --timeout); 
			}
			
			
			
			
			
			
			

		void i2c_sendStart(void)
			{
							uint32_t timeout = 50000;
							I2C1->CR1 |= I2C_CR1_START;
							while(((I2C1->SR1 & I2C_SR1_SB) == 0) && --timeout);
							(void)I2C1->SR2; 
			}
			
			
			
			
			
			

		void i2c_sendStop(void)			{    I2C1->CR1 |= I2C_CR1_STOP;		}




		
		

		uint8_t i2c_sendAddrForWrite(uint8_t addr)
			{
				
						uint32_t timeout = 50000;
						I2C1->DR = (addr << 1); 		// 	7-bit to 8-bit Write
				
						while (timeout--) 
							{
								
// 						NACK		
								
								if (I2C1->SR1 & I2C_SR1_AF) 
									{ 
												I2C1->SR1 &= ~I2C_SR1_AF;
												i2c_sendStop();
												return 1;
									}
					
// 			Success
									
							if (I2C1->SR1 & I2C_SR1_ADDR) 
								{
									(void)I2C1->SR2;
									return 0;
							}
					}
// 			Timeout
					
					return 2; 
			}
			
			
			
			
			

		uint8_t i2c_sendData(uint8_t data)
			{
							uint32_t timeout = 50000;
							I2C1->DR = data;
							while(((I2C1->SR1 & I2C_SR1_TXE) == 0) && --timeout);
							return (timeout == 0) ? 1 : 0;
			}
			
			