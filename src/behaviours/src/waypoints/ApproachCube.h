#ifndef approachcube_h
#define approachcube_h

#include "../TagUtilities.h"
#include "../logic/LogicTypes.h"
#include "Waypoint.h"
#include "WaypointUtilities.h"
#include "../LinearPID.h"
#include "../LinRotPID.h"
#include "../Cube.h"

typedef struct approach_cube_params
{
    double dist_goal = 0.15;
    double dist_max_output = 60;

    double yaw_goal = -0.023;
    double yaw_max_output = 60;

    double skid_rotate_threshold = 0.05;
} CubeParams;

class ApproachCube : public Waypoint
{
    public:
        ApproachCube( LogicInputs *i, CubeParams cp ) : Waypoint( i ), c_params(cp) {}
        virtual void run();
    private:
        CubeParams c_params;
};

#endif
