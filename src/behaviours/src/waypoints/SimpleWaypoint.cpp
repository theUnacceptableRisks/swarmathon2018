 #include "SimpleWaypoint.h"
#include "SimpleWaypointStates.h"

SimpleWaypoint::SimpleWaypoint( struct SimpleWaypointParams params ) : Waypoint(), goal_x(params.x), goal_y(params.y)
{
    //inputs
    inputs.addElement( "current_location", params.current_position );
    inputs.addElement( "current_linear_vel", params.linear_vel );
    inputs.addElement( "current_linear_vel", params.angular_vel );
    //outputs are automatically built into the inherited class
    //states
    addState( "simple_init", new SimpleWaypointInit() );
    addState( "simple_rotate", new SimpleWaypointRotate() );
    addState( "simple_skid", new SimpleWaypointSkid() );
    addState( "simple_arrived", new SimpleWaypointArrived() );
    //misc
    driving_params.goal_x = goal_x;
    driving_params.goal_y = goal_y;
}
