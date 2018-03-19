#include "Velocity.h"

double generateVelocity( VelParams params )
{
    double constant = 0.0;
    double output = 0.0;
    double error = fabs( params.error_current - params.error_goal );

    if( error > params.deccel_point )
    {
        output = params.max_velocity;
    }
    else
    {
        output = error * ( params.max_velocity / params.deccel_point );
    }

    if( output < MIN_VEL )
        output = MIN_VEL;
    return output;
}

