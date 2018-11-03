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
				//for (int p = 0; p < mask.size(); p++)
				//{
				//	for (int q = 0; q < mask.size(); q++)
				//	{
				//		if ((x + p) > image.width() || (y + q) > image.height())
				//		{
				//			continue;
				//		}
				//		sum = sum + mask[p][q] * image(x + p, q + y);
				//	}
				//}

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
	return image;
}


CImg<int> sexdetii(CImg<int>& image, vector<vector<int>> mask)
{
	for (int x = 0; x < image.width(); x++)
	{
		for (int y = 0; y < image.height(); y++)
		{
			for (int c = 0; c < image.spectrum(); c++)
			{
				int sum = 0;
				int c00 = image(x, y, 0, c);
				int c01 = image(x, y + 1, 0, c);
				int c02 = image(x, y + 2, 0, c);
				int c10 = image(x + 1, y, 0, c);
				int c11 = image(x + 1, y + 1, 0, c);
				int c12 = image(x + 1, y + 2, 0, c);
				int c20 = image(x + 2, y, 0, c);
				int c21 = image(x + 2, y + 1, 0, c);
				int c22 = image(x + 2, y + 2, 0, c);
				for (int p = 0; p < mask.size(); p++)
				{
					for (int q = 0; q < mask.size(); q++)
					{
						if ((x + p) > image.width() || (y + q) > image.height())
						{
							continue;
						}
						int cc = image(x + p, q + y);
						int m = mask[p][q];
						sum = sum + mask[p][q] * image(x + q, p + y);
					}
				}
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
	return image;
}