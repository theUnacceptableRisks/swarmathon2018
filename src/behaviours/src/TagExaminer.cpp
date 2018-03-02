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
    if(distToTag(columns[4][0]) < minDist){
        cout << "SUCCESS" << endl;
        return SUCCESS;
    }

    if(columns[3].size() == 0 && columns[4].size() == 0 && columns[5].size() == 0) {
        int foundTagIndex = -1;
        for(int i = 0; i < columns.size(); i ++) {
            if(i ==  3 || i == 4 || i == 5){
                continue;
            }

            if(columns[i].size() > 0) {
                foundTagIndex = i;
                break;
            }
        }

        if(foundTagIndex > 4) {
            cout << "RIGHT" << endl;
            return RIGHT;
        }else if (foundTagIndex < 4){
            cout << "LEFT" << endl;
            return LEFT;
        }
        else {
            cout << "FAIL" << endl;
            return FAIL;
        }
    }

    //Find a long col
    int longColIndex = -1;
    for(int i = 0; i < columns.size(); i ++) {
        if(columns[i].size() > 3) {
            longColIndex = i;
            break;
        }
    }

    if(longColIndex == -1) {
        cout << "FAIL" << endl;
        return FAIL;
    }else{
        //Is there also a short line
        int shortColIndex = -1;
        for(int i = 0; i < columns.size(); i++) {
            if(columns[i].size() < 3) {
                shortColIndex = i;
                break;
            }
        }

        if(shortColIndex == -1) {
            cout << "FAIL" << endl;
        }else{
            if(longColIndex < shortColIndex) {
                cout << "RIGHT" << endl;
                return RIGHT;
            }else{
                cout << "LEFT" << endl;
                return LEFT;
            }
        }
    }


    if((columns[3].size() > 0 || columns[3].size() > 0 || columns[3].size() > 0) && (longColIndex == -1)){
        if(abs(abs(distToTag(columns[3][0])) - abs(distToTag(columns[5][0]))) < margin){
            cout << "STRAIGHT";
            return STRAIGHT;
        }
        else if(distToTag(columns[3][0]) > distToTag(columns[5][0])){
            return RIGHT;
        }else{
            return LEFT;
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

double TagExaminer::distToTag(Tag x) {
    return sqrt(x.getPositionX() * x.getPositionX() + x.getPositionY() * x.getPositionY() + x.getPositionZ() * x.getPositionZ());
}
