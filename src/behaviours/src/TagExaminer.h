#ifndef TAGEXAMINER_H
#define TAGEXAMINER_H

#pragma once
#include "Tag.h"
#include <vector>
#include <cmath>

using namespace std;

class TagExaminer
{
public:
	TagExaminer(std::vector<Tag> column, int columnSize, double center);
	vector<pair<double, double>> populate(double min, double max, double center, double wid);
	vector<Tag> sortVec(vector<Tag> column);
	vector<pair<double, double>> sortVec(vector<pair<double, double>> p);
	vector<tuple<int, int, Tag>> sortTuple(vector<tuple<int, int, Tag>>);
	void getMinMax(vector<Tag> column);
	void split(vector <pair < double, double >>);
	void vectorOut(vector<Tag> column);
	void vectorOut(vector<pair<double, double>>);
	void graph();

	void setColumnSize(int newSize) {
		colWid = newSize;
	}
	void setCenter(double newCenter){
		center = newCenter;
	}



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
	vector<tuple<int, int, Tag>> holding;
};

#endif