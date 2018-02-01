#ifndef distancepidstates_h
#define distancepidstates_h

#include "../state_machine/State.h"
#include "DistancePID.h"

class DistancePIDDrive : public State
{
    public:
        DistancePIDDrive( std::string id ) : State( id ), owner(0) {}
        virtual void action();
};

#endif
