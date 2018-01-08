#include "SimpleWaypoint.h"
#include "SimpleWaypointStates.h"

SimpleWaypoint::SimpleWaypoint( SimpleWaypointInputs i ) : Waypoint(), inputs(i), goal_x(i.x), goal_y(i.y)
{
    //inputs are automatically handled above
    //outputs are automatically built into the inherited class
    //states
    addState( "simple_init", new SimpleWaypointInit() );
    addState( "simple_rotate", new SimpleWaypointRotate() );
    addState( "simple_skid", new SimpleWaypointSkid() );
    addState( "simple_arrived", new SimpleWaypointArrived() );
    //pids | gotta build these like this or it acts weird
    pids.fast_vel_pid = PID();
    pids.fast_yaw_pid = PID();
    pids.slow_vel_pid = PID();
    pids.slow_yaw_pid = PID();
    pids.const_vel_pid = PID();
    pids.const_yaw_pid = PID();

    pids.fast_vel_pid.SetConfiguration( WaypointUtilities::fastVelConfig() );
    pids.fast_yaw_pid.SetConfiguration( WaypointUtilities::fastYawConfig() );
    pids.slow_vel_pid.SetConfiguration( WaypointUtilities::slowVelConfig() );
    pids.slow_yaw_pid.SetConfiguration( WaypointUtilities::slowYawConfig() );
    pids.const_vel_pid.SetConfiguration( WaypointUtilities::constVelConfig() );
    pids.const_yaw_pid.SetConfiguration( WaypointUtilities::constYawConfig() );
    //misc
    driving_params.goal_x = goal_x;
    driving_params.goal_y = goal_y;

}

bool SimpleWaypoint::updateDrivingParams()
{
    bool success = false;

    driving_params.current_x = *inputs.current_position.x;
    driving_params.current_y = *inputs.current_position.y;
    driving_params.current_theta = *inputs.current_position.theta;
    driving_params.current_linear_vel = *inputs.current_linear_vel;
    driving_params.current_angular_vel = *inputs.angular_vel;

    return success;
}
