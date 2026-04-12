	/* _______________________________________________________________________________________________________________________________________________________
		|																																																																			  								|
		|			AUTHOR:																				TOM GONCIN																																													|			
		|																																																																			  								|
		|			FILE LAST EDITED DATE:												MARCH 13, 2026 - 23:29 CST																																					|
		|																																																																    				 						|
		| 		FILE DECSCRIPTION:														Relay Source File			 								 																															|
		|																											-> Set up, default & ON/OFF configurations																												|
		|_______________________________________________________________________________________________________________________________________________________| */

	
				#include "relay.h"
				#include "i2c.h"



							#define RELAY_I2C_ADDR 0x18
							
							
							
							

		void Relay_Init(void)
			{

						i2c_waitForReady();
						i2c_sendStart();
				
// 				Send 0x00 to ensure relay starts OFF on power turned on				
				
						if (i2c_sendAddrForWrite(RELAY_I2C_ADDR) == 0)							{		i2c_sendData(0x00);		}
						
						i2c_sendStop(); 	// OFF
			}

			
			
			
			
		void Relay_On(void)
			{
						i2c_waitForReady();
						i2c_sendStart();
				
						if (i2c_sendAddrForWrite(RELAY_I2C_ADDR) == 0)						{		i2c_sendData(0x01);		}
						i2c_sendStop();
			}

			
			
			
			
		void Relay_Off(void)
			{
						i2c_waitForReady();
						i2c_sendStart();
				
						if (i2c_sendAddrForWrite(RELAY_I2C_ADDR) == 0)						{			i2c_sendData(0x00);		}
						i2c_sendStop();
			}