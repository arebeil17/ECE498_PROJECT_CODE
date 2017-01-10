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
#define IDLE 0
#define DEFAULT 1
#define EXE_SYNCH 2
#define EXE_ASYNCH 3

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

//LED Module definitions
#define LED_SLOT1_PIN 17
#define LED_SLOT2_PIN 18
#define LED_SLOT3_PIN 19

#endif // KEYWORDS_H
