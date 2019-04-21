#ifndef AD5662_H
#define AD5662_H


class AD5662
{
  public:
	  /******************************************************************************/
	  /* AD5662 Power Modes                                                         */
	  /******************************************************************************/  
	  int AD5662_LOAD = 0x0;
	  int AD5662_PWRDWN_1K  =       0x1 ;
	  int AD5662_PWRDWN_100K =      0x2;
	  int AD5662_PWRDWN_TRISTATE=   0x3;
	  int AD5662_FULLSCALE      = 65535;
  
	  AD5662(int CS, float VoltageReference, int ComType){AD5662_CS = CS; AD5662_VoltageReference = VoltageReference; AD5662_COM = ComType;};
	  void ad5662_BitBang(int data, int clk){AD5662_DATA = data; AD5662_CLK = clk; AD5662_COM = 2;};
	  void ad5662_Init(void);
	  void ad5662_Write(int mode, unsigned long data);
	  void ad5662_SetVoltage(float vOut, float vRef);
  protected:
  private:
	  int AD5662_COM = 1;
	  int AD5662_CS = 10;
	  int AD5662_DATA;
	  int AD5662_CLK;
	  float AD5662_VoltageReference = 2.5;

};

#endif

#include <SPI.h>
#include <Wire.h>

void AD5662::ad5662_Init(void)
{
	pinMode(AD5662::AD5662_CS, OUTPUT);
	digitalWrite(AD5662::AD5662_CS, HIGH);
	/* Setup SPI Interface */
	
	switch (AD5662_COM)
	{
		case 0:
			Wire.begin();
			break;
		case 1:
			SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE2)); // SPI setup SPI communication
			SPI.begin();
			break;
		case 2:
			pinMode(AD5662::AD5662_DATA, OUTPUT);
			pinMode(AD5662::AD5662_CLK, OUTPUT);
			digitalWrite(AD5662::AD5662_DATA, LOW);
			digitalWrite(AD5662::AD5662_CLK, LOW);
			break;
		default:
			break;
	}
	
}

void AD5662::ad5662_Write(int mode, unsigned long data)
{
	unsigned char dataBuf[3]   = { mode,             // dataBuf[0] MSB
		(data & 0x0000FF00) >> 8,  // dataBuf[1] MID
	(data & 0x000000FF) >> 0}; // dataBuf[2] LSB
	
	digitalWrite(AD5662::AD5662_CS, LOW);
	
	switch (AD5662_COM)
	{
		case 0:
			Wire.write(dataBuf[0]);
			Wire.write(dataBuf[1]);
			Wire.write(dataBuf[2]);
			break;
		case 1:
			SPI.transfer(dataBuf[0]);
			SPI.transfer(dataBuf[1]);
			SPI.transfer(dataBuf[2]);
			break;
		case 2:
			for (int i = 0; i<=2; i++)
			{
				for (int j=7; j>=0; j--)
				{
					digitalWrite(AD5662::AD5662_DATA, (dataBuf[i] >> j) & 1);
					digitalWrite(AD5662::AD5662_CLK, HIGH);
					digitalWrite(AD5662::AD5662_CLK, LOW);
				}
			}
			break;
		default:
			break;
	}
	

	digitalWrite(AD5662::AD5662_CS, HIGH);
}

void AD5662::ad5662_SetVoltage(float vOut, float vRef)
{
	int16_t dacCode = 0;
	if (vOut <= vRef)
	{
		dacCode  = (int16_t)((float)(vOut / AD5662::AD5662_VoltageReference) * AD5662::AD5662_FULLSCALE);
		ad5662_Write(0, dacCode);
	}
	
}
