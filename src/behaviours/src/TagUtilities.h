#ifndef tagutilities_h
#define tagutilities_h

#include "Tag.h"
#include "PID.h"

namespace TagUtilities
{
    bool hasTag( std::vector<Tag> *tags, int id );
    float getDistance( Tag tag );

    //pids specific to tag info
    
};

#endif
