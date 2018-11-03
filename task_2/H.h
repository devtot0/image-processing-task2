#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "CImg.h"
using namespace cimg_library;

using namespace std;

vector<double> hhyper(vector<int> in_hist, int min, int max);
CImg<int> bw_hhyper(CImg<int> &image, vector<int> histogram,int min, int max);
CImg<int> rgb_hhyper(CImg<int> &image, vector< vector<int> >  histogram, int min, int max);
 