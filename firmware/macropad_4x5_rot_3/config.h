// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* any side can be master by default, enable split sync to support it */

/* SPI config for display */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP10
#define SPI_MOSI_PIN GP11
//#define SPI_MISO_PIN GP12

/* LCD config */
#define LCD_DC_PIN GP6
#define LCD_CS_PIN GP5
#define LCD_RST_PIN GP9
#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS TRUE

/* No Display Timeout */
#undef  QUANTUM_PAINTER_DISPLAY_TIMEOUT
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0

/* Encode Config */
#define ENCODERS 3 //No of encoders
/*
 * Encoder Left  : A -> GP16, B ->GP17
 * Encoder Right : A -> GP19, B ->GP20
 * Encoder Main  : A -> GP14, B ->GP15
 */

#if 0
#define ENCODER_RESOLUTIONS {4, 0} //Resolution, Encoder No
#endif

/*                     LEFT   MAIN  RIGHT */
#define ENCODER_A_PINS {GP16, GP14, GP19}
#define ENCODER_B_PINS {GP17, GP15, GP20}

#define ENCODER_LEFT_PUSH_BUTTON_PIN  GP18
#define ENCODER_MAIN_PUSH_BUTTON_PIN  GP22
#define ENCODER_RIGHT_PUSH_BUTTON_PIN GP21

#define TAPPING_TERM 240
#define TAPPING_TERM_PER_KEY
