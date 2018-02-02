#ifndef waypointutility_h
#define waypointutility_h

#include <math.h>
#include <tuple>
#include <angles/angles.h>
#include "../Tag.h"
#include "../PID.h"

namespace WaypointUtilities
{
    typedef struct driving_params
    {
        double goal_x = 0.0;
        double goal_y = 0.0;
        double *current_x = 0;
        double *current_y = 0;
        double *current_theta = 0;
        double *current_linear_vel = 0;
        double *current_angular_vel = 0;
    } DrivingParams;

    /******************
     * Trig Shortcuts *
     ******************/
    float getDistanceToTag( Tag tag );
    float getDistance( DrivingParams params );
    float getGoalTheta( DrivingParams params );
    float getAngularCorrectionNeeded( DrivingParams params );

   /*************
    * PID Stuff *
    *************/
    typedef struct pid_package
    {
        PID vel_pid;
        PID yaw_pid;
    } PidPackage;

    typedef struct pid_params
    {
        float velocity_error = 0.0;	//the discrepency between current velocity and what you want to be at
        float angular_error = 0.0;	//the discrepency between the current angle and what angle you want to be facing
        float velocity_goal = 0.0;
        float angular_goal = 0.0;
        float saturation_point = 0.0;	//not quite sure what this is about... entirely...
    } PidParams;

    std::tuple<int,int> executePid( PidParams &params, PidPackage &pids );

};

#endif
