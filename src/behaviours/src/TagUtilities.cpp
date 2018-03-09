#include "TagUtilities.h"

double TagUtilities::getDistance( Tag tag )
{
    return hypot( hypot( tag.getPositionX(), tag.getPositionY() ), tag.getPositionZ() );
}

bool TagUtilities::hasTag( std::vector<Tag> *tags, int id )
{
    bool can_see = false;
    if( tags->size() > 0 )
    {
        for( int i = 0; i < tags->size(); i++ )
        {
            if( tags->at(i).getID() == id )
            {
                can_see = true;
                break;
            }
        }
    }
    return can_see;
}

double TagUtilities::angleToTag( Tag tag )
{
    return 0.0;
}

int TagUtilities::numberOfTags( std::vector<Tag> *tags, int id )
{
    int tagCount = 0;
    if( tags->size() > 0 )
    {
        for( int i = 0; i < tags->size(); i++ )
        {
            if( tags->at(i).getID() == id )
            {
                tagCount ++;
            }
        }
    }
    return tagCount;
}

Tag TagUtilities::getClosestTag( std::vector<Tag> *tags, int id )
{
    Tag closest_tag = tags->at(0);
    double closest_dist = TagUtilities::getDistance( closest_tag );

    for( int i = 1; i < tags->size(); i++ )
    {
        double new_dist = TagUtilities::getDistance( tags->at(i) );
        if( new_dist < closest_dist )
        {
            closest_dist = new_dist;
            closest_tag = tags->at(i);
        }
    }
    return closest_tag;
}

