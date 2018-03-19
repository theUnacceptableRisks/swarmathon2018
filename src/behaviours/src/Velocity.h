#include "math.h"

#define MIN_VEL 0.1

typedef struct vel_params
{
    double error_current;
    double error_goal;
    double deccel_point;
    double max_velocity = 0.35;
} VelParams;

double generateVelocity( VelParams params );
