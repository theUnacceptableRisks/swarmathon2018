#include "LinearWaypoint.h"

void LinearWaypoint::run()
{
    std::tuple<int,int> output;
    /* in irl */
//    double current_distance = fabs( this->original_x - this->inputs->raw_odom.x );
    /* in sim */
    double current_distance = hypot( original_x - inputs->raw_odom.x, original_y - inputs->raw_odom.y );

    if( current_distance >= l_params.distance )
        this->has_arrived = true;

    if( this->has_arrived == false )
    {
        PidInputs pid_inputs;

        pid_inputs.measured = l_params.distance - current_distance;
        pid_inputs.goal = 0;
        pid_inputs.time = inputs->time.toSec();
        pid_inputs.max_output = l_params.max_output;

        output = linear_pid.execute( pid_inputs );

        if( l_params.reverse )
        {
            setOutputLeftPWM( (-1)*std::get<0>(output) );
            setOutputRightPWM( (-1)*std::get<1>(output) );
        }
        else
        {
            setOutputLeftPWM( std::get<0>(output) );
            setOutputRightPWM( std::get<1>(output) );
        }
    }
    else
    {
        setOutputLeftPWM( 0 );
        setOutputRightPWM( 0 );
    }
}
