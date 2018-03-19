#include "LinRotPID.h"

std::tuple<int,int> LinRotPID::execute( PidInputs inputs )
{
    int output;

    if( prev_goal != inputs.goal )
        reset();

    double error = inputs.goal - inputs.measured;
    double dt = inputs.time - prev_time;

    output = runPID( fabs( error ), dt );

    prev_time = inputs.time;
    prev_goal = inputs.goal;

    if( output > inputs.saturation )
        output = inputs.saturation;

    if( inputs.measured < inputs.goal )
    {
        return std::make_tuple( output*(-1), output );
    }
    return std::make_tuple( output, output*(-1) );
}
