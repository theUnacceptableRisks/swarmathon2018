#ifndef returndrive_h
#define returndrive_h

#include "../../state_machine/State.h"
#include "ReturnMachine.h"

class ReturnDrive : public State
{
    public:
        ReturnDrive() : State( "return_drive" ) {}
        virtual void action()
        {
            ReturnMachine *ssm = dynamic_cast<ReturnMachine *> (owner);
            if( ssm && ssm->waypoints.size() > 0 )
            {
                Waypoint *waypoint = ssm->waypoints.front();
                if( waypoint )
                {
                    if( waypoint->hasArrived() )
                        ssm->nextWaypoint();
                }
                else
                   std::cout << "waypoint is null... shouldn't be" << std::endl;
            }
        }
};

#endif
