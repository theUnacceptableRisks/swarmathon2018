#include "SimpleWaypoint.h"
#include "SimpleWaypointStates.h"

SimpleWaypoint::SimpleWaypoint( WaypointUtilities::DrivingParams i, SimpleWaypointSupplementalInputs si ) : Waypoint(), inputs(i), supplemental_inputs(si)
{
    //inputs are automatically handled above
    //outputs are automatically built into the inherited class
    //states
    addState( "simple_init", new SimpleWaypointInit() );
    addState( "simple_rotate", new SimpleWaypointRotate() );
    addState( "simple_skid", new SimpleWaypointSkid() );
    addState( "simple_final_approach", new SimpleWaypointFinalApproach() );
    addState( "simple_arrived", new SimpleWaypointArrived() );

   //pids | gotta build these like this or it acts weird
    pids.vel_pid = PID();
    pids.yaw_pid = PID();

    PIDConfig vel_config;
    vel_config.Kp = 60; //proportional constant
    vel_config.Ki = 0; //integral constant
    vel_config.Kd = 0; //derivative constant
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

    PIDConfig yaw_config;
    yaw_config.Kp = 100;
    yaw_config.Ki = 0;
    yaw_config.Kd = 0;
    yaw_config.satUpper = 255;
    yaw_config.satLower = -255;
    yaw_config.antiWindup = yaw_config.satUpper/6;
    yaw_config.errorHistLength = 4;
    yaw_config.alwaysIntegral = false;
    yaw_config.resetOnSetpoint = true;
    yaw_config.feedForwardMultiplier = 0;
    yaw_config.integralDeadZone = 0.01;
    yaw_config.integralErrorHistoryLength = 10000;
    yaw_config.integralMax = yaw_config.satUpper/3;
    yaw_config.derivativeAlpha = 0.7;


    pids.vel_pid.SetConfiguration( vel_config );
    pids.yaw_pid.SetConfiguration( yaw_config );

}
