#ifndef returninit_h
#define returninit_h

#include "ReturnMachine.h"
#include "../../state_machine/State.h"
#include "../../waypoints/Waypoint.h"
#include "../../waypoints/SimpleWaypoint.h"
#include "../../waypoints/WaypointUtilities.h"


#include <math.h> 

#define PI 3.14159265

extern int roverID;
extern int numberOfRovers;

class ReturnInit : public State
{
    public:
        ReturnInit() : State( "return_init" ), setup_complete(false) {}
        virtual void action()
        {
            ReturnMachine *ssm = dynamic_cast<ReturnMachine *> (owner);
            if( ssm )
            {
                SimpleWaypoint *waypoint = 0;
                SimpleParams params;
                double x = 0;
                double y = 0;

                params.skid_steer_threshold = 0.15;
                
                    params.goal_x = 0;
                    params.goal_y = 0;
                    cout << "x: " << params.goal_x << " | y: " << params.goal_y << endl;
                    waypoint = new SimpleWaypoint( ssm->inputs, params );
                    ssm->waypoints.push_back( (Waypoint *)waypoint );
                

                setup_complete = true;
            }
        }
        virtual std::string transition()
        {
            std::string transition_to = getIdentifier();

            if( setup_complete )
                transition_to = "return_drive";

            return transition_to;
        }
    private:
        bool setup_complete;
};

#endif
