#ifndef searchinit_h
#define searchinit_h

#include "SearchMachine.h"
#include "../../state_machine/State.h"
#include "../../waypoints/Waypoint.h"
#include "../../waypoints/SimpleWaypoint.h"
#include "../../waypoints/WaypointUtilities.h"


#include <math.h> 

#define PI 3.14159265

extern int roverID;
extern int numberOfRovers;

class SearchInit : public State
{
    public:
        SearchInit() : State( "search_init" ), setup_complete(false) {}
        virtual void action()
        {
            SearchMachine *ssm = dynamic_cast<SearchMachine *> (owner);
            if( ssm )
            {
                SimpleWaypoint *waypoint = 0;
                SimpleParams params;
                double x = 0;
                double y = 0;

                params.skid_steer_threshold = 0.15;
                for(int i = 1; i < 15; i ++){
                    params.goal_x = cos( ((((2*PI)/numberOfRovers)*roverID ) * ((i%4)/2)  ) + ((((2*PI)/numberOfRovers)*(roverID+1) ) * (int)( (i+2)%4/2)) ) * (int) ((i+1)/2);
                    params.goal_y = sin( ((((2*PI)/numberOfRovers)*roverID ) * ((i%4)/2)  ) + ((((2*PI)/numberOfRovers)*(roverID+1) ) * (int)( (i+2)%4/2)) ) * (int) ((i+1)/2);
                    cout << "x: " << params.goal_x << " | y: " << params.goal_y << endl;
                    waypoint = new SimpleWaypoint( ssm->inputs, params );
                    ssm->waypoints.push_back( (Waypoint *)waypoint );
                }

                setup_complete = true;
            }
        }
        virtual std::string transition()
        {
            std::string transition_to = getIdentifier();

            if( setup_complete )
                transition_to = "search_drive";

            return transition_to;
        }
    private:
        bool setup_complete;
};

#endif
