#ifndef searchstate_h
#define searchstate_h

#include "../state_machine/State.h"
#include "LogicMachine.h"
#include "LogicState.h"
#include "search/SearchMachine.h"

class SearchState : public State
{
    public:
        SearchState( IOTable *io );
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual std::string transition( void );
    private:
        SearchMachine search_machine;
};

#endif
