#include <opencv2/opencv.hpp>
#include <iostream>

int main() {

	const unsigned char STANDARD_RED = 175;
	const unsigned char STANDARD_GREEN = 140;
	const unsigned char STANDARD_BLUE = 102;
	const unsigned char LOWER = 75;
	const unsigned char UPPER = 45;
	const unsigned char N = 4;

	cv::Mat original;
	original=cv::imread("sample.png");

	cv::Mat face_slicing;
	face_slicing = original.clone();


	cv::Mat face_map = cv::Mat(face_slicing.rows, face_slicing.cols, CV_8UC1);

	cv::Mat output = cv::Mat::zeros(original.rows, original.cols, CV_8UC3);
	

	for (int i = 0; i < face_slicing.rows; i++) {
		for (int j = 0; j < face_slicing.cols; j++) {
			unsigned char blue=face_slicing.data[3*(i*face_slicing.cols+j)];
			unsigned char green = face_slicing.data[3 * (i*face_slicing.cols + j)+1];
			unsigned char red = face_slicing.data[3 * (i*face_slicing.cols + j)+2];
			if((STANDARD_RED-LOWER>red || STANDARD_RED+UPPER<red)||(STANDARD_BLUE - LOWER > blue || STANDARD_BLUE + UPPER < blue)||(STANDARD_GREEN - LOWER > green || STANDARD_GREEN + UPPER < green))
			{
				face_slicing.data[3 * (i * face_slicing.cols + j)] = 0;
				face_slicing.data[3 * (i * face_slicing.cols + j) + 1] = 0;
				face_slicing.data[3 * (i * face_slicing.cols + j) + 2] = 0;

				face_map.data[i*face_slicing.cols+j]=0;
			}
			else {
				face_map.data[i * face_slicing.cols + j] = 255;
			}

		}
	}
	
	

	cv::Mat zero_padding_rgb = cv::Mat::zeros(original.rows + 2*N, original.cols + 2*N, CV_8UC3);
	for (int i = N; i < original.rows+N; i++) {
		for (int j = N; j < original.cols+N; j++) {
			zero_padding_rgb.data[3 * ((i) * (original.cols+2*N) + j)] = original.data[3 * ((i-N) * original.cols + (j-N))];
			zero_padding_rgb.data[3 * ((i) * (original.cols+2*N) + j) + 1] = original.data[3 * ((i-N) * original.cols + (j-N)) + 1];
			zero_padding_rgb.data[3 * ((i) * (original.cols+2*N) + j) + 2] = original.data[3 * ((i-N) * original.cols + (j-N)) + 2];
		}
	}

	for (int i = N; i < zero_padding_rgb.rows-N; i++) {
		for (int j = N; j < zero_padding_rgb.cols-N; j++) {
			int red_total = 0;
			int blue_total = 0;
			int green_total = 0;
			for (int a = 0; a < 2 * N + 1; a++) {
				for (int b = 0; b < 2 * N + 1; b++) {
					blue_total += zero_padding_rgb.data[3 * ((i - N + a) * zero_padding_rgb.cols + (j - N + b))];
					green_total += zero_padding_rgb.data[3 * ((i - N + a) * zero_padding_rgb.cols + (j - N + b)) + 1];
					red_total += zero_padding_rgb.data[3 * ((i - N + a) * zero_padding_rgb.cols + (j - N + b)) + 2];
				}
			}
			zero_padding_rgb.data[3 * (i * zero_padding_rgb.cols + j)] = blue_total / ((2 * N + 1) * (2 * N + 1));
			zero_padding_rgb.data[3 * (i * zero_padding_rgb.cols + j) + 1] = green_total / ((2 * N + 1) * (2 * N + 1));
			zero_padding_rgb.data[3 * (i * zero_padding_rgb.cols + j) + 2] = red_total/ ((2 * N + 1) * (2 * N + 1));
		}
	}

	for (int i = 0; i < original.rows; i++) {
		for (int j = 0; j < original.cols; j++) {
			if (face_map.data[i * original.cols + j] ==255) {
				output.data[3*(i*original.cols+j)] = zero_padding_rgb.data[3 * ((i + N) * zero_padding_rgb.cols + (j + N))];
				output.data[3 * (i * original.cols + j)+1] = zero_padding_rgb.data[3 * ((i + N) * zero_padding_rgb.cols + (j + N))+1];
				output.data[3 * (i * original.cols + j)+2] = zero_padding_rgb.data[3 * ((i + N) * zero_padding_rgb.cols + (j + N))+2];
			}
			else {
				output.data[3 * (i * original.cols + j)] = original.data[3 * (i * original.cols + j)];
				output.data[3 * (i * original.cols + j) + 1] = original.data[3 * (i * original.cols + j) + 1];
				output.data[3 * (i * original.cols + j) + 2] = original.data[3 * (i * original.cols + j) + 2];
			}
		}
	}
	
	cv::imshow("input", original);
	cv::imshow("face slicing", face_slicing);
	cv::imshow("face map", face_map);
	cv::imshow("smoothing",zero_padding_rgb );
	cv::imshow("output",output);
	cv::waitKey(0);
	return 0;
}