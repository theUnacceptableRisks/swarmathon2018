#include "PID.h"
#include <cmath>
#include <angles/angles.h>
#include <iostream>

int PID::execute( PidInputs inputs )
{
    double output = params.bias;

    /* something has changed, and that means we need to clear this out. */
    if( prev_goal != inputs.goal )
        reset();

    double error = inputs.goal - inputs.measured;
    double dt = inputs.time - prev_time;

    if( params.radians_mode )
    {
        error = angles::shortest_angular_distance( inputs.measured, inputs.goal );
    }

    /* Porportional */
    output += error * params.Kp;

    /* Integral */
    if( params.Ki != 0 && fabs( error ) <= params.integration_point && prev_time != 0 )
    {
        addIntegral( fabs( error * dt ) );
        output += getErrorIntegral() * params.Ki * ( error / fabs( error ) );
    }

    /* Derivative */
    output += ( error - prev_error ) / dt;

    prev_time = inputs.time;
    prev_goal = inputs.goal;

    /* check our maximum output limits */
    if( fabs( output ) > inputs.max_output )
    {
        if( output < 0 )
            output = (-1)*inputs.max_output;
        else
            output = inputs.max_output;
    }

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
