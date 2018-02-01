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
        float angularCorrection = WaypointUtilities::getAngularCorrectionNeeded( sw_owner->driving_params );

        if( WaypointUtilities::getDistance( sw_owner->driving_params ) < sw_owner->simple_params.final_approach_threshold &&
            angularCorrection < sw_owner->simple_params.skid_steer_threshold ) //todo setup distance tolerance handling
        {
            if( sw_owner->secondary_driving_params.current_x && sw_owner->secondary_driving_params.current_y )
                transition_to = "simple_final_approach";
            else
                transition_to = "simple_arrived";
        }
        else if( getIdentifier() == "simple_final_approach" )
        {
            if( fabs( WaypointUtilities::getDistance( sw_owner->secondary_driving_params ) ) >= sw_owner->simple_params.final_approach_threshold )
                transition_to = "simple_arrived";

        }
        else
        {
            if( fabs( angularCorrection ) > sw_owner->simple_params.skid_steer_threshold ) //todo setup angular tolerance handling
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

void SimpleWaypointRotate::onExit( std::string next_state )
{
    if( sw_owner && next_state == "simple_final_approach" )
        sw_owner->approach_vel = 20;
}

void SimpleWaypointRotate::action()
{
    WaypointUtilities::PidParams params;
    std::tuple<int,int> leftAndRight = std::make_tuple<int,int>( 0, 0 );

    if( sw_owner )
    {
        params.velocity_error = 0.0;
        params.velocity_goal = 0.0;
        params.angular_error = WaypointUtilities::getAngularCorrectionNeeded( sw_owner->driving_params );
        params.angular_goal = WaypointUtilities::getGoalTheta( sw_owner->driving_params );
        params.saturation_point = sw_owner->simple_params.max_vel; //180 seems to be standard...?

        leftAndRight = WaypointUtilities::executePid( params, sw_owner->pids );

        sw_owner->setOutputLeftPWM( std::get<0>( leftAndRight ) );
        sw_owner->setOutputRightPWM( std::get<1>( leftAndRight ) );
    }
}

/*******************************
 * SimpleWaypoint Skid State *
 *******************************/

void SimpleWaypointSkid::onExit( std::string next_state )
{
    if( sw_owner && next_state == "simple_final_approach" )
    {
        sw_owner->approach_vel = 0;
        sw_owner->approach_vel += std::get<0>( sw_owner->getOutput() );
        sw_owner->approach_vel += std::get<1>( sw_owner->getOutput() );
        sw_owner->approach_vel /= 2;
    }
}

void SimpleWaypointSkid::action()
{
    WaypointUtilities::PidParams params;
    std::tuple<int,int> leftAndRight = std::make_tuple<int,int>( 0, 0 );

    if( sw_owner )
    {
        params.velocity_error = WaypointUtilities::getDistance( sw_owner->driving_params );
        params.velocity_goal = 0.0;
        params.angular_error = WaypointUtilities::getAngularCorrectionNeeded( sw_owner->driving_params );
        params.angular_goal = WaypointUtilities::getGoalTheta( sw_owner->driving_params );
        params.saturation_point = sw_owner->simple_params.max_vel; //180 seems to be standard...?

        leftAndRight = WaypointUtilities::executePid( params, sw_owner->pids );

        sw_owner->setOutputLeftPWM( std::get<0>( leftAndRight ) );
        sw_owner->setOutputRightPWM( std::get<1>( leftAndRight ) );
    }
}

/***************************************
 * SimpleWaypoint Final Approach State *
 ***************************************/
void SimpleWaypointFinalApproach::onEnter( std::string prev_state )
{
    if( sw_owner && sw_owner->secondary_driving_params.current_x && sw_owner->secondary_driving_params.current_y )
    {
        sw_owner->secondary_driving_params.goal_x = *sw_owner->secondary_driving_params.current_x;
        sw_owner->secondary_driving_params.goal_y = *sw_owner->secondary_driving_params.current_y;
    }
}

void SimpleWaypointFinalApproach::action()
{
    sw_owner->setOutputLeftPWM( sw_owner->approach_vel );
    sw_owner->setOutputRightPWM( sw_owner->approach_vel );
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


