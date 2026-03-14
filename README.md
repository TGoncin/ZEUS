# ZEUS
Automated Soil Moisture Controlled Irrigation System


## Purpose

The purpose of this project is to design and build a microcontroller based soil moisture monitoring and irrigation controller that automatically decides whether evening watering is required and, if necessary, activates a water pump after sunset to protect plants from heat stress and leaf burn. This system addresses the real world problem of inconsistent manual watering and midday irrigation damage by continuously checking soil moisture throughout the day, but only permitting watering during a configurable evening window when conditions are gentler on the plants.
<br>
<br>

## System Description

The device will function as a dedicated garden irrigation assistant that measures soil moisture using a sensor, compares the readings against user defined dry and wet thresholds, and stores the latest status for the upcoming evening watering cycle. During the day, the controller evaluates whether the soil will require water that evening; if moisture remains above the threshold, the system inhibits pump activation and preserves water, while if the soil is persistently dry, it arms the pump to run in the evening time slot.
An I2C LCD module will provide clear status messages such as “No water required this evening” when moisture is adequate and “Water required this evening” when the soil has fallen below the dry threshold, allowing the user to understand plant needs without reading raw sensor values. When the scheduled evening period arrives, the controller will re check the sensor and, if still dry, enable the relay driven pump for a calibrated duration or until moisture returns to an acceptable level, thereby delivering targeted irrigation while avoiding overwatering.
<br>
<br>

## Inputs & Outputs

Component	Device	Interface	Function
Analog Input 1	Soil Moisture Sensor	ADC	Samples soil moisture level and converts it to a voltage representing “dry” or “wet” soil conditions
Digital Input 2	Time/Mode Configuration	Buttons or Encoder, GPIO	Allows the user to set moisture thresholds and configure the evening watering window or manual override modes
Digital Input 1	Real Time Clock or Time Source	Interface as applicable	Provides current time information so the controller can distinguish daytime monitoring from the evening watering period
Output 1	Pump Relay or MOSFET Driver	GPIO	Switches the water pump on or off during the evening window when the soil is below the dry threshold
Output  2	I2C LCD	I2C	Displays real time soil status, thresholds, and diagnostic text such as “No water required this evening” or “Water required this evening.”

<br>
<br>
