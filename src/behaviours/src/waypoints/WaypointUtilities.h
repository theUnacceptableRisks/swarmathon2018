#ifndef waypointutility_h
#define waypointutility_h

#include <math.h>
#include <tuple>
#include <angles/angles.h>
#include "../PID.h"

namespace WaypointUtilities
{
    typedef struct standard_driving_params
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

    void standardPackage( PidPackage &package );

    /*
     Need PID functions like in DriveController fastPID( errorVel, errorYaw, goalVel, goalYaw ) etc
     However, make it a general function that takes two structures, the PidPackage and another parameters structure.
     Params will take, fast, slow, const, errors, goals, and saturation point
     Will return a tuple for left and right
    */

};

#endif
