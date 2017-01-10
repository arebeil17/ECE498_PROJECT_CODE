/*
* File: Payload.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: December 24th, 2016
*
* Description: Implementation of Payload class's interface.
*
*/
/**************************************************************************************************/
#include "Payload.h"
/**************************************************************************************************/

Payload::Payload()
{
	id = 0;
	state = 0;
	//Command command;
	idle = true;
	mode = 0;
	config = 0;
}

Payload::~Payload()
{
}

int Payload::getId()
{
	return id;
}

void Payload::setId(int id)
{
	this->id = id;
}

int Payload::getState()
{
	return state;
}

void Payload::setState(int State)
{
	this->state = state;
}

bool Payload::isIdle()
{
	return this->idle;
}

void Payload::setIdle(bool idle)
{
	this->idle = idle;
}

int Payload::getMode()
{
	return this->mode;
}

void Payload::setMode(int mode)
{
	this->mode = mode;
}

int Payload::getConfig()
{
	return this->config;
}

void Payload::setConfig(int config)
{
	this->config = config;
}
