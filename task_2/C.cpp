#include "pch.h"
#include "C.h"

double mean(vector<int> in_hist) {

	double sum = 0;
	for (int i = 0; i < in_hist.size(); i++) {//number of pixels

		sum += in_hist[i];
	}
	double result = 0;
	for (int i = 0; i < in_hist.size(); i++) {
		result += i * in_hist[i];
	}
	return result / sum;
}

double variance(vector<int> in_hist) {
	double sum = 0;
	for (int i = 0; i < in_hist.size(); i++) {//number of pixels

		sum += in_hist[i];
	}
	double result = 0;
	double mean_value = mean(in_hist);//b-dash in the manual
	for (int i = 0; i < in_hist.size(); i++) {
		result += (i-mean_value)*(i-mean_value) * in_hist[i];
	}
	return result / sum;
}
double stddev(vector<int> in_hist) {
	return std::sqrt(variance(in_hist));
}
double varcoi(vector<int> in_hist) {
	return stddev(in_hist) / mean(in_hist);
}
double asyco(vector<int> in_hist) {
	double mean_value = mean(in_hist);//
	double stddev_value = stddev((in_hist));
	stddev_value = 1/(stddev_value * stddev_value*stddev_value);//ready to be implemented
	double sum = 0;
	for (int i = 0; i < in_hist.size(); i++) {//number of pixels

		sum += in_hist[i];
	}
	double result = 0;
	for (int i = 0; i < in_hist.size(); i++) {
		result += (i - mean_value)*(i - mean_value) *(i - mean_value)* in_hist[i];
	}
	return (result / sum)*stddev_value;


}
double flatco(vector<int> in_hist) {
	double mean_value = mean(in_hist);//
	double stddev_value = stddev((in_hist));
	stddev_value = 1 / (stddev_value * stddev_value*stddev_value*stddev_value);//ready to be implemented
	double sum = 0;
	for (int i = 0; i < in_hist.size(); i++) {//number of pixels

		sum += in_hist[i];
	}
	double result = 0;
	for (int i = 0; i < in_hist.size(); i++) {
		result += (i - mean_value)*(i - mean_value)*(i - mean_value) *(i - mean_value)* in_hist[i];
	}
	return (result / sum)*stddev_value-3;//or should it be in the sum?
}
double varcoii(vector<int> in_hist) {
	double sum = 0;
	for (int i = 0; i < in_hist.size(); i++) {//number of pixels

		sum += in_hist[i];
	}
	double result = 0;
	for (int i = 0; i < in_hist.size(); i++) {
		result += in_hist[i] * in_hist[i];
	}
	return (result / sum)/sum;
}
double entropy(vector<int> in_hist) {
	double sum = 0;
	for (int i = 0; i < in_hist.size(); i++) {//number of pixels

		sum += in_hist[i];
	}
	double result = 0;
	for (int i = 0; i < in_hist.size(); i++) {
		result += in_hist[i] * log2(in_hist[i]/sum);
	}
	return -result / sum;


}