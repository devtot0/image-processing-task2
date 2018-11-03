
#include "pch.h"
#include <iostream>
#include "CImg.h"
#include <string>
#include "H.h"
#include "S.h"
#include "O.h";
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

void scale_bw(vector<int> &in_bw, vector<float> &out_bw) {
	float max = 0;
	for (int i = 0; i < in_bw.size(); i++)
	{
		if (in_bw[i] > max) max = in_bw[i];
	}

	for (int i = 0; i < in_bw.size(); i++)
	{
		out_bw[i] = in_bw[i] / max;
	}


}

void scale_rgb(vector<vector<int>> &in_rgb, vector< vector<float> > &out_rgb) {
	float max = 0;
	for (int c = 0; c < 3; c++) {//finding maximum auxiallary variable used for scaling
		for (int i = 0; i < in_rgb[0].size(); i++)
		{
			if (in_rgb[c][i] > max) max = in_rgb[c][i];
		}
	}
	for (int c = 0; c < 3; c++) {//calculating the fraction for every histogram value
		for (int i = 0; i < in_rgb[0].size(); i++)
		{
			out_rgb[c][i] = in_rgb[c][i]/ max;
		}
	}


}
void draw_rectangle(int x, int h, int w, int r, int g, int b, CImg<int> &canvas) {//x-horizontal position, h-rectangle height, w - width, rgb-channels, canvas

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			canvas(x+i, canvas.height() - j, 0, 0) = r;
			canvas(x+i, canvas.height() - j, 0, 1) = g;
			canvas(x+i, canvas.height() - j, 0, 2) = b;
		}
	}
}

CImg<int> print_bw(vector<float> in_bw, CImg<int>& canvas) {//in_bw is a vector of scaled histogram values in this function

	for (int i = 0; i < in_bw.size(); i++) {//iterating through scaled vector
		int t = in_bw[i] * canvas.height();
		draw_rectangle(i * 2, t, 2, 0, 0, 0, canvas);//in_bw[i]*height to scale the proper percentage
	}
	return canvas;
}
CImg<int> print_rgb(vector< vector<float> > in_rgb, CImg<int>& canvas, char channel) {

	if(channel=='r'){
		for (int i = 0; i < in_rgb[0].size(); i++) {//iterating through scaled vector

			draw_rectangle(i * 2, in_rgb[0][i] * canvas.height(), 2, 255, 0, 0, canvas);//in_bw[i]*height to scale the proper percentage
		
		}
	}
	else if (channel == 'g') {
		for (int i = 0; i < in_rgb[0].size(); i++) {//iterating through scaled vector

			draw_rectangle(i * 2, in_rgb[1][i] * canvas.height(), 2, 0, 255, 0, canvas);//in_bw[i]*height to scale the proper percentage

		}
	}
	else {
		for (int i = 0; i < in_rgb[0].size(); i++) {//iterating through scaled vector

			draw_rectangle(i * 2, in_rgb[2][i] * canvas.height(), 2, 0, 0, 255, canvas);//in_bw[i]*height to scale the proper percentage

		}
	}

	return canvas;
}


int main(int argc, char* argv[])
{	//initial histogram values
	vector<int> bw_histogram_values(256, 0);
	vector< vector<int> > rgb_histogram_values{ vector<int>(256,0) ,vector<int>(256,0) ,vector<int>(256,0) };
	//scaled histogram values
	vector<float> percent_bw(256, 0);
	vector< vector<float> > percent_rgb{ vector<float>(256, 0) ,vector<float>(256, 0) ,vector<float>(256, 0) };
	CImg<int> canvas("background.bmp");
	vector<string> args;
	for (int i = 0; i < argc; i++) {
		args.push_back(string(argv[i]));
	}

	if (argc >= 4) {
		if (args[1] == "--orosenfeld") {
			CImg<int> image(argv[2]);
			CImg<int> result = orosenfeld(image,stoi(args[3]));
			result.save("rosenfeld.bmp");
		}
		if (args[1] == "--sexdetii") {
			CImg<int> image(argv[2]);
			if (args[3] == "mask_optimized") {
				CImg<int> result = sexdetii(image);
				result.save("mask_optimized.bmp");
			}
			if (args[3] == "mask_universal") {
				vector < vector<int>> mask  { {-1,-1,-1},{1,-2,1},{1,1,1} };
				CImg<int> result = sexdetii(image,mask);
				result.save("mask_universal.bmp");
			}
			
		}
		if (args[1] == "--histogram") {
			CImg<int> image2(argv[3]);
			if (args[2] == "--r") {
				gen_rgb_histogram(image2, rgb_histogram_values);
				scale_rgb(rgb_histogram_values,percent_rgb);
				CImg<int> histogram_r=print_rgb(percent_rgb, canvas, 'r');
				histogram_r.save("histogram_r.bmp");
			}
			else if (args[2] == "--g") {
				gen_rgb_histogram(image2, rgb_histogram_values);
				gen_rgb_histogram(image2, rgb_histogram_values);
				scale_rgb(rgb_histogram_values, percent_rgb);
				CImg<int> histogram_g = print_rgb(percent_rgb, canvas, 'g');
				histogram_g.save("histogram_g.bmp");
			}
			else if (args[2] == "--b") {
				gen_rgb_histogram(image2, rgb_histogram_values);
				gen_rgb_histogram(image2, rgb_histogram_values);
				scale_rgb(rgb_histogram_values, percent_rgb);
				CImg<int> histogram_b = print_rgb(percent_rgb, canvas, 'b');
				histogram_b.save("histogram_b.bmp");

			}
			else if (args[2] == "--bw") {
				gen_bw_histogram(image2, bw_histogram_values);
				scale_bw(bw_histogram_values, percent_bw); 
				CImg<int> histogram_bw = print_bw(percent_bw, canvas);
				histogram_bw.save("histogram_bw.bmp");
			}

			else cout << "Wrong command" << endl;
		}
		if (args[1] == "--hhyper") {
			int min, max;
			try {
				min = stoi(args[4]);
				max = stoi(args[5]);
			}
			catch (...) {
				cout << "it's not int!";
				system("pause");
				return 1;
			}

			CImg<int> image2(argv[3]);
			if (args[2] == "--rgb") {

				gen_rgb_histogram(image2, rgb_histogram_values);
				CImg<int> output_rgb = rgb_hhyper(image2, rgb_histogram_values,min,max);
				output_rgb.save("hhyper_rgb.bmp");
				
			}
			
			else if (args[2] == "--bw") {
				gen_bw_histogram(image2, bw_histogram_values);
				
				CImg<int> output_bw = bw_hhyper(image2, bw_histogram_values,min,max);
				output_bw.save("hhyper_bw.bmp");
			}

			else cout << "Wrong command" << endl;
		}
		system("pause");
	}





}

