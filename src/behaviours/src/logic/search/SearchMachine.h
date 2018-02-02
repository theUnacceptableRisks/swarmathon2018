#ifndef searchmachine_h
#define searchmachine_h

#include "../SubMachine.h"

class SearchMachine : public SubMachine
{
    friend class SearchInit;
    friend class SearchDrive;
    public:
        SearchMachine( IOTable *io );
};

#endif
