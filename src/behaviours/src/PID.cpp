#include "PID.h"
#include <cmath>
#include <iostream>

int PID::runPID( double error, double dt )
{
    double output = params.bias;

    /* Porportional */
    output += error * params.Kp;

    /* Integral */
    if( params.Ki != 0 && ( fabs( error ) <= params.integration_point || params.integration_point == 0 ) && prev_time != 0 )
    {
        error_inf += (error * dt);
        output += error_inf * params.Ki;
    }
    else
    {
        error_inf = 0;
    }

    /* Derivative */
    output += ( ( error - prev_error ) / dt ) * params.Kd;

    return (int)output;
}

void PID::setParams( PidParams new_params )
{
    this->params = new_params;
    this->reset();
}

void PID::reset()
{
    error_inf = 0;
    prev_error = 0.;
    prev_time = 0.;
}

