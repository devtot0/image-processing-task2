#include "pch.h"
#include "H.h"

using namespace std;


vector<double> hhyper(vector<int> in_hist) {

	double min = 0;//minimal brightness
	double max = 0;
	double sum = 0;
	for (int i = 0; i < in_hist.size(); i++) {

		if (in_hist[i] != 0) {
			min = i;//i is a minimal non-zero value, "old" minimum color brightness
			break;
		}
	}

	for (int i = in_hist.size() - 1; i >= 0; i--) {

		if (in_hist[i] != 0) {
			max = i;//i is a maximal non-zero value, "old" maxumim color brightness
			break;
		}

	}
	for (int i = 0; i < in_hist.size(); i++) {//number of pixels

		sum += in_hist[i];
	}
	vector<double> result;
	for (int i = 0; i < in_hist.size(); i++) {
		double current_sum = 0;
		for (int j = 0; j <= i; j++) {//number of pixels with brightness less or equal than i
			current_sum += in_hist[i];
		}
		double temp = min * (std::pow(max / min, current_sum / sum));//
		result.push_back(temp);
	}
	return result;
}