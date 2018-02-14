
#include "TagExaminer.h"
#include <tuple>
#include <vector>
#include <utility>
#include <iostream>
#include <map>

using namespace std;

TagExaminer::TagExaminer(vector<Tag> column, int columnSize, double center)
{
	//init member vars
	this->rawTags = column;
	this->colWid = columnSize;
	this->center = center;

	//Set the mins and maxes of the x values in the vector of tags
	//cout << "Sorting mins and maxes..." << endl;
	getMinMax(column);
	//cout << "Sorted." << endl;

	//Sort the vec in order from left to right based on X Position
	//cout << "Sorting Tags" << endl;
	this->sortedTags = sortVec(column);
	//cout << "Tags sorted." << endl;

	//vectorOut(sortedTags);

	//Figure out the vector range
	//cout << "Calculating ranges" << endl;
	vector <pair < double, double >> populated = populate(min, max, center, colWid);
	//cout << "Calculated." << endl;

	//Put tags in appopriate range

	//cout << "Populating Tags into ranges" << endl;
	split(populated);
	//cout << "Populated" << endl;

	//graph
	//cout << "\n\nGraphing the locations of tags" << endl;
	cout << "\n\n-----------------------------------\n\n";

	graph();
	cout << "\n\n-----------------------------------\n\n";

	cout << endl;

}


vector<pair <double, double>> TagExaminer::populate(double min, double max, double center, double wid)
{

	vector <pair < double, double >> nums;
	pair <double, double> apair;
	int count = 1;
	int incr = 0;
	double start = center + (wid / 2);

	//cout << "-----------------------------------\n";

	while ((start > min)) {
		if (count % 2 != 0) {
			apair.first = start;
			start = start - wid;
			apair.second = start;
			if (apair.first > apair.second) {
				double temp = apair.first;
				apair.first = apair.second;
				apair.second = temp;
			}
			nums.push_back(apair);
			numRanges++;
			incr++;
		}
		count++;
	}

	apair.first = 0;
	apair.second = 0;
	count = 1;
	start = center + (wid / 2);
	while ((start < max)) {
		if (count % 2 != 0) {
			apair.first = start;
			start = start + wid;
			apair.second = start;

			if (apair.first > apair.second) {
				double temp = apair.first;
				apair.first = apair.second;
				apair.second = temp;
			}
			nums.push_back(apair);

			numRanges++;
			incr++;
		}
		count++;
	}
	nums = sortVec(nums);
	//vectorOut(nums);

	//cout << "Ranges: " << numRanges << endl;
	//cout << "-----------------------------------\n\n";

	return nums;
}

void TagExaminer::getMinMax(vector<Tag> column)
{
	this->min = column[0].getPositionX();
	this->max = column[0].getPositionX();

	for (int i = 0; i < column.size(); i++) {
		if (column[i].getPositionX() > max) {
			max = column[i].getPositionX();
		}
		if (column[i].getPositionX() < min) {
			min = column[i].getPositionX();
		}
	}
}


void TagExaminer::split(vector <pair < double, double>> overall)
{

	for (int i = 0; i < sortedTags.size(); i++) {//Loop through tags
		vector <Tag> w;
		ranges.push_back(w);
		for (int j = 0; j < overall.size(); j++) {//Loop through pairs

			if (sortedTags[i].getPositionX() >= overall[j].first && sortedTags[i].getPositionX() <= overall[j].second) {

				ranges.at(j).push_back(sortedTags[i]);
				//cout << "Matched Tag XPos:" << sortedTags[i].getPositionX() << " Into Range " << j << ". Range total: " << ranges.at(j).size() << endl;
				//cout << "Matched into range " << ranges.at(j).size() - 1 << " position " << j << endl;

				holding.push_back(make_tuple(ranges.at(j).size() - 1, j, sortedTags[i]));

				if (ranges.at(j).size() > largestRange) {
					largestRange = ranges.at(j).size();
				}
			}
		}
	}
}

void TagExaminer::graph()
{
	holding = sortTuple(holding);
	int z = 0;
	for (int i = 0; i < 9; i++) {
		//cout << "[" << (std::get<1>(holding[i])) << " " << (std::get<0>(holding[i])) << "]\t";

		if (get<0>(holding[i]) > z) {
			z = get<0>(holding[i]);
			cout << endl;
		}

		cout << (std::get<2>(holding[i])).getPositionX() << "\t|\t"; //Almost works
	}
	cout << endl << endl << endl;
}

void TagExaminer::vectorOut(vector<Tag> column)
{
	//cout << "\n\n-----------------------------------\n\n";
	for (Tag t : column) {
		cout << "Tag: " << t.getPositionX() << ", " << t.getPositionY() << ", " << t.getPositionZ() << endl;
	}
//	cout << "\n\n-----------------------------------\n\n";
}

void TagExaminer::vectorOut(vector<pair<double, double>> pairlist)
{
	//cout << "\n\n-----------------------------------\n\n";
	for (pair<double, double> p : pairlist) {
		cout << "(" << p.first << ", " << p.second << ")" << endl;
	}
	//cout << "\n\n-----------------------------------\n\n";
}



vector<Tag> TagExaminer::sortVec(vector<Tag> column)
{
	//sort tags based on x position value(least to greatest)
	for (int i = 0; i < column.size() - 1; i++) {
		for (int j = 0; j < column.size() - i - 1; j++) {
			if (column[j].getPositionX() > column[j + 1].getPositionX()) {
				std::swap(column[j], column[j + 1]);
			}
		}
	}
	//the sorted tags by X value
	this->sortedTags = column;
	return column;
}

vector<tuple<int, int, Tag>> TagExaminer::sortTuple(vector<tuple<int, int, Tag>> tup)
{
	//sort tags based on x position value(least to greatest)
	for (int i = 0; i < tup.size() - 1; i++) {
		for (int j = 0; j < tup.size() - i - 1; j++) {
			if (std::get<0>(tup[j]) > std::get<0>(tup[j + 1])) {
				std::swap(tup[j], tup[j + 1]);
			}
		}
	}
	//the sorted tags by X value
	return tup;
}

//sort the pairs to make proper ranges
vector<pair<double, double>> TagExaminer::sortVec(vector<pair<double, double>> p)
{
	//sort tags based on x position value(least to greatest)
	for (int i = 0; i < p.size() - 1; i++) {
		for (int j = 0; j < p.size() - i - 1; j++) {
			if (p[j].first > p[j + 1].first) {
				std::swap(p[j], p[j + 1]);
			}
		}
	}
	return p;
}
