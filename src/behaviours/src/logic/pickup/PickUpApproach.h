#ifndef pickupapproach_h
#define pickupapproach_h

#include "PickUpMachine.h"
#include "../../state_machine/State.h"
#include "../../waypoints/ApproachTagWaypoint.h"

class PickUpApproach : public State
{
    public:
        PickUpApproach() : State( "pickup_approach" ) {}
        virtual void onEnter( std::string next_state )
        {
            PickUpMachine *pum = dynamic_cast<PickUpMachine*> ( owner );
            if( pum )
            {
                ApproachTagWaypoint *waypoint = new ApproachTagWaypoint( pum->inputs );
                pum->clearWaypoints();
                pum->waypoints.push_back( dynamic_cast<Waypoint*>( waypoint)  );
            }

        }
        virtual void onExit( std::string next_state )
        {
            PickUpMachine *pum = dynamic_cast<PickUpMachine*> ( owner );
            if( pum )
            {
                pum->clearWaypoints();
            }
        }
        //action will test for major distance shifts
        //transition will transition to another state
};


#endif
