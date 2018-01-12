#ifndef searchdrive_h
#define searchdrive_h

class SearchDrive : public SearchStateBase
{
    public:
        SearchDrive() : SearchStateBase( "search_drive" ) {}
        virtual void action()
        {
           if( ssm_owner && ssm_owner->waypoints.size() > 0 )
           {
               Waypoint *waypoint = ssm_owner->waypoints.front();
               if( waypoint )
               {
                   if( waypoint->hasArrived() )
                       ssm_owner->nextWaypoint();
               }
               else
                   std::cout << "waypoint is null... shouldn't be" << std::endl;
           }
        }
};

#endif
