#ifndef waypoint_h
#define waypoint_h

#include "../state_machine/StateMachine.h"

class Waypoint : public StateMachine
{
    public:
        Waypoint()
        {
            outputs.addElement( "left_velocity", new IOInt( &output_left_velocity ) );
            outputs.addElement( "right_velocity", new IOInt( &output_right_velocity ) );
        }
    protected:
        void setOutputLeftVelocity( int vel ) { output_left_velocity = vel; }
        void setOutputRightVelocity( int vel ) { output_right_velocity = vel; }
    private:
        int output_left_velocity;
        int output_right_velocity;
};

#endif
