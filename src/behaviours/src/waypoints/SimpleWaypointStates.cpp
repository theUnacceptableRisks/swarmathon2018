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

    if( sw_owner->updateDrivingParams() )
    {
        if( WaypointUtilities::getDistance( sw_owner->driving_params ) < .1 ) //todo setup distance tolerance handling
        {
            transition_to = "simple_arrived";
        }
        else
        {
            float angularCorrection = WaypointUtilities::getAngularCorrectionNeeded( sw_owner->driving_params );
            if( fabs( angularCorrection ) > .2 ) //todo setup angular tolerance handling
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
}



/*******************************
 * SimpleWaypoint Rotate State *
 *******************************/

void SimpleWaypointRotate::action()
{
    WaypointUtilities::PidParams params;
    if( sw_owner->updateDrivingParams() )
    {
        params.type = WaypointUtilities::FAST_PID;
        params.velocity_error = 0.0;
        params.velocity_goal = 0.0;
        params.angular_error = WaypointUtilities::getAngularCorrectionNeeded( sw_owner->driving_params );
//        params.angular
        
    }
}

/*******************************
 * SimpleWaypoint Skid State *
 *******************************/

void SimpleWaypointSkid::action()
{

}

/*******************************
 * SimpleWaypoint Arrived State *
 *******************************/

void SimpleWaypointArrived::action()
{

}


