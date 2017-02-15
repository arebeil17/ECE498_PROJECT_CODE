#ifndef SOUND_MODULE_H
#define SOUND_MODULE_H
/*************/
/*
* File: Sound_Module.h
* Author: Andres Rebeil
* NetID: andres07
* Date: January 10th, 2017
*
* Description: This header file contains the Sound_Module class's interface.
*/

/**************************************************************************************************/
#include <Module.h>
/**************************************************************************************************/

using namespace std;

//Sound_Module is a Subclass of the Module Superclass
class Sound_Module: public Module {
    private:

    public:
      Sound_Module();
};

#endif // SOUND_MODULE_H
