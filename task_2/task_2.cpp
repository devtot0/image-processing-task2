
#include "pch.h"
#include <iostream>
#include "CImg.h"
#include <vector>
using namespace std;
using namespace cimg_library;

void gen_bw_histogram(CImg<int> img, vector<int> &histogram) {

	for (int x = 0; x < img.width(); x++) {
		for (int y = 0; y < img.height(); y++) {
			for (int z = 0; z < 256; z++)
				if (img(x, y, 0, 0) == z) histogram[z]++;

		}
	}

}

void gen_rgb_histogram(CImg<int> img, vector< vector<int> > &rgb_histogram) {

	for (int x = 0; x < img.width(); x++) {
		for (int y = 0; y < img.width(); y++) {
			for (int c = 0; c < 3; c++) {
				for (int z = 0; z < 256; z++) {
					if (img(x, y, 0, c) == z) rgb_histogram[c][z]++;
				}
			}
		}
	}
}

int main()
{
	vector<int> bw_histogram_values(256, 0);
	vector< vector<int> > rgb_histogram_values(3, vector<int>(256,0));
	

	//CImg<int> image("lena.bmp");
	CImg<int> image("lenac.bmp");

	gen_bw_histogram(image, bw_histogram_values);
	gen_rgb_histogram(image, rgb_histogram_values);
	for (int i = 0; i < bw_histogram_values.size(); i++) cout << bw_histogram_values[i] << endl;
	
	CImg<int> bw_histogram(512, 512, 1, 1,255);
	bw_histogram.display();
    cout << "Hello World!\n"; 
}

