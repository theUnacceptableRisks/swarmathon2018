#include "LinearWaypoint.h"

void LinearWaypoint::run()
{
    std::tuple<int,int> output;
    double current_distance = fabs( this->original_x - this->inputs->raw_odom.x );

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

        setOutputLeftPWM( std::get<0>(output) );
        setOutputRightPWM( std::get<1>(output) );
    }
    else
    {
        setOutputLeftPWM( 0 );
        setOutputRightPWM( 0 );
    }
}
