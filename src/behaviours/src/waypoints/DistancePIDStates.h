#ifndef distancepidstates_h
#define distancepidstates_h

#include "../state_machine/State.h"
#include "DistancePID.h"

class DistancePIDDrive : public State
{
    public:
        DistancePIDDrive() : State( "drive_state" ) {}
        virtual void action();
};

#endif
