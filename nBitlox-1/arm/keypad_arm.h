/*
 * keypad_arm.h
 *
 *  Created on: Oct 12, 2014
 *      Author: thesquid
 */

#ifndef KEYPAD_ARM_H_
#define KEYPAD_ARM_H_

#ifdef __cplusplus
     extern "C" {
#endif

extern char getFullKeys(void);
extern char getAcceptCancelKeys(void);
extern char NewKeyRoutine(void);
extern char getTouchPadKey(void);
extern void setupTouchem(void);
extern char touchTest(void);
#ifdef __cplusplus
     }
#endif

#endif /* KEYPAD_ARM_H_ */
