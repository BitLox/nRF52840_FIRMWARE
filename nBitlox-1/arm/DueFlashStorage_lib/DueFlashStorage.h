/* 
DueFlashStorage saves non-volatile data for Arduino Due.
The library is made to be similar to EEPROM library
Uses flash block 1 per default.

Note: uploading new software will erase all flash so data written to flash
using this library will not survive a new software upload. 

Inspiration from Pansenti at https://github.com/Pansenti/DueFlash
Rewritten and modified by Sebastian Nilsson
*/




#if defined(__MSP430_CPU__) || defined(__SAM3X8E__)|| defined(__SAM3A8C__)

#ifndef DUEFLASHSTORAGE_H
#define DUEFLASHSTORAGE_H


#include <stdio.h>
#include <Arduino.h>
#include "flash_efc.h"
#include "efc.h"
#include "../../hwinterface.h"
// 1Kb of data
#define DATA_LENGTH   ((IFLASH1_PAGE_SIZE/sizeof(byte))*4)



// choose a start address that's offset to show that it doesn't have to be on a page boundary
//#define  FLASH_START  ((byte *)IFLASH1_ADDR)
//#define  FLASH_START  ((byte *)((IFLASH1_ADDR)+(4*(IFLASH1_SIZE/5))))
#define  FLASH_START  ((byte *)(IFLASH1_ADDR + IFLASH1_SIZE - (IFLASH1_PAGE_SIZE * (EEPROM_SIZE / IFLASH1_PAGE_SIZE))))

//  FLASH_DEBUG can be enabled to get debugging information displayed.
//#define FLASH_DEBUG

#ifdef FLASH_DEBUG
#define _FLASH_DEBUG(x) Serial.print(x)
#else
#define _FLASH_DEBUG(x)
#endif

#ifdef __cplusplus
     extern "C" {
#endif


//  DueFlash is the main class for flash functions
class DueFlashStorage {
public:
  DueFlashStorage();
  
  // write() writes the specified amount of data into flash.
  // flashStart is the address in memory where the write should start
  // data is a pointer to the data to be written
  // dataLength is length of data in bytes
  
	byte read(uint32_t address);
	byte* readAddress(uint32_t address);
	boolean write(uint32_t address, byte value);
	boolean write(uint32_t address, byte *data, uint32_t dataLength);
};


#ifdef __cplusplus
     }
#endif

#endif

#endif
