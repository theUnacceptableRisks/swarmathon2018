#ifndef simplewaypointstates_h
#define simplewaypointstates_h

#include "../state_machine/State.h"


class SimpleWaypointInit : public State
{
    public:
        SimpleWaypointInit() : State( "simple_init" ) {}
        virtual void onEnter( std::string prev_state )
        {
            owner->goal_x = 10;
            owner->goal_y = 10;
        }
//        virtual void transition();
};

#endif
