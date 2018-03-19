#ifndef approachcube_h
#define approachcube_h

#include "../TagUtilities.h"
#include "../logic/LogicTypes.h"
#include "Waypoint.h"
#include "WaypointUtilities.h"
#include "../LinearPID.h"
#include "../LinRotPID.h"
#include "../Cube.h"

#define OPTIMAL_LOCK_DISTANCE 0.35
#define CAMERA_OFFSET -0.023

typedef struct approach_cube_params
{
    double dist_goal = 0.15;
    double dist_max_output = 30;

    double yaw_goal = -0.023;
    double yaw_max_output = 80;

    double skid_rotate_threshold = 0.05;
} CubeParams;

class ApproachCube : public Waypoint
{
    public:
        ApproachCube( LogicInputs *i, CubeParams cp ) : Waypoint( i ), c_params(cp)
        {
            linear_pid = LinearPID( WaypointUtilities::getDistSkidBasedPIDParams() );
            linear_rot_pid = LinRotPID( WaypointUtilities::getLinearRotSkidBasedPIDParams() );

            PidParams params;

            params.Kp = 0.;
            params.Ki = 20.;
            params.Kd = 0.;
            params.integration_point = 0;
            final_rot_pid = LinRotPID( params );
        }
        virtual void run();
    private:
        CubeParams c_params;
        LinearPID linear_pid;
        LinRotPID linear_rot_pid;
        LinRotPID final_rot_pid;
};

#endif
