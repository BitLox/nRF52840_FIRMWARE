// Do not remove the include below
//#include "main.h"
#include "Arduino.h"

#include <string.h>
#include "avr2arm.h"
#include "../hwinterface.h"
#include "../common.h"
#include "../storage_common.h"
#include "../stream_comm.h"
#include "../wallet.h"
#include "../xex.h"
#include "../hexstring.h"

//#include "../ssp.h" UNNEEDED

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
//#include <Bluefruit_FileIO.h>
//#define FILENAME    "/bitlox.txt"
//#define CONTENTS    "DEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEF"
//File file(InternalFS);
#endif

//#include "DueTimer/DueTimer.h" UNNEEDED

#include "GB2312.h"
#include "eink.h"
#include "due_ePaper_lib/GT20L16P1Y_D.h"

#include "../baseconv.h"
#include "../prandom.h"
#include "keypad_arm.h"
#include "ask_strings.h"



char testResult;

//#define TURBO

//void setupIdentifier() {
////	uint32_t unique_id_chip[4];
////
////	flash_read_unique_id(unique_id_chip, 4);
////
////	initDisplay();
////	overlayBatteryStatus(BATT_VALUE_DISPLAY);
////	writeEinkNoDisplaySingle("DEVICE UNIQUE ID", COL_1_X, LINE_0_Y);
////	writeUnderline(STRIPE_X_START, STRIPE_Y_START, STRIPE_X_END, STRIPE_Y_END);
////	writeEinkDrawNumberSingle(unique_id_chip[0], COL_1_X, LINE_1_Y);
////	writeEinkDrawNumberSingle(unique_id_chip[1], COL_1_X, LINE_2_Y);
////	writeEinkDrawNumberSingle(unique_id_chip[2], COL_1_X, LINE_3_Y);
////	writeEinkDrawNumberSingle(unique_id_chip[3], COL_1_X, LINE_4_Y);
////	display();
////	waitForButtonPress();
////
////	clearDisplay();
//}

void useWhatComms(void);

int level;

#if defined(__MSP430_CPU__) || defined(__SAM3X8E__)|| defined(__SAM3A8C__)

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))

#endif


#if defined(__MSP430_CPU__) || defined(__SAM3X8E__)|| defined(__SAM3A8C__)

void Software_Reset(void) {
//============================================================================================
//   führt ein Reset des Arduino DUE aus...
//
//   Parameter: keine
//   Rueckgabe: keine
//============================================================================================
  const int RSTC_KEY = 0xA5;
  #if defined(__MSP430_CPU__) || defined(__SAM3X8E__)|| defined(__SAM3A8C__)
  RSTC->RSTC_CR = RSTC_CR_KEY(RSTC_KEY) | RSTC_CR_PROCRST | RSTC_CR_PERRST;
  #endif
  while (true);
}

#endif

#if defined(__MSP430_CPU__) || defined(__SAM3X8E__)|| defined(__SAM3A8C__)

DueFlashStorage dueFlashStorage1;

#endif

/** This will be called whenever something very unexpected occurs. This
  * function must not return. */
//void fatalError(void)
//{
//	streamError();
////	cli();
//	for (;;)
//	{
//		// do nothing
//	}
//}

/** PBKDF2 is used to derive encryption keys. In order to make brute-force
  * attacks more expensive, this should return a number which is as large
  * as possible, without being so large that key derivation requires an
  * excessive amount of time (> 1 s). This is a platform-dependent function
  * because key derivation speed is platform-dependent.
  *
  * In order to permit key recovery when the number of iterations is unknown,
  * this should be a power of 2. That way, an implementation can use
  * successively greater powers of 2 until the correct number of iterations is
  * found.
  * \return Number of iterations to use in PBKDF2 algorithm.
  */
uint32_t getPBKDF2Iterations(void)
{
	return 2048;
//	return 128;
}



//void useWhatComms(void)
//{
//	char rChar;
//	int r;
//	int s;
//	uint8_t temp1[1];
//	writeUSB_BLE_Screen();
//
//	rChar = waitForNumberButtonPress();
//	r = rChar - '0';
////	r = 1;
//	switch (rChar){
//	case '1':
//		temp1[0] = 0;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		deactivateBLE();
//		break;
//	case '2':
//		temp1[0] = 0;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		deactivateBLE();
//		break;
//	case '3':
//		temp1[0] = 0;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		deactivateBLE();
//		break;
//	case 'Y':
//		temp1[0] = 0;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		deactivateBLE();
//		break;
//	case '7':
//		temp1[0] = 0;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		deactivateBLE();
//		break;
//	case '8':
//		temp1[0] = 0;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		deactivateBLE();
//		break;
//
//
//	case '4':
//		temp1[0] = 1;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
//		activateBLE();
//		break;
//	case '5':
//		temp1[0] = 1;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
//		activateBLE();
//		break;
//	case '6':
//		temp1[0] = 1;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
//		activateBLE();
//		break;
//	case '9':
//		temp1[0] = 1;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
//		activateBLE();
//		break;
//	case '0':
//		temp1[0] = 1;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
//		activateBLE();
//		break;
//	case 'N':
//		temp1[0] = 1;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
//		activateBLE();
//		break;
//
//	default:
//		s = 0;
//		temp1[0] = s;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		break;
//	}
//}
//
//void useWhatCommsStealth(void)
//{
//	char rChar;
//	int r;
//	int s;
//	uint8_t temp1[1];
//
//	r = rChar - '0';
//	r = 1;
//	rChar = '1';
//	switch (rChar){
//	case '1':
//		temp1[0] = 0;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
////		writeUSB_Screen();
//		deactivateBLE();
//		break;
//	case '2':
//		temp1[0] = 0;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		deactivateBLE();
//		break;
//	case '3':
//		temp1[0] = 0;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		deactivateBLE();
//		break;
//	case 'Y':
//		temp1[0] = 0;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		deactivateBLE();
//		break;
//	case '7':
//		temp1[0] = 0;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		deactivateBLE();
//		break;
//	case '8':
//		temp1[0] = 0;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		deactivateBLE();
//		break;
//
//
//	case '4':
//		temp1[0] = 1;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
//		activateBLE();
//		break;
//	case '5':
//		temp1[0] = 1;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
//		activateBLE();
//		break;
//	case '6':
//		temp1[0] = 1;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
//		activateBLE();
//		break;
//	case '9':
//		temp1[0] = 1;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
//		activateBLE();
//		break;
//	case '0':
//		temp1[0] = 1;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
//		activateBLE();
//		break;
//	case 'N':
//		temp1[0] = 1;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
//		activateBLE();
//		break;
//
//	default:
//		s = 0;
//		temp1[0] = s;
//		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		break;
//	}
//}
//
//void useWhatCommsDuress(void)
//{
//	char rChar;
//	int r;
//	int s;
//	uint8_t temp1[1];
//	writeUSB_BLE_Screen();
//
//	rChar = waitForNumberButtonPress();
//	r = rChar - '0';
////	r = 1;
////	rChar = '1';
//	switch (rChar){
//	case '1':
////		temp1[0] = 0;
////		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
////		deactivateBLE();
//		break;
//	case '2':
////		temp1[0] = 0;
////		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
////		deactivateBLE();
//		break;
//	case '3':
////		temp1[0] = 0;
////		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
////		deactivateBLE();
//		break;
//	case 'Y':
////		temp1[0] = 0;
////		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
////		deactivateBLE();
//		break;
//	case '7':
////		temp1[0] = 0;
////		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
////		deactivateBLE();
//		break;
//	case '8':
////		temp1[0] = 0;
////		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
////		deactivateBLE();
//		break;
//
//
//	case '4':
////		temp1[0] = 1;
////		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
////		activateBLE();
//		break;
//	case '5':
////		temp1[0] = 1;
////		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
////		activateBLE();
//		break;
//	case '6':
////		temp1[0] = 1;
////		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
////		activateBLE();
//		break;
//	case '9':
////		temp1[0] = 1;
////		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
////		activateBLE();
//		break;
//	case '0':
////		temp1[0] = 1;
////		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
////		activateBLE();
//		break;
//	case 'N':
////		temp1[0] = 1;
////		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeBLE_Screen();
////		activateBLE();
//		break;
//
//	default:
////		s = 0;
////		temp1[0] = s;
////		nonVolatileWrite(temp1, DEVICE_COMMS_SET_ADDRESS, 1);
//		writeUSB_Screen();
//		break;
//	}
//showReady();
//}
//
//
//void useWhatSetup(void)
//{
//	char rChar;
//	bool yesOrNo;
//	int r;
//	int s;
//	uint8_t temp1[1];
//
//	inputInterjectionNoAck(ASKUSER_INITIAL_SETUP);
//
//	rChar = waitForNumberButtonPress();
//
//	clearDisplay();
//	r = rChar - '0';
//	switch (rChar){
//	case '1':
//		temp1[0] = 0;
//
//		buttonInterjectionNoAckSetup(ASKUSER_DESCRIBE_STANDARD_SETUP);
//
//		yesOrNo = waitForButtonPress();
//		clearDisplay();
//		if(!yesOrNo)
//		{
//			pinStatusCheckandPremadePIN();
//		}else if(yesOrNo)
//		{
//			useWhatSetup();
//			break;
//		}
//		level = 1;
//		break;
//
//	case '2':
//		temp1[0] = 0;
//
//		buttonInterjectionNoAckSetup(ASKUSER_DESCRIBE_ADVANCED_SETUP);
//
//		yesOrNo = waitForButtonPress();
//
//		clearDisplay();
//
//		if(!yesOrNo)
//		{
//			pinStatusCheck();
//		}else if(yesOrNo)
//		{
//			useWhatSetup();
//			break;
//		}
//		level = 2;
//
//		doAEMSet();
//
//		break;
//	case '3':
//		temp1[0] = 0;
//
//		buttonInterjectionNoAckSetup(ASKUSER_DESCRIBE_EXPERT_SETUP);
//
//		yesOrNo = waitForButtonPress();
//		clearDisplay();
//
//		if(!yesOrNo)
//		{
//			pinStatusCheckExpert();
//		}else if(yesOrNo)
//		{
//			useWhatSetup();
//			break;
//		}
//		level = 3;
//
//		doAEMSet();
//
//		break;
//	case 'Y':
//		temp1[0] = 0;
//
//		buttonInterjectionNoAckSetup(ASKUSER_DESCRIBE_STANDARD_SETUP);
//
//		yesOrNo = waitForButtonPress();
//		clearDisplay();
//
//		if(!yesOrNo)
//		{
//			pinStatusCheckandPremadePIN();
//		}else if(yesOrNo)
//		{
//			useWhatSetup();
//			break;
//		}
//		level = 1;
//
//		break;
//
//
//	case 'N':
//		temp1[0] = 1;
//		writeX_Screen();
//		Software_Reset();
//		break;
//
//	case '0':
//		writeEinkDisplay("READY FOR RESTORE...", false, COL_1_X, LINE_0_Y, "MAY TAKE UP TO 2 MINUTES",false,COL_1_X,LINE_1_Y, "TO DECRYPT AND WRITE",false,COL_1_X,LINE_2_Y, "WALLET DATA",false,COL_1_X,LINE_3_Y, "",false,0,0);
//		useWhatCommsStealth();
//		initUsart();
//		loop();
//		break;
//
//	default:
//		useWhatSetup();
//		break;
//	}
//}
//
//
//
//
//void setupSequence(int level){
//	bool canceledWalletCreation;
//	int strength;
//	if(level == 1)
//	{
//		strength = 128;
//		initialFormatAuto();
//		canceledWalletCreation = createDefaultWalletAuto(strength, level);
//		useWhatComms();
//		initUsart();
//		if(!canceledWalletCreation)
//		{
//			showQRcode(0,0,0);
//		}else{
//			showReady();
//		}
//
//	}
//	else if(level == 2)
//	{
//		strength = 192;
//		initialFormatAuto();
//		canceledWalletCreation = createDefaultWalletAuto(strength, level);
//		useWhatComms();
//		initUsart();
//
//		if(!canceledWalletCreation)
//		{
//			showQRcode(0,0,0);
//		}else{
//			showReady();
//		}
//	}
//	else if(level == 3)
//	{
//		strength = 256;
//		initialFormatAuto();
//		canceledWalletCreation = createDefaultWalletAuto(strength, level);
//		useWhatComms();
//		initUsart();
//
//		if(!canceledWalletCreation)
//		{
//			showQRcode(0,0,0);
//		}else{
//			showReady();
//		}
//	}
//}


void blinkem()
{
//	  pinMode(13, OUTPUT);
//	  pinMode(14, OUTPUT);
//	  pinMode(15, OUTPUT);
//	  pinMode(16, OUTPUT);

	  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
	  delay(100);              // wait for a second
	  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
	  delay(1000);              // wait for a second
	  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)

	  digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
	  delay(100);              // wait for a second
	  digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
	  delay(1000);              // wait for a second
	  digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)

	  digitalWrite(15, HIGH);   // turn the LED on (HIGH is the voltage level)
	  delay(100);              // wait for a second
	  digitalWrite(15, LOW);    // turn the LED off by making the voltage LOW
	  delay(1000);              // wait for a second
	  digitalWrite(15, HIGH);   // turn the LED on (HIGH is the voltage level)

	  digitalWrite(16, HIGH);   // turn the LED on (HIGH is the voltage level)
	  delay(100);              // wait for a second
	  digitalWrite(16, LOW);    // turn the LED off by making the voltage LOW
	  delay(1000);              // wait for a second
	  digitalWrite(16, HIGH);   // turn the LED on (HIGH is the voltage level)

}



void setup()
{
//	void __stack_chk_guard_setup(void);

//	init();

	pinMode(13, OUTPUT);
	pinMode(14, OUTPUT);
	pinMode(15, OUTPUT);
	pinMode(16, OUTPUT);



	initDisplay();
	writeEinkNoDisplay("v67_nRF52840", COL_1_X, LINE_0_Y, "EXPERIMENTAL",COL_1_X, LINE_2_Y, "",5,50, "",5,70, "",0,0);

////    overlayBatteryStatus(BATT_VALUE_DISPLAY);
////	writeUnderline(STRIPE_X_START, STRIPE_Y_START, STRIPE_X_END, STRIPE_Y_END);

	display();

	showReady();
	Serial.begin(9600);

	while (!Serial) { // needed to keep leonardo/micro from starting too fast!
	delay(10);
	}


	#if defined(NRF52840_XXAA)
	setupTouchem();

//	blinkem();
//	extEEPROM myEEPROM(kbits_256, 1, 64, 0x50);
//	byte i2cStat = myEEPROM.begin(myEEPROM.twiClock100kHz);
//	InternalFS.begin();
	#endif



	languageMenuInitially();

	initFormatting();

//
//	int AemStatus;
//	AemStatus = checkUseAEM();
//
//	if(AemStatus != 127)
//	{
//		;
//	}
//	else if (AemStatus == 127)
//	{
////		startTimer2();
//		doAEMValidate(false);
////		stopTimer2();
//	}
//
//
//	int pinStatus;
//	pinStatus = checkHasPIN();
//
//	if(pinStatus != 127)
//	{
//		useWhatSetup();
//	}
//	else if (pinStatus == 127)
//	{
////		startTimer2();
//		checkDevicePIN(false);
////		stopTimer2();
//	}
//
//
//	useWhatCommsStealth();
//	initUsart();
//
//	if(is_formatted != 123)
//	{
//		setupSequence(level);
//	}
//	else
//	{
////		setupIdentifier();
//
//		useWhatComms();
//		initUsart();
//
//		showReady();
//
//	}


}

// The loop function is called in an endless loop
void loop()
{

//	testResult = touchTest();
//	Serial.println(testResult);
//	Serial.println("-------------------");


//	processPacket();
}

