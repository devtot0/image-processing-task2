#include "pch.h" 
#include "S.h"

CImg<int> sexdetii(CImg<int>& image)
{
	for (int x = 2; x < image.width()-2; x++)
	{
		for (int y = 2; y < image.height()-2; y++)
		{
			for (int c = 0; c < image.spectrum(); c++)
			{
				int sum = 0;


				sum = -image(x, y, 0, c) //image(x,y)*(-1)
					- image(x + 1, y, 0, c) //image(x+1,y)*(-1)
					- image(x + 2, y, 0, c) //image(x+2,y)*(-1)
					+ image(x, y + 1, 0, c) //image(x,y+1)*
					- 2 * image(x + 1, y + 1, 0, c) //image(x+1,y+1)*(-2)
					+ image(x + 2, y + 1, 0, c) //image(x+2,y+1)*(-1)
					+ image(x, y + 2, 0, c) //image(x,y+2)
					+ image(x + 1, y + 2, 0, c) //image(x+1,y+2)
					+ image(x + 2, y + 2, 0, c); //image(x+2,y+2)
					
				if (sum > 255) {
					sum = 255;
				}
				if (sum < 0) {
					sum = 0;
				}
				image(x, y, 0, c) = sum;
			}
		}
	}


	//for (int x = 0; x < image.width(); x++)
	//{
	//	for (int y = 0; y < image.height() ; y++)
	//	{
	//		for (int c = 0; c < image.spectrum(); c++)
	//		{
	//			int sum = 0;

	//			sum = -image(x, y, 0, c);
	//			if (x < image.width() - 1) {
	//				sum -= image(x + 1, y, 0, c);
	//			}

	//			//sum = -image(x, y, 0, c) //image(x,y)*(-1)
	//			//	- image(x + 1, y, 0, c) //image(x+1,y)*(-1)
	//			//	- image(x + 2, y, 0, c) //image(x+2,y)*(-1)
	//			//	+ image(x, y + 1, 0, c) //image(x,y+1)*
	//			//	- 2 * image(x + 1, y + 1, 0, c) //image(x+1,y+1)*(-2)
	//			//	+ image(x + 2, y + 1, 0, c) //image(x+2,y+1)*(-1)
	//			//	+ image(x, y + 2, 0, c) //image(x,y+2)
	//			//	+ image(x + 1, y + 2, 0, c) //image(x+1,y+2)
	//			//	+ image(x + 2, y + 2, 0, c); //image(x+2,y+2)

	//			if (sum > 255) {
	//				sum = 255;
	//			}
	//			if (sum < 0) {
	//				sum = 0;
	//			}
	//			image(x, y, 0, c) = sum;
	//		}
	//	}
	//}
	return image;
}


CImg<int> sexdetii(CImg<int>& image, vector<vector<int>> mask,int divider)
{
	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height(); y++)
		{
			for (int c = 0; c < image.spectrum(); c++)
			{
				int sum = 0;				
				for (int q = 0; q < mask.size(); q++)
				{
					for (int p = 0; p < mask.size(); p++)
					{
						if ((y + p) > image.width() || (x + q) > image.height())
						{
							continue;
						}
						sum = sum + mask[p][q] * image(x + q, p + y,c);
					}
				}
				if (sum > 255) {
					sum = 255;
				}
				if (sum < 0) {
					sum = 0;
				}
				image(x, y, 0, c) = sum/divider;
			}
		}
	}
	return image;
}