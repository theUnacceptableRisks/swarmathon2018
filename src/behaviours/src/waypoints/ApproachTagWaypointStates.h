#ifndef approachtagwaypointstates_h
#define approachtagwaypointstates_h

#include "../state_machine/State.h"
#include "ApproachTagWaypoint

class ApproachTagBase : public State
{
    public:
        ApproachTagBase( std::string id ) : State ( id ), at_owner(0) {}
        virtual bool setOwner( StateMachine *sm );
    protected:
        ApproachTagWaypoint *at_owner;
};

#endif
