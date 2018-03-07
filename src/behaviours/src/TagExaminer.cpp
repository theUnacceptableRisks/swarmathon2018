#include "TagExaminer.h"
#include <stdlib.h>     /* absolute value */

using namespace std;

/*
  TagExaminer takes april tags collected via a video input and sorts
  them into "columns" based on their X position (left or right of cam).
  By doing this, you can visually see where tags are located.
  
  To graphically see, call tagexaminerobject.graph();

  TagExaminer also helps line up with tags. If trying to approach
  a series of tags, TagExaminer will tell you which way to rotate
  so that the tags are aligned perpendicularly. 
  
  To determine which way to turn, call tagexaminerobject.determineTurning();
    
*/

TagExaminer::TagExaminer() {}

/*
This will take tags froma  vector and store them into the vector "tags"
*/
void TagExaminer::loadTags(vector<Tag> fromTagHandler) {
    tags = fromTagHandler;
    determineRange();
}

/*
 * Determines at what ranges the TagExaminer should scan for tags
 * These are vertical "columns" of tags
 * That will be sorted from closest to furthest
 */
void TagExaminer::determineRange() {
    //TODO: This will do for now.
    columns.resize(9);  // resize top level vector

    for (int i = 0; i < tags.size(); i++) {
        double x = tags[i].getPositionX();

        if (x <= -0.209 && x >= -.269) {
            columns[0].push_back(tags[i]);
        } else if (x <= -.163 && x >= -.223) {
            columns[1].push_back(tags[i]);
        } else if (x <= -0.092 && x >= -0.162) {
            columns[2].push_back(tags[i]);
        } else if (x <= -0.031 && x >= -0.091) {
            columns[3].push_back(tags[i]);
        } else if (x >= -.03 && x <= 0.03) {
            columns[4].push_back(tags[i]);
        } else if (x >= 0.031 && x <= 0.091) {
            columns[5].push_back(tags[i]);
        } else if (x >= 0.092 && x <= 0.162) {
            columns[6].push_back(tags[i]);
        } else if (x >= 0.163 && x <= 0.223) {
            columns[7].push_back(tags[i]);
        } else if (x >= 0.209 && x <= .269) {
            columns[8].push_back(tags[i]);
        }
    }
    
    //Sort the columns
    for (int i = 0; i < 9; i++) {
        sortColumn(columns[i]);
    }
}

/*
 * Sort the vertical columns from closest to furthest
 */
void TagExaminer::sortColumn(vector<Tag> &arr) {
    unsigned long n = arr.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            double x = arr[j].getPositionX(), y = arr[j].getPositionY(), z = arr[j].getPositionZ();
            double x2 = arr[j + 1].getPositionX(), y2 = arr[j + 1].getPositionY(), z2 = arr[j + 1].getPositionZ();

            double distance1 = sqrt(x * x + y * y + z * z);
            double distance2 = sqrt(x2 * x2 + y2 * y2 + z2 * z2);

            if (distance1 > distance2) {
                swap(arr[j], arr[j + 1]);
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
TagExaminer::Turns TagExaminer::determineTurning() {

    TagExaminer::Turns turn;

    //If there's tags existant in 3, 4, and 5, 
    if (columns[3].size() > 0 && columns[4].size() > 0 && columns[5].size() > 0) {
	cout << "A";
        //if the 3rd and 5th are the same distance away...
        if (isClose(columns[3][0], columns[5][0], margin)) {
            //You're straight on
            cout << "STRAIGHT" << endl;
            turn = STRAIGHT;
            
        //But instead, if the left column is closer...
        } else if (getDist(columns[3][0]) < getDist(columns[5][0])) {

            cout << "LEFT" << endl;
            turn = LEFT;
        } else {
        //Otherwise, it's the remaining scenario
            cout << "RIGHT" << endl;
            turn = RIGHT;
        }
    //But what if there's 3 and 4, but no tags in 5?
    } else {  
	cout << "B";
        //Let's go through all the columns
        for (int i = 0; i < columns.size(); i++) {
            //Check to see if the i'th column isn't empty
            if (columns[i].size() > 0) {
                //See if it's to the right
                if (i > 5) {
                    cout << "RIGHT" << endl;
                    turn = RIGHT;
                } else if (i < 4) {
                //or the left
                    cout << "LEFT" << endl;
                    turn = LEFT;
                } else {
                //or just straight ahead
                    cout << "STRAIGHT" << endl;
                    turn = STRAIGHT;
                }
                break;
            }
        }
    }
    
    //Just incase we still want to detect corners
    //In order to determine to wiggle or not
    cout << "Distance: " << getDist(columns[4][0]) << endl;
    
    if(turn == STRAIGHT && getDist(columns[4][0]) < minDistance) {
        //Go through the columns
        for(int i = 0; i < columns.size(); i++) {
            //Make sure i'th column has tags
            if(columns[i].size() > 1) {
                //Compares the first and last tags in that column. Checks how far away.
                //The more tags in a column, the further, and there's only
                //"long" columns where there's corners.
                if(abs(getDist(columns[i][0]) - getDist(columns[i][columns[i].size() - 1])) > .1) {
                    cout << "We have a corner at index " << i << endl;
                    turn = CORNER;
                    break;
                }
            }
        }
    }
    
    return turn;
}

//Visually displays the location of the tags
void TagExaminer::graph() {
    for (int i = 0; i < columns.size(); i++) {
        cout << "Column " << i << ": (" << columns[i].size() << ")" << endl;
        for (int j = 0; j < columns.at(i).size(); j++) {
            cout << "\t>#" << (j + 1) << ": " << columns.at(i)[j].getPositionX() << endl;
        }
    }
}

//Clear out the tags so when new data is given, there's no old
void TagExaminer::clear() {
    tags.clear();
    for (int i = 0; i < columns.size(); i++)
        columns[i].clear();
}

//Returns distance from camera to tag
double TagExaminer::getDist(Tag x) {
    return sqrt(x.getPositionX() * x.getPositionX() + x.getPositionY() * x.getPositionY() +
                x.getPositionZ() * x.getPositionZ());
}

//Returns true if Tag X is within m of Tag y
bool TagExaminer::isClose(Tag x, Tag y, double m) {
    if (abs(getDist(x) - getDist(y)) < m) {
            return true;
    }

    return false;
}
