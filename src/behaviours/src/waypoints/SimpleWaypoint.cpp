#include "SimpleWaypoint.h"
#include <math.h>

void SimpleWaypoint::run()
{
    forceTransition( internalTransition() );
    internalAction();
}

SWState SimpleWaypoint::internalTransition()
{
    SWState transition_to = internal_state;

    float angular_correction = WaypointUtilities::getAngularCorrectionNeeded( this->driving_params );
    float distance_to_waypoint = WaypointUtilities::getDistance( this->driving_params );

    if( fabs( distance_to_waypoint ) < this->simple_params.arrived_threshold )
        transition_to = SIMPLE_ARRIVED;
    else
    {
        if( fabs( angular_correction ) > this->simple_params.skid_steer_threshold )
            transition_to = SIMPLE_ROTATE;
        else
            transition_to = SIMPLE_SKID;
    }

    return transition_to;
}

void SimpleWaypoint::internalAction()
{
    this->inputs->goal_x = this->driving_params.goal_x;
    this->inputs->goal_y = this->driving_params.goal_y;
    switch( internal_state )
    {
        default: break;
        case SIMPLE_ARRIVED:
            this->has_arrived = true;
            setOutputLeftPWM( 0 );
            setOutputRightPWM( 0 );
            break;
        case SIMPLE_ROTATE:
        {
            MotorParams m_params;
            std::tuple<int,int> output;

            m_params.yaw_deccel_point = this->simple_params.yaw_deccel;
            m_params.yaw_current = *this->driving_params.current_theta;
            m_params.yaw_goal = WaypointUtilities::getGoalTheta( this->driving_params );
            m_params.yaw_in_radians = true;
            m_params.yaw_max_output = this->simple_params.yaw_max_output;

            output = this->inputs->controller.generateRotationalOutput( m_params );

            setOutputLeftPWM( std::get<0>( output ) );
            setOutputRightPWM( std::get<1>( output ) );
            break;
        }
        case SIMPLE_SKID:
        {
            MotorParams m_params;
            std::tuple<int,int> output;

            m_params.dist_deccel_point = this->simple_params.dist_deccel;
            m_params.dist_current = WaypointUtilities::getDistance( this->driving_params );
            m_params.dist_goal = this->simple_params.dist_goal;
            m_params.dist_max_output = this->simple_params.dist_max_output;

            m_params.yaw_deccel_point = this->simple_params.yaw_deccel;
            m_params.yaw_current = *this->driving_params.current_theta;
            m_params.yaw_goal = WaypointUtilities::getGoalTheta( this->driving_params );
            m_params.yaw_in_radians = true;
            m_params.yaw_max_output = this->simple_params.yaw_max_output;

            output = this->inputs->controller.generateSkidOutput( m_params );

            setOutputLeftPWM( std::get<0>( output ) );
            setOutputRightPWM( std::get<1>( output ) );
            break;
        }
    }
}

void SimpleWaypoint::forceTransition( SWState transition_to )
{
    internal_state = transition_to;
}
