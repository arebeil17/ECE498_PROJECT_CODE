/*
* File: ModuleController.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: January 3rd, 2017
*
* Description: Implementation of Module class's interface.
*
*/
/**************************************************************************************************/
#include "ModuleController.h"
/**************************************************************************************************/

ModuleController::ModuleController()
{
    id.readPorts(); //Determine loaded payload modules
    
}
/**************************************************************************************************/
