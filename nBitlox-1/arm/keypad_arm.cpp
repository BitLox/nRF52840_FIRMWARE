/*
 * keypad_arm.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: thesquid
 */

#include "main.h"
#include "keypad_arm.h"
#include <Keypad.h>
#include "Arduino.h"

#include "GB2312.h"
#include "eink.h"
#include "due_ePaper_lib/GT20L16P1Y_D.h"


#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;



#if defined(__SAM3X8E__)
#define ROW_PIN_1      69
#define ROW_PIN_2      68
#define ROW_PIN_3      67
#define COL_PIN_1      66
#define COL_PIN_2      65
#define COL_PIN_3      64
#define COL_PIN_4      63

const byte ROWS = 3; //three rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'3','2','1','0'},
  {'7','6','5','4'},
  {'N','Y','9','8'}
};
byte rowPins[ROWS] = {ROW_PIN_1, ROW_PIN_2, ROW_PIN_3}; //connect to the row pinouts of the keypad A15 A14 A13
byte colPins[COLS] = {COL_PIN_1, COL_PIN_2, COL_PIN_3, COL_PIN_4}; //connect to the column pinouts of the keypad A12 A11 A10 A9

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



#endif

#if defined(__SAM3A8C__)
#define ROW_PIN_1      22
#define ROW_PIN_2      23
#define ROW_PIN_3      24
#define COL_PIN_1      18
#define COL_PIN_2      19
#define COL_PIN_3      20
#define COL_PIN_4      21
#endif

#if defined(NRF52840_XXAA)
//not needed with capacitive keys
#define ROW_PIN_1      22
#define ROW_PIN_2      23
#define ROW_PIN_3      24
#define COL_PIN_1      18
#define COL_PIN_2      19
#define COL_PIN_3      20
#define COL_PIN_4      21
#endif


void setupTouchem() {
//  Serial.begin(9600);
//
//  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
//    delay(10);
//  }

  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
}


char touchGetInput()
{
	 char theKey = ' ';

//	 do  {
	// Get the currently touched pads
	  currtouched = cap.touched();

	  for (uint8_t i=0; i<12; i++) {
	    // it if *is* touched and *wasnt* touched before, alert!
	    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
	      Serial.print(i);
	      Serial.println(" touched in touchGetInput");
	      switch (i){
	      case 0	:
	    	  theKey = '1';
	      	  break;
	      case 1	:
	    	  theKey = '4';
	      	  break;
	      case 2	:
	    	  theKey = '7';
	      	  break;
	      case 3	:
	    	  theKey = '@';
	      	  break;
	      case 4	:
	    	  theKey = '2';
	      	  break;
	      case 5	:
	    	  theKey = '5';
	      	  break;
	      case 6	:
	    	  theKey = '8';
	      	  break;
	      case 7	:
	    	  theKey = '0';
	      	  break;
	      case 8	:
	    	  theKey = '3';
	      	  break;
	      case 9	:
	    	  theKey = '6';
	      	  break;
	      case 10	:
	    	  theKey = '9';
	      	  break;
	      case 11	:
	    	  theKey = '~';
	      	  break;
	      default	:
	    	  theKey = ' ';
	      }
	      Serial.print(theKey);
	      Serial.println(" returned as theKey");
	    }

	    // if it *was* touched and now *isnt*, alert!
//	    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
//	      Serial.print(i); Serial.println(" released");
//	    }
	  }

	  // reset our state
	  lasttouched = currtouched;
//	 }while(theKey !='0' && theKey !='1' && theKey !='2' && theKey !='3' && theKey !='4' && theKey !='5' && theKey !='6' && theKey !='7' && theKey !='8' && theKey !='9' && theKey !='Y' && theKey !='N' );

	 return theKey;

}


char touchTest()
{
	 char theKey = ' ';

	 do  {
	// Get the currently touched pads
	  currtouched = cap.touched();

	  for (uint8_t i=0; i<12; i++) {
	    // it if *is* touched and *wasnt* touched before, alert!
	    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
	      Serial.print(i);
	      Serial.println(" touched in touchTest");
	      switch (i){
	      case 0	:
	    	  theKey = '1';
	      	  break;
	      case 1	:
	    	  theKey = '4';
	      	  break;
	      case 2	:
	    	  theKey = '7';
	      	  break;
	      case 3	:
	    	  theKey = 'Y';
	      	  break;
	      case 4	:
	    	  theKey = '2';
	      	  break;
	      case 5	:
	    	  theKey = '5';
	      	  break;
	      case 6	:
	    	  theKey = '8';
	      	  break;
	      case 7	:
	    	  theKey = '0';
	      	  break;
	      case 8	:
	    	  theKey = '3';
	      	  break;
	      case 9	:
	    	  theKey = '6';
	      	  break;
	      case 10	:
	    	  theKey = '9';
	      	  break;
	      case 11	:
	    	  theKey = 'N';
	      	  break;
	      default	:
	    	  theKey = '@';
	      }
	      Serial.print(theKey);
	      Serial.println(" returned as theKey");
	    }

	    // if it *was* touched and now *isnt*, alert!
//	    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
//	      Serial.print(i); Serial.println(" released");
//	    }
	  }

	  // reset our state
	  lasttouched = currtouched;
	 }while(theKey !='0' && theKey !='1' && theKey !='2' && theKey !='3' && theKey !='4' && theKey !='5' && theKey !='6' && theKey !='7' && theKey !='8' && theKey !='9' && theKey !='Y' && theKey !='N' );

	 return theKey;

}

char touchTestNoWhile()
{
	 char theKey = ' ';

//	 do  {
	// Get the currently touched pads
	  currtouched = cap.touched();

	  for (uint8_t i=0; i<12; i++) {
	    // it if *is* touched and *wasnt* touched before, alert!
	    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
	      Serial.print(i);
	      Serial.println(" touched in touchTest");
	      switch (i){
	      case 0	:
	    	  theKey = '1';
	      	  break;
	      case 1	:
	    	  theKey = '4';
	      	  break;
	      case 2	:
	    	  theKey = '7';
	      	  break;
	      case 3	:
	    	  theKey = 'Y';
	      	  break;
	      case 4	:
	    	  theKey = '2';
	      	  break;
	      case 5	:
	    	  theKey = '5';
	      	  break;
	      case 6	:
	    	  theKey = '8';
	      	  break;
	      case 7	:
	    	  theKey = '0';
	      	  break;
	      case 8	:
	    	  theKey = '3';
	      	  break;
	      case 9	:
	    	  theKey = '6';
	      	  break;
	      case 10	:
	    	  theKey = '9';
	      	  break;
	      case 11	:
	    	  theKey = 'N';
	      	  break;
	      default	:
	    	  theKey = '@';
	      }
	      Serial.print(theKey);
	      Serial.println(" returned as theKey");
	    }

	    // if it *was* touched and now *isnt*, alert!
//	    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
//	      Serial.print(i); Serial.println(" released");
//	    }
	  }

	  // reset our state
	  lasttouched = currtouched;
//	 }while(theKey !='0' && theKey !='1' && theKey !='2' && theKey !='3' && theKey !='4' && theKey !='5' && theKey !='6' && theKey !='7' && theKey !='8' && theKey !='9' && theKey !='Y' && theKey !='N' );

	 return theKey;

}

char getFullKeys(void)
{
#if defined(__SAM3X8E__)
	char key = keypad.getKey();
#endif
#if defined(__SAM3A8C__)
	char key = NewKeyRoutine();
#endif
#if defined(NRF52840_XXAA)
	char key = touchTest();
#endif

	if (key){
		return(key);
	}

	return ' '; // have to change this to something not normally returned
}

char getFullKeysInput(void)
{
#if defined(__SAM3X8E__)
	char key = keypad.getKey();
#endif
#if defined(__SAM3A8C__)
	char key = NewKeyRoutine();
#endif
#if defined(NRF52840_XXAA)
	char key = touchGetInput();
#endif

	if (key){
		return(key);
	}

	return '#'; // have to change this to something not normally returned
}

char getAcceptCancelKeys(void)
{
#if defined(__SAM3X8E__)
	char key = keypad.getKey();
#endif
#if defined(__SAM3A8C__)
	char key = NewKeyRoutine();
#endif
#if defined(NRF52840_XXAA)
	char key = touchTestNoWhile();
#endif

	if (key=='Y' || key=='N'){
		return(key);
	}


	return ' ';
}



char NewKeyRoutine(void)
{
	const char* ptr_pressed;
	char pressed;

	pinMode(ROW_PIN_3, INPUT_PULLUP);
	pinMode(ROW_PIN_2, INPUT_PULLUP);
	pinMode(ROW_PIN_1, INPUT_PULLUP);
	pinMode(COL_PIN_1, OUTPUT);
	pinMode(COL_PIN_2, OUTPUT);
	pinMode(COL_PIN_3, OUTPUT);
	pinMode(COL_PIN_4, OUTPUT);
	digitalWrite(COL_PIN_1, HIGH);
	digitalWrite(COL_PIN_2, HIGH);
	digitalWrite(COL_PIN_3, HIGH);
	digitalWrite(COL_PIN_4, HIGH);


//	do
//	{
		  int buttonState;
		  int pushButton;
		  int pushOutput;

		  pushButton = ROW_PIN_3;
		  pushOutput = COL_PIN_1;
		  digitalWrite(pushOutput, LOW);
		  buttonState = digitalRead(pushButton);
		  if (buttonState == 0) {
//		    Serial.println("Button Pressed: 8");
		    return '9';// '8'; //1 is 8; button 8 is 8
		  }
		  delay(1);        // delay in between reads for stability
		  digitalWrite(pushOutput, HIGH);

		  pushButton = ROW_PIN_2;
		  pushOutput = COL_PIN_1;
		  digitalWrite(pushOutput, LOW);
		  buttonState = digitalRead(pushButton);
		  if (buttonState == 0) {
//		    Serial.println("Button Pressed: 7");
		    return '8'; // '7'; //7
		  }
		  delay(1);        // delay in between reads for stability
		  digitalWrite(pushOutput, HIGH);

		  pushButton = ROW_PIN_1;
		  pushOutput = COL_PIN_1;
		  digitalWrite(pushOutput, LOW);
		  buttonState = digitalRead(pushButton);
		  if (buttonState == 0) {
//		    Serial.println("Button Pressed: 3");
		    return '3'; //3
		  }
		  delay(1);        // delay in between reads for stability
		  digitalWrite(pushOutput, HIGH);




		  pushButton = ROW_PIN_3;
		  pushOutput = COL_PIN_2;
		  digitalWrite(pushOutput, LOW);
		  buttonState = digitalRead(pushButton);
		  if (buttonState == 0) {
//		    Serial.println("Button Pressed: N");  // 8 due
		    return 'Y'; // 'N'; //N
		  }
		  delay(1);        // delay in between reads for stability
		  digitalWrite(pushOutput, HIGH);

		  pushButton = ROW_PIN_2;
		  pushOutput = COL_PIN_2;
		  digitalWrite(pushOutput, LOW);
		  buttonState = digitalRead(pushButton);
		  if (buttonState == 0) {
//		    Serial.println("Button Pressed: 6");
		    return '7'; // '6'; //6
		  }
		  delay(1);        // delay in between reads for stability
		  digitalWrite(pushOutput, HIGH);

		  pushButton = ROW_PIN_1;
		  pushOutput = COL_PIN_2;
		  digitalWrite(pushOutput, LOW);
		  buttonState = digitalRead(pushButton);
		  if (buttonState == 0) {
//		    Serial.println("Button Pressed: 2");
		    return '2'; //2
		  }
		  delay(1);        // delay in between reads for stability
		  digitalWrite(pushOutput, HIGH);




		  pushButton = ROW_PIN_3;
		  pushOutput = COL_PIN_3;
		  digitalWrite(pushOutput, LOW);
		  buttonState = digitalRead(pushButton);
		  if (buttonState == 0) {
//		    Serial.println("Button Pressed: Y");
		    return '6'; //'Y'; // Y
		  }
		  delay(1);        // delay in between reads for stability
		  digitalWrite(pushOutput, HIGH);

		  pushButton = ROW_PIN_2;
		  pushOutput = COL_PIN_3;
		  digitalWrite(pushOutput, LOW);
		  buttonState = digitalRead(pushButton);
		  if (buttonState == 0) {
//		    Serial.println("Button Pressed: 5");
		    return '5'; //5
		  }
		  delay(1);        // delay in between reads for stability
		  digitalWrite(pushOutput, HIGH);

		  pushButton = ROW_PIN_1;
		  pushOutput = COL_PIN_3;
		  digitalWrite(pushOutput, LOW);
		  buttonState = digitalRead(pushButton);
		  if (buttonState == 0) {
//		    Serial.println("Button Pressed: 1");
		    return '1';
		  }
		  delay(1);        // delay in between reads for stability
		  digitalWrite(pushOutput, HIGH);




		  pushButton = ROW_PIN_3;
		  pushOutput = COL_PIN_4;
		  digitalWrite(pushOutput, LOW);
		  buttonState = digitalRead(pushButton);
		  if (buttonState == 0) {
//		    Serial.println("Button Pressed: 9");
		    return '0';// '9';
		  }
		  delay(1);        // delay in between reads for stability
		  digitalWrite(pushOutput, HIGH);

		  pushButton = ROW_PIN_2;
		  pushOutput = COL_PIN_4;
		  digitalWrite(pushOutput, LOW);
		  buttonState = digitalRead(pushButton);
		  if (buttonState == 0) {
//		    Serial.println("Button Pressed: 4");
		    return '4'; //4
		  }
		  delay(1);        // delay in between reads for stability
		  digitalWrite(pushOutput, HIGH);

		  pushButton = ROW_PIN_1;
		  pushOutput = COL_PIN_4;
		  digitalWrite(pushOutput, LOW);
		  buttonState = digitalRead(pushButton);
		  if (buttonState == 0) {
//		    Serial.println("Button Pressed: 0");
		    return 'N'; //'0';
		  }
		  delay(1);        // delay in between reads for stability
		  digitalWrite(pushOutput, HIGH);


//	} while (1);

	return ' ';

}

