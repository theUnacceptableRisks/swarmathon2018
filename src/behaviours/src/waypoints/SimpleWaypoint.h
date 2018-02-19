#ifndef simplewaypoint_h
#define simplewaypoint_h

#include "Waypoint.h"
#include "../PID.h"

//SimpleWaypointStates seperate .cpp/.h

typedef enum
{
    SIMPLE_INIT,
    SIMPLE_ROTATE,
    SIMPLE_SKID,
    SIMPLE_FINAL_APPROACH,
    SIMPLE_ARRIVED
} SWState;

typedef struct simple_params
{
    double skid_steer_threshold = 0.4;
    double final_approach_threshold = 0.2;
    double max_vel = 40;
    double goal_x = 0;
    double goal_y = 0;
} SimpleParams;


class SimpleWaypoint : public Waypoint
{
    public:
        SimpleWaypoint( LogicInputs *i, SimpleParams sp ) : Waypoint( i ), simple_params(sp), internal_state(SIMPLE_INIT) {}
        virtual void run();
    private:
        SWState internalTransition();
        void internalAction();
        void forceTransition( SWState transition_to );

        SimpleParams simple_params;
        SWState internal_state;



 };

#endif
