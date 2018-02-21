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

	vector<Tag> tags;
	vector<vector<Tag>> columns;
	vector< pair<double, double>> ranges;

	void loadTags(vector<Tag>);
	void determineRange();
	void TagExaminer::sortColumn(vector<Tag> &);
	void graph();
	void clear();



private:
	const double colWidth = .06;
	const double center = 0;
	const double colMin = -.3;
	const double colMax = .3;	
};

