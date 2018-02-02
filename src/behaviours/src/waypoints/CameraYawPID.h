#ifndef camerayawpid_h
#define camerayawpid_h

#include "Waypoint.h"
#include "WaypointUtilities.h"
#include "../PID.h"

typedef struct camera_yaw_params
{
    double kp;
    double ki;
    double kd;
} CameraYawParams;

class CameraYawPID : public Waypoint
{
    public:
        CameraYawPID( LogicInputs *i, CameraYawParams p );
        virtual void run();
    private:
        CameraYawParams params;
        WaypointUtilities::PidPackage pids;
};

#endif
