#pragma once
#include "pch.h"
#include <iostream>
#include "CImg.h"
#include <string>
#include <vector>
#include <cmath>

using namespace std;
using namespace cimg_library;

double mean(vector<int> in_hist);
double variance(vector<int> in_hist);
double stddev(vector<int> in_hist);
double varcoi(vector<int> in_hist);
double asyco(vector<int> in_hist);
double flatco(vector<int> in_hist);
double varcoii(vector<int> in_hist);
double entropy(vector<int> in_hist);


