#include "SimpleWaypointStates.h"

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

}



/********************
 * Blank Init State *
 ********************/
