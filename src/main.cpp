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

#include "DEV_Config.h"
#include "EPD_4in2.h"

using namespace std;

int main() {
	cout << "Hello World!!!!" << endl; // prints Hello World

#ifdef RPI
    std::cout << "EPD_4IN2_test Demo\r\n" << endl;
    if(DEV_Module_Init()!=0){
        return -1;
    }
#endif

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
