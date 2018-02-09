#include "ApproachTagWaypoint.h"

ApproachTagWaypoint::ApproachTagWaypoint( LogicInputs *i, int dt, double distance ) : Waypoint( i ), desired_tag_id(dt), prev_dist_to_tag(distance)
{
    //addState

    //initPIDs
    pids.vel_pid = PID();
    pids.yaw_pid = PID();

    PIDConfig vel_config;
    vel_config.Kp = 160; //proportional constant
    vel_config.Ki = 0; //integral constant
    vel_config.Kd = 0; //derivative constant
    vel_config.satUpper = 255; //upper limit for PID output
    vel_config.satLower = -255; //lower limit for PID output
    vel_config.antiWindup = vel_config.satUpper; //prevent integral from acruing error untill propor$
    vel_config.errorHistLength = 4; //how many time steps to average error over
    vel_config.alwaysIntegral = false; //should the integral alway be on or only when there is error
    vel_config.resetOnSetpoint = true; //reset the integral and error history whent he setpoint chan$
    vel_config.feedForwardMultiplier = 0; //gives 127 pwm at 0.4 commandedspeed  ORIG:320
    vel_config.integralDeadZone = 0.01; //set the integral dead zone, prevented integral from growin$
    vel_config.integralErrorHistoryLength = 10000; //how many time ticks should error history should$
    vel_config.integralMax = vel_config.satUpper/2; //what is the limit of the integral output for t$
    vel_config.derivativeAlpha = 0.7; //dead code not used

    PIDConfig yaw_config;
    yaw_config.Kp = 480;
    yaw_config.Ki = 7;
    yaw_config.Kd = 0;
    yaw_config.satUpper = 255;
    yaw_config.satLower = -255;
    yaw_config.antiWindup = yaw_config.satUpper/6;
    yaw_config.errorHistLength = 4;
    yaw_config.alwaysIntegral = true;
    yaw_config.resetOnSetpoint = true;
    yaw_config.feedForwardMultiplier = 0;
    yaw_config.integralDeadZone = 0.01;
    yaw_config.integralErrorHistoryLength = 10000;
    yaw_config.integralMax = yaw_config.satUpper/3;
    yaw_config.derivativeAlpha = 0.7;

    pids.vel_pid.SetConfiguration( vel_config );
    pids.yaw_pid.SetConfiguration( yaw_config );
}

void ApproachTagWaypoint::run()
{
    WaypointUtilities::PidParams params;
    std::tuple<int,int> leftAndRight = std::make_tuple<int,int> ( 0, 0 );
    double curr_dist_to_tag = 0.0;

    if( has_arrived == false )
    {
        if( TagUtilities::hasTag( &inputs->tags, desired_tag_id ) )
        {
            curr_dist_to_tag = TagUtilities::getDistance( inputs->tags.back() );

            if( fabs( prev_dist_to_tag - curr_dist_to_tag ) > RATE_OF_CHANGE_MAX )
            {
                if( prev_dist_to_tag < MAX_DISTANCE_FOR_ARRIVAL )
                {
                     has_arrived = true;
                     setOutputLeftPWM( 0 );
                     setOutputRightPWM( 0 );
                 }
            }
            else
            {
                params.velocity_error = curr_dist_to_tag;
                params.velocity_goal = 0.0;
                params.angular_error = 0.023 + (-1)*( inputs->tags.back().getPositionX() );
                params.angular_goal = 0.00;
                params.saturation_point = 40;

                leftAndRight = WaypointUtilities::executePid( params, pids );

                setOutputLeftPWM( std::get<0>( leftAndRight ) );
                setOutputRightPWM( std::get<1>( leftAndRight ) );
            }

        }
        else if( prev_dist_to_tag < MAX_DISTANCE_FOR_ARRIVAL )
        {
            std::cout << "this zero" << std::endl;
            setOutputLeftPWM( 0 );
            setOutputRightPWM( 0 );
            has_arrived = true;
        }
        else
        {
            std::cout << "that zero" << std::endl;
            /* need to start counting failures here */
            setOutputLeftPWM( 0 );
            setOutputRightPWM( 0 );
        }
    }
}
