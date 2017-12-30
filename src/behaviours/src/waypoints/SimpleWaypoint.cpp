#include "SimpleWaypoint.h"
#include "SimpleWaypointStates.h"

SimpleWaypoint::SimpleWaypoint( struct SimpleWaypointParams params ) : goal_x(params.x), goal_y(params.y)
{
    addInput( "current_location", params.current_position );
    addState( "simple_init", new SimpleWaypointInit() );
    addOutput( "linear_velocity", Output
}
