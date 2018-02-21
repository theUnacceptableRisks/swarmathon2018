#include "TagExaminer.h"
#include <utility>      // std::pair, std::make_pair

using namespace std;
TagExaminer::TagExaminer()
{
	//Todo: Either make a algorithm to get all ranges
	//Or manually place them all inside a vector pair and then
	//redo determineRange Func
	//ranges[0].first = -0.269;
	//ranges[0].second = -0.209;
}

TagExaminer::~TagExaminer()
{
}

void TagExaminer::loadTags(vector<Tag> fromTagHandler)
{
	tags = fromTagHandler;
	determineRange();
	graph();
}

void TagExaminer::determineRange()
{
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
		else {
			cout << "No range for tag at index " << i << endl;
			//cout << i << "," << x << "\n";
		}
	}
	cout << "Tags organized into ranges" << endl;
	//Now sort all the vector<Tags>
	//cout << columns[0][0].getPositionX();
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
				Tag swap = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = swap;
			}
		}

	}

}

void TagExaminer::graph()
{
	for (int i = 0; i < columns.size(); i++){
		cout << "Column " << i << ": " << endl;
		for (int j = 0; j < columns.at(i).size(); j++) {
			cout << "\t>#" << (j + 1) << ": " << columns.at(i)[j].getPositionX() << endl;
		}
	}
}
