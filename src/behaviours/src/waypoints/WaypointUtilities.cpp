#include "WaypointUtilities.h"


/******************
 * Trig Shortcuts *
 ******************/
float WaypointUtilities::getDistance( DrivingParams params )
{
    //simple hypotenuse of the difference between the two points
    //order shouldnt matter as long as its consistant
    return hypot( fabs( params.goal_x - *params.current_x ),
                  fabs( params.goal_y - *params.current_y ) );
}

float WaypointUtilities::getGoalTheta( DrivingParams params )
{
    //goal_theta -> tan = opposite/adjacent, ie this gives us an angular heading we need to be on to reach out destination
    return atan2( ( params.goal_y - *params.current_y ), ( params.goal_x - *params.current_x ) );
}

float WaypointUtilities::getAngularCorrectionNeeded( DrivingParams params )
{
    //shortest_angular_distance finds the smaller of the two amounts we could rotate in either direction to arrive there
    return angles::shortest_angular_distance( *params.current_theta, getGoalTheta( params ) );
}

/*************
 * PID Stuff *
 *************/

/*
std::tuple<int,int> WaypointUtilities::executePid( PidParams &params, PidPackage &pids )
{
    float vel = 0.0;
    float yaw = 0.0;
    int left = 0;
    int right = 0;

    vel = pids.vel_pid.PIDOut( params.velocity_error, params.velocity_goal );
    yaw = pids.yaw_pid.PIDOut( params.angular_error, params.angular_goal );
    left = (int)(vel - yaw);
    right = (int)(vel + yaw);

    if (left  >  params.saturation_point) {left  =  params.saturation_point;}
    if (left  < -params.saturation_point) {left  = -params.saturation_point;}
    if (right >  params.saturation_point) {right =  params.saturation_point;}
    if (right < -params.saturation_point) {right = -params.saturation_point;}

    return std::make_tuple( left, right );
}
*/

/* linear */

/* generate a linear output based on a linaer distance in meters from a target */
PidParams WaypointUtilities::getDistPIDParams()
{
    PidParams params;
    /* in sim */
    params.Kp = 60.;
    params.Ki = 0.;
    params.Kd = 0.;
    params.integration_point = 0.15;

    /* in irl */
//    params.Kp = 55.;
 //   params.Ki = 15.;
  //  params.Kd = 1.;
   // params.integration_point = 0.15;
    return params;
}

/* rotation */

/* generate a rotational output ba+sed on radian measurements from a target */
PidParams WaypointUtilities::getRadianRotPIDParams()
{
    PidParams params;

    /* in sim */
    params.Kp = 60.;
    params.Ki = 0.;
    params.Kd = 0.;
    params.integration_point = 0.15;
    /* in irl */
//    params.Kp = 120.;
  //  params.Ki = 15.;
   // params.Kd = 5.;
   // params.integration_point = 0.15;

    return params;
}

/* generate a rotational output based on meter measurements from a target */
/* TODO: may need to break this up into camera and sonar distances but will try as one */
PidParams WaypointUtilities::getLinearRotPIDParams()
{
    PidParams params;

    /* in sim */
    params.Kp = 60.;
    params.Ki = 0.;
    params.Kd = 0.;
    params.integration_point = 0.1;
    /* in irl */
//    params.Kp = 180.;
//    params.Ki = 40.;
//    params.Kd = 20.;
//    params.integration_point = 0.1;

    return params;
}

/* skid linear */

PidParams WaypointUtilities::getDistSkidBasedPIDParams()
{
    PidParams params;

    /* in sim */
    params.Kp = 60.;
    params.Ki = 0.;
    params.Kd = 0.;
    params.integration_point = 0.15;
    /* in irl */
  //  params.Kp = 50.;
 //   params.Ki = 5.;
//    params.Kd = 5.;
//    params.integration_point = 0.15;

    return params;

}

/* skid rotation */

PidParams WaypointUtilities::getRadianRotSkidBasedPIDParams()
{
    PidParams params;

    /* in sim */
    params.Kp = 60.;
    params.Ki = 0.;
    params.Kd = 0.;
    params.integration_point = 0.15;
    /* in irl */
 //   params.Kp = 130.;
//    params.Ki = 15.;
//    params.Kd = 5.;
//    params.integration_point = 0.15;

    return params;
}

PidParams WaypointUtilities::getLinearRotSkidBasedPIDParams()
{
    PidParams params;

    /* in sim */
    params.Kp = 60.;
    params.Ki = 0.;
    params.Kd = 0.;
    params.integration_point = 0.1;
    /* in irl */
//    params.Kp = 140.;
  //  params.Ki = 10.;
    //params.Kd = 5.;
    //params.integration_point = 0.1;

    return params;
}

