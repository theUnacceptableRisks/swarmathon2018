#include "TagExaminer.h"
#include <stdlib.h>     /* abs */

using namespace std;

TagExaminer::TagExaminer()
{
	//todo: 
	/*

	Make a detection function to say if 
	home base tags are aligned/straight
	
	*/
}

TagExaminer::~TagExaminer()
{
}

void TagExaminer::loadTags(vector<Tag> fromTagHandler)
{
    tags = fromTagHandler;
    determineRange();
	//graph();
	//determineTurning();
	clear();
}

void TagExaminer::determineRange()
{
	//TODO: Resize these and eventually have a loop instead of 50 ifs.
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

void TagExaminer::sortColumn(vector<Tag> &arr)
{
	int n = arr.size();

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

TagExaminer::Turns TagExaminer::determineTurning()
{
	//Compare the left most and right most tag to draw a "line"
	//to see which direction it needs to go to.

	Tag left, right;

	//First, find the left most column.

	double lx = left.getPositionX(), ly = left.getPositionY(), lz = left.getPositionZ();
	double rx = right.getPositionX(), ry = right.getPositionY(), rz = right.getPositionZ();
	//Should I have to worry about absolute values?
	double ldist = sqrt(lx * lx + ly * ly + lz * lz);
	double rdist = sqrt(rx * rx + ry * ry + rz * rz);

	if (abs(abs(ldist) - abs(rdist)) <= margin) {
		cout << "CORNER" << endl;
		return CORNER;
	}
	else if (abs(ldist) > abs(rdist)) {
		cout << "RIGHT" << endl;
		return RIGHT;
	}
	else {
		cout << "LEFT" << endl;
		return LEFT;
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
