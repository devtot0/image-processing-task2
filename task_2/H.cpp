#include "pch.h"
#include "H.h"

using namespace std;


vector<double> hhyper(vector<int> in_hist, int min, int max) {

	double sum = 0;
	for (int i = min; i < in_hist.size(); i++) {

		if (in_hist[i] != 0) {
			min = i;//i is a minimal non-zero value, "old" minimum color brightness
			break; 
		}
	}

	for (int i = max; i >= 0; i--) {

		if (in_hist[i] != 0) {
			max = i;//i is a maximal non-zero value, "old" maxumim color brightness
			break;
		}

	}
	for (int i = min; i < max; i++) //number of pixels
	{
		sum += in_hist[i];
	}
	vector<double> result;
	for (int i = 0; i < in_hist.size(); i++) {
		if (i<min || i>max) {
			result.push_back(0);
			continue;
		}
		double current_sum = 0;
		for (int j = 0; j <= i; j++) {//number of pixels with brightness less or equal than i
			current_sum += in_hist[i];
		}
		double temp = min * (std::pow(max / min, current_sum / sum));//
		result.push_back(temp);
	}
	return result;
}

CImg<int> bw_hhyper(CImg<int> &image, vector<int> histogram,int min, int max)
{
	vector<double> altered = hhyper(histogram,min,max);
	/*for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height(); y++)
		{
			for (int c = 0; c < image.spectrum(); c++) {
				image(x, y, 0,c) = altered[image(x, y, 0,c)];
			}
		}
	}*/
	return image;
}

CImg<int> rgb_hhyper(CImg<int>& image, vector<vector<int>> histogram, int min, int max)
{
	vector <int> original_r = histogram[0];
	vector <int> original_g = histogram[1];
	vector <int> original_b = histogram[2];

	vector <double> altered_r = hhyper(original_r, min, max);
	vector <double> altered_g = hhyper(original_g, min, max);
	vector <double> altered_b = hhyper(original_b, min, max);

	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height(); y++)
		{

			
				image(x, y, 0, 0) = altered_r[image(x, y, 0, 0)];
				image(x, y, 0, 1) = altered_g[image(x, y, 0, 1)];
				image(x, y, 0, 2) = altered_b[image(x, y, 0, 2)];
			
		}
	}
	return image;
}

