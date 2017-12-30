#include "SimpleWaypoint.h"
#include "SimpleWaypointStates.h"

SimpleWaypoint::SimpleWaypoint( struct SimpleWaypointParams params ) : goal_x(params.x), goal_y(params.y)
{
    //inputs
    inputs.addElement( "current_location", params.current_position );
    //outputs
    outputs.addElement( "linear_velocity", new IOFloat( &linear_velocity ) );
    outputs.addElement( "angular_velocity", new IOFloat( &angular_velocity ) );
    //states
    addState( "simple_init", new SimpleWaypointInit() );
}
