#ifndef waypointutility_h
#define waypointutility_h

#include <math.h>
#include <tuple>
#include <angles/angles.h>
#include "../PID.h"

namespace WaypointUtilities
{
    typedef struct driving_params
    {
        float goal_x;
        float goal_y;
        float current_x;
        float current_y;
        float current_theta;
    } DrivingParams;

    /******************
     * Trig Shortcuts *
     ******************/
    float getDistance( DrivingParams params );
    float getAngularCorrectionNeeded( DrivingParams params );

   /*************
    * PID Stuff *
    *************/
    PIDConfig fastVelConfig();
    PIDConfig fastYawConfig();
    PIDConfig slowVelConfig();
    PIDConfig slowYawConfig();
    PIDConfig constVelConfig();
    PIDConfig constYawConfig();

    typedef struct pid_package
    {
        PID fast_vel_pid = PID( WaypointUtilities::fastVelConfig() );
        PID fast_yaw_pid = PID( WaypointUtilities::fastYawConfig() );

        PID slow_vel_pid = PID( WaypointUtilities::slowVelConfig() );
        PID slow_yaw_pid = PID( WaypointUtilities::slowYawConfig() );

        PID const_vel_pid = PID( WaypointUtilities::constVelConfig() );
        PID const_yaw_pid = PID( WaypointUtilities::constYawConfig() );
    } PidPackage;

    typedef enum
    {
        FAST_PID, SLOW_PID, CONST_PID
    } PidType;

    typedef struct pid_params
    {
        WaypointUtilities::PidType type;
        float velocity_error;	//the discrepency between current velocity and what you want to be at
        float angular_error;	//the discrepency between the current angle and what angle you want to be facing
        float velocity_goal;
        float angular_goal;
        float saturation_point;	//not quite sure what this is about... entirely...
    } PidParams;

    std::tuple<int,int> executePid( WaypointUtilities::PidParams params, WaypointUtilities::PidPackage &pids );

};

#endif
