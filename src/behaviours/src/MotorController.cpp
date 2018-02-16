#include "MotorController.h"
#include <iostream>

std::tuple<int,int> MotorController::generateLinearOutput( MotorParams params )
{
    double constant = 0.0;
    int vel_output = 0;
    double dist_error = params.dist_current - params.dist_goal;

    if( fabs( dist_error ) > params.dist_deccel_point )
    {
        if( dist_error > 0 )
            vel_output = params.dist_max_output;
        else
            vel_output = (-1)*params.dist_max_output;
    }
    else
    {
        constant = calcKonstant( params.dist_max_output, params.dist_deccel_point );
        std::cout << "Constant: " << constant << std::endl;
        vel_output = getOutput( dist_error, constant );
    }

    if( vel_output > 0 )
        vel_output += this->min_motor_output;
    else
        vel_output -= this->min_motor_output;

    return std::make_tuple ( vel_output, vel_output );
}

std::tuple<int,int> MotorController::generateRotationalOutput( MotorParams params )
{
    int yaw_output = 0;
    int left_output = 0;
    int right_output = 0;
    double constant = 0.0;
    double yaw_error = params.yaw_current - params.yaw_goal;

    if( fabs( yaw_error ) > params.yaw_deccel_point )
        yaw_output = params.yaw_max_output;
    else
    {
        constant = calcKonstant( params.yaw_max_output, params.yaw_deccel_point );
        yaw_output = getOutput( fabs( yaw_error ), constant );
    }

    if( yaw_error <= 0 )
    {
       left_output = (-1)*( yaw_output + this->min_motor_output );
       right_output = yaw_output + this->min_motor_output;
    }
    else
    {
       left_output = yaw_output + this->min_motor_output;
       right_output = (-1)*( yaw_output + this->min_motor_output );
    }


    return std::make_tuple ( left_output, right_output );
}

std::tuple<int,int> MotorController::generateSkidOutput( MotorParams params )
{
    int vel_output = 0;
    int yaw_output = 0;
    int left_output = 0;
    int right_output = 0;
    double dist_error = params.dist_current - params.dist_goal;
    double yaw_error = params.yaw_current - params.yaw_goal;

    return std::make_tuple ( left_output, right_output );
}

double MotorController::calcKonstant( int max, double deccel )
{
    return ( ( (double)max ) / deccel );
}

int MotorController::getOutput( double error, double konstant )
{
    return (int)( error * konstant );
}
