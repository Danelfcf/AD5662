# AD5662
this is still being written. There are three ways to communicate to the DAC, via I2C, SPI and bitbang. If the communication type si via the bitbang code after init you must call the following to set the communication pins.
void ad5662_BitBang(int data, int clk){AD5662_DATA = data; AD5662_CLK = clk; AD5662_COM = 2;};
