#ifndef gripper_h
#define gripper_h

#include <math.h>
#include <tuple>
#include "state_machine/Error.h"

namespace Gripper
{
    typedef enum
    {
        UP_OPEN, UP_CLOSED,
        DOWN_OPEN, DOWN_CLOSED,
        HOVER_OPEN, HOVER_CLOSED
    } Position;

    std::tuple<double,double> getWristFingerValuesForPosition( Position pos );
}
#endif
