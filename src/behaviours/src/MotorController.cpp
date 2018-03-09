#include "MotorController.h"
#include  <angles/angles.h>
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
        vel_output = getOutput( dist_error, constant );
    }

    if( vel_output >= 0 )
        vel_output += this->min_motor_output + LINEAR_BUMP;
    else
        vel_output -= this->min_motor_output + LINEAR_BUMP;

    return std::make_tuple ( vel_output, vel_output );
}

std::tuple<int,int> MotorController::generateRotationalOutput( MotorParams params )
{
    int yaw_output = 0;
    int left_output = 0;
    int right_output = 0;
    double constant = 0.0;
    double yaw_error = 0.0;

    if( params.yaw_in_radians )
    {
        yaw_error = angles::shortest_angular_distance( params.yaw_current, params.yaw_goal );
        yaw_error *= -1;
    }
    else
        yaw_error = params.yaw_current - params.yaw_goal;

    if( fabs( yaw_error ) > params.yaw_deccel_point )
        yaw_output = params.yaw_max_output;
    else
    {
        constant = calcKonstant( params.yaw_max_output, params.yaw_deccel_point );
        yaw_output = getOutput( fabs( yaw_error ), constant );
    }

    if( yaw_error <= 0 )
    {
       left_output = (-1)*( yaw_output + this->min_rot_output + ROTATION_BUMP );
       right_output = yaw_output + this->min_rot_output + ROTATION_BUMP;
    }
    else
    {
       left_output = yaw_output + this->min_rot_output + ROTATION_BUMP;
       right_output = (-1)*( yaw_output + this->min_rot_output + ROTATION_BUMP );
    }


    return std::make_tuple ( left_output, right_output );
}

std::tuple<int,int> MotorController::generateSkidOutput( MotorParams params )
{
    std::tuple<int,int> linear_output;
    std::tuple<int,int> rotational_output;
    int left_output = 0;
    int right_output = 0;

    linear_output = this->generateLinearOutput( params );
    rotational_output = this->generateRotationalOutput( params );

    left_output = std::get<0>( rotational_output );
    right_output = std::get<1>( rotational_output );

    /* remove the min values from the rotational stuff */

    if( left_output < 0 )
        left_output += this->min_rot_output - SKID_BUMP;
    else
        left_output -= this->min_rot_output - SKID_BUMP;

    if( right_output < 0 )
        right_output += this->min_rot_output - SKID_BUMP;
    else
        right_output -= this->min_rot_output - SKID_BUMP;


    /* these can always be addition because backwards skid is unlikely to happen, and if it does, it should sort itself out */
    left_output += std::get<0>( linear_output );
    right_output += std::get<1>( linear_output );

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

void MotorController::changeMotorMin( int new_min )
{
    this->min_motor_output = new_min;
}

void MotorController::changeRotationalMin( int rot_min )
{
   this->min_rot_output = rot_min;
}
