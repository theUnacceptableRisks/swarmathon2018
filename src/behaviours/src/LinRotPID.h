#ifndef linrotpid_h
#define linrotpid_h

#include "PID.h"

class LinRotPID : public PID
{
    public:
        LinRotPID() : PID() {}
        LinRotPID( PidParams P ) : PID( P ) {}
        virtual std::tuple<int,int> execute( PidInputs inputs );
};

#endif
