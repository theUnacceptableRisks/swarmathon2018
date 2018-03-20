#ifndef tagutilities_h
#define tagutilities_h

#include "Tag.h"
#include "Cube.h"
#include "PID.h"

namespace TagUtilities
{
    bool hasTag( std::vector<Tag> *tags, int id );
    double getDistance( Tag tag );
    double angleToTag( Tag tag );
    int numberOfTags(std::vector<Tag> *tags, int id);
    Tag getClosestTag( std::vector<Tag> *tags, int id );
    Tag getClosestTagSane( std::vector<Tag> *tags, int id, double tolerance );
    bool hasTagInRange( std::vector<Tag> *tags, int id, double min, double max);
    Cube getClosestCube( std::vector<Cube> *cubes );
    Cube getSecondClosestCube( std::vector<Cube> *cubes );
};

#endif
