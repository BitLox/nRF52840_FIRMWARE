/*
 * random.h
 *
 *  Created on: Jun 15, 2020
 *      Author: player1
 */

#include "Arduino.h"

#ifndef ARM_RANDOM_H_
#define ARM_RANDOM_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int hardwareRandom32Bytes(uint8_t *buffer);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* ARM_RANDOM_H_ */


