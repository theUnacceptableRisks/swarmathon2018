#pragma once
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
		SUCCESS,
		FAIL
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
	double getDist(Tag);
    bool isClose(Tag, Tag, double);

    //
	const double margin = 0.008;
    const double wiggleDist = 0.25;
    const double minDist = 0.18;
    //
private:
	const double colWidth = .06;
	const double center = 0;
	const double colMin = -.3;
	const double colMax = .3;

};
