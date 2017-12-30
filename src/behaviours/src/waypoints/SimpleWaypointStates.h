#ifndef simplewaypointstates_h
#define simplewaypointstates_h

#include "../state_machine/State.h"

class SimpleWaypointInit : public State
{
    public:
        SimpleWaypointInit() : State( "simple_init" ) {}
        virtual void onEnter( std::string prev_state );
//        virtual void transition();
};

#endif
