#include <opencv2/opencv.hpp>
#include <random>
#include <algorithm>

unsigned char* Padding(unsigned char* img, int rows, int cols,int n) {


	unsigned char* mirror_padding_rgb = (unsigned char*)malloc(sizeof(unsigned char)*(3 * (rows + 2 * n) * (cols + 2 * n)));


	for (int i = 0; i < rows + 2 * n; i++) {
		for (int j = 0; j < cols + 2 * n; j++) {

			if ((i < n && j < n)) {//왼쪽 위 대각선

				mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)] = img[3 * ((((n - i - 1)) * cols) + (n - j - 1))];
				mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j) + 1] = img[3 * ((((n - i - 1)) * cols) + (n - j - 1)) + 1];
				mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j) + 2] = img[3 * ((((n - i - 1)) * cols) + (n - j - 1)) + 2];

			}
			else if ((i < n && j >= cols + n - 1)) {//오른쪽 위 대각선

				mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)] = img[3 * ((((+n - i - 1)) * cols) + cols - 1 - (j - (n + cols - 1)))];
				mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 1] = img[3 * ((((+n - i - 1)) * cols) + cols - 1 - (j - (n + cols - 1))) + 1];
				mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 2] = img[3 * ((((+n - i - 1)) * cols) + cols - 1 - (j - (n + cols - 1))) + 2];


			}
			else if ((i >= rows + n - 1 && j < n)) {//왼쪽 아래 대각선

				mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)] = img[3 * ((rows - 1 - (i - (n + rows - 1))) * cols + (n - j - 1))];
				mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j) + 1] = img[3 * ((rows - 1 - (i - (n + rows - 1))) * cols + (n - j - 1)) + 1];
				mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j) + 2] = img[3 * ((rows - 1 - (i - (n + rows - 1))) * cols + (n - j - 1)) + 2];

			}
			else if ((i >= rows + n - 1 && j >= cols + n - 1)) {//오른쪽 아래 대각선

				mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + cols - 1 - (j - (n + cols - 1)))];
				mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j) + 1] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + cols - 1 - (j - (n + cols - 1))) + 1];
				mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j) + 2] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + cols - 1 - (j - (n + cols - 1))) + 2];


			}
			else if ((i < n && j >= n && j <= n + cols - 1)) {// 위

				mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)] = img[3 * ((((n - i - 1)) * cols) + j - n)];
				mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 1] = img[3 * ((((n - i - 1)) * cols) + j - n) + 1];
				mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 2] = img[3 * ((((n - i - 1)) * cols) + j - n) + 2];


			}
			else if ((i >= rows + n - 1 && j >= n && j <= n + cols - 1)) {//아래
				mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + j - n)];

				mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 1] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + j - n) + 1];
				mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 2] = img[3 * (((rows - 1 - (i - (n + rows - 1))) * cols) + j - n) + 2];
			}
			else if ((i >= n && i <= rows + n - 1 && j < n)) {//왼쪽
				if (rows < rows + n - 1) {
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)] = img[3 * (((i - n) * cols) + (n - j - 1))];
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 1] = img[3 * (((i - n) * cols) + (n - j - 1)) + 1];
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 2] = img[3 * (((i - n) * cols) + (n - j - 1)) + 2];
				}
				else {
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)] = img[3 * (((i)*cols) + 2 * (n - j - 1))];
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 1] = img[3 * (((i)*cols) + 2 * (n - j - 1)) + 1];
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 2] = img[3 * (((i)*cols) + 2 * (n - j - 1)) + 2];


				}
			}
			else if ((i >= n && i <= rows + n - 1 && j >= cols + n - 1)) {//오른쪽
				if (rows < rows + n - 1) {
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)] = img[3 * (((i - n) * cols) + cols - 1 - (j - (n + cols - 1)))];
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 1] = img[3 * (((i - n) * cols) + cols - 1 - (j - (n + cols - 1))) + 1];
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 2] = img[3 * (((i - n) * cols) + cols - 1 - (j - (n + cols - 1))) + 2];

				}
				else {
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j)] = img[3 * (((i)*cols) + cols - 1 - (j - (n + cols - 1)))];
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 1] = img[3 * (((i)*cols) + cols - 1 - (j - (n + cols - 1))) + 1];
					mirror_padding_rgb[3 * ((i) * (cols + 2 * n) + j) + 2] = img[3 * (((i)*cols) + cols - 1 - (j - (n + cols - 1))) + 2];

				}
			}
			else {//복사하는 부분
				if (i - n < rows) {//정상적으로 복사

					mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)] = img[3 * (((i - n) * cols) + j - n)];
					mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j) + 1] = img[3 * (((i - n) * cols) + j - n) + 1];
					mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j) + 2] = img[3 * (((i - n) * cols) + j - n) + 2];

				}
				else {//원본의 맨 아랫줄을 복사하는 경우 예외 처리

					mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j)] = img[3 * (((i - 2 * n) * cols) + j - 2 * n)];
					mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j) + 1] = img[3 * (((i - 2 * n) * cols) + j - 2 * n) + 1];
					mirror_padding_rgb[3 * (((i) * (cols + 2 * n)) + j) + 2] = img[3 * (((i - 2 * n) * cols) + j - 2 * n) + 2];
				}
			}
		}
	}
	return mirror_padding_rgb;
}

unsigned char* MedianFilter(unsigned char* src,int rows,int cols,int n) {
	unsigned char* pad = Padding(src,rows,cols,n);


	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* output = (unsigned char*)malloc(sizeof(unsigned char) * (3 * (rows) * (cols)));

	unsigned char* filterR = (unsigned char*)malloc(sizeof(unsigned char) * (2 * n + 1) * (2 * n + 1));
	unsigned char* filterG = (unsigned char*)malloc(sizeof(unsigned char) * (2 * n + 1) * (2 * n + 1));
	unsigned char* filterB = (unsigned char*)malloc(sizeof(unsigned char) * (2 * n + 1) * (2 * n + 1));
	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					filterB[(a*(2*n+1) + b)] = pad[3 * ((i - n + a) * pad_cols + (j - n + b))];
					filterG[(a*(2*n+1)+b)+1] = pad[3 * ((i - n + a) * pad_cols + (j - n + b)) + 1];
					filterR[(a*(2*n+1)+b)+1] = pad[3 * ((i - n + a) * pad_cols + (j - n + b)) + 2];
				}
			}

			std::sort(filterR, filterR +  (2 * n + 1) * (2 * n + 1));
			std::sort(filterG, filterG + (2 * n + 1) * (2 * n + 1));
			std::sort(filterB, filterB + (2 * n + 1) * (2 * n + 1));

			int median = ((2 * n + 1) * (2 * n + 1)) / 2;

			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n))] = filterB[median];
			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = filterG[median];
			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 2] = filterR[median];

		}
	}

	return output;

}
unsigned char* MeanFilter(unsigned char* src,int rows,int cols,int n) {
	unsigned char* pad = Padding(src, rows, cols,n);



	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* output = (unsigned char*)malloc(sizeof(unsigned char) * (3 * (rows) * (cols)));

	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {

			int mirror_padding_red_tmp = 0;
			int mirror_padding_green_tmp = 0;
			int mirror_padding_blue_tmp = 0;

			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {

					mirror_padding_blue_tmp += pad[3 * ((i - n + a) * pad_cols + (j - n + b))];
					mirror_padding_green_tmp += pad[3 * ((i - n + a) * pad_cols + (j - n + b)) + 1];
					mirror_padding_red_tmp += pad[3 * ((i - n + a) * pad_cols + (j - n + b)) + 2];

				}
			}
			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n))] = mirror_padding_blue_tmp / ((2 * n + 1) * (2 * n + 1));
			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 1] = mirror_padding_green_tmp / ((2 * n + 1) * (2 * n + 1));
			output[3 * ((i - n) * (pad_cols - 2 * n) + (j - n)) + 2] = mirror_padding_red_tmp / ((2 * n + 1) * (2 * n + 1));
		}
	}

	return output;
}


int main(void) {
	cv::Mat input=cv::imread("Lena.png");

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 100);

	
	
	cv::Mat noise1=cv::Mat(input.rows,input.cols,CV_8UC3);
	cv::Mat noise2 = cv::Mat(input.rows, input.cols, CV_8UC3);

	cv::Mat firstGaussianNoise= cv::Mat(input.rows, input.cols, CV_8UC3);
	cv::Mat secondGaussianNoise = cv::Mat(input.rows, input.cols, CV_8UC3);

	cv::Mat firstSaltandpepperNoise = cv::Mat(input.rows, input.cols, CV_8UC3);
	cv::Mat secondSaltandpepperNoise = cv::Mat(input.rows, input.cols, CV_8UC3);

	cv::Mat first_gaussian_mean = cv::Mat(input.rows, input.cols, CV_8UC3);
	cv::Mat first_gaussian_median = cv::Mat(input.rows, input.cols, CV_8UC3);
	cv::Mat second_gaussian_mean = cv::Mat(input.rows, input.cols, CV_8UC3);
	cv::Mat second_gaussian_median = cv::Mat(input.rows, input.cols, CV_8UC3);

	cv::Mat first_saltandpepper_mean = cv::Mat(input.rows, input.cols, CV_8UC3);
	cv::Mat first_saltandpepper_median = cv::Mat(input.rows, input.cols, CV_8UC3);
	cv::Mat second_saltandpepper_mean = cv::Mat(input.rows, input.cols, CV_8UC3);
	cv::Mat second_saltandpepper_median = cv::Mat(input.rows, input.cols, CV_8UC3);


	cv::randn(noise1, 0, 20);
	cv::randn(noise2, 0, 55);
	

	for (int i = 0; i < 3 * input.rows * input.cols; i+=3) {
		firstGaussianNoise.data[i] = std::max(0, std::min(255, input.data[i] + noise1.data[i]));
		firstGaussianNoise.data[i+1] = std::max(0, std::min(255, input.data[i+1] + noise1.data[i+1]));
		firstGaussianNoise.data[i+2] = std::max(0, std::min(255, input.data[i+2] + noise1.data[i+2]));

		secondGaussianNoise.data[i] = std::max(0, std::min(255, input.data[i] + noise2.data[i]));
		secondGaussianNoise.data[i+1] = std::max(0, std::min(255, input.data[i+1] + noise2.data[i+1]));
		secondGaussianNoise.data[i+2] = std::max(0, std::min(255, input.data[i+2] + noise2.data[i+2]));

		int random_number = dis(gen);
		if (random_number <= 5) {
			firstSaltandpepperNoise.data[i] = 0;
			firstSaltandpepperNoise.data[i+1] = 0;
			firstSaltandpepperNoise.data[i+2] = 0;
		}
		else if (random_number >= 95) {
			firstSaltandpepperNoise.data[i] = 255;
			firstSaltandpepperNoise.data[i+1] = 255;
			firstSaltandpepperNoise.data[i+2] = 255;
		}
		else {
			firstSaltandpepperNoise.data[i] = input.data[i];
			firstSaltandpepperNoise.data[i+1] = input.data[i+1];
			firstSaltandpepperNoise.data[i+2] = input.data[i+2];
		}

		if (random_number <= 10) {
			secondSaltandpepperNoise.data[i] = 0;
			secondSaltandpepperNoise.data[i+1] = 0;
			secondSaltandpepperNoise.data[i+2] = 0;
		}
		else if (random_number >= 90) {
			secondSaltandpepperNoise.data[i] = 255;
			secondSaltandpepperNoise.data[i+1] = 255;
			secondSaltandpepperNoise.data[i+2] = 255;
		}
		else {
			secondSaltandpepperNoise.data[i] = input.data[i];
			secondSaltandpepperNoise.data[i+1] = input.data[i+1];
			secondSaltandpepperNoise.data[i+2] = input.data[i+2];
		}
		
	}

	int n = 2;

	first_gaussian_mean.data = MeanFilter(firstGaussianNoise.data, firstGaussianNoise.rows, firstGaussianNoise.cols,n);
	first_gaussian_median.data = MedianFilter(firstGaussianNoise.data, firstGaussianNoise.rows, firstGaussianNoise.cols,n);

	second_gaussian_mean.data = MeanFilter(secondGaussianNoise.data,secondGaussianNoise.rows, secondGaussianNoise.cols,n);
	second_gaussian_median.data = MedianFilter(secondGaussianNoise.data, secondGaussianNoise.rows, secondGaussianNoise.cols,n);

	first_saltandpepper_mean.data = MeanFilter(firstSaltandpepperNoise.data, firstSaltandpepperNoise.rows, firstSaltandpepperNoise.cols,n);
	first_saltandpepper_median.data = MedianFilter(firstSaltandpepperNoise.data, firstSaltandpepperNoise.rows, firstSaltandpepperNoise.cols,n);

	second_saltandpepper_mean.data = MeanFilter(secondSaltandpepperNoise.data, secondSaltandpepperNoise.rows, secondSaltandpepperNoise.cols,n);
	second_saltandpepper_median.data = MedianFilter(secondSaltandpepperNoise.data, secondSaltandpepperNoise.rows, secondSaltandpepperNoise.cols,n);



	cv::imwrite("first_gau.png", firstGaussianNoise);
	cv::imwrite("first_salt.png", firstSaltandpepperNoise);

	cv::imwrite("second_gau.png", secondGaussianNoise);
	cv::imwrite("second_salt.png", secondSaltandpepperNoise);

	cv::imwrite("mean_first_gau.png", first_gaussian_mean);
	cv::imwrite("median_first_gau.png", first_gaussian_median);

	cv::imwrite("mean_second_gau.png", second_gaussian_mean);
	cv::imwrite("median_second_gau.png", second_gaussian_median);

	cv::imwrite("mean_first_salt.png", first_saltandpepper_mean);
	cv::imwrite("median_first_salt.png", first_saltandpepper_median);

	cv::imwrite("mean_second_salt.png", second_saltandpepper_mean);
	cv::imwrite("median_second_salt.png", second_saltandpepper_median);



	cv::imshow("first gau",firstGaussianNoise);
	cv::imshow("first salt", firstSaltandpepperNoise);

	cv::imshow("second gau", secondGaussianNoise);
	cv::imshow("second salt", secondSaltandpepperNoise);
	
	cv::imshow("mean first gau", first_gaussian_mean);
	cv::imshow("median first gau", first_gaussian_median);

	cv::imshow("mean second gau", second_gaussian_mean);
	cv::imshow("median second gau", second_gaussian_median);

	cv::imshow("mean first salt", first_saltandpepper_mean);
	cv::imshow("median first salt", first_saltandpepper_median);

	cv::imshow("mean second salt", second_saltandpepper_mean);
	cv::imshow("median second salt", second_saltandpepper_median);

	
	cv::waitKey(0);

	return 0;
}