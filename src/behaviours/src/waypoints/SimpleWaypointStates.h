#ifndef simplewaypointstates_h
#define simplewaypointstates_h

#include "../state_machine/State.h"
#include "SimpleWaypoint.h"

class SimpleWaypointState : public State
{
    public:
        SimpleWaypointState( std::string id ) : State( id ), sw_owner(0) {}
        virtual bool setOwner( StateMachine *sm );
        virtual std::string transition();
        virtual std::string debugString() { return ( "running state: " + getIdentifier() ); }
    protected:
        SimpleWaypoint *sw_owner;
};

class SimpleWaypointInit : public SimpleWaypointState
{
    public:
        SimpleWaypointInit() : SimpleWaypointState( "simple_init" ) {}
};

class SimpleWaypointRotate : public SimpleWaypointState
{
    public:
        SimpleWaypointRotate() : SimpleWaypointState( "simple_rotate" ) {}
        virtual void action();
};

class SimpleWaypointSkid : public SimpleWaypointState
{
    public:
        SimpleWaypointSkid() : SimpleWaypointState( "simple_skid" ) {}
        virtual void action();
};

class SimpleWaypointArrived : public SimpleWaypointState
{
    public:
        SimpleWaypointArrived() : SimpleWaypointState( "simple_arrived" ) {}
        virtual void action();
};

#endif
