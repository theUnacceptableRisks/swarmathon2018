#pragma once
#include "Tag.h"
#include <vector>

using namespace std;
class TagExaminer
{

public:
	TagExaminer();

    enum Turns{
                INIT,
		LEFT,
		RIGHT,
		STRAIGHT,
		CORNER
	};
	
	Turns determineTurning();
	
    // margin suggests how close tags
	// have to be to be considered straight
	const double margin = 0.012;
	const double minDistance = .25;
	
    vector<Tag> tags;
    vector<vector<Tag>> columns;

	void loadTags(vector<Tag>);
	void determineRange();
	void sortColumn(vector<Tag> &);
	void graph();
	void clear();
	
	double getDist(Tag);
    bool isClose(Tag, Tag, double);

    

};
