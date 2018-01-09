#ifndef searchstate_h
#define searchstate_h

#include "../state_machine/State.h"
#include "LogicMachine.h"

class SearchState : public LogicState
{
   public:
       SearchState() : State ( "search_state" ), ss_owner(0) {}
       virtual bool setOwner( StateMachine *sm );
       virtual void action( void );
//       virtual std::string transition( void );
   private:
       SearchMachine search_machine;

};

#endif
