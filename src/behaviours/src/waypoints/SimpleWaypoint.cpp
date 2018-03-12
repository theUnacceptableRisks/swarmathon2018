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
            double output;

            pid_inputs.measured = *driving_params.current_theta;
            pid_inputs.goal = WaypointUtilities::getGoalTheta( driving_params );
            pid_inputs.time = inputs->time.toSec();
            pid_inputs.max_output = simple_params.rotational_max;

            output = rotational_pid.execute( pid_inputs );

            setOutputLeftPWM( (-1)*output );
            setOutputRightPWM( output );
            break;
        }
        case SIMPLE_SKID:
        {
            PidInputs pid_inputs;
            double linear_output;
            double rotational_output;

            pid_inputs.measured = (-1)*WaypointUtilities::getDistance( driving_params );
            pid_inputs.goal = 0; //trying to go a distance, why wouldn't you want to zero that distance?
            pid_inputs.time = inputs->time.toSec();
            pid_inputs.max_output = simple_params.linear_max;

            linear_output = linear_pid.execute( pid_inputs );

            pid_inputs.measured = *driving_params.current_theta;
            pid_inputs.goal = WaypointUtilities::getGoalTheta( driving_params );
            pid_inputs.max_output = simple_params.skid_rotational_max;

            rotational_output = rotational_pid.execute( pid_inputs );

            setOutputLeftPWM( linear_output - rotational_output );
            setOutputRightPWM( linear_output + rotational_output );
            break;
        }
    }
}

void SimpleWaypoint::forceTransition( SWState transition_to )
{
    internal_state = transition_to;
}
