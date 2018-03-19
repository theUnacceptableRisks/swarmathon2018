#include "RadRotPID.h"

std::tuple<int,int> RadRotPID::execute( PidInputs inputs )
{
    int output;

    if( prev_goal != inputs.goal )
        reset();

    double error = angles::shortest_angular_distance( inputs.measured, inputs.goal );
    double dt = inputs.time - prev_time;

    output = runPID( fabs( error ), dt );

    prev_time = inputs.time;
    prev_goal = inputs.goal;

    if( output > inputs.saturation )
        output = inputs.saturation;

    if( error >= 0 )
    {
        return std::make_tuple( output*(-1), output );
    }

    return std::make_tuple( output, output*(-1) );
}
