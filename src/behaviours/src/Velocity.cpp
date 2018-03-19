#include "Velocity.h"

double generateVelocity( VelParams params )
{
    double constant = 0.0;
    double output = 0.0;
    double error = fabs( params.error_measured - params.error_goal );

    if( fabs( error ) > params.deccel_point )
    {
        if( output < 0 )
            output = -params.max_velocity;
        else
            output = params.max_velocity;
    }
    else
    {
        output = error * ( params.max_velocity / params.deccel_point );
    }

    if( fabs( output ) < params.min_velocity )
    {
        if( output < 0 )
            output = -params.min_velocity;
        else
            output = params.min_velocity;
    }
    return output;
}

