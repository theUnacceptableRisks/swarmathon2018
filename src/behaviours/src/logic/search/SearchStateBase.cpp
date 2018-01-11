#include "SearchStateBase.h"

bool SearchStateBase::setOwner( StateMachine *sm )
{
    bool success = false;

    if( !owner && !ssm_owner )
    {
        owner = sm;
        ssm_owner = (SearchMachine *)sm;
        success = true;
    }
}
