#include "SimpleWaypoint.h"
#include "SimpleWaypointStates.h"

SimpleWaypoint::SimpleWaypoint( LogicInputs *i, SimpleParams sp ) : Waypoint( i ), simple_params(sp)
{
    //inputs are automatically handled above
    //outputs are automatically built into the inherited class
    //states
    addState( "simple_init", new SimpleWaypointInit() );
    addState( "simple_rotate", new SimpleWaypointRotate() );
    addState( "simple_skid", new SimpleWaypointSkid() );
    addState( "simple_final_approach", new SimpleWaypointFinalApproach() );
    addState( "simple_arrived", new SimpleWaypointArrived() );

    //driving params
    driving_params.goal_x = simple_params.goal_x;
    driving_params.goal_y = simple_params.goal_y;
    driving_params.current_x = &inputs->odom_accel.x;
    driving_params.current_y = &inputs->odom_accel.y;
    driving_params.current_theta = &inputs->odom_accel.theta;
    driving_params.current_linear_vel = &inputs->linear_vel_odom_accel;
    driving_params.current_angular_vel = &inputs->angular_vel_odom_accel;

    //secondary driving params (used for arrival)
    secondary_driving_params.current_x = &inputs->raw_odom.x;
    secondary_driving_params.current_y = &inputs->raw_odom.y;


    //pids | gotta build these like this or it acts weird
    pids.vel_pid = PID();
    pids.yaw_pid = PID();

    PIDConfig vel_config;
    vel_config.Kp = 80; //proportional constant
    vel_config.Ki = 0; //integral constant
    vel_config.Kd = 0; //derivative constant
//    vel_config.start_integrating = 0.22;

    pids.vel_pid.SetConfiguration( vel_config );

}
