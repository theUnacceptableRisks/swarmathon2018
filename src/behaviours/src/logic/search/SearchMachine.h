#ifndef searchmachine_h
#define searchmachine_h

#include "../LogicMachine.h"

class SearchMachine : public SubMachine
{
    friend class SearchInit;
    friend class SearchDrive;
    public:
        SearchMachine( IOTable *io );
};

#endif
