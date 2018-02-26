#include "TagExaminer.h"
#include <stdlib.h>     /* absolute value */

using namespace std;

TagExaminer::TagExaminer()
{
	/*
	Make a detection function to say if 
	home base tags are aligned/straight
	*/
}

TagExaminer::~TagExaminer()
{
    //TODO: I'm sure something could go here.
}

void TagExaminer::loadTags(vector<Tag> fromTagHandler)
{
    tags = fromTagHandler;
    determineRange();
	//graph();
	//determineTurning();
}
/*
 * Determines at what ranges the TagExaminer should scan for tags
 * These are vertical "columns" of tags
 * That will be sorted from closest to furthest
 */
void TagExaminer::determineRange()
{
	//TODO: Resize these and eventually have a loop instead of 50 if statements.
	columns.resize(9);  // resize top level vector

    for (int i = 0; i < tags.size(); i++) {
        double x = tags[i].getPositionX();

        if (x <= -0.209 && x >= -.269) {
            columns[0].push_back(tags[i]);
        }
        else if (x <= -.148 && x >= -.208) {
            columns[1].push_back(tags[i]);
        }
        else if (x <= -0.087 && x >= -0.147) {
            columns[2].push_back(tags[i]);
        }
        else if (x <= -0.026 && x >= -0.086) {
            columns[3].push_back(tags[i]);
        }
        else if (x >= -.025 && x <= 0.025) {
            columns[4].push_back(tags[i]);
        }
        else if (x >= 0.026 && x <= 0.086) {
            columns[5].push_back(tags[i]);
        }
        else if (x >= 0.087 && x <= 0.147) {
            columns[6].push_back(tags[i]);
        }
        else if (x >= 0.148 && x <= 0.208) {
            columns[7].push_back(tags[i]);
        }
        else if (x >= 0.209 && x <= .269) {
            columns[8].push_back(tags[i]);
        }
    }

	for (int i = 0; i < 9; i++) {
		sortColumn(columns[i]);
	}
}
/*
 * Sort the vertical columns from closest to furthest
 */
void TagExaminer::sortColumn(vector<Tag> &arr)
{
	unsigned long n = arr.size();

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			double x = arr[j].getPositionX(), y = arr[j].getPositionY(), z = arr[j].getPositionZ();
			double x2 = arr[j + 1].getPositionX(), y2 = arr[j + 1].getPositionY(), z2 = arr[j + 1].getPositionZ();

			double distance1 = sqrt(x*x + y*y + z*z);
			double distance2 = sqrt(x2*x2 + y2*y2 + z2*z2);

			if (distance1 > distance2)
			{
                swap( arr[j], arr[j+1] );
			}
		}
	}
}
/*
 * Once the TagExaminer is needed, run this function to
 * determine which direction is needed for the rover to
 * turn.
 * This will take the middle [4] column, and then
 * analyze the immediate left [3] and right [5] column
 * to determine if the rover should turn left or right.
 */
TagExaminer::Turns TagExaminer::determineTurning()
{
    //First determine if these columns have something in them.
	//If the rover sees only a tag in column 3, and not 5, then it should
    //Go in that direction.

    if(columns[3].size() > 0 && columns[5].size() == 0) {
        cout << "LEFT" << endl;
        return LEFT;
    }
    //Then the opposite, if there's a tag at 5 and not 3
   else  if(columns[5].size() > 0 && columns[3].size() == 0) {
        cout << "RIGHT" << endl;
        return RIGHT;
    }
    // If both have tags,
    else if(columns[3].size() > 0 && columns[5].size() > 0) {
        Tag left = columns[3][0], right = columns[5][0];
        //Distances from the rover to the closest rover in that column

        double ldist = sqrt(pow(left.getPositionX(),2) + pow(left.getPositionY(),2) + pow(left.getPositionZ(),2));
        double rdist = sqrt(pow(right.getPositionX(),2) + pow(right.getPositionY(),2) + pow(right.getPositionZ(),2));

        if((ldist - rdist) > (-1 * margin) && (ldist - rdist) < (margin)) {
            cout << "STRAIGHT: ";
            cout << ldist - rdist << endl;
            return STRAIGHT;
        }
        else if(ldist > rdist) {
            cout << "RIGHT" << endl;
            return RIGHT;
        }
        else {
            cout << "LEFT" << endl;
            return LEFT;
        }

    }
    else {
        cout << "Other: ";
        //A tag not in 3//5 has been found.
        //Let's turn towards that tag.

        //Find the column that has the tag
        int tagCol;
        for(int i = 0; i < columns.size(); i ++) {
            if(columns[i].size() > 0) {
                tagCol = i;
                break;
            }
        }

        //Now that we have that,
        if(tagCol == 4 || tagCol == 3 || tagCol == 5) {
            //it's near the middle
            cout << "STRAIGHT" << endl;
            return STRAIGHT;
        }
        else if(tagCol < 4) {
            cout << "LEFT" << endl;
            return LEFT;
        }
        else{
            cout << "RIGHT" << endl;
            return RIGHT;
        }
    }
}

void TagExaminer::graph()
{
	for (int i = 0; i < columns.size(); i++){
		cout << "Column " << i << ": (" << columns[i].size() << ")" << endl;
		for (int j = 0; j < columns.at(i).size(); j++) {
			cout << "\t>#" << (j + 1) << ": " << columns.at(i)[j].getPositionX() << endl;
		}
	}
}

void TagExaminer::clear(){
	tags.clear();
        for( int i = 0; i < columns.size(); i++ )
            columns[i].clear();
}
