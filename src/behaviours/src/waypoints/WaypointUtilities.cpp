#include "WaypointUtilities.h"


/******************
 * Trig Shortcuts *
 ******************/
float WaypointUtilities::getDistance( DrivingParams params )
{
    //simple hypotenuse of the difference between the two points
    //order shouldnt matter as long as its consistant
    return hypot( fabs( params.goal_x - params.current_x ),
                  fabs( params.goal_y - params.current_y ) );
}

float WaypointUtilities::getAngularCorrectionNeeded( DrivingParams params )
{
    //goal_theta -> tan = opposite/adjacent, ie this gives us an angular heading we need to be on to reach out destination
    //shortest_angular_distance finds the smaller of the two amounts we could rotate in either direction to arrive there

    float goal_theta = atan2( ( params.goal_y - params.current_y ), ( params.goal_x - params.current_x ) );

    return angles::shortest_angular_distance( params.current_theta, goal_theta );
}

/*************
 * PID Stuff *
 *************/

PIDConfig WaypointUtilities::fastVelConfig()
{
  PIDConfig config;

  config.Kp = 60; //proportional constant
  config.Ki = 10; //integral constant
  config.Kd = 2; //derivative constant
  config.satUpper = 255; //upper limit for PID output
  config.satLower = -255; //lower limit for PID output
  config.antiWindup = config.satUpper; //prevent integral from acruing error untill proportional output drops below a certain limit
  config.errorHistLength = 4; //how many time steps to average error over
  config.alwaysIntegral = true; //should the integral alway be on or only when there is error
  config.resetOnSetpoint = true; //reset the integral and error history whent he setpoint changes
  config.feedForwardMultiplier = 610; //gives 127 pwm at 0.4 commandedspeed  ORIG:320
  config.integralDeadZone = 0.01; //set the integral dead zone, prevented integral from growing or shrinking do to noise
  config.integralErrorHistoryLength = 10000; //how many time ticks should error history should be stored for integration
  config.integralMax = config.satUpper/2; //what is the limit of the integral output for the PID
  config.derivativeAlpha = 0.7; //dead code not used

  return config;
}

PIDConfig WaypointUtilities::fastYawConfig() {
  PIDConfig config;

  config.Kp = 60;
  config.Ki = 15;
  config.Kd = 5;
  config.satUpper = 255;
  config.satLower = -255;
  config.antiWindup = config.satUpper/6;
  config.errorHistLength = 4;
  config.alwaysIntegral = false;
  config.resetOnSetpoint = true;
  config.feedForwardMultiplier = 0;
  config.integralDeadZone = 0.01;
  config.integralErrorHistoryLength = 10000;
  config.integralMax = config.satUpper/3;
  config.derivativeAlpha = 0.7;

  return config;
}

PIDConfig WaypointUtilities::slowVelConfig() {
  PIDConfig config;

  config.Kp = 100;
  config.Ki = 8;
  config.Kd = 1.1;
  config.satUpper = 255;
  config.satLower = -255;
  config.antiWindup = config.satUpper/2;
  config.errorHistLength = 4;
  config.alwaysIntegral = true;
  config.resetOnSetpoint = true;
  config.feedForwardMultiplier = 320; //gives 127 pwm at 0.4 commandedspeed
  config.integralDeadZone = 0.01;
  config.integralErrorHistoryLength = 10000;
  config.integralMax = config.satUpper/2;
  config.derivativeAlpha = 0.7;

  return config;
}

PIDConfig WaypointUtilities::slowYawConfig() {
  PIDConfig config;

  config.Kp = 70;
  config.Ki = 16;
  config.Kd = 10;
  config.satUpper = 255;
  config.satLower = -255;
  config.antiWindup = config.satUpper/4;
  config.errorHistLength = 4;
  config.alwaysIntegral = false;
  config.resetOnSetpoint = true;
  config.feedForwardMultiplier = 0;
  config.integralDeadZone = 0.01;
  config.integralErrorHistoryLength = 10000;
  config.integralMax = config.satUpper/6;
  config.derivativeAlpha = 0.7;

  return config;
}

PIDConfig WaypointUtilities::constVelConfig() {
  PIDConfig config;

  config.Kp = 60;
  config.Ki = 10;
  config.Kd = 2;
  config.satUpper = 255;
  config.satLower = -255;
  config.antiWindup = config.satUpper;
  config.errorHistLength = 4;
  config.alwaysIntegral = true;
  config.resetOnSetpoint = true;
  config.feedForwardMultiplier = 610; //gives 127 pwm at 0.4 commandedspeed  ORIG:320
  config.integralDeadZone = 0.01;
  config.integralErrorHistoryLength = 10000;
  config.integralMax = config.satUpper/2;
  config.derivativeAlpha = 0.7;

  return config;
}

PIDConfig WaypointUtilities::constYawConfig() {
  PIDConfig config;

  config.Kp = 5;
  config.Ki = 5;
  config.Kd = 0;
  config.satUpper = 255;
  config.satLower = -255;
  config.antiWindup = config.satUpper/4;
  config.errorHistLength = 4;
  config.alwaysIntegral = true;
  config.resetOnSetpoint = true;
  config.feedForwardMultiplier = 0;
  config.integralDeadZone = 0.01;
  config.integralErrorHistoryLength = 10000;
  config.integralMax = config.satUpper;
  config.derivativeAlpha = 0.6;

  return config;
}

