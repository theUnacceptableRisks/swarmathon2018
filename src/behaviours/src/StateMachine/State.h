#ifndef state_h
#define state_h

/*************************************************************************
 * This is the base State that all states should inherit from to be used *
 * inside of the D State Machine library implementation.                 *
 *                                                                       *
 * Written by Daniel R. Koris                                            *
 *************************************************************************/

class State
{
    public:
        State( std::string si = "abstract" ) : state_identifier(si) {}
        //virtual functions
        virtual void 		action( void ) {}
        virtual std::string 	transition( void ) { return state_identifier; }	//it will always transition to itself by default
        virtual void 		onEnter( std::string prev_state ) {}
        virtual void 		onExit( std::string next_state ) {}
        virtual std::string 	debugString() { return ""; }
        virtual std::string	getIdentifier() { return state_identifier; }
    private:
        std::string state_identifier;

};

#endif
