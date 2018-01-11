#ifndef searchstate_h
#define searchstate_h

#include "../state_machine/State.h"
#include "LogicMachine.h"
#include "LogicState.h"
#include "search/SearchMachine.h"

class SearchState : public LogicState
{
   public:
       SearchState() : LogicState ( "search_state" ) {}
       virtual bool setOwner( StateMachine *sm );
       virtual void action( void );
//       virtual std::string transition( void );
       virtual std::string debugString() { return "search state running"; }
   private:
       SearchMachine search_machine;

};

#endif
