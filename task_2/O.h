#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "CImg.h"
using namespace cimg_library;
using namespace std;
CImg<int> orosenfeld(CImg<int>& image,int P);