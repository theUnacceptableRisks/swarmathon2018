#ifndef simplewaypoint_h
#define simplewaypoint_h

#include "../state_machine/StateMachine.h"
#include "../inputs/InputLocation.h"

//SimpleWaypointStates seperate .cpp/.h

struct SimpleWaypointParams
{
    InputLocation *current_position;
    float x;
    float y;
};

class SimpleWaypoint : public StateMachine
{
    friend class SimpleWaypointState;
    public:
        SimpleWaypoint( struct SimpleWaypointParams params );
    private:
        const float goal_x;
        const float goal_y;
        float linear_velocity;
        float angular_velocity;
};

//constructor builds adds states, initialized with inputs
//getVelocities function?

#endif
