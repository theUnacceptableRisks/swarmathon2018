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


/**********************************************
 * General Transition Function For All States *
 **********************************************
 | This determines the state to transition to |
 | as well as updates the driving_params      |
 \********************************************/

std::string SimpleWaypointState::transition()
{
    std::string transition_to = getIdentifier();
    InputLocation *current_location = (InputLocation *)sw_owner->inputs.getIO( "current_location" );

    if( is_io_valid( current_location, iolocation_validator ) )
    {
        sw_owner->driving_params.current_x = current_location->getX();
        sw_owner->driving_params.current_y = current_location->getY();
        sw_owner->driving_params.current_theta = current_location->getTheta();

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
        messaging::errorMsg( __func__, "Invalid current location input" );
    }
}



/*******************************
 * SimpleWaypoint Rotate State *
 *******************************/

void SimpleWaypointRotate::action()
{
    
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


