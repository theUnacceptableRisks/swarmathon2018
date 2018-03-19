#ifndef linvelpid_h
#define linvelpid_h

#include "PID.h"

class LinVelPID : public PID
{
    public:
        LinVelPID() : PID() {}
        LinVelPID( PidParams P ) : PID( P ) {}
        virtual std::tuple<int,int> execute( PidInputs inputs );
};

#endif
