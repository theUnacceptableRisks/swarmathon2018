#ifndef simplewaypoint_h
#define simplewaypoint_h

#include <tuple>
#include "../state_machine/StateMachine.h"
#include "../SimpleWaypointStates.h"
#include "../PID.h"

//SimpleWaypointStates seperate .cpp/.h

struct SimpleWaypointParams
{
    InputLocation *current_position;
    float x;
    float y;
}

class SimpleWaypoint : public StateMachine
{
    public:
        SimpleWaypoint( struct SimpleWaypointParams ) : goal_x(SimpleWaypointParams.x), goal_y(SimpleWaypointParams.y)
        {
            addInput( "current_position", SimpleWaypointParams.current_position );
            //add states
            addState( "simple_init", new SimpleWaypointInit() );
        }

    private:
        float goal_x;
        float goal_y;
};

//constructor builds adds states, initialized with inputs
//getVelocities function?

#endif
