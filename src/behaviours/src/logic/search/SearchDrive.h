#ifndef searchdrive_h
#define searchdrive_h

class SearchDrive : public SearchStateBase
{
    public:
        SearchDrive() : SearchStateBase( "search_drive" ) {}
        virtual void action()
        {
           if( ssm_owner->waypoints.at(0)->hasArrived() )
              ssm_owner->nextWaypoint();
        }
};

#endif
