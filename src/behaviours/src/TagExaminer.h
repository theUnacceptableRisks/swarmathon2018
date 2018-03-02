#pragma once
#include <string>
#include "Tag.h"
#include <vector>
#include <utility>      // std::pair, std::make_pair

using namespace std;
class TagExaminer
{


public:
	TagExaminer();
	~TagExaminer();

	enum Turns{
		LEFT,
		RIGHT,
		STRAIGHT,
        RIGHT_CORNER,
        LEFT_CORNER,
		SUCCESS,
        NONE
	};

	vector<Tag> tags;
	vector<vector<Tag>> columns;
	vector< pair<double, double>> ranges;

	void loadTags(vector<Tag>);
	void determineRange();
	void sortColumn(vector<Tag> &);
	Turns determineTurning();
	void graph();
	void clear();
	double distToTag(Tag);
    string getDirection(Turns t){
        if(t == LEFT)
            return "LEFT";
        else if(t == RIGHT)
            return "RIGHT";
        else if(t == STRAIGHT)
            return "STRAIGHT";
        else if(t == RIGHT_CORNER)
            return "RIGHT_CORNER";
        else if(t == LEFT_CORNER)
            return "LEFT_CORNER";
        else
            return "NONE";
    }

    //
	const double margin = 0.008;
	const double minDist = 0.20;
    //
private:
	const double colWidth = .06;
	const double center = 0;
	const double colMin = -.3;
	const double colMax = .3;

};
