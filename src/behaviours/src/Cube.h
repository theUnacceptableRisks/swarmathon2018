#ifndef cube_h
#define cube_h

#include "Tag.h"
#include <cmath>
#include <vector>

#define CUBE_TOLERANCE 0.048

class Cube
{
    public:
        Cube( Tag init_tag );
        bool checkTag( Tag tag );
        double getPositionX();
        double getPositionY();
        double getPositionZ();
        double getDistance();
        double getGroundDistance();
    private:
        std::vector<Tag> tags;

};

#endif
