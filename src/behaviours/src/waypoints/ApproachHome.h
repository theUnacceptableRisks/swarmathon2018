#ifndef approachhome_h
#define approachhome_h

#include "../TagUtilities.h"
#include "../logic/LogicTypes.h"
#include "Waypoint.h"
#include "WaypointUtilities.h"
#include "../LinearPID.h"
#include "../LinRotPID.h"
#include "../Cube.h"

#define CAMERA_OFFSET -0.023

typedef struct approach_home_params
{
    double dist_goal = 0.25;
    double dist_max_output = 30;

    double yaw_goal = -0.023;
    double yaw_max_output = 80;
} HomeParams;



class ApproachHome : public Waypoint
{
    public:
        ApproachHome( LogicInputs *i, HomeParams hp ) : Waypoint( i ), h_params(hp)
        {
            linear_pid = LinearPID( WaypointUtilities::getDistSkidBasedParams() );
            linear_rot_pid = LinRotPID( WaypointUtilities::getLinearRotSkidBasedPIDParams() );
        }
        virtual void run();
    private:
        HomeParams h_params;
        LinearPID linear_pid;
        LinRotPID linear_rot_pid;
};

#endif
