
#include <opencv2/opencv.hpp>
#include "MemoryControl.hpp"


unsigned char YChange(unsigned char* img_data,int x,int y,int rows,int cols) {
	return (unsigned char)(0.114 * img_data[3 * (y * cols + x)] + 0.587 * img_data[3 * (y * cols + x) + 1] + 0.299 * img_data[3 * (y * cols + x) + 2]);
}

unsigned char UChange(unsigned char* img_data, int x, int y, int rows, int cols) {
	return (unsigned char)std::max(0, std::min(255, (int)(-0.169 * img_data[3 * (y * cols + x) + 2] - 0.331 * img_data[3 * (y * cols + x) + 1] + 0.499 * img_data[3 * (y * cols + x)]) + 128));
}
unsigned char VChange(unsigned char* img_data, int x, int y, int rows, int cols) {

	return (unsigned char)std::max(0, std::min(255, (int)(0.499 * img_data[3 * (y * cols + x)+2] - 0.418 * img_data[3 * (y * cols + x)+1] - 0.081 * img_data[3 * (y * cols + x)]) + 128));

}

unsigned char* GrayScaleReturner(unsigned char* img_data,int rows,int cols) {
	unsigned char* Y = MemAlloc(rows * cols,0);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Y[i * cols + j] = YChange(img_data, j, i, rows, cols);
		}
	}

	return Y;
}

unsigned char* YUVReturner(unsigned char* img_data,int rows,int cols) {
	unsigned char* YUV = MemAlloc(3 * rows * cols, 0);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			YUV[3 * (i * cols + j)] = YChange(img_data,j,i,rows,cols);
			YUV[3 * (i * cols + j) + 1] = UChange(img_data,j,i,rows,cols);
			YUV[3 * (i * cols + j) + 2] = VChange(img_data,j,i,rows,cols);
		}
	}

	return YUV;
}

unsigned char* ProgressiveReturner(unsigned char* img_data,int rows,int cols) {
	unsigned char* for_write = MemAlloc(3 * rows * cols, 0);
	unsigned char* only_red = MemAlloc(rows * cols, 0);
	unsigned char* only_blue = MemAlloc(rows * cols, 0);
	unsigned char* only_green = MemAlloc(rows * cols, 0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			only_red[i * rows + j] = img_data[3 * (i * cols + j) + 2];
			only_green[i * rows + j] = img_data[3 * (i * cols + j) + 1];
			only_blue[i * rows + j] = img_data[3 * (i * cols + j)];
		}
	}
	int idx = 0;
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (k == 0) {
					for_write[idx] = only_red[i * cols + j];
				}
				else if (k == 1) {
					for_write[idx] = only_blue[i * cols + j];
				}
				else {
					for_write[idx] = only_green[i * cols + j];
				}
				idx++;
			}
		}
	}
	

	MemFree(only_red);
	MemFree(only_blue);
	MemFree(only_green);

	return for_write;
}