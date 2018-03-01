#ifndef findhome_h
#define findhome_h

typedef enum
{
    FINDHOME_INIT,
    FINDHOME_GOHOME,
    FINDHOME_LOST,
    FINDHOME_COMPLETE,
    FINDHOME_RESET
} FHState;

class FindHomeState : public State
{
    public:
        FindHomeState( IOTable *io ) : State( "findhome_state" ), internal_state(FINDHOME_INIT) {}
        virtual void action( void );
        virtual void onEnter();
        virtual void onExit();
        virtual std::string transition();

    private:
        FHState internalTransition();
        void internalAction();
        void forceTransition( FHState transition_to );

        std::vector<Waypoint *> waypoints;
        LogicInputs *inputs;
        LogicOutputs *outputs;
        FHState internal_state;
};

#endif
