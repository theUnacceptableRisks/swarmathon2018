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
            PidInputs pid_inputs;
            std::tuple<int,int> output;

            pid_inputs.measured = *driving_params.current_theta;
            pid_inputs.goal = WaypointUtilities::getGoalTheta( driving_params );
            pid_inputs.time = inputs->time.toSec();
            pid_inputs.max_output = simple_params.rotational_max;

            output = rotational_pid.execute( pid_inputs );

            setOutputLeftPWM( std::get<0>(output) );
            setOutputRightPWM( std::get<1>(output) );
            break;
        }
        case SIMPLE_SKID:
        {
            PidInputs pid_inputs;
            std::tuple<int,int> linear_output;
            std::tuple<int,int> rotational_output;

            pid_inputs.measured = WaypointUtilities::getDistance( driving_params );
            pid_inputs.goal = 0; //trying to go a distance, why wouldn't you want to zero that distance?
            pid_inputs.time = inputs->time.toSec();
            pid_inputs.max_output = simple_params.skid_max;

            linear_output = linear_pid.execute( pid_inputs );

            pid_inputs.measured = *driving_params.current_theta;
            pid_inputs.goal = WaypointUtilities::getGoalTheta( driving_params );
            pid_inputs.max_output = simple_params.skid_max;

            rotational_output = rotational_pid.execute( pid_inputs );

            setOutputLeftPWM( std::get<0>(linear_output) + std::get<0>(rotational_output) );
            setOutputRightPWM( std::get<1>(linear_output) + std::get<1>(rotational_output) );
            break;
        }
    }
}

void SimpleWaypoint::forceTransition( SWState transition_to )
{
    internal_state = transition_to;
}
