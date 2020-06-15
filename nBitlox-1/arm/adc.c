/** \file adc.c
  *
  * \brief Samples the AVR's analog-to-digital convertor.
  *
  * Contains functions which sample from one of the AVR's analog-to-digital
  * converter inputs. Hopefully that input (see initAdc() for which input
  * is selected) is connected to a hardware noise source.
  *
  * A good choice for a hardware noise source is amplified zener/avalanche
  * noise from the reverse biased B-E junction of a NPN transistor. But such
  * a source requires a > 8 volt source, which is higher than the AVR's supply
  * voltage. To help solve this issue, two complementary square waves are
  * outputted from pins PB0 and PB1 (digital out pins 8 and 9 on Arduino).
  * Those pins can be connected to a charge pump circuit to generate the
  * required voltage.
  *
  * This file is licensed as described by the file LICENCE.
  */

#include "Arduino.h"

#include <stdlib.h>

#include "../common.h"
#include "../hwinterface.h"
#include "hwinit.h"



///////////////////////////////////////////

//#include <string.h>
//#include "avr2arm.h"
////#include "../prandom.h"
//#include "../storage_common.h"
//#include "../stream_comm.h"
//#include "../wallet.h"
//#include "../xex.h"
//#include "../hexstring.h"
//#include "../utf8.h"
////
////
//#include "lcd_and_input.h"
////
//#include "BLE.h"
//#include "keypad_alpha.h"
//#include "usart.h"
//#include "eink.h"
//#include "due_ePaper_lib/GT20L16P1Y_D.h"
////
//#include "../baseconv.h"
//
//#include "keypad_arm.h"
//


////////////////////////////////////////////


/** Fill buffer with 32 random bytes from a hardware random number generator.
  * \param buffer The buffer to fill. This should have enough space for 32
  *               bytes.
  * \return An estimate of the total number of bits (not bytes) of entropy in
  *         the buffer.
  */

//Moved to random.cpp regarding the random() problem with finding the damn routine

//int hardwareRandom32Bytes(uint8_t *buffer)
//{
//	uint16_t entropy;
//	entropy = 128; // this needs to be proven somehow
//	uint8_t i;
//	  for (i = 0; i < 8; i++)
//	  {
//
//		#if defined(__MSP430_CPU__) || defined(__SAM3X8E__)|| defined(__SAM3A8C__)
//
//		uint32_t num = trng_read_output_data(TRNG);
//
//		#endif
//
//		#if defined(NRF52840_XXAA)
//
//		randomSeed(analogRead(0));
//		uint32_t num = random(100000);
//
////		uint32_t num = 42;
//
//		#endif
//
//		buffer[(i * 4) + 0] = (num >> 24) & 0xFF;
//		buffer[(i * 4) + 1] = (num >> 16) & 0xFF;
//		buffer[(i * 4) + 2] = (num >> 8) & 0xFF;
//		buffer[(i * 4) + 3] = (num) & 0xFF;
//	  }
//		return entropy;
//}

int batteryLevel(void)
{
	int val = 0;           // variable to store the value read

	int analogPin = 29;     // potentiometer wiper (middle terminal) connected to analog pin 3
	pinMode (analogPin, INPUT);

	val = analogRead(analogPin);
	return val;
}
