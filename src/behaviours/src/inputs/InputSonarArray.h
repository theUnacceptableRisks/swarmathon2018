#ifndef inputsonararray
#define inputsonararray

#include "../state_machine/IOType.h"

class InputSonarArray : public IOType
{
    public:
        InputSonarArray( double *us_left, double *us_right, double *us_center ) :
            IOType( ROVER_IO.SONAR, ROVER_SUM.SON, sizeof( InputSonarArray ) ), sonar_left(us_left),
            sonar_right(us_right), sonar_center(us_center) {}
        double getLeft()	{ return *sonar_left; }
        double getRight()	{ return *sonar_right; }
        double getCenter()	{ return *sonar_center; }
    private:
        double *sonar_left;
        double *sonar_right;
        double *sonar_center;
};

VALIDATOR iosonar_validator = { ROVER_IO.SONAR, sizeof( InputSonarArray ), ROVER_SUM.SON };

#endif
