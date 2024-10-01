#include <opencv2/opencv.hpp>


using namespace cv;
int main(void) {
	Mat src = imread("Lena.png");
	Mat dst = Mat::zeros(src.rows+128, src.cols+128, CV_8UC3);

	double h = 0.5;

	Mat M = Mat(2, 2, CV_64F);
	M.at<double>(0, 0) = 1;
	M.at<double> (0, 1) = h;
	M.at<double>(1, 0) = h;
	M.at<double>(1, 1) = 1;
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			
			Mat p = Mat(2, 1, CV_64F);
			p.at<double>(0, 0) = j;
			p.at<double>(1, 0) = i;

			Mat result = M.inv()* p;
			int row = result.at<double>(1, 0);
			int col = result.at<double>(0, 0);
			if (row<0 || col<0 || row >= src.rows || col >= src.cols) {
				continue;
			}
			dst.at<Vec3b>(i, j) = src.at<Vec3b>(row, col);
		}
	}

	imshow("result", dst);
	waitKey(0);
	return 0;
}