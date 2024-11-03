/* Copyright 2021 duoshock 
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 2 of the License, or 
 * (at your option) any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

//#define DEBUG_ENABLE

/*********************** 
 *  ENCODER CONFIG 
 **********************/
#define ENCODERS 3 //No of encoders
/*
 * Encoder Left  : A -> GP16, B ->GP17
 * Encoder Right : A -> GP19, B ->GP20
 * Encoder Main  : A -> GP14, B ->GP15
 */

#if 0
#define ENCODER_RESOLUTIONS {4, 0} //Resolution, Encoder No
#endif

//                     LEFT   MAIN  RIGHT
#define ENCODER_A_PINS {GP16, GP14, GP19}
#define ENCODER_B_PINS {GP17, GP15, GP20}

/*********************** 
 *  ST7789 LCD CONFIG 
 **********************/
#define USE_SPI1
//#define DISPLAY_DRIVER ST7789
//#define LCD_WIDTH  320
//#define LCD_HEIGHT 170
//#define SPI_DRIVER   SPID1
#define SPI_SCK_PIN  GP10
#define SPI_MOSI_PIN GP11
#define SPI_MODE 0
#define ST7789
#define LCD_SPI_DIVISOR 16

#define LCD_CS_PIN   GP5
#define LCD_DC_PIN   GP6
#define LCD_RST_PIN  GP9
//#define LCD_SCK_PIN  GP10
//#define LCD_MOSI_PIN GP11

