#ifndef KEYWORDS_H
#define KEYWORDS_H
/*************/
/*
* File: Keywords.h
* Author: Andres Rebeil
* NetID: andres07
* Date: January 6th, 2017
*
* Description: This header file contains the all of the MPB Systems definitions.
* All keywords found in the source files can be found here.
*/
/**************************************************************************************************/

/**************************************************************************************************/
#define ROOT_PIN 23

//Module current state definitions
#define INITIAL 0
#define WAIT 1
#define EXECUTE 2
#define ABORT 0xFF

//Module Type definitions
#define NO_MODULE 0
#define LED_MODULE 1
#define SOUND_MODULE 2
#define LCD_MODULE 4
#define NUM_MODULES 3

//Module Mode definitions
#define SYNCH_MODE 1
#define ASYNCH_MODE 2

//Module Command priority definitions
#define NORMAL 2
#define CRITICAL 3
#define NONE 0

//Command definitions
#define NO_COMMAND 0x00
#define SIMULT_FUNCTION_1 0x01
#define SIMULT_FUNCTION_2 0x02
#define SIMULT_FUNCTION_3 0x03
#define SIMULT_FUNCTION_4 0x04
#define SIMULT_FUNCTION_5 0x05
#define SIMULT_FUNCTION_6 0x06
#define SIMULT_FUNCTION_7 0x07

#define INDEPENDENT_FUNCTION_1 0x81
#define INDEPENDENT_FUNCTION_2 0x82
#define INDEPENDENT_FUNCTION_3 0x83
#define INDEPENDENT_FUNCTION_4 0x84
#define INDEPENDENT_FUNCTION_5 0x85
#define INDEPENDENT_FUNCTION_6 0x86

#define RED  1
#define GREEN  2
#define BLUE  3
#define WHITE  4
#define PURPLE  5
#define CORAL  6
#define LT_BLUE  7

#endif // KEYWORDS_H
