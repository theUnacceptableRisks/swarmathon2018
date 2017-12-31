#ifndef waypoint_h
#define waypoint_h

#include "../state_machine/StateMachine.h"

class Waypoint : public StateMachine
{
    public:
        /* this needs to be changed into lefts and rights... */
        Waypoint()
        {
            outputs.addElement( "linear_velocity", new IOFloat( &output_linear_velocity ) );
            outputs.addElement( "angular_velocity", new IOFloat( &output_angular_velocity ) );
        }
    protected:
        void setOutputLinearVelocity( float vel ) { output_linear_velocity = vel; }
        void setOutputAngularVelocity( float vel ) { output_angular_velocity = vel; }
    private:
        float output_linear_velocity;
        float output_angular_velocity;
};

#endif
