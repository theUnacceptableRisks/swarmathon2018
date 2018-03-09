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

Tag TagUtilities::getClosestTagSane( std::vector<Tag> *tags, int id, double tolerance )
{
    Tag selected_tag = TagUtilities::getClosestTag( tags, id );
    double distance = TagUtilities::getDistance( selected_tag );

    if( tags->size() > 1 )
    {
        std::vector<Tag> selection_of_tags;
        for( int i = 0; i < tags->size(); i++ )
        {
            Tag current_tag = tags->at(i);
            double current_distance = TagUtilities::getDistance( current_tag );

            if( current_distance - distance < tolerance )
                selection_of_tags.push_back( current_tag );
        }
        if( selection_of_tags.size() > 1 )
        {
            Tag curr_selection = selection_of_tags.at(0);
            double curr_x = fabs( curr_selection.getPositionX() );

            for( int i = 1; i < selection_of_tags.size(); i++ )
            {
                Tag new_tag = selection_of_tags.at(i);
                double new_x = new_tag.getPositionX();
                if( new_x <= curr_x )
                {
                    curr_x = new_x;
                    curr_selection = new_tag;
                }
            }
            selected_tag = curr_selection;
        }
    }
    return selected_tag;
}
