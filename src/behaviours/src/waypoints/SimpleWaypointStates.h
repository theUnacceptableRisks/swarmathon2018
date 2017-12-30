#ifndef simplewaypointstates_h
#define simplewaypointstates_h

#include "../state_machine/State.h"

class SimpleWaypointState : public State
{
    public:
        virtual bool setOwner( StateMachine *sm );
        virtual std::string transition();
    protected:
        SimpleWaypoint *sw_owner;
};

class SimpleWaypointInit : public SimpleWaypointState
{
    public:
        SimpleWaypointInit() : State( "simple_init" );
};
#endif
