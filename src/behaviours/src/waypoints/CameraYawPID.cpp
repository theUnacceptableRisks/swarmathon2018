#include "CameraYawPID.h"
#include "../TagUtilities.h"

CameraYawPID::CameraYawPID( LogicInputs *i, CameraYawParams p ) : Waypoint( i ), params(p)
{
    pids.vel_pid = PID();

    PIDConfig yaw_config;
    yaw_config.Kp = params.kp; //proportional constant
    yaw_config.Ki = params.ki; //integral constant
    yaw_config.Kd = params.kd; //derivative constant
    yaw_config.satUpper = 255; //upper limit for PID output
    yaw_config.satLower = -255; //lower limit for PID output
    yaw_config.antiWindup = yaw_config.satUpper; //prevent integral from acruing error untill proportional out$
    yaw_config.errorHistLength = 4; //how many time steps to average error over
    yaw_config.alwaysIntegral = true; //should the integral alway be on or only when there is error
    yaw_config.resetOnSetpoint = true; //reset the integral and error history whent he setpoint changes
    yaw_config.feedForwardMultiplier = 0; //gives 127 pwm at 0.4 commandedspeed  ORIG:320
    yaw_config.integralDeadZone = 0.01; //set the integral dead zone, prevented integral from growing or s$
    yaw_config.integralErrorHistoryLength = 10000; //how many time ticks should error history should be st$
    yaw_config.integralMax = yaw_config.satUpper/2; //what is the limit of the integral output for the PID
    yaw_config.derivativeAlpha = 0.7; //dead code not used

    pids.yaw_pid.SetConfiguration( yaw_config );

}

void CameraYawPID::run()
{
    WaypointUtilities::PidParams wp_params;
    std::tuple<int,int> leftAndRight = std::make_tuple<int,int> ( 0, 0 );
    if( TagUtilities::hasTag( &inputs->tags, 0 ) )
    {
        wp_params.velocity_error = 0;
        wp_params.velocity_goal = 0.0;
        wp_params.angular_error = (-1)*(inputs->tags.back().getPositionX());
        wp_params.angular_goal = 0.0;
        wp_params.saturation_point = 80;

        leftAndRight = WaypointUtilities::executePid( wp_params, pids );

        setOutputLeftPWM( std::get<0>( leftAndRight ) );
        setOutputRightPWM( std::get<1>( leftAndRight ) );
    }
    else
    {
        setOutputLeftPWM( 0 );
        setOutputRightPWM( 0 );
    }
}