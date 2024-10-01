#include <opencv2/opencv.hpp>

void GrayPadding(unsigned char* img, unsigned char* dst,int rows, int cols, int n) {

	for (int i = 0; i < rows + 2 * n; i++) {
		for (int j = 0; j < cols + 2 * n; j++) {

			if ((i < n && j < n)) {//왼쪽 위 대각선

				dst[((i) * (cols + 2 * n)) + j] = img[(((n - i - 1)) * cols) + (n - j - 1)];

			}
			else if ((i < n && j >= cols + n - 1)) {//오른쪽 위 대각선

				dst[(i) * (cols + 2 * n) + j] = img[(((n - i - 1)) * cols) + cols - 1 - (j - (n + cols - 1))];


			}
			else if ((i >= rows + n - 1 && j < n)) {//왼쪽 아래 대각선

				dst[((i) * (cols + 2 * n)) + j] = img[(rows - 1 - (i - (n + rows - 1))) * cols + (n - j - 1)];

			}
			else if ((i >= rows + n - 1 && j >= cols + n - 1)) {//오른쪽 아래 대각선

				dst[((i) * (cols + 2 * n)) + j] = img[((rows - 1 - (i - (n + rows - 1))) * cols) + cols - 1 - (j - (n + cols - 1))];


			}
			else if ((i < n && j >= n && j <= n + cols - 1)) {// 위

				dst[(i) * (cols + 2 * n) + j] = img[(((n - i - 1)) * cols) + j - n];


			}
			else if ((i >= rows + n - 1 && j >= n && j <= n + cols - 1)) {//아래
				dst[(i) * (cols + 2 * n) + j] = img[((rows - 1 - (i - (n + rows - 1))) * cols) + j - n];


			}
			else if ((i >= n && i <= rows + n - 1 && j < n)) {//왼쪽
				if (rows < rows + n - 1) {
					dst[(i) * (cols + 2 * n) + j] = img[((i - n) * cols) + (n - j - 1)];
				}
				else {
					dst[(i) * (cols + 2 * n) + j] = img[((i)*cols) + 2 * (n - j - 1)];


				}
			}
			else if ((i >= n && i <= rows + n - 1 && j >= cols + n - 1)) {//오른쪽
				if (rows < rows + n - 1) {
					dst[(i) * (cols + 2 * n) + j] = img[((i - n) * cols) + cols - 1 - (j - (n + cols - 1))];

				}
				else {
					dst[(i) * (cols + 2 * n) + j] = img[((i)*cols) + cols - 1 - (j - (n + cols - 1))];

				}
			}
			else {//복사하는 부분
				if (i - n < rows) {//정상적으로 복사

					dst[((i) * (cols + 2 * n)) + j] = img[((i - n) * cols) + j - n];

				}
				else {//원본의 맨 아랫줄을 복사하는 경우 예외 처리

					dst[((i) * (cols + 2 * n)) + j] = img[((i - 2 * n) * cols) + j - 2 * n];

				}
			}
		}
	}
}

void ColorPadding(unsigned char* img,unsigned char* dst, int rows, int cols, int n) {

	//프로그레시브 rgb

		
		for (int i = 0; i < rows + 2 * n; i++) {
			for (int j = 0; j < cols + 2 * n; j++) {

				if ((i < n && j < n)) {//왼쪽 위 대각선

					dst[3*(((i) * (cols + 2 * n)) + j)] = img[3*((((n - i - 1)) * cols) + (n - j - 1))];
					dst[3 * (((i) * (cols + 2 * n)) + j)+1] = img[3 * ((((n - i - 1)) * cols) + (n - j - 1))+1];
					dst[3 * (((i) * (cols + 2 * n)) + j)+2] = img[3 * ((((n - i - 1)) * cols) + (n - j - 1))+2];

				}
				else if ((i < n && j >= cols + n - 1)) {//오른쪽 위 대각선

					dst[3*((i) * (cols + 2 * n) + j)] = img[3*(((( + n - i - 1)) * cols) + cols - 1 - (j - (n + cols - 1)))];
					dst[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * ((((+n - i - 1)) * cols) + cols - 1 - (j - (n + cols - 1)))+1];
					dst[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * ((((+n - i - 1)) * cols) + cols - 1 - (j - (n + cols - 1)))+2];


				}
				else if ((i >= rows + n - 1 && j < n)) {//왼쪽 아래 대각선

					dst[3*(((  i) * (cols + 2 * n)) + j)] = img[3*(( rows - 1 - (i - (n + rows - 1))) * cols + (n - j - 1))];
					dst[3 * (((i) * (cols + 2 * n)) + j)+1] = img[3 * ((rows - 1 - (i - (n + rows - 1))) * cols + (n - j - 1))+1];
					dst[3 * (((i) * (cols + 2 * n)) + j)+2] = img[3 * ((rows - 1 - (i - (n + rows - 1))) * cols + (n - j - 1))+2];

				}
				else if ((i >= rows + n - 1 && j >= cols + n - 1)) {//오른쪽 아래 대각선

					dst[3*((( i) * (cols + 2 * n)) + j)] = img[3*(((rows - 1 - (i - (n + rows - 1))) * cols) + cols - 1 - (j - (n + cols - 1)))];
					dst[3 * (((i) * (cols + 2 * n)) + j)+1] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + cols - 1 - (j - (n + cols - 1)))+1];
					dst[3 * (((i) * (cols + 2 * n)) + j)+2] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + cols - 1 - (j - (n + cols - 1)))+2];


				}
				else if ((i < n && j >= n && j <= n + cols - 1)) {// 위

					dst[3*((i) * (cols + 2 * n) + j)] = img[3*((( (n - i - 1)) * cols) + j - n)];
					dst[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * ((((n - i - 1)) * cols) + j - n)+1];
					dst[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * ((((n - i - 1)) * cols) + j - n)+2];


				}
				else if ((i >= rows + n - 1 && j >= n && j <= n + cols - 1)) {//아래
					dst[3*(( i) * (cols + 2 * n) + j)] = img[3*(((rows - 1 - (i - (n + rows - 1))) * cols) + j - n)];

					dst[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + j - n)+1];
					dst[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + j - n)+2];
				}
				else if ((i >= n && i <= rows + n - 1 && j < n)) {//왼쪽
					if (rows < rows + n - 1) {
						dst[3*(( i) * (cols + 2 * n) + j)] = img[3*((( i - n) * cols) + (n - j - 1))];
						dst[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * (((i - n) * cols) + (n - j - 1))+1];
						dst[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * (((i - n) * cols) + (n - j - 1))+2];
					}
					else {
						dst[3*(( i) * (cols + 2 * n) + j)] = img[3*((( i)*cols) + 2 * (n - j - 1))];
						dst[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * (((i)*cols) + 2 * (n - j - 1))+1];
						dst[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * (((i)*cols) + 2 * (n - j - 1))+2];


					}
				}
				else if ((i >= n && i <= rows + n - 1 && j >= cols + n - 1)) {//오른쪽
					if (rows < rows + n - 1) {
						dst[3*(( i) * (cols + 2 * n) + j)] = img[3*((( i - n) * cols) + cols - 1 - (j - (n + cols - 1)))];
						dst[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * (((i - n) * cols) + cols - 1 - (j - (n + cols - 1)))+1];
						dst[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * (((i - n) * cols) + cols - 1 - (j - (n + cols - 1)))+2];

					}
					else {
						dst[3*(( i) * (cols + 2 * n) + j)] = img[3*((( i)*cols) + cols - 1 - (j - (n + cols - 1)))];
						dst[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * (((i)*cols) + cols - 1 - (j - (n + cols - 1)))+1];
						dst[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * (((i)*cols) + cols - 1 - (j - (n + cols - 1)))+2];

					}
				}
				else {//복사하는 부분
					if (i - n < rows) {//정상적으로 복사

						dst[3*(((i) * (cols + 2 * n)) + j)] = img[3*((( i - n) * cols) + j - n)];
						dst[3 * (((i) * (cols + 2 * n)) + j)+1] = img[3 * (((i - n) * cols) + j - n)+1];
						dst[3 * (((i) * (cols + 2 * n)) + j)+2] = img[3 * (((i - n) * cols) + j - n)+2];

					}
					else {//원본의 맨 아랫줄을 복사하는 경우 예외 처리

						dst[3*(((i) * (cols + 2 * n)) + j)] = img[3*(((i - 2 * n) * cols) + j - 2 * n)];
						dst[3 * (((i) * (cols + 2 * n)) + j)+1] = img[3 * (((i - 2 * n) * cols) + j - 2 * n)+1];
						dst[3 * (((i) * (cols + 2 * n)) + j)+2] = img[3 * (((i - 2 * n) * cols) + j - 2 * n)+2];
					}
				}
			}
	}
}


void GrayAverage(unsigned char* img,unsigned char* dst,int rows,int cols,int n) {

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc(pad_rows * pad_cols, 0);
		
	GrayPadding(img,pad,rows, cols, n);

	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {

			int mirror_padding_gray_tmp = 0;

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {;

					mirror_padding_gray_tmp += pad[(i - n + a) * pad_cols + (j - n + b)];			

				}
			}
			dst[(i - n) * (pad_cols-2*n) + (j - n)] = mirror_padding_gray_tmp / ((2 * n + 1) * (2 * n + 1));
		}
	}

	MemFree(pad);
}

void ColorAverage(unsigned char* img, unsigned char* dst,int rows, int cols, int n) {

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc(3*pad_rows * pad_cols, 0);

	ColorPadding(img,pad, rows, cols, n);

	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {

			int mirror_padding_red_tmp = 0;
			int mirror_padding_green_tmp = 0;
			int mirror_padding_blue_tmp = 0;

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
	
					mirror_padding_blue_tmp += pad[3*((i - n + a) * pad_cols + (j - n + b))];
					mirror_padding_green_tmp += pad[3*((i - n + a) * pad_cols + (j - n + b))+1];
					mirror_padding_red_tmp += pad[3*((i - n + a) * pad_cols + (j - n + b))+2];

				}
			}
			dst[3*((i - n) * (pad_cols - 2 * n) + (j - n))] = mirror_padding_blue_tmp / ((2 * n + 1) * (2 * n + 1));
			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n))+1] = mirror_padding_green_tmp / ((2 * n + 1) * (2 * n + 1));
			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n))+2] = mirror_padding_red_tmp / ((2 * n + 1) * (2 * n + 1));
		}
	}

	MemFree(pad);
}

void GraySharpening(unsigned char* img,unsigned char* dst, int rows, int cols, double* kernel,int n) {

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc(pad_rows * pad_cols, 0);

	GrayPadding(img, pad, rows, cols, n);

	unsigned char* laplacian = MemAlloc((pad_rows - 2 * n) * (pad_cols - 2 * n), 0);

	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			int mirror_laplacian_gray_tmp = 0;

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					mirror_laplacian_gray_tmp += pad[(i - n + a) * pad_cols + (j - n + b)] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];

				}
			}

			laplacian[(i - n) * (pad_cols-2*n) + (j - n)] = std::max(0, std::min(255, mirror_laplacian_gray_tmp));
		}
	}

	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			dst[(i - n) * (pad_cols-2*n) + (j - n)] = std::max(0, std::min(255, pad[i * pad_cols + j] - laplacian[(i - n) * (pad_cols-2*n) + j - n]));
		}
	}

	MemFree(laplacian);
	MemFree(pad);
	
}


void ColorSharpening(unsigned char* img, unsigned char* dst, int rows, int cols,double* kernel ,int n) {
	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc(3*pad_rows * pad_cols, 0);
	ColorPadding(img, pad, rows, cols, n);

	unsigned char* laplacian = MemAlloc(3 * (pad_rows -2* n) * (pad_cols - 2 * n), 0);

	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			int mirror_laplacian_red_tmp = 0;
			int mirror_laplacian_green_tmp = 0;
			int mirror_laplacian_blue_tmp = 0;

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					mirror_laplacian_red_tmp += pad[3*((i - n + a) * pad_cols + (j - n + b))+2] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];
					mirror_laplacian_green_tmp += pad[3 * ((i - n + a) * pad_cols + (j - n + b)) + 1] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];
					mirror_laplacian_blue_tmp += pad[3 * ((i - n + a) * pad_cols + (j - n + b))] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];

				}
			}

			laplacian[3*((i - n) * (pad_cols - 2 * n) + (j - n))+2] = std::max(0, std::min(255, mirror_laplacian_red_tmp));
			laplacian[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = std::max(0, std::min(255, mirror_laplacian_green_tmp));
			laplacian[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) ] = std::max(0, std::min(255, mirror_laplacian_blue_tmp));
		}
	}

	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			dst[3*((i - n) * (pad_cols - 2 * n) + (j - n))+2] = std::max(0, std::min(255, pad[3*(i * pad_cols + j)+2] - laplacian[3*((i - n) * (pad_cols - 2 * n) + j - n)+2]));
			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = std::max(0, std::min(255, pad[3 * (i * pad_cols + j) + 1] - laplacian[3 * ((i - n) * (pad_cols - 2 * n) + j - n) + 1]));
			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n))] = std::max(0, std::min(255, pad[3 * (i * pad_cols + j)] - laplacian[3 * ((i - n) * (pad_cols - 2 * n) + j - n) ]));
		}
	}

	MemFree(laplacian);
	MemFree(pad);
}


void GraySmoothing(unsigned char* img, unsigned char* dst,int rows, int cols,int n) {
	double kernel[9] ={
		1.0/16.0, 2.0/16.0, 1.0/16.0,
		2.0/16.0, 4.0/16.0, 2.0/16.0,
		1.0/16.0, 2.0/16.0, 1.0/16.0};

	n = 1;
	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc(pad_rows * pad_cols, 0); 
	GrayPadding(img,pad, rows, cols, n);


	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			double mirror_smooth_gray_tmp = 0;

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					mirror_smooth_gray_tmp += pad[((i - n + a) * pad_cols + (j - n + b))] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];
				

				}
			}

			dst[((i - n) * (pad_cols - 2 * n) + (j - n))] = std::max(0, std::min(255, (int)mirror_smooth_gray_tmp));
		}
	}

	MemFree(pad);

}

void ColorSmoothing(unsigned char* img,unsigned char* dst, int rows, int cols, int n) {
	double kernel[9] = {
		1 / 16.f, 2 / 16.f, 1 / 16.f,
			2 / 16.f ,4 / 16.f, 2 / 16.f,
			1 / 16.f, 2 / 16.f, 1 / 16.f};

	n = 1;

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc(3 * pad_rows * pad_cols, 0);
	ColorPadding(img, pad,rows, cols, n);


	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			double mirror_smooth_red_tmp = 0;
			double mirror_smooth_green_tmp = 0;
			double mirror_smooth_blue_tmp = 0;

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					mirror_smooth_red_tmp += pad[3*((i - n + a) * pad_cols + (j - n + b))+2] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];
					mirror_smooth_green_tmp += pad[3 * ((i - n + a) * pad_cols + (j - n + b)) + 1] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];
					mirror_smooth_blue_tmp += pad[3 * ((i - n + a) * pad_cols + (j - n + b))] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];
				}
			}

			dst[3*((i - n) * (pad_cols - 2 * n) + (j - n))+2] = std::max(0, std::min(255, (int)mirror_smooth_red_tmp));
			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = std::max(0, std::min(255, (int)mirror_smooth_green_tmp));
			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) ] = std::max(0, std::min(255, (int)mirror_smooth_blue_tmp));
		}
	}

	MemFree(pad);

}

void GrayFiltering(unsigned char* img,unsigned char* dst,int rows,int cols,double* kernel,int n) {

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc(pad_rows * pad_cols, 0);
	GrayPadding(img, pad, rows, cols, n);

	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			double mirror_tmp = 0;


			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					mirror_tmp += pad[ ((i - n + a) * pad_cols + (j - n + b))] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];
				
				}
			}

			dst[ ((i - n) * (pad_cols - 2 * n) + (j - n)) ] = std::max(0, std::min(255, (int)mirror_tmp));

		}
	}

	MemFree(pad);
}

void ColorFiltering(unsigned char* img,unsigned char* dst, int rows, int cols, double* kernel, int n) {
	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc(3*pad_rows * pad_cols, 0);
	ColorPadding(img, pad, rows, cols, n);

	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			double mirror_red_tmp = 0;
			double mirror_green_tmp = 0;
			double mirror_blue_tmp = 0;

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					mirror_red_tmp += pad[3 * ((i - n + a) * pad_cols + (j - n + b)) + 2] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];
					mirror_green_tmp += pad[3 * ((i - n + a) * pad_cols + (j - n + b)) + 1] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];
					mirror_blue_tmp += pad[3 * ((i - n + a) * pad_cols + (j - n + b))] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];
				}
			}

			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 2] = std::max(0, std::min(255, (int)mirror_red_tmp));
			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = std::max(0, std::min(255, (int)mirror_green_tmp));
			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n))] = std::max(0, std::min(255, (int)mirror_blue_tmp));
		}
	}

	MemFree(pad);
}

void GrayGeometricMeanFilter(unsigned char* img,unsigned char* dst, int rows, int cols, int n) {
	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc(pad_rows * pad_cols, 0);
	GrayPadding(img, pad, rows, cols, n);

	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			double mirror_tmp = 1;


			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					mirror_tmp *= pad[((i - n + a) * pad_cols + (j - n + b))];
				}
			}

			double result=std::pow(mirror_tmp, 1 /((2 * n + 1) * (2 * n + 1)));

			dst[((i - n) * (pad_cols - 2 * n) + (j - n))] = std::max(0, std::min(255, (int)result));

		}
	}
	MemFree(pad);
}

void ColorGeometricMeanFilter(unsigned char* img,unsigned char* dst, int rows, int cols, int n) {
	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc(3 * pad_rows * pad_cols, 0);
	ColorPadding(img, pad, rows, cols, n);


	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			double mirror_red_tmp = 1;
			double mirror_green_tmp = 1;
			double mirror_blue_tmp = 1;

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					mirror_red_tmp *= pad[3 * ((i - n + a) * pad_cols + (j - n + b)) + 2];
					mirror_green_tmp *= pad[3 * ((i - n + a) * pad_cols + (j - n + b)) + 1];
					mirror_blue_tmp *= pad[3 * ((i - n + a) * pad_cols + (j - n + b))];
				}
			}

			mirror_red_tmp=std::pow(mirror_red_tmp, 1 / ((2 * n + 1) * (2 * n + 1)));
			mirror_green_tmp=std::pow(mirror_green_tmp, 1 / ((2 * n + 1) * (2 * n + 1)));
			mirror_blue_tmp=std::pow(mirror_blue_tmp, 1 / ((2 * n + 1) * (2 * n + 1)));


			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 2] = std::max(0, std::min(255, (int)mirror_red_tmp));
			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = std::max(0, std::min(255, (int)mirror_green_tmp));
			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n))] = std::max(0, std::min(255, (int)mirror_blue_tmp));
		}
	}

	MemFree(pad);
}

void ColorMedianFilter(unsigned char* src,unsigned char* dst,int rows,int cols,int n) {

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc(3 * pad_rows * pad_cols, 0);
	ColorPadding(src, pad, rows, cols, n);


	unsigned char* filterR = MemAlloc((2 * n + 1) * (2 * n + 1), 0);
	unsigned char* filterG = MemAlloc((2 * n + 1) * (2 * n + 1), 0);
	unsigned char* filterB = MemAlloc((2 * n + 1) * (2 * n + 1), 0);
	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					filterB[(a * (2 * n + 1) + b)] = pad[3 * ((i - n + a) * pad_cols + (j - n + b))];
					filterG[(a * (2 * n + 1) + b) + 1] = pad[3 * ((i - n + a) * pad_cols + (j - n + b)) + 1];
					filterR[(a * (2 * n + 1) + b) + 1] = pad[3 * ((i - n + a) * pad_cols + (j - n + b)) + 2];
				}
			}

			std::sort(filterR, filterR + (2 * n + 1) * (2 * n + 1));
			std::sort(filterG, filterG + (2 * n + 1) * (2 * n + 1));
			std::sort(filterB, filterB + (2 * n + 1) * (2 * n + 1));

			int median = ((2 * n + 1) * (2 * n + 1)) / 2;

			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n))] = filterB[median];
			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = filterG[median];
			dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 2] = filterR[median];

		}
	}

	MemFree(pad);
}

void GrayMedianFilter(unsigned char* src,unsigned char* dst, int rows, int cols, int n) {

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc( pad_rows * pad_cols, 0);
	GrayPadding(src, pad, rows, cols, n);

	unsigned char* filter = (unsigned char*)malloc(sizeof(unsigned char) * (2 * n + 1) * (2 * n + 1));
	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					filter[(a * (2 * n + 1) + b)] = pad[((i - n + a) * pad_cols + (j - n + b))];
				}
			}
			std::sort(filter, filter + (2 * n + 1) * (2 * n + 1));


			int median = ((2 * n + 1) * (2 * n + 1)) / 2;

			dst[((i - n) * (pad_cols - 2 * n) + (j - n))] = filter[median];
		}
	}

	free(filter);
	MemFree(pad);

}

void GrayAdaptiveMedianFilter(unsigned char* src, unsigned char* dst, int rows, int cols, int MaxN) {
	int n=1;
	
	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc(pad_rows * pad_cols, 0);
	GrayPadding(src, pad, rows, cols, n);


	unsigned char* filter = (unsigned char*)malloc(sizeof(unsigned char) * (2 * n + 1) * (2 * n + 1));


	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					filter[(a * (2 * n + 1) + b)] = pad[((i - n + a) * pad_cols + (j - n + b))];
				}
			}

			std::sort(filter, filter + (2 * n + 1) * (2 * n + 1));

			int median = ((2 * n + 1) * (2 * n + 1)) / 2;
			int Zxy = pad[i * pad_cols + j];
			int Zmin = filter[0];
			int Zmax = filter[(2 * n + 1) * (2 * n + 1) - 1];

			int A1 = filter[median] - Zmin;
			int A2 = filter[median] - Zmax;
			if (A1 > 0 && A2 < 0) {
				int B1 = Zxy - Zmin;
				int B2 = Zxy - Zmax;
				if (B1 > 0 && B2 < 0) {
					dst[((i - n) * (pad_cols - 2 * n) + (j - n))] = Zxy;
				}
				else {
					dst[((i - n) * (pad_cols - 2 * n) + (j - n))] = filter[median];
				}

			}
			else {
				if (n == MaxN) {
					dst[((i - n) * (pad_cols - 2 * n) + (j - n))] = Zxy;
				}
				else {
					int j_distance = j - n;
					int i_distance = i - n;
					n += 1;

					MemFree(pad);

					pad_rows = rows + 2 * n;
					pad_cols = cols + 2 * n;

					pad = MemAlloc(pad_rows * pad_cols, 0);
					GrayPadding(src, pad, rows, cols, n);

					free(filter);
					filter = (unsigned char*)malloc(sizeof(unsigned char) * (2 * n + 1) * (2 * n + 1));

					j = n - 1 + j_distance;
					i = n + i_distance;
				}
			}
		}
	}
	
	MemFree(pad);
	free(filter);
}

void ColorAdaptiveMedianFilter(unsigned char* src, unsigned char* dst, int rows, int cols, int MaxN) {
	int n = 1;

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* pad = MemAlloc(3*pad_rows * pad_cols, 0);
	ColorPadding(src, pad, rows, cols, n);


	unsigned char* filterR = (unsigned char*)malloc(sizeof(unsigned char) * (2 * n + 1) * (2 * n + 1));
	unsigned char* filterG = (unsigned char*)malloc(sizeof(unsigned char) * (2 * n + 1) * (2 * n + 1));
	unsigned char* filterB = (unsigned char*)malloc(sizeof(unsigned char) * (2 * n + 1) * (2 * n + 1));



	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					filterR[(a * (2 * n + 1) + b)] = pad[3*((i - n + a) * pad_cols + (j - n + b))+2];
					filterG[(a * (2 * n + 1) + b)] = pad[3*((i - n + a) * pad_cols + (j - n + b))+1];
					filterB[(a * (2 * n + 1) + b)] = pad[3*((i - n + a) * pad_cols + (j - n + b))];
				}
			}

			std::sort(filterR, filterR + (2 * n + 1) * (2 * n + 1));
			std::sort(filterG, filterG + (2 * n + 1) * (2 * n + 1));
			std::sort(filterB, filterB + (2 * n + 1) * (2 * n + 1));

			int median = ((2 * n + 1) * (2 * n + 1)) / 2;

			int ZxyR = pad[3*(i * pad_cols + j)+2];
			int ZxyG = pad[3 * (i * pad_cols + j) +1];
			int ZxyB = pad[3 * (i * pad_cols + j)];

			int ZminR = filterR[0];
			int ZmaxR = filterR[(2 * n + 1) * (2 * n + 1) - 1];
			int ZminG = filterG[0];
			int ZmaxG = filterG[(2 * n + 1) * (2 * n + 1) - 1];
			int ZminB = filterB[0];
			int ZmaxB = filterB[(2 * n + 1) * (2 * n + 1) - 1];

			int A1R = filterR[median] - ZminR;
			int A2R = filterR[median] - ZmaxR;

			int A1G = filterG[median] - ZminG;
			int A2G = filterG[median] - ZmaxG;

			int A1B = filterB[median] - ZminB;
			int A2B = filterB[median] - ZmaxB;

			if ((A1R > 0 && A2R < 0)&&(A1G>0 && A2G<0)&&(A1B>0&&A2G<0)){
				int B1R = ZxyR - ZminR;
				int B2R = ZxyR - ZmaxR;

				int B1G = ZxyG - ZminG;
				int B2G = ZxyG - ZmaxG;

				int B1B = ZxyB - ZminB;
				int B2B = ZxyB - ZmaxB;

				if ((B1R > 0 && B2R < 0) && (B1G > 0 && B2G < 0) && (B1B > 0 && B2G < 0)) {
					dst[3*((i - n) * (pad_cols - 2 * n) + (j - n))+2] = ZxyR;
					dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = ZxyG;
					dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) ] = ZxyB;
				}
				else {
					dst[3*((i - n) * (pad_cols - 2 * n) + (j - n))+2] = filterR[median];
					dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = filterG[median];
					dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) ] = filterB[median];
				}

			}
			else {
				if (n == MaxN) {
					dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 2] = ZxyR;
					dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = ZxyG;
					dst[3 * ((i - n) * (pad_cols - 2 * n) + (j - n))] = ZxyB;
				}
				else {
					int j_distance = j - n;
					int i_distance = i - n;
					n += 1;
					MemFree(pad);
					pad_rows = rows + 2 * n;
					pad_cols = cols + 2 * n;
					pad = MemAlloc(3 * pad_rows * pad_cols, 0);
					ColorPadding(src, pad, rows, cols, n);
					free(filterR);
					free(filterG);
					free(filterB);
					filterR = (unsigned char*)malloc(sizeof(unsigned char) * (2 * n + 1) * (2 * n + 1));
					filterG = (unsigned char*)malloc(sizeof(unsigned char) * (2 * n + 1) * (2 * n + 1));
					filterB = (unsigned char*)malloc(sizeof(unsigned char) * (2 * n + 1) * (2 * n + 1));
					j = n - 1 + j_distance;
					i = n + i_distance;
				}
			}
		}
	}
	MemFree(pad);
	free(filterR);
	free(filterG);
	free(filterB);
}
