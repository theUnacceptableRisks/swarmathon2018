#include "ApproachTagWaypoint.h"

ApproachTagWaypoint::ApproachTagWaypoint( ApproachTagParmas p ) : inputs(p)
{
    //addState

    //initPIDs
    pids.fast_vel_pid = PID();
    pids.fast_yaw_pid = PID();
    pids.slow_vel_pid = PID();
    pids.slow_yaw_pid = PID();
    pids.const_vel_pid = PID();
    pids.const_yaw_pid = PID();

    pids.fast_vel_pid.SetConfiguration( TagUtilities::fastVelConfig() );
    pids.fast_yaw_pid.SetConfiguration( TagUtilities::fastYawConfig() );
    pids.slow_vel_pid.SetConfiguration( TagUtilities::slowVelConfig() );
    pids.slow_yaw_pid.SetConfiguration( TagUtilities::slowYawConfig() );
    pids.const_vel_pid.SetConfiguration( TagUtilities::constVelConfig() );
    pids.const_yaw_pid.SetConfiguration( TagUtilities::constYawConfig() );
}
