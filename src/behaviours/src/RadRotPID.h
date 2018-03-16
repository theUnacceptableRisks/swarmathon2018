#ifndef ratrotpid_h
#define ratrotpid_h

#include "PID.h"
#include <angles/angles.h>

class RadRotPID : public PID
{
    public:
        RadRotPID() : PID() {}
        RadRotPID( PidParams P ) : PID( P ) {}
        virtual std::tuple<int,int> execute( PidInputs inputs );
};

#endif
