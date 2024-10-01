#include <opencv2/opencv.hpp>

unsigned char* GrayPadding(unsigned char* img, int rows, int cols, int n) {
	unsigned char* mirror_padding_gray = MemAlloc((rows + 2 * n) * (cols + 2 * n), 0);

	for (int i = 0; i < rows + 2 * n; i++) {
		for (int j = 0; j < cols + 2 * n; j++) {

			if ((i < n && j < n)) {//왼쪽 위 대각선

				mirror_padding_gray[((i) * (cols + 2 * n)) + j] = img[(((n - i - 1)) * cols) + (n - j - 1)];

			}
			else if ((i < n && j >= cols + n - 1)) {//오른쪽 위 대각선

				mirror_padding_gray[(i) * (cols + 2 * n) + j] = img[(((n - i - 1)) * cols) + cols - 1 - (j - (n + cols - 1))];


			}
			else if ((i >= rows + n - 1 && j < n)) {//왼쪽 아래 대각선

				mirror_padding_gray[((i) * (cols + 2 * n)) + j] = img[(rows - 1 - (i - (n + rows - 1))) * cols + (n - j - 1)];

			}
			else if ((i >= rows + n - 1 && j >= cols + n - 1)) {//오른쪽 아래 대각선

				mirror_padding_gray[((i) * (cols + 2 * n)) + j] = img[((rows - 1 - (i - (n + rows - 1))) * cols) + cols - 1 - (j - (n + cols - 1))];


			}
			else if ((i < n && j >= n && j <= n + cols - 1)) {// 위

				mirror_padding_gray[(i) * (cols + 2 * n) + j] = img[(((n - i - 1)) * cols) + j - n];


			}
			else if ((i >= rows + n - 1 && j >= n && j <= n + cols - 1)) {//아래
				mirror_padding_gray[(i) * (cols + 2 * n) + j] = img[((rows - 1 - (i - (n + rows - 1))) * cols) + j - n];


			}
			else if ((i >= n && i <= rows + n - 1 && j < n)) {//왼쪽
				if (rows < rows + n - 1) {
					mirror_padding_gray[(i) * (cols + 2 * n) + j] = img[((i - n) * cols) + (n - j - 1)];
				}
				else {
					mirror_padding_gray[(i) * (cols + 2 * n) + j] = img[((i)*cols) + 2 * (n - j - 1)];


				}
			}
			else if ((i >= n && i <= rows + n - 1 && j >= cols + n - 1)) {//오른쪽
				if (rows < rows + n - 1) {
					mirror_padding_gray[(i) * (cols + 2 * n) + j] = img[((i - n) * cols) + cols - 1 - (j - (n + cols - 1))];

				}
				else {
					mirror_padding_gray[(i) * (cols + 2 * n) + j] = img[((i)*cols) + cols - 1 - (j - (n + cols - 1))];

				}
			}
			else {//복사하는 부분
				if (i - n < rows) {//정상적으로 복사

					mirror_padding_gray[((i) * (cols + 2 * n)) + j] = img[((i - n) * cols) + j - n];

				}
				else {//원본의 맨 아랫줄을 복사하는 경우 예외 처리

					mirror_padding_gray[((i) * (cols + 2 * n)) + j] = img[((i - 2 * n) * cols) + j - 2 * n];

				}
			}
		}
	}
	return mirror_padding_gray;
}

unsigned char* ColorPadding(unsigned char* img, int rows, int cols, int n) {

	//프로그레시브 rgb

	unsigned char* mirror_padding_rgb = MemAlloc(3*(rows + 2 * n) * (cols + 2 * n), 0);

		
		for (int i = 0; i < rows + 2 * n; i++) {
			for (int j = 0; j < cols + 2 * n; j++) {

				if ((i < n && j < n)) {//왼쪽 위 대각선

					mirror_padding_rgb[3*(((i) * (cols + 2 * n)) + j)] = img[3*((((n - i - 1)) * cols) + (n - j - 1))];
					mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)+1] = img[3 * ((((n - i - 1)) * cols) + (n - j - 1))+1];
					mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)+2] = img[3 * ((((n - i - 1)) * cols) + (n - j - 1))+2];

				}
				else if ((i < n && j >= cols + n - 1)) {//오른쪽 위 대각선

					mirror_padding_rgb[3*((i) * (cols + 2 * n) + j)] = img[3*(((( + n - i - 1)) * cols) + cols - 1 - (j - (n + cols - 1)))];
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * ((((+n - i - 1)) * cols) + cols - 1 - (j - (n + cols - 1)))+1];
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * ((((+n - i - 1)) * cols) + cols - 1 - (j - (n + cols - 1)))+2];


				}
				else if ((i >= rows + n - 1 && j < n)) {//왼쪽 아래 대각선

					mirror_padding_rgb[3*(((  i) * (cols + 2 * n)) + j)] = img[3*(( rows - 1 - (i - (n + rows - 1))) * cols + (n - j - 1))];
					mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)+1] = img[3 * ((rows - 1 - (i - (n + rows - 1))) * cols + (n - j - 1))+1];
					mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)+2] = img[3 * ((rows - 1 - (i - (n + rows - 1))) * cols + (n - j - 1))+2];

				}
				else if ((i >= rows + n - 1 && j >= cols + n - 1)) {//오른쪽 아래 대각선

					mirror_padding_rgb[3*((( i) * (cols + 2 * n)) + j)] = img[3*(((rows - 1 - (i - (n + rows - 1))) * cols) + cols - 1 - (j - (n + cols - 1)))];
					mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)+1] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + cols - 1 - (j - (n + cols - 1)))+1];
					mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)+2] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + cols - 1 - (j - (n + cols - 1)))+2];


				}
				else if ((i < n && j >= n && j <= n + cols - 1)) {// 위

					mirror_padding_rgb[3*((i) * (cols + 2 * n) + j)] = img[3*((( (n - i - 1)) * cols) + j - n)];
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * ((((n - i - 1)) * cols) + j - n)+1];
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * ((((n - i - 1)) * cols) + j - n)+2];


				}
				else if ((i >= rows + n - 1 && j >= n && j <= n + cols - 1)) {//아래
					mirror_padding_rgb[3*(( i) * (cols + 2 * n) + j)] = img[3*(((rows - 1 - (i - (n + rows - 1))) * cols) + j - n)];

					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + j - n)+1];
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + j - n)+2];
				}
				else if ((i >= n && i <= rows + n - 1 && j < n)) {//왼쪽
					if (rows < rows + n - 1) {
						mirror_padding_rgb[3*(( i) * (cols + 2 * n) + j)] = img[3*((( i - n) * cols) + (n - j - 1))];
						mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * (((i - n) * cols) + (n - j - 1))+1];
						mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * (((i - n) * cols) + (n - j - 1))+2];
					}
					else {
						mirror_padding_rgb[3*(( i) * (cols + 2 * n) + j)] = img[3*((( i)*cols) + 2 * (n - j - 1))];
						mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * (((i)*cols) + 2 * (n - j - 1))+1];
						mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * (((i)*cols) + 2 * (n - j - 1))+2];


					}
				}
				else if ((i >= n && i <= rows + n - 1 && j >= cols + n - 1)) {//오른쪽
					if (rows < rows + n - 1) {
						mirror_padding_rgb[3*(( i) * (cols + 2 * n) + j)] = img[3*((( i - n) * cols) + cols - 1 - (j - (n + cols - 1)))];
						mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * (((i - n) * cols) + cols - 1 - (j - (n + cols - 1)))+1];
						mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * (((i - n) * cols) + cols - 1 - (j - (n + cols - 1)))+2];

					}
					else {
						mirror_padding_rgb[3*(( i) * (cols + 2 * n) + j)] = img[3*((( i)*cols) + cols - 1 - (j - (n + cols - 1)))];
						mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+1] = img[3 * (((i)*cols) + cols - 1 - (j - (n + cols - 1)))+1];
						mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)+2] = img[3 * (((i)*cols) + cols - 1 - (j - (n + cols - 1)))+2];

					}
				}
				else {//복사하는 부분
					if (i - n < rows) {//정상적으로 복사

						mirror_padding_rgb[3*(((i) * (cols + 2 * n)) + j)] = img[3*((( i - n) * cols) + j - n)];
						mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)+1] = img[3 * (((i - n) * cols) + j - n)+1];
						mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)+2] = img[3 * (((i - n) * cols) + j - n)+2];

					}
					else {//원본의 맨 아랫줄을 복사하는 경우 예외 처리

						mirror_padding_rgb[3*(((i) * (cols + 2 * n)) + j)] = img[3*(((i - 2 * n) * cols) + j - 2 * n)];
						mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)+1] = img[3 * (((i - 2 * n) * cols) + j - 2 * n)+1];
						mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)+2] = img[3 * (((i - 2 * n) * cols) + j - 2 * n)+2];
					}
				}
			}
	}
	return mirror_padding_rgb;
}


unsigned char* GrayAverage(unsigned char* img,int rows,int cols,int n) {
	unsigned char* pad = GrayPadding(img, rows, cols, n);

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* output = MemAlloc((pad_rows - 2 * n) * (pad_cols - 2 * n), 0);
	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {

			int mirror_padding_gray_tmp = 0;

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {;

					mirror_padding_gray_tmp += pad[(i - n + a) * pad_cols + (j - n + b)];			

				}
			}
			output[(i - n) * (pad_cols-2*n) + (j - n)] = mirror_padding_gray_tmp / ((2 * n + 1) * (2 * n + 1));
		}
	}

	return output;
}

unsigned char* ColorAverage(unsigned char* img, int rows, int cols, int n) {
	unsigned char* pad = ColorPadding(img, rows, cols, n);

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* output = MemAlloc(3*(pad_rows - 2 * n) * (pad_cols - 2 * n), 0);
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
			output[3*((i - n) * (pad_cols - 2 * n) + (j - n))] = mirror_padding_blue_tmp / ((2 * n + 1) * (2 * n + 1));
			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n))+1] = mirror_padding_green_tmp / ((2 * n + 1) * (2 * n + 1));
			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n))+2] = mirror_padding_red_tmp / ((2 * n + 1) * (2 * n + 1));
		}
	}

	return output;
}

unsigned char* GraySharpening(unsigned char* img, int rows, int cols, double* kernel,int n) {

	unsigned char* pad = GrayPadding(img, rows, cols, n);
	
	int pad_rows = rows + 2*n;
	int pad_cols = cols + 2*n;

	unsigned char* laplacian = MemAlloc((pad_rows - 2 * n) * (pad_cols - 2 * n), 0);
	unsigned char* output = MemAlloc((pad_rows - 2 * n) * (pad_cols - 2 * n), 0);

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
			output[(i - n) * (pad_cols-2*n) + (j - n)] = std::max(0, std::min(255, pad[i * pad_cols + j] - laplacian[(i - n) * (pad_cols-2*n) + j - n]));
		}
	}


	return output;
	
}


unsigned char* ColorSharpening(unsigned char* img, int rows, int cols,double* kernel ,int n) {
	unsigned char* pad = ColorPadding(img, rows, cols, n);
	int pad_rows = rows + 2*n;
	int pad_cols = cols + 2*n;
	unsigned char* laplacian = MemAlloc(3 * (pad_rows -2* n) * (pad_cols - 2 * n), 0);
	unsigned char* output = MemAlloc(3 * (pad_rows -2* n) * (pad_cols - 2 * n), 0);

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
			output[3*((i - n) * (pad_cols - 2 * n) + (j - n))+2] = std::max(0, std::min(255, pad[3*(i * pad_cols + j)+2] - laplacian[3*((i - n) * (pad_cols - 2 * n) + j - n)+2]));
			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = std::max(0, std::min(255, pad[3 * (i * pad_cols + j) + 1] - laplacian[3 * ((i - n) * (pad_cols - 2 * n) + j - n) + 1]));
			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n))] = std::max(0, std::min(255, pad[3 * (i * pad_cols + j)] - laplacian[3 * ((i - n) * (pad_cols - 2 * n) + j - n) ]));
		}
	}


	return output;
}


unsigned char* GraySmoothing(unsigned char* img, int rows, int cols,int n) {
	double* kernel= new double[9] {
		1.0/16.0, 2.0/16.0, 1.0/16.0,
		2.0/16.0, 4.0/16.0, 2.0/16.0,
		1.0/16.0, 2.0/16.0, 1.0/16.0};

	n = 1;

	unsigned char* pad = GrayPadding(img, rows, cols, n);

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* output = MemAlloc((pad_rows - 2*n) * (pad_cols - 2*n), 0);

	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			double mirror_smooth_gray_tmp = 0;

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					mirror_smooth_gray_tmp += pad[((i - n + a) * pad_cols + (j - n + b))] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];
				

				}
			}

			output[((i - n) * (pad_cols - 2 * n) + (j - n))] = std::max(0, std::min(255, (int)mirror_smooth_gray_tmp));
		}
	}

	return output;
}

unsigned char* ColorSmoothing(unsigned char* img, int rows, int cols, int n) {
	double* kernel = new double[9] {
		1 / 16.f, 2 / 16.f, 1 / 16.f,
			2 / 16.f ,4 / 16.f, 2 / 16.f,
			1 / 16.f, 2 / 16.f, 1 / 16.f};

	n = 1;

	unsigned char* pad = GrayPadding(img, rows, cols, n);

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;


	unsigned char* output = MemAlloc(3*(pad_rows - 2 * n) * (pad_cols - 2 * n), 0);

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

			output[3*((i - n) * (pad_cols - 2 * n) + (j - n))+2] = std::max(0, std::min(255, (int)mirror_smooth_red_tmp));
			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = std::max(0, std::min(255, (int)mirror_smooth_green_tmp));
			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) ] = std::max(0, std::min(255, (int)mirror_smooth_blue_tmp));
		}
	}

	return output;
}

unsigned char* GrayFiltering(unsigned char* img,int rows,int cols,double* kernel,int n) {
	unsigned char* pad = GrayPadding(img, rows, cols, n);

	int pad_rows = rows + 2*n;
	int pad_cols = cols + 2*n;

	unsigned char* output = MemAlloc( (pad_rows - 2 * n) * (pad_cols - 2 * n), 0);
	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			double mirror_tmp = 0;


			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					mirror_tmp += pad[ ((i - n + a) * pad_cols + (j - n + b))] * kernel[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];
				
				}
			}

			output[ ((i - n) * (pad_cols - 2 * n) + (j - n)) ] = std::max(0, std::min(255, (int)mirror_tmp));

		}
	}

	return output;
}

unsigned char* ColorFiltering(unsigned char* img, int rows, int cols, double* kernel, int n) {
	unsigned char* pad = ColorPadding(img, rows, cols, n);
	 
	int pad_rows = rows + 2*n;
	int pad_cols = cols + 2*n;

	unsigned char* output = MemAlloc(3 * (pad_rows - 2 * n) * (pad_cols - 2 * n), 0);

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

			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 2] = std::max(0, std::min(255, (int)mirror_red_tmp));
			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = std::max(0, std::min(255, (int)mirror_green_tmp));
			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n))] = std::max(0, std::min(255, (int)mirror_blue_tmp));
		}
	}

	return output;
}