#ifndef extendedglobals_h
#define extendedglobals_h

#include "state_machine/Globals.h"

class ROVER_IOTYPES : IOTYPES
{
    public:
        const int LOCATION = 2;
        const int SONAR = 3;
        const int TAGS = 4;
} ROVER_IO;

class ROVER_SUMS : SUMS
{
    public:
        const char LOC = 'l';
        const char SON = 's';
        const char TAG = 't';
} ROVER_SUM;

#endif
