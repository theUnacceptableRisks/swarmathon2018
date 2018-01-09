#include "LogicState.h"

bool LogicState::setOwner( StateMachine *sm )
{
    bool success = false;

    if( !owner && !lm_owner )
    {
        owner = sm;
        lm_owner = (LogicMachine *)sm;
        success = true;
    }
    return success;
}

