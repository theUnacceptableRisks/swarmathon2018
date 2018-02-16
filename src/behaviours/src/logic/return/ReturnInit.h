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
        double k = .1;
        double compX = 0;
        double compY = 0;
   

        ReturnInit(IOTable *io) : State( "return_init" ), setup_complete(false) {}
        virtual void action()
        {
            ReturnMachine *ssm = dynamic_cast<ReturnMachine *> (owner);
            if( ssm )
            {
                compX = ssm->inputs->odom_accel_gps.x;
                compY = ssm->inputs->odom_accel_gps.y;
                SimpleWaypoint *waypoint = 0;
                SimpleParams params;
                //WaypointUtilities::DrivingParams location;
                
                //double distanceFromHome = hypot(*location.current_x, *location.current_y);
                //double unitX = *location.current_x / distanceFromHome;
                //double unitY = *location.current_y / distanceFromHome;

               double distanceFromHome = hypot(compX, compY);
                compX/=distanceFromHome;
                compY/=distanceFromHome;     
                
                params.skid_steer_threshold = 0.15;
                double dot = 0;
                double x = 0, y = 0;
                for (double i = 0; i < 30; i+=0.5){
                    x = i * cos(i);
                    y = i * sin(i);

                    dot = -1*(x*compX + y*compY)/(hypot(x-compX,y-compY));
                    dot += 1.3;
                    dot /= 2;
                   
                    params.goal_x = x * dot * k;
                    params.goal_y = y * dot * k;


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
                transition_to = "return_drive";

            return transition_to;
        }
    private:
        bool setup_complete;
};

#endif
