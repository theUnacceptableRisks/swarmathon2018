#include "ApproachTagWaypoint.h"

ApproachTagWaypoint::ApproachTagWaypoint( LogicInputs *i, int dt ) : Waypoint( i ), desired_tag_id(dt), validation_counter(0), internal_state(AT_CENTER)
{
    //addState

    //initPIDs
    pids.vel_pid = PID();
    pids.yaw_pid = PID();

    PIDConfig vel_config;
    vel_config.Kp = 120; //proportional constant
    vel_config.Ki = 5; //integral constant
    vel_config.Kd = 0; //derivative constant
    vel_config.start_integrating = 0.12;
    vel_config.max_error_history = 20;

    PIDConfig yaw_config;
    yaw_config.Kp = 240;
    yaw_config.Ki = 0;
    yaw_config.Kd = 0;

    pids.vel_pid.SetConfiguration( vel_config );
    pids.yaw_pid.SetConfiguration( yaw_config );
}

void ApproachTagWaypoint::run()
{
    if( TagUtilities::hasTag( &inputs->tags, desired_tag_id ) )
    {
        forceTransition( internalTransition() );
        internalAction();
    }
}

ATState ApproachTagWaypoint::internalTransition()
{
    ATState transition_to = internal_state;

    switch( internal_state )
    {
        case AT_CENTER:
            if( fabs( inputs->tags.back().getPositionX() ) < 0.05 )
                validation_counter++;
            if( validation_counter > 5 )
            {
                validation_counter = 0;
                transition_to = AT_APPROACH;
            }
            break;
        case AT_APPROACH:
            break;
        case AT_ARRIVED:
            break;
        case AT_FAILED:
            break;
    }

    return transition_to;
}

void ApproachTagWaypoint::internalAction()
{
    WaypointUtilities::PidParams params;
    std::tuple<int,int> leftAndRight = std::make_tuple<int,int> ( 0, 0 );

    switch( internal_state )
    {
        case AT_CENTER:
            std::cout << "AT CENTR" << std::endl;
            params.velocity_error = 0;
            params.velocity_goal = 0;
            params.angular_error = (-1)*(inputs->tags.back().getPositionX());
            params.angular_goal = 0.0;
            params.saturation_point = 30;

            leftAndRight = WaypointUtilities::executePid( params, pids );

            setOutputLeftPWM( std::get<0>( leftAndRight ) );
            setOutputRightPWM( std::get<1>( leftAndRight ) );

            break;
        case AT_APPROACH:
            std::cout << "AT APPROACH" << std::endl;
            params.velocity_error = TagUtilities::getDistance( inputs->tags.back() ) - 0.1;
            params.velocity_goal = 0;
            params.angular_error = (-1)*(inputs->tags.back().getPositionX());
            params.angular_goal = 0.0;
            params.saturation_point = 30;

            leftAndRight = WaypointUtilities::executePid( params, pids );

            setOutputLeftPWM( std::get<0>( leftAndRight ) );
            setOutputRightPWM( std::get<1>( leftAndRight ) );
            break;
        case AT_ARRIVED:
            break;
        case AT_FAILED:
            break;
    }
}

void ApproachTagWaypoint::forceTransition( ATState transition_to )
{
    internal_state = transition_to;
}

/*



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
                params.velocity_error = 0; //curr_dist_to_tag - 0.19;
                params.velocity_goal = 0.0;
                params.angular_error = (-0.018) + (-1)*( inputs->tags.back().getPositionX() );
                cout << "angular error: " << params.angular_error << std::endl;
                params.angular_goal = 0.00;
                cout << "angular goal: " << params.angular_goal << std::endl;
                params.saturation_point = 40;

                leftAndRight = WaypointUtilities::executePid( params, pids );

                setOutputLeftPWM( std::get<0>( leftAndRight ) );
                setOutputRightPWM( std::get<1>( leftAndRight ) );
                prev_dist_to_tag = curr_dist_to_tag;
            }

        }
        else if( prev_dist_to_tag < MAX_DISTANCE_FOR_ARRIVAL )
        {
            setOutputLeftPWM( 0 );
            setOutputRightPWM( 0 );
            has_arrived = true;
        }
        else
        {
            * need to start counting failures here *
            setOutputLeftPWM( 0 );
            setOutputRightPWM( 0 );
        }
    }
}*/
