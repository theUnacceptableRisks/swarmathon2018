#include "SimpleWaypointStates.h"
#include "WaypointUtility.h"
#include "Error.h"

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



std::string SimpleWaypointInit::transition()
{
    std::string transition_to = getIdentifier();
    DrivingParams params;
    InputLocation *current_location = sw_owner.inputs[ "current_location" ];

    if( is_io_valid( current_location, iolocation_validator ) )
    {
        params.goal_x = sw_owner.goal_x;
        params.goal_y = sw_owner.goal_y;
        params.current_x = InputLocation->getX();
        params.current_y = InputLocation->getY();
        params.current_theta = InputLocation->getTheta();
    }
    else
    {
        messaging::errorMsg( __func__, "Invalid current location input" );
    }
}



/********************
 * Blank Init State *
 ********************/
