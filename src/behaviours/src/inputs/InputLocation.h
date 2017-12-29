#include "../state_machine/IOType.h"
#include <geometry_msgs/Pose2D.h>

class InputLocation : public IOType
{
    public:
        InputLocation( geometry_msgs::Pose2D *loc ) : IOType( IO_LOCATION, LOC_SUM, sizeof( InputLocation ) ),
            location(loc) {}
        double getX()		{ return location->x; }
        double getY()		{ return location->y; }
        double getTheta()	{ return location->theta; }

    private:
        geometry_msgs::Pose2D *location;
};

VALIDATOR iolocation_validator = { IO_LOCATION, sizeof( InputLocation ), LOC_SUM };
