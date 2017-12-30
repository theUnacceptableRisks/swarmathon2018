#ifndef inputlocation_h
#define inputlocation_h

#include "../state_machine/IOType.h"
#include <geometry_msgs/Pose2D.h>
#include "../ExtendedGlobals.h"

class InputLocation : public IOType
{
    public:
        InputLocation( geometry_msgs::Pose2D *loc ) : IOType( IOTYPE_LOC, SUM_LOC, sizeof( InputLocation ) ),
            location(loc) {}
        double getX()		{ return location->x; }
        double getY()		{ return location->y; }
        double getTheta()	{ return location->theta; }

    private:
        geometry_msgs::Pose2D *location;
};

extern VALIDATOR iolocation_validator;

#endif
