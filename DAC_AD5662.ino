// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       AD5662.ino
    Created:	4/20/2019 12:53:15 PM
    Author:     DESKTOP-22L6KM4\Daniel
*/
// Define User Types below here or use a .h file
//
#include "AD5662.h"
AD5662 DAC(10, 2.5, 1); // ChipSelect = 10, Voltage Reference = 2.5v, communication type SPI (0-i2c, 1-SPI, 3-BitBang)
void setup()
{
	DAC.ad5662_Init();
}

// Add the main program code into the continuous loop() function
void loop()
{
	
	while (true)
	{
		int i = 0;
		
		while (i<DAC.AD5662_FULLSCALE)
		{
			DAC.ad5662_Write(DAC.AD5662_LOAD, i);
			i++;
		}
		
	}
	
}

