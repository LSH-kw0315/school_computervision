#include <opencv2/opencv.hpp>

unsigned char* Padding(unsigned char* img,int rows,int cols) {
	int n = 1;

	unsigned char* mirror_padding_gray = (unsigned char*)malloc(sizeof(unsigned char)*(rows + 2 * n) * (cols + 2 * n));

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

unsigned char* HorizontalSobelEdgeFilter(unsigned char* src,int rows,int cols) {
	int n = 1;
	float* horizontalFilter = (float*)malloc(sizeof(float)*(2*n+1)*(2*n+1));

	horizontalFilter[0] = -1;
	horizontalFilter[1] = -2;
	horizontalFilter[2] = -1;

	horizontalFilter[3] = 0;
	horizontalFilter[4] = 0;
	horizontalFilter[5] = 0;

	horizontalFilter[6] = 1;
	horizontalFilter[7] = 2;
	horizontalFilter[8] = 1;


	unsigned char* pad = Padding(src, rows, cols);

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* output = (unsigned char*)malloc(sizeof(unsigned char)*((pad_rows - 2 * n) * (pad_cols - 2 * n)));


	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			double mirror_tmp = 0;


			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					mirror_tmp += pad[((i - n + a) * pad_cols + (j - n + b))] * horizontalFilter[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];

				}
			}

			
			int to_abs=std::abs((int)mirror_tmp);
			output[((i - n) * (pad_cols - 2 * n) + (j - n))] = std::min(255, to_abs);
			

			//output[((i - n) * (pad_cols - 2 * n) + (j - n))] = std::max(0, std::min(255, (int)mirror_tmp));

		}
	}

	return output;


}

unsigned char* VerticalSobleEdgeFilter(unsigned char* src,int rows,int cols) {
	int n = 1;
	float* verticalFilter = (float*)malloc(sizeof(float) * (2 * n + 1) * (2 * n + 1));

	verticalFilter[0] = -1;
	verticalFilter[3] = -2;
	verticalFilter[6] = -1;

	verticalFilter[1] = 0;
	verticalFilter[4] = 0;
	verticalFilter[7] = 0;

	verticalFilter[2] = 1;
	verticalFilter[5] = 2;
	verticalFilter[8] = 1;


	unsigned char* pad = Padding(src, rows, cols);

	int pad_rows = rows + 2 * n;
	int pad_cols = cols + 2 * n;

	unsigned char* output = (unsigned char*)malloc(sizeof(unsigned char) * ((pad_rows - 2 * n) * (pad_cols - 2 * n)));


	for (int i = n; i < pad_rows - n; i++) {
		for (int j = n; j < pad_cols - n; j++) {
			double mirror_tmp = 0;


			for (int a = 0; a < 2 * n + 1; a++) {
				for (int b = 0; b < 2 * n + 1; b++) {
					mirror_tmp += pad[((i - n + a) * pad_cols + (j - n + b))] * verticalFilter[((2 * n + 1) - 1 - a) * (2 * n + 1) + (2 * n + 1) - 1 - b];

				}
			}

			
			int to_abs = std::abs((int)mirror_tmp);
			output[((i - n) * (pad_cols - 2 * n) + (j - n))] = std::min(255, to_abs);
			

			//output[((i - n) * (pad_cols - 2 * n) + (j - n))] = std::max(0, std::min(255, (int)mirror_tmp));

		}
	}

	return output;
}

int main(void) {
	
	cv::Mat input = cv::imread("Lena.png");
	cv::Mat grayscale;
	cv::cvtColor(input, grayscale, cv::COLOR_BGR2GRAY);

	cv::Mat naive_gx=cv::Mat(grayscale.rows,grayscale.cols,CV_8UC1);
	cv::Mat naive_gy= cv::Mat(grayscale.rows, grayscale.cols, CV_8UC1);

	naive_gx.data = HorizontalSobelEdgeFilter(grayscale.data, grayscale.rows, grayscale.cols);
	naive_gy.data = VerticalSobleEdgeFilter(grayscale.data, grayscale.rows, grayscale.cols);

	
	cv::imshow("gx", naive_gx);
	cv::imshow("gy", naive_gy);


	cv::Mat naive_output = cv::Mat(grayscale.rows, grayscale.cols, CV_8UC1);

	int max = -1;
	for (int i = 0; i < grayscale.rows * grayscale.cols; i++) {
		naive_output.data[i] = std::min(255, naive_gx.data[i] + naive_gy.data[i]);
		if (max < naive_output.data[i]) {
			max = naive_output.data[i];
		}
	}

	
	cv::imshow("naive output", naive_output);

	
	cv::Mat naive_thresholding = cv::Mat(grayscale.rows, grayscale.cols, CV_8UC1);

	float ratio = 0.2;

	for (int i = 0; i < grayscale.rows * grayscale.cols; i++) {
		if (naive_output.data[i] <= max && naive_output.data[i] >= max * ratio) {
			naive_thresholding.data[i] = 255;
		}
		else {
			naive_thresholding.data[i] = 0;
		}
	}
	
	cv::imshow("naive thresholding", naive_thresholding);
	cv::waitKey(0);

	////

	cv::Mat gaussian_grayscale1;
	cv::Mat gaussian_grayscale2;
	
	cv::GaussianBlur(grayscale, gaussian_grayscale1, cv::Size(3, 3), 5, 5, cv::BORDER_REFLECT);
	cv::GaussianBlur(grayscale, gaussian_grayscale2, cv::Size(5, 5), 20,20, cv::BORDER_REFLECT);

	///

	cv::Mat gaussian1_gx = cv::Mat(grayscale.rows, grayscale.cols, CV_8UC1);
	cv::Mat gaussian1_gy = cv::Mat(grayscale.rows, grayscale.cols, CV_8UC1);

	gaussian1_gx.data = HorizontalSobelEdgeFilter(gaussian_grayscale1.data, grayscale.rows, grayscale.cols);
	gaussian1_gy.data = VerticalSobleEdgeFilter(gaussian_grayscale1.data, grayscale.rows, grayscale.cols);


	cv::imshow("gaussian1_gx", gaussian1_gx);
	cv::imshow("gaussian1_gy", gaussian1_gy);


	cv::Mat gaussian_output1 = cv::Mat(grayscale.rows, grayscale.cols, CV_8UC1);

	max = -1;
	for (int i = 0; i < grayscale.rows * grayscale.cols; i++) {
		gaussian_output1.data[i] = std::min(255, gaussian1_gx.data[i] + gaussian1_gy.data[i]);
		if (max < gaussian_output1.data[i]) {
			max = gaussian_output1.data[i];
		}
	}


	cv::imshow("gaussian output1", gaussian_output1);


	cv::Mat gaussian_thresholding1 = cv::Mat(grayscale.rows, grayscale.cols, CV_8UC1);


	for (int i = 0; i < grayscale.rows * grayscale.cols; i++) {
		if (gaussian_output1.data[i] <= max && gaussian_output1.data[i] >= max * ratio) {
			gaussian_thresholding1.data[i] = 255;
		}
		else {
			gaussian_thresholding1.data[i] = 0;
		}
	}

	cv::imshow("gaussian thresholding1", gaussian_thresholding1);
	cv::waitKey(0);

	///

	cv::Mat gaussian2_gx = cv::Mat(grayscale.rows, grayscale.cols, CV_8UC1);
	cv::Mat gaussian2_gy = cv::Mat(grayscale.rows, grayscale.cols, CV_8UC1);

	gaussian2_gx.data = HorizontalSobelEdgeFilter(gaussian_grayscale2.data, grayscale.rows, grayscale.cols);
	gaussian2_gy.data = VerticalSobleEdgeFilter(gaussian_grayscale2.data, grayscale.rows, grayscale.cols);


	cv::imshow("gussian2_gx", gaussian2_gx);
	cv::imshow("gaussian2_gy", gaussian2_gy);


	cv::Mat gaussian_output2 = cv::Mat(grayscale.rows, grayscale.cols, CV_8UC1);

	max = -1;
	for (int i = 0; i < grayscale.rows * grayscale.cols; i++) {
		gaussian_output2.data[i] = std::min(255, gaussian2_gx.data[i] + gaussian2_gy.data[i]);
		if (max < gaussian_output2.data[i]) {
			max = gaussian_output2.data[i];
		}
	}


	cv::imshow("gaussian output2", gaussian_output2);


	cv::Mat gaussian_thresholding2 = cv::Mat(grayscale.rows, grayscale.cols, CV_8UC1);


	for (int i = 0; i < grayscale.rows * grayscale.cols; i++) {
		if (gaussian_output2.data[i] <= max && gaussian_output2.data[i] >= max * ratio) {
			gaussian_thresholding2.data[i] = 255;
		}
		else {
			gaussian_thresholding2.data[i] = 0;
		}
	}

	cv::imshow("gaussian thresholding2", gaussian_thresholding2);
	cv::waitKey(0);

	return 0;
}