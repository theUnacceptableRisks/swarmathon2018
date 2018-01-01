#include "SimpleWaypointStates.h"
#include "WaypointUtilities.h"
#include "../state_machine/Error.h"

/***********************************************
 * The template for all states in this machine *
 ***********************************************/

bool SimpleWaypointState::setOwner( StateMachine *sm )
{
    bool success = false;

    if( !owner && !sw_owner )
    {
       owner = sm;
       sw_owner = (SimpleWaypoint *)sm;
    }
    return success;
}



 /********************************************\
 * General Transition Function For All States *
 **********************************************
 | This determines the state to transition to |
 | as well as updates the driving_params      |
 \********************************************/

std::string SimpleWaypointState::transition()
{
    std::string transition_to = getIdentifier();

    std::cout << "starting transition" << std::endl;

    if( sw_owner->updateDrivingParams() )
    {
        if( WaypointUtilities::getDistance( sw_owner->driving_params ) < .1 ) //todo setup distance tolerance handling
        {
            transition_to = "simple_arrived";
        }
        else
        {
            float angularCorrection = WaypointUtilities::getAngularCorrectionNeeded( sw_owner->driving_params );
            if( fabs( angularCorrection ) > .3 ) //todo setup angular tolerance handling
            {
                transition_to = "simple_rotate";
            }
            else
            {
                transition_to = "simple_skid";
            }
        }
    }
    else
    {
        messaging::errorMsg( __func__, "updateDrivingParams failed to update." );
    }
    return transition_to;
}



/*******************************
 * SimpleWaypoint Rotate State *
 *******************************/

void SimpleWaypointRotate::action()
{
    WaypointUtilities::PidParams params;
    std::tuple<int,int> leftAndRight;

    if( sw_owner->updateDrivingParams() )
    {
        params.type = WaypointUtilities::SLOW_PID;
        params.velocity_error = 0.0;
        params.velocity_goal = 0.0;
        params.angular_error = WaypointUtilities::getAngularCorrectionNeeded( sw_owner->driving_params );
        params.angular_goal = WaypointUtilities::getGoalTheta( sw_owner->driving_params );
        params.saturation_point = 20; //180 seems to be standard...?

        leftAndRight = WaypointUtilities::executePid( params, sw_owner->pids );
    }
    std::cout << "Left is " << std::get<0>( leftAndRight ) << std::endl;
    std::cout << "Right is " << std::get<1>( leftAndRight ) << std::endl;

    sw_owner->setOutputLeftVelocity( std::get<0>( leftAndRight ) );
    sw_owner->setOutputRightVelocity( std::get<1>( leftAndRight ) );
}

/*******************************
 * SimpleWaypoint Skid State *
 *******************************/

void SimpleWaypointSkid::action()
{
    WaypointUtilities::PidParams params;
    std::tuple<int,int> leftAndRight;

    if( sw_owner->updateDrivingParams() )
    {
        params.type = WaypointUtilities::FAST_PID;
        params.velocity_error = sw_owner->driving_params.current_linear_vel - .35;
        params.velocity_goal = .35;
        params.angular_error = WaypointUtilities::getAngularCorrectionNeeded( sw_owner->driving_params );
        params.angular_goal = WaypointUtilities::getGoalTheta( sw_owner->driving_params );
        params.saturation_point = 180; //180 seems to be standard...?

        leftAndRight = WaypointUtilities::executePid( params, sw_owner->pids );
    }

    sw_owner->setOutputLeftVelocity( std::get<0>( leftAndRight ) );
    sw_owner->setOutputRightVelocity( std::get<1>( leftAndRight ) );
}

/*******************************
 * SimpleWaypoint Arrived State *
 *******************************/

void SimpleWaypointArrived::action()
{
    sw_owner->setOutputLeftVelocity( 0 );
    sw_owner->setOutputRightVelocity( 0 );
}


