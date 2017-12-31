 #include "SimpleWaypoint.h"
#include "SimpleWaypointStates.h"

SimpleWaypoint::SimpleWaypoint( struct SimpleWaypointParams params ) : Waypoint(), goal_x(params.x), goal_y(params.y)
{
    //inputs
    inputs.addElement( "current_location", params.current_position );
    inputs.addElement( "current_linear_vel", params.linear_vel );
    inputs.addElement( "current_angular_vel", params.angular_vel );
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

bool SimpleWaypoint::updateDrivingParams()
{
    InputLocation *current_location = (InputLocation *)inputs.getIO( "current_location" );
    IOFloat *linear_vel = (IOFloat *)inputs.getIO( "current_linear_vel" );
    IOFloat *angular_vel = (IOFloat *)inputs.getIO( "current_angular_vel" );
    bool success = false;

    //need to test IOTypes for validity before using
    if( is_io_valid( current_location, iolocation_validator ) &&
        is_io_valid( linear_vel, ioflt_validator ) &&
        is_io_valid( angular_vel, ioflt_validator ) )
    {
        driving_params.current_x = current_location->getX();
        driving_params.current_y = current_location->getY();
        driving_params.current_theta = current_location->getTheta();
        driving_params.current_linear_vel = linear_vel->getValue();
        driving_params.current_angular_vel = angular_vel->getValue();
        success = true;
    }

    return success;
}
