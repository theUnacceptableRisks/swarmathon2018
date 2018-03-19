#include "LinVelPID.h"

std::tuple<int,int> LinVelPID::execute( PidInputs inputs )
{
    int output;

    double error = inputs.goal - inputs.measured;
    double dt = inputs.time - prev_time;

    output = runPID( error, dt );

    prev_time = inputs.time;
    prev_goal = inputs.goal;

    if( fabs( output ) > inputs.saturation )
    {
        if( output < 0 )
            output = -inputs.saturation;
        else
            output = inputs.saturation;
    }

    return std::make_tuple( output, output );
}
