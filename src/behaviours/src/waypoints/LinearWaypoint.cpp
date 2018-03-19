#include "LinearWaypoint.h"

void LinearWaypoint::run()
{
    std::tuple<int,int> output;
    /* real world */
//    double current_distance = this->original_x - this->inputs->raw_odom.x;
    /* sim world */
    double current_distance = hypot( original_x - inputs->raw_odom.x, original_y - inputs->raw_odom.y );

    if( current_distance >= fabs( l_params.distance ) )
        this->has_arrived = true;

    if( this->has_arrived == false )
    {
        VelParams v_params;

        v_params.error_measured = l_params.distance - ( current_distance ;
        v_params.error_goal = l_params.distance;
        v_params.max_velocity = l_params.max_velocity;
        v_params.deccel_point = l_params.deccel_point;

        PidInputs pid_inputs;

        pid_inputs.measured = inputs->linear_vel;
        pid_inputs.goal = generateVelocity( v_params );
        pid_inputs.time = inputs->time.toSec();
        pid_inputs.saturation = l_params.max_output;

        output = linear_pid.execute( pid_inputs );

        setOutputLeftPWM( std::get<0>(output) );
        setOutputRightPWM( std::get<1>(output) );
    }
    else
    {
        setOutputLeftPWM( 0 );
        setOutputRightPWM( 0 );
    }
}
