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
       success = true;
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

    if( sw_owner )
    {
        if( WaypointUtilities::getDistance( sw_owner->inputs ) < .1 ) //todo setup distance tolerance handling
        {
            transition_to = "simple_arrived";
        }
        else
        {
            float angularCorrection = WaypointUtilities::getAngularCorrectionNeeded( sw_owner->inputs );

            if( fabs( angularCorrection ) > .4 ) //todo setup angular tolerance handling
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
        messaging::errorMsg( __func__, "sw_owner is null." );
    }

    return transition_to;
}



/*******************************
 * SimpleWaypoint Rotate State *
 *******************************/

void SimpleWaypointRotate::action()
{
    WaypointUtilities::PidParams params;
    std::tuple<int,int> leftAndRight = std::make_tuple<int,int>( 0, 0 );

    if( sw_owner )
    {
        params.type = WaypointUtilities::FAST_PID;
        params.velocity_error = 0.0;
        params.velocity_goal = 0.0;
        params.angular_error = WaypointUtilities::getAngularCorrectionNeeded( sw_owner->inputs );
        params.angular_goal = WaypointUtilities::getGoalTheta( sw_owner->inputs );
        params.saturation_point = 180; //180 seems to be standard...?

        leftAndRight = WaypointUtilities::executePid( params, sw_owner->pids );

        sw_owner->setOutputLeftPWM( std::get<0>( leftAndRight ) );
        sw_owner->setOutputRightPWM( std::get<1>( leftAndRight ) );
    }
}

/*******************************
 * SimpleWaypoint Skid State *
 *******************************/

void SimpleWaypointSkid::action()
{
    WaypointUtilities::PidParams params;
    std::tuple<int,int> leftAndRight = std::make_tuple<int,int>( 0, 0 );

    if( sw_owner )
    {
        params.type = WaypointUtilities::FAST_PID;
        params.velocity_error = .35 - *sw_owner->inputs.current_linear_vel;
        params.velocity_goal = .35;
        params.angular_error = WaypointUtilities::getAngularCorrectionNeeded( sw_owner->inputs );
        params.angular_goal = WaypointUtilities::getGoalTheta( sw_owner->inputs );
        params.saturation_point = 180; //180 seems to be standard...?

        leftAndRight = WaypointUtilities::executePid( params, sw_owner->pids );

        sw_owner->setOutputLeftPWM( std::get<0>( leftAndRight ) );
        sw_owner->setOutputRightPWM( std::get<1>( leftAndRight ) );
    }
}

/*******************************
 * SimpleWaypoint Arrived State *
 *******************************/

void SimpleWaypointArrived::action()
{
    if( sw_owner )
    {
        sw_owner->setOutputLeftPWM( 0 );
        sw_owner->setOutputRightPWM( 0 );
        sw_owner->has_arrived = true;
    }
}


