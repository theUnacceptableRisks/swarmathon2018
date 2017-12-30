#include "SimpleWaypoint.h"
#include "SimpleWaypointStates.h"

SimpleWaypoint::SimpleWaypoint( struct SimpleWaypointParams params ) : goal_x(params.x), goal_y(params.y)
{
    //inputs
    addInput( "current_location", params.current_position );
    //outputs
    addOutput( "linear_velocity", new IOFloat( &linear_velocity ) );
    addOutput( "angular_velocity", new IOFloat( &angular_velocity ) );
    //states
    addState( "simple_init", new SimpleWaypointInit() );
}
