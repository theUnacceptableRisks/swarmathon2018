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
