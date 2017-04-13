/*
* File: Module.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: January 3, 2017
*
* Description: Implementation of Module class's interface.
*
*/
/**************************************************************************************************/
#include "Module.h"
/**************************************************************************************************/
Module::Module()
{
}
Module::Module(uint8_t moduleType)
{
		switch(moduleType){
			case LED_MODULE:
					this->moduleType = moduleType;
			break;
			case SOUND_MODULE:
					this->moduleType = moduleType;
			break;
			case LCD_MODULE:
					this->moduleType = moduleType;
			break;
	}
}
