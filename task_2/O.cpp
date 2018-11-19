#include "pch.h" 
#include "O.h"
using namespace cimg_library;

using namespace std;
CImg<int> orosenfeld(CImg<int>& image,int P)
{
	CImg<int> result = image;
	double factor = 1 / (double)P;
	//CImg<int> result(image.width(), image.height(), 1, image.spectrum());
	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height(); y++)
		{
			for (int c = 0; c < image.spectrum(); c++)
			{
				double sum = 0;
				/*int p = 0;
				for (p; p <= P; p++)*/
				/*{
					sum = sum + image(x + P - p, y, c) - image(x - p, y, c);
				}*/
				for (int i = P - 1; i >= 0; i--)
				{
					if ((x + i) > image.width()) {
						continue;
					}
					sum += image(x + i, y, 0, c);
				}
				for (int i = 1; i <= P; i++)
				{
					if ((x - i) < 0) {
						continue;
					}
					sum -= image(x - i, y, 0, c);
				}
				sum *= factor;
				//if (sum < 0) sum *= - 1;
				// if coœ ? ifture : ifnottrue
				result(x, y, 0, c) = sum < 0 ? sum * -1 : sum;
			}
		}
	}
	return result;
}