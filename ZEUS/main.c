


	/* _______________________________________________________________________________________________________________________________________________________
		|																																																																			  								|
		|																																																																			  								|
		|			AUTHOR:																				TOM GONCIN																																													|			
		|																																																																			  								|
		|			FILE LAST EDITED DATE:												MARCH 13, 2026 - 00:24 CST																																					|
		|																																																																    				 						|
		| 		FILE DECSCRIPTION:														ZEUS		Main Source File  																																					|
		|																											-> 4 Buttons Processing																																						|
		|																											-> State machines hardware override 																															|
		|_______________________________________________________________________________________________________________________________________________________| */
				
				

			#include "stm32f10x.h"
			#include <stdbool.h>
			
							#include "soilSensor.h"
							#include "relay.h"
							#include "i2c.h"
							#include "watchDogTimer.h"
							#include "delay.h"
							#include "buttons.h"
							#include "timer.h"
							#include "lcd.h"

// 															Hysteresis Zone

																		#define DRY_THRESHOLD 2300          // 		Dry soil			Calibrated ADC value
																		#define WET_THRESHOLD 3000          // 		Moist Soil		Calibrated ADC value



int main ( void ) 
{
	
//-------------------------> Initializations <-------------------------

	
	
	
    tim2_init (  );        // 	Hardware Delays 										us / ms
    tim3_init (  );        //   Tick 																REAL 1 SECOND
    Buttons_Init (  );     // 	Pull-Up hardwired
		SoilSensor_Init (  );  // 	Pins:	Analog & Power
    LCD_Init (  );         // 	I2C1 , 2004A display								0x27
    Relay_Init (  );       // 	Relay = OFF on startup 							I2C 0x18
    IWDG_Init (  );        // 	Watchdog for power cut							~26.2s timeout


	
	
	
//-------------------------> State variables <-------------------------
	
	
	
	
		uint16_t adc_high 					= 0;       // MAXIMUM -> HIGH CONDUCTIVITY reading on soil moisture sensor
		uint16_t adc_low  					= 4095;    // MINIMUM -> LOW CONDUCTIVITY reading on soil moisture sensor reading [ 12bit=(0,4095) ]
    uint16_t moisture_level     = 0;			 // ACTUAL soil sensosr reading
    uint16_t pump_run_time      = 0;   		 // TIM3 checks REAL seconds
		
    bool     is_evening_window       = false;
    bool     watering_required_tonight = false;

	
	
	
// ----> SET CURRENT TIME <----


    uint8_t hours   = 12;
    uint8_t minutes = 13;
    uint8_t seconds = 0;


    static int last_mode = -1;




//-------------------------> Main Loop <----------------------------




    while  ( 1 ) 
			{

				IWDG_Feed();

				
// ----> REAL-SECOND TICK  ( TIM3 )  <----			EVERYTHING is based on time - - - advances on 1s tick hardware
				
				
        if  ( tim3_second_elapsed (  )  ) // No drift. No accumulated delay_ms error.
        {
            seconds++;

            if  ( seconds >= 60 ) 
            {
									seconds = 0;
									minutes++;

									if  ( minutes >= 60 ) 
									{
												minutes = 0;
												hours++;

												if  ( hours >= 24 ) 		{		hours = 0;		}
									}
            }


						
						
						
// ----> SCHEDULED SOIL MOISTURE CHECK <----


            if  (   (  hours == 16 && minutes == 0 && seconds == 0  ) 		||	  (  hours == 18 && minutes == 0 && seconds == 0  )   ) 		//  (  16:00 and 18:00  )  a.k.a ONCE per day
							{
								
										SoilSensor_PowerOn (  );
										delay_ms ( 20 );
										moisture_level = SoilSensor_Read (  );
										SoilSensor_PowerOff (  );

									
										if       ( moisture_level < DRY_THRESHOLD )  		{ 	watering_required_tonight = true;	}
										else if  ( moisture_level > WET_THRESHOLD )  		{		watering_required_tonight = false;	}
							}


							
							
							
							
// ----> EVENING WINDOW CHECK <----
							
							
            is_evening_window =  ( hours == 20 && minutes >= 30 );   // 	20:30 to 20:59:59


							
							
							
// ----> RESET FLAGS <----				[ PM -> 21:00:00 ]	
							
							
							if  ( hours == 21 && minutes == 0 && seconds == 0 ) 
								{
											watering_required_tonight = false;
											pump_run_time = 0;   										// 	Tomorows FLOOD PROTECTION reset
								}

								
								

// ----> PUMP TIMER  ( Normal Mode only )  <----

							if  ( watering_required_tonight && is_evening_window && pump_run_time < 300 ) 								{		pump_run_time++;		}		//	++ ONLY during watering window -> real seconds
				}



			
			
//----> BUTTON STATE MACHINE <----

			
        int current_mode = Buttons_Get_ACTIVE_Mode (  );

        if  ( current_mode != last_mode ) 
					{
								LCD_Clear (  );
								last_mode = current_mode;
					}


				
				
				
//----> 	MODE 4: 	EMERGENCY / FORCE OFF 	<----

					
        if  ( current_mode == 4 ) 
					{
						
								Relay_Off (  );

							
								LCD_SetCursor ( 0, 0 ); LCD_SendString ( "SYSTEM DISABLED:    " );
								LCD_SetCursor ( 1, 0 ); LCD_SendString ( "FORCED OFF          " );
								LCD_SetCursor ( 2, 0 ); LCD_SendString ( "To Override: Turn ON" );
								LCD_SetCursor ( 3, 0 ); LCD_SendString ( "4TH BUTTON          " );

					}

				
				
				
				

// ----> 	MODE 3: 	FORCE ON 		= 	IGNORES:	Everything <----

					
        else if  ( current_mode == 3 ) 
					{
						
								Relay_On (  );

							
								LCD_SetCursor ( 0, 0 ); LCD_SendString ( "MANUAL MODE:        " );
								LCD_SetCursor ( 1, 0 ); LCD_SendString ( "All Config VOID     " );
								LCD_SetCursor ( 2, 0 ); LCD_SendString ( "System is Currently:" );
								LCD_SetCursor ( 3, 0 ); LCD_SendString ( "Watering...         " );
					}


					
					
					
					
					
// ----> 	MODE 2: VOID TIME  		= 	Uses:		Sensor 		[ SOIL POLLED EVERY ++ of loop ] <----
//																	IGNORES:	Schedule

					
					
        else if  ( current_mode == 2 ) 
					{	
						
								SoilSensor_PowerOn (  );
								delay_ms ( 20 );
								moisture_level = SoilSensor_Read (  );
								SoilSensor_PowerOff (  );

							
								bool manual_soil_is_dry =  ( moisture_level < DRY_THRESHOLD );

							
								LCD_SetCursor ( 0, 0 ); LCD_SendString ( "MODE: Day/Night VOID" );
						
						
// 					Displaying raw ADC values (Also for calibration)
						
								char buf[21];
								LCD_SetCursor ( 1, 0 ); LCD_SendString ( "Raw ADC:            " );
								
						
// 					Converting # to string manually
						
								buf[0] = '0' + (moisture_level / 1000);
								buf[1] = '0' + ((moisture_level % 1000) / 100);
								buf[2] = '0' + ((moisture_level % 100) / 10);
								buf[3] = '0' + (moisture_level % 10);
								buf[4] = ' '; buf[5] = ' '; buf[6] = ' ';
								buf[7] = '\0';
								
								
								LCD_SetCursor(1, 9);
								LCD_SendString(buf);
								
								delay_ms(500);

								if  ( manual_soil_is_dry ) 
									{
										
												Relay_On (  );
												LCD_SetCursor ( 2, 0 ); LCD_SendString ( "Soil Status: DRY    " );
												LCD_SetCursor ( 3, 0 ); LCD_SendString ( "Pump: RUNNING       " );
									}
								else
									{
								
												Relay_Off (  );
												LCD_SetCursor ( 2, 0 ); LCD_SendString ( "Soil Status: OK     " );
												LCD_SetCursor ( 3, 0 ); LCD_SendString ( "Pump: OFF           " );
									}
					}


					
					
					
					
					
//----> MODE 1: NORMAL 		=		Uses:		Schedule, sensor, time windowe 	<----

					
					
        else
					{
						
								LCD_SetCursor ( 0, 0 ); LCD_SendString ( "NORMAL MODE:        " );
								LCD_SetCursor ( 1, 0 ); LCD_SendString ( "Regular Operation   " );

						
								if  ( watering_required_tonight && is_evening_window ) 
									{
										
											if  ( pump_run_time < 300 ) 
												{
													
															Relay_On (  );
													
															LCD_SetCursor ( 2, 0 ); LCD_SendString ( "System is Currently:" );
															LCD_SetCursor ( 3, 0 ); LCD_SendString ( "Watering...         " );
												}
											else
												{
													
															Relay_Off (  );
													
															watering_required_tonight = false;
															LCD_SetCursor ( 2, 0 ); LCD_SendString ( "System Idle         " );
															LCD_SetCursor ( 3, 0 ); LCD_SendString ( "Watering Complete.  " );
												}
									}
								else
									{
										
											Relay_Off (  );

										
											if  ( watering_required_tonight && !is_evening_window ) 
												{
															LCD_SetCursor ( 2, 0 ); LCD_SendString ( "System Queued:      " );
															LCD_SetCursor ( 3, 0 ); LCD_SendString ( "Watering at 20:30   " );
												}
											else
												{
															LCD_SetCursor ( 2, 0 ); LCD_SendString ( "System Idle:        " );
															LCD_SetCursor ( 3, 0 ); LCD_SendString ( "Standby. No Action. " );
												}
									}
					}



        delay_ms ( 100 );			// 	PREVENTS RACING CONDITIONS 	from hammering I2C bus hammering
    }
	}