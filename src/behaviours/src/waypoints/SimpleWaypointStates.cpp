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
        float angularCorrection = WaypointUtilities::getAngularCorrectionNeeded( sw_owner->inputs );

        if( WaypointUtilities::getDistance( sw_owner->inputs ) < sw_owner->supplemental_inputs.final_approach_threshold &&
            angularCorrection < sw_owner->supplemental_inputs.skid_steer_threshold ) //todo setup distance tolerance handling
        {
            if( sw_owner->supplemental_inputs.odom_x && sw_owner->supplemental_inputs.odom_y )
                transition_to = "simple_final_approach";
            else
                transition_to = "simple_arrived";
        }
        else if( getIdentifier() == "simple_final_approach" )
        {
            WaypointUtilities::DrivingParams final_params;
            final_params.goal_x = sw_owner->approach_x;
            final_params.goal_y = sw_owner->approach_y;
            final_params.current_x = sw_owner->supplemental_inputs.odom_x;
            final_params.current_y = sw_owner->supplemental_inputs.odom_y;

            if( WaypointUtilities::getDistance( final_params ) <= sw_owner->supplemental_inputs.final_approach_threshold )
                transition_to = "simple_arrived";

        }
        else
        {
            if( fabs( angularCorrection ) > sw_owner->supplemental_inputs.skid_steer_threshold ) //todo setup angular tolerance handling
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
        params.velocity_error = WaypointUtilities::getDistance( sw_owner->inputs );
        params.velocity_goal = .35;
        params.angular_error = WaypointUtilities::getAngularCorrectionNeeded( sw_owner->inputs );
        params.angular_goal = WaypointUtilities::getGoalTheta( sw_owner->inputs );
        params.saturation_point = 180; //180 seems to be standard...?

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
    if( sw_owner && sw_owner->supplemental_inputs.odom_x && sw_owner->supplemental_inputs.odom_y )
    {
        sw_owner->approach_x = *sw_owner->supplemental_inputs.odom_x;
        sw_owner->approach_y = *sw_owner->supplemental_inputs.odom_y;
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


