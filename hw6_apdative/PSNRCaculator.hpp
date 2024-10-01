#include <math.h>
double GetGrayPSNR(unsigned char* original,unsigned char* result,int rows,int cols) {
	double MSE=0;
	for (int i = 0; i < rows * cols; i++) {
		MSE+=pow((original[i] - result[i]), 2);
	}
	MSE /= (rows * cols);

	return 10 * log10(pow(255, 2) / MSE);
}

double GetColorPSNR(unsigned char* original, unsigned char* result, int rows, int cols) {
	double MSE=0;
	for (int i = 0; i < 3 * rows * cols; i ++) {
		MSE += pow((original[i] - result[i]), 2);
	}
	MSE /= (3 * rows * cols);

	return 10 * log10(pow(255, 2) / MSE);
}