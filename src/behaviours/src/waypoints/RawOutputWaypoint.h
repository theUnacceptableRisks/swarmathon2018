#ifndef rawoutputwaypoint_h
#define rawoutputwaypoint_h

#include "Waypoint.h"

typedef struct rawoutputparams
{
    int left_output = 0;
    int right_output = 0;
    double duration = 0.;
} RawOutputParams;

class RawOutputWaypoint : public Waypoint
{
    public:
        RawOutputWaypoint( LogicInputs *i, RawOutputParams rop ) : Waypoint( i ), r_params(rop), start_time(i->time.toSec()) {}
        virtual void run();
    private:
        RawOutputParams r_params;
        double start_time;
};

#endif
