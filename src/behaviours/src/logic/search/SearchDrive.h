#ifndef searchdrive_h
#define searchdrive_h

class SearchDrive : public SearchStateBase
{
    public:
        SearchDrive() : SearchStateBase( "search_drive" ) {}
        virtual void action()
        {
            SearchMachine *ssm = std::dynamic_cast<SearchMachine *> (owner);
            if( ssm && ssm->waypoints.size() > 0 )
            {
                Waypoint *waypoint = ssm->waypoints.front();
                if( waypoint )
                {
                    if( waypoint->hasArrived() )
                        ssm->nextWaypoint();
                }
                else
                   std::cout << "waypoint is null... shouldn't be" << std::endl;
            }
        }
};

#endif
