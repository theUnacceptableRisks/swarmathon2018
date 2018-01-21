#ifndef gripper_h
#define gripper_h

#include <math.h>
#include <tuple>
#include "state_machine/Error.h"

namespace Gripper
{
    typedef enum
    {
        GRIPPER_UP_OPEN, GRIPPER_UP_CLOSED,
        GRIPPER_DOWN_OPEN, GRIPPER_DOWN_CLOSED,
        GRIPPER_HOVER_OPEN, GRIPPER_HOVER_CLOSED
    } Position;

    std::tuple<double,double> getWristFingerValuesForPosition( gripper_position pos );
}
#endif
