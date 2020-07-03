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
#include "GUI_BMPfile.h"
#include "ImageData.h"
#include "DEV_Config.h"
#include "EPD_4in2.h"

using namespace std;

int main() {

#ifdef INTEL_EDISON
    std::cout << "EPD_4IN2_test Demo\r\n" << endl;
    if(DEV_Module_Init()!=0){
        return -1;
    }

    printf("e-Paper Init and Clear...\r\n");
        EPD_4IN2_Init();
        EPD_4IN2_Clear();
        DEV_Delay_ms(500);
#endif

#if 1
        //Create a new image cache
        UBYTE *BlackImage;
        /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
        UWORD Imagesize = ((EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1)) * EPD_4IN2_HEIGHT;
        if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
            printf("Failed to apply for black memory...\r\n");
            return -1;
        }
        printf("Paint_NewImage\r\n");
        Paint_NewImage(BlackImage, EPD_4IN2_WIDTH, EPD_4IN2_HEIGHT, 0, WHITE);

        EPD_4IN2_Init_4Gray();
		printf("show Gray------------------------\r\n");
		//free(BlackImage);
		//BlackImage = NULL;
		Imagesize = ((EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 4 ): (EPD_4IN2_WIDTH / 4 + 1)) * EPD_4IN2_HEIGHT;
		if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
			printf("Failed to apply for black memory...\r\n");
			return -1;
		}
		Paint_NewImage(BlackImage, EPD_4IN2_WIDTH, EPD_4IN2_HEIGHT, 0, WHITE);
		Paint_SetScale(4);
#endif
#if 0
		Paint_Clear(WHITE);
		Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
	    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
	    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
	    Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	    Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	    Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	    Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	    Paint_DrawCircle(45, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	    Paint_DrawCircle(105, 95, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	    Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	    Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	    Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
	    Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
	    Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
	    Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);
	    Paint_DrawString_CN(140, 0, "���abc", &Font12CN, GRAY1, GRAY4);
	    Paint_DrawString_CN(140, 40, "���abc", &Font12CN, GRAY2, GRAY3);
	    Paint_DrawString_CN(140, 80, "���abc", &Font12CN, GRAY3, GRAY2);
	    Paint_DrawString_CN(140, 120, "���abc", &Font12CN, GRAY4, GRAY1);

	    Paint_DrawString_CN(220, 0, "΢ѩ����", &Font24CN, GRAY1, GRAY4);
	    Paint_DrawString_CN(220, 40, "΢ѩ����", &Font24CN, GRAY2, GRAY3);
	    Paint_DrawString_CN(220, 80, "΢ѩ����", &Font24CN, GRAY3, GRAY2);
	    Paint_DrawString_CN(220, 120, "΢ѩ����", &Font24CN, GRAY4, GRAY1);

		EPD_4IN2_4GrayDisplay(BlackImage);
		//it seems if I pause here in the debugger, the screen ends up washed out...
		DEV_Delay_ms(2000);
#endif

#if 1
	Paint_Clear(WHITE);
	GUI_ReadBmp_4Gray("/media/sdcard/helloWorld/pic/10x10.bmp", 100, 100);
	EPD_4IN2_4GrayDisplay(BlackImage);
	DEV_Delay_ms(1000 * 2);
#endif

#if 0
	GUI_ReadBmp_4Gray("/media/sdcard/helloWorld/pic/4in2_Scale.bmp", 0, 0);
	EPD_4IN2_4GrayDisplay(BlackImage);
	DEV_Delay_ms(2000);

	Paint_Clear(WHITE);
    GUI_ReadBmp("/media/sdcard/helloWorld/pic/100x100.bmp", 20, 20);
    EPD_4IN2_4GrayDisplay(BlackImage);
	DEV_Delay_ms(2000);
#endif
	EPD_4IN2_Clear();

    printf("Goto Sleep...\r\n");
    EPD_4IN2_Sleep();
    free(BlackImage);
    BlackImage = NULL;

    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();

	return 0;
}
