//============================================================================
// Name        : main.cpp
// Author      : Daniel
// Version     :
// Copyright   : Your copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdint.h>
#include <unistd.h>
#include <mraa/spi.h>

#include "GUI_Paint.h"
#include "DEV_Config.h"
#include "EPD_4in2.h"

using namespace std;

int main() {
	cout << "Hello World!!!!" << endl; // prints Hello World

#ifdef INTEL_EDISON
    std::cout << "EPD_4IN2_test Demo\r\n" << endl;
    if(DEV_Module_Init()!=0){
        return -1;
    }

    printf("e-Paper Init and Clear...\r\n");
        EPD_4IN2_Init();
        EPD_4IN2_Clear();
        DEV_Delay_ms(500);

        //Create a new image cache
        UBYTE *BlackImage;
        /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
        UWORD Imagesize = ((EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1)) * EPD_4IN2_HEIGHT;
        if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
            printf("Failed to apply for black memory...\r\n");
            return -1;
        }
        //printf("Paint_NewImage\r\n");
        //Paint_NewImage(BlackImage, EPD_4IN2_WIDTH, EPD_4IN2_HEIGHT, 0, WHITE);
#endif

	std::cout << "Testing SPI" << endl;
	mraa_spi_context spi;
	spi = mraa_spi_init(0);

	uint8_t data;
	int recv_int;
	int i;

	while(1) {
		for(i = 0; i < 100; i++) {
			data = i;
			recv_int = mraa_spi_write(spi, data);
			cout << "Received: " << recv_int << endl;
			usleep(20000);
		}
	}

	return 0;
}
