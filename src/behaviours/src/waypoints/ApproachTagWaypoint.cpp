#include "ApproachTagWaypoint.h"

ApproachTagWaypoint::ApproachTagWaypoint( LogicInputs *i ) : Waypoint( i )
{
    //addState

    //initPIDs
    pids.vel_pid = PID();
    pids.yaw_pid = PID();

    PIDConfig vel_config;
    vel_config.Kp = 180; //proportional constant
    vel_config.Ki = 0; //integral constant
    vel_config.Kd = 0; //derivative constant
    vel_config.satUpper = 255; //upper limit for PID output
    vel_config.satLower = -255; //lower limit for PID output
    vel_config.antiWindup = vel_config.satUpper; //prevent integral from acruing error untill propor$
    vel_config.errorHistLength = 4; //how many time steps to average error over
    vel_config.alwaysIntegral = false; //should the integral alway be on or only when there is error
    vel_config.resetOnSetpoint = true; //reset the integral and error history whent he setpoint chan$
    vel_config.feedForwardMultiplier = 0; //gives 127 pwm at 0.4 commandedspeed  ORIG:320
    vel_config.integralDeadZone = 0.01; //set the integral dead zone, prevented integral from growin$
    vel_config.integralErrorHistoryLength = 10000; //how many time ticks should error history should$
    vel_config.integralMax = vel_config.satUpper/2; //what is the limit of the integral output for t$
    vel_config.derivativeAlpha = 0.7; //dead code not used

    PIDConfig yaw_config;
    yaw_config.Kp = 430;
    yaw_config.Ki = 7;
    yaw_config.Kd = 0;
    yaw_config.satUpper = 255;
    yaw_config.satLower = -255;
    yaw_config.antiWindup = yaw_config.satUpper/6;
    yaw_config.errorHistLength = 4;
    yaw_config.alwaysIntegral = true;
    yaw_config.resetOnSetpoint = true;
    yaw_config.feedForwardMultiplier = 0;
    yaw_config.integralDeadZone = 0.01;
    yaw_config.integralErrorHistoryLength = 10000;
    yaw_config.integralMax = yaw_config.satUpper/3;
    yaw_config.derivativeAlpha = 0.7;

    pids.vel_pid.SetConfiguration( vel_config );
    pids.yaw_pid.SetConfiguration( yaw_config );
}

void ApproachTagWaypoint::run()
{
    WaypointUtilities::PidParams params;
    std::tuple<int,int> leftAndRight = std::make_tuple<int,int> ( 0, 0 );

    if( TagUtilities::hasTag( &inputs->tags, 0 ) )
    {
        params.velocity_error = WaypointUtilities::getDistanceToTag( inputs->tags.back() );
        params.velocity_goal = 0.0;
        params.angular_error = (-1)*( inputs->tags.back().getPositionX() );
        params.angular_goal = 0.028;
        params.saturation_point = 20;

        leftAndRight = WaypointUtilities::executePid( params, pids );

        setOutputLeftPWM( std::get<0>( leftAndRight ) );
        setOutputRightPWM( std::get<1>( leftAndRight ) );
    }
    else
    {
        setOutputLeftPWM( 0 );
        setOutputRightPWM( 0 );
    }
}
