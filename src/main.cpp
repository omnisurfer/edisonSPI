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

	//debug spi code
	/*
	edisonSPI = mraa_spi_init(0);
	//mraa_spi_mode(edisonSPI, MRAA_SPI_MODE0);
	//mraa_spi_frequency(edisonSPI, 10e6);
	//mraa_spi_lsbmode(edisonSPI, 0);
	//mraa_spi_bit_per_word(edisonSPI, 8);

    uint8_t data;
    int recv_int;
    int i;

    while(1) {
		for(i = 0; i < 100; i++) {
			data = i;
			recv_int = mraa_spi_write(edisonSPI, data);
			printf("Received: %d\n", recv_int);
			usleep(2000);
		}
    }
	 */
	// debug pin code

	/*
	mraa_gpio_context testPin = mraa_gpio_init(3);
	cout << "mode result: " << mraa_gpio_mode(testPin, MRAA_GPIO_PULLUP) << endl;
	cout << "dir result: " << mraa_gpio_dir(testPin, MRAA_GPIO_OUT) << endl;
	bool state = false;
	for(int i = 0; i < 60; i++) {
		cout << "write result: " << mraa_gpio_write(testPin, state) << endl;
		state = !state;
		usleep(1000 * 1000);
	}

	cout << "out of loop" << endl;
	*/

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

	return 0;
}
