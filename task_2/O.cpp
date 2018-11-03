#include "pch.h" 
#include "O.h"
using namespace cimg_library;

using namespace std;
CImg<int> orosenfeld(CImg<int>& image,int P)
{
	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height(); y++)
		{
			for (int c = 0; c < image.spectrum(); c++)
			{
				int sum = 0;
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
				int color= sum / P;
				image(x, y, 0, c) = color;
			}
		}
	}
	return image;
}