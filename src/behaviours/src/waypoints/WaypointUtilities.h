#ifndef waypointutility_h
#define waypointutility_h

#include <math.h>
#include <angles/angles.h>

namespace WaypointUtilities
{
    typedef struct standard_driving_params
    {
        float goal_x;
        float goal_y;
        float current_x;
        float current_y;
        float current_theta;
    } DrivingParams;

    float getDistance( DrivingParams params );
    float getAngularCorrectionNeeded( DrivingParams params );

};

#endif
