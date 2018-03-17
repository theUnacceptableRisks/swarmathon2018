#include "LinearPID.h"
#include <iostream>

std::tuple<int,int> LinearPID::execute( PidInputs inputs )
{
    int output;

    if( prev_goal != inputs.goal )
        reset();

    double error = inputs.goal - inputs.measured;
    double dt = inputs.time - prev_time;

    /* only pass the magnitude of the error, we'll deal with signs later */

    output = runPID( fabs( error ), dt );
    /* store these for the next iteration, it is important */
    prev_time = inputs.time;
    prev_goal = inputs.goal;

    /* cap our output at the desired max */
    if( output > inputs.max_output )
        output = inputs.max_output;

    return std::make_tuple ( output, output );
}
