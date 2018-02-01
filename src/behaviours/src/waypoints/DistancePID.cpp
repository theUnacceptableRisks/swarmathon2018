#include "DistancePID.h"
#include "DistancePIDState.h"

DistancePID::DistancePID( LogicInput *i, DistancePIDParams p ) : Waypoint( i ), params(p)
{
    //states

    //driving params
    driving_params.goal_x = 0;
    driving_params.goal_y = 0;
    driving_params.current_x = &inputs->raw_odom.x;
    driving_params.current_y = &inputs->raw_odom.y;

    pids.vel_pid = PID();

    PIDConfig vel_config;
    vel_config.Kp = params.kp; //proportional constant
    vel_config.Ki = params.ki; //integral constant
    vel_config.Kd = params.kd; //derivative constant
    vel_config.satUpper = 255; //upper limit for PID output
    vel_config.satLower = -255; //lower limit for PID output
    vel_config.antiWindup = vel_config.satUpper; //prevent integral from acruing error untill proportional out$
    vel_config.errorHistLength = 4; //how many time steps to average error over
    vel_config.alwaysIntegral = true; //should the integral alway be on or only when there is error
    vel_config.resetOnSetpoint = true; //reset the integral and error history whent he setpoint changes
    vel_config.feedForwardMultiplier = 0; //gives 127 pwm at 0.4 commandedspeed  ORIG:320
    vel_config.integralDeadZone = 0.01; //set the integral dead zone, prevented integral from growing or s$
    vel_config.integralErrorHistoryLength = 10000; //how many time ticks should error history should be st$
    vel_config.integralMax = vel_config.satUpper/2; //what is the limit of the integral output for the PID
    vel_config.derivativeAlpha = 0.7; //dead code not used
}
