#include "RotationalWaypoint.h"

void RotationalWaypoint::run()
{
    std::tuple<int,int> output;

    double correction_radian = angles::shortest_angular_distance( r_params.rotate_to, inputs->odom_accel_gps.theta );

    if( fabs( correction_radian ) < r_params.arrived_threshold )
    {
        has_arrived = true;
        setOutputLeftPWM( 0 );
        setOutputRightPWM( 0 );
    }

    if( has_arrived == false )
    {
        PidInputs pid_inputs;

        pid_inputs.measured = inputs->odom_accel_gps.theta;
        pid_inputs.goal = r_params.rotate_to;
        pid_inputs.time = inputs->time.toSec();
        pid_inputs.max_output = r_params.rotational_max;

        output = rot_pid.execute( pid_inputs );

        setOutputLeftPWM( std::get<0>( output ) );
        setOutputRightPWM( std::get<1>( output ) );

    }
    else
    {
        setOutputLeftPWM( 0 );
        setOutputRightPWM( 0 );
    }
}
