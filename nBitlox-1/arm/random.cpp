/*
 * random.cpp
 *
 *  Created on: Jun 15, 2020
 *      Author: player1
 */

#include "Arduino.h"

#include "hw_rng.h"

#include <string.h>
#include "avr2arm.h"
#include "../hwinterface.h"
#include "../common.h"
#include "../storage_common.h"
#include "../stream_comm.h"
#include "../wallet.h"
#include "../xex.h"
#include "../hexstring.h"

#include "../utf8.h"

#include "hwinit.h"
#include "lcd_and_input.h"

#include "BLE.h"
#include "keypad_alpha.h"
#include "usart.h"

#if defined(__MSP430_CPU__) || defined(__SAM3X8E__)|| defined(__SAM3A8C__)
#include "DueFlashStorage_lib/DueFlashStorage.h"
#endif

#if defined(NRF52840_XXAA)
#include "extEEPROM.h"
#endif


#include "GB2312.h"
#include "eink.h"
#include "due_ePaper_lib/GT20L16P1Y_D.h"

#include "../baseconv.h"
#include "../prandom.h"
#include "keypad_arm.h"
#include "ask_strings.h"


int hardwareRandom32Bytes(uint8_t *buffer)
{
	uint16_t entropy;
	entropy = 128; // this needs to be proven somehow
	uint8_t i;
	  for (i = 0; i < 8; i++)
	  {

		#if defined(__MSP430_CPU__) || defined(__SAM3X8E__)|| defined(__SAM3A8C__)

		uint32_t num = trng_read_output_data(TRNG);

		#endif

		#if defined(NRF52840_XXAA)

//		randomSeed(analogRead(0));
		uint32_t num = SimpleHacks::HW_RNG::get_uint32();

//		uint32_t num = 42;

		#endif

		buffer[(i * 4) + 0] = (num >> 24) & 0xFF;
		buffer[(i * 4) + 1] = (num >> 16) & 0xFF;
		buffer[(i * 4) + 2] = (num >> 8) & 0xFF;
		buffer[(i * 4) + 3] = (num) & 0xFF;
	  }
		return entropy;
}

