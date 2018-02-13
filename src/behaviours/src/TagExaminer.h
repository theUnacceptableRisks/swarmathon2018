#pragma once
#include "Tag.h";
#include <vector>
#include <cmath>

using namespace std;

class TagExaminer
{
public:
	TagExaminer(vector<Tag> column, int columnSize, int center);
	vector<pair<double, double>> populate(double min, double max, double center, double wid);
	vector<Tag> sortVec(vector<Tag> column);
	vector<pair<double, double>> sortVec(vector<pair<double, double>> p);
	void getMinMax(vector<Tag> column);
	void split(vector <pair < double, double >>);
	void vectorOut(vector<Tag> column);
	void vectorOut(vector<pair<double, double>>);
	void graph();



private:
	vector<Tag> rawTags;
	vector<Tag> sortedTags;
	double colWid;
	double center;
	double min;
	double max;
	int numRanges = 0;
	int largestRange = 0;
	vector<vector<Tag>> ranges;
};

