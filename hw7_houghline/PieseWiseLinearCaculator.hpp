#include <opencv2/opencv.hpp>

void GetPieseWiseLookupTable(double* lookup,int r1,int s1,int r2,int s2) {

	for (int i = 0; i < 256; i++) {
		if (i < r1) {
			lookup[i] = ((s1) / (r1)) * (i - r1) + s1;
		}
		else if (i >= r1 && i < r2) {
			lookup[i] = ((s2 - s1) / (r2 - r1)) * (i - r1) + s1;
		}
		else if (i >= r2) {
			lookup[i] = ((255 - s2) / (255 - r2)) * (i - 255) + 255;
		}
	}
}

void GrayPieseWiseLinear(unsigned char* src,unsigned char* dst,int rows,int cols,int r1,int s1,int r2,int s2) {
	double* lookup = (double*)malloc(sizeof(double) * 256);
		
	GetPieseWiseLookupTable(lookup,r1, s1, r2, s2);
	for (int i = 0; i < cols * rows; i++) {
		dst[i] = lookup[src[i]];
	}
}

void ColorPieseWiseLinear(unsigned char* src,unsigned char* dst,int rows,int cols,int r1,int s1,int r2,int s2) {
	double* lookup = (double*)malloc(sizeof(double) * 256);

	GetPieseWiseLookupTable(lookup, r1, s1, r2, s2);

	for (int i = 0; i < 3*cols * rows; i++) {
		dst[i] = lookup[src[i]];
	}
}