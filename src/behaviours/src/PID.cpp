#include "PID.h"
#include <cmath>
#include <iostream>

int PID::runPID( double error, double dt )
{
    double output = params.bias;

    /* Porportional */
    output += error * params.Kp;

    /* Integral */
    if( params.Ki != 0 && error <= params.integration_point && prev_time != 0 )
    {
        error_inf += (error * dt);
        output += error_inf * params.Ki;
//        addIntegral( error * dt );
//        output += getErrorIntegral() * params.Ki;
    }
    else
    {
        error_inf = 0;
     //   error_integral.clear();
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
    error_derivative.clear();
    error_integral.clear();
    error_inf = 0;
    prev_error = 0.;
    prev_time = 0.;
}

void PID::addIntegral( double value )
{
    if( error_integral.size() > INTEG_MAX )
    {
        error_integral.erase( error_integral.begin() );
    }
    error_integral.push_back( value );
}

double PID::getErrorIntegral()
{
    double ret = 0.0;
    int size = error_integral.size();

    if( size != 0 )
    {
        for( int i = 0; i < size; i++ )
            ret += error_integral.at(i);
    }

    return ret;
}
