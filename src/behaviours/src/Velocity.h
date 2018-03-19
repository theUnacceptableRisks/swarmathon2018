#include "math.h"

typedef struct vel_params
{
    double error_measured;
    double error_goal;
    double deccel_point;
    double max_velocity = 0.35;
    double min_velocity = 0.1;
} VelParams;

double generateVelocity( VelParams params );
