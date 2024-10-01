#include <opencv2/opencv.hpp>

int main(void) {

	//왜 되는지 모르겠음;

	cv::Mat p = cv::Mat(8, 6, CV_64F);
	cv::Mat pT = cv::Mat(6, 8, CV_64F);
	cv::Mat ppT = cv::Mat::zeros(6, 6, CV_64F);
	cv::Mat x = cv::Mat(8, 1, CV_64F);
	cv::Mat p_i = cv::Mat(8, 6, CV_64F);
	cv::Mat result = cv::Mat::zeros(6, 1, CV_64F);

	
	p.at<double>(0, 0) = 100;
	p.at<double>(0, 1) = 100;
	p.at<double>(0, 2) = 0;
	p.at<double>(0, 3) = 0;
	p.at<double>(0, 4) = 1;
	p.at<double>(0, 5) = 0;

	p.at<double>(1, 0) = 0;
	p.at<double>(1, 1) = 0;
	p.at<double>(1, 2) = 100;
	p.at<double>(1, 3) = 100;
	p.at<double>(1, 4) = 0;
	p.at<double>(1, 5) = 1;

	p.at<double>(2, 0) = 412;
	p.at<double>(2, 1) = 100;
	p.at<double>(2, 2) = 0;
	p.at<double>(2, 3) = 0;
	p.at<double>(2, 4) = 1;
	p.at<double>(2, 5) = 0;

	p.at<double>(3, 0) = 0;
	p.at<double>(3, 1) = 0;
	p.at<double>(3, 2) = 412;
	p.at<double>(3, 3) = 100;
	p.at<double>(3, 4) = 0;
	p.at<double>(3, 5) = 1;

	p.at<double>(4, 0) = 100;
	p.at<double>(4, 1) = 412;
	p.at<double>(4, 2) = 0;
	p.at<double>(4, 3) = 0;
	p.at<double>(4, 4) = 1;
	p.at<double>(4, 5) = 0;

	p.at<double>(5, 0) = 0;
	p.at<double>(5, 1) = 0;
	p.at<double>(5, 2) = 100;
	p.at<double>(5, 3) = 412;
	p.at<double>(5, 4) = 0;
	p.at<double>(5, 5) = 1;

	p.at<double>(6, 0) = 412;
	p.at<double>(6, 1) = 412;
	p.at<double>(6, 2) = 0;
	p.at<double>(6, 3) = 0;
	p.at<double>(6, 4) = 1;
	p.at<double>(6, 5) = 0;

	p.at<double>(7, 0) = 0;
	p.at<double>(7, 1) = 0;
	p.at<double>(7, 2) = 412;
	p.at<double>(7, 3) = 412;
	p.at<double>(7, 4) = 0;
	p.at<double>(7, 5) = 1;
	


	/*
	p.at<double>(0, 0) = 173;
	p.at<double>(0, 1) = 284;
	p.at<double>(0, 2) = 0;
	p.at<double>(0, 3) = 0;
	p.at<double>(0, 4) = 1;
	p.at<double>(0, 5) = 0;

	p.at<double>(1, 0) = 0;
	p.at<double>(1, 1) = 0;
	p.at<double>(1, 2) = 173;
	p.at<double>(1, 3) = 284;
	p.at<double>(1, 4) = 0;
	p.at<double>(1, 5) = 1;

	p.at<double>(2, 0) = 477;
	p.at<double>(2, 1) = 33;
	p.at<double>(2, 2) = 0;
	p.at<double>(2, 3) = 0;
	p.at<double>(2, 4) = 1;
	p.at<double>(2, 5) = 0;

	p.at<double>(3, 0) = 0;
	p.at<double>(3, 1) = 0;
	p.at<double>(3, 2) = 477;
	p.at<double>(3, 3) = 33;
	p.at<double>(3, 4) = 0;
	p.at<double>(3, 5) = 1;

	p.at<double>(4, 0) = 248;
	p.at<double>(4, 1) = 455;
	p.at<double>(4, 2) = 0;
	p.at<double>(4, 3) = 0;
	p.at<double>(4, 4) = 1;
	p.at<double>(4, 5) = 0;

	p.at<double>(5, 0) = 0;
	p.at<double>(5, 1) = 0;
	p.at<double>(5, 2) = 248;
	p.at<double>(5, 3) = 455;
	p.at<double>(5, 4) = 0;
	p.at<double>(5, 5) = 1;

	p.at<double>(6, 0) = 553;
	p.at<double>(6, 1) = 193;
	p.at<double>(6, 2) = 0;
	p.at<double>(6, 3) = 0;
	p.at<double>(6, 4) = 1;
	p.at<double>(6, 5) = 0;

	p.at<double>(7, 0) = 0;
	p.at<double>(7, 1) = 0;
	p.at<double>(7, 2) = 553;
	p.at<double>(7, 3) = 193;
	p.at<double>(7, 4) = 0;
	p.at<double>(7, 5) = 1;
	*/

	/*
	for (int i = 0; i < p.rows; i++) {
		for (int j = 0; j < p.cols; j++) {
			pT.at<double>(j, i) = p.at<double>(i, j);
		}
	}
	
	
	ppT = pT * p;
	*/

	
	x.at<double>(0, 0) = 173;
	x.at<double>(1, 0) = 284;

	x.at<double>(2, 0) = 477;
	x.at<double>(3, 0) = 33;

	x.at<double>(4, 0) = 248;
	x.at<double>(5, 0) = 455;

	x.at<double>(6, 0) = 553;
	x.at<double>(7, 0) = 193;
	

	/*
	x.at<double>(0, 0) = 100;
	x.at<double>(1, 0) = 100;

	x.at<double>(2, 0) = 412;
	x.at<double>(3, 0) = 100;

	x.at<double>(4, 0) = 100;
	x.at<double>(5, 0) = 412;

	x.at<double>(6, 0) = 412;
	x.at<double>(7, 0) = 412;
	*/
	cv::invert(p, p_i, cv::DECOMP_SVD);



	printf("p_i\n");

	for (int i = 0; i < p_i.rows; i++) {
		for (int j = 0; j < p_i.cols; j++) {
			printf("%f\n", p_i.at<double>(i, j));
		}
		printf("--------------\n");
	}
	
	
	for (int i = 0; i < p_i.rows; i++) {
		for (int j = 0; j < p_i.cols; j++) {
			result.at<double>(i, 0) += p_i.at<double>(i, j) * x.at<double>(j, 0);
		}
	}

	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			printf("%f\n", result.at<double>(i, j));
		}
		printf("--------------\n");
	}


	cv::Mat target = cv::imread("lena_t.jpg");
	cv::cvtColor(target, target, cv::COLOR_BGR2GRAY);
	cv::Mat output = cv::Mat::zeros(512, 512, CV_8UC1);


	double m1 = result.at<double>(0, 0);
	double m2 = result.at<double>(1, 0);
	double m3 = result.at<double>(2, 0);
	double m4 = result.at<double>(3, 0);
	double t1 = result.at<double>(4, 0);
	double t2 = result.at<double>(5, 0);

	for (int i = 0; i < output.rows; i++) {
		for (int j = 0; j < output.cols; j++) {

			//이번에는 원본이 회전되었을 경우 실제 실수 좌표가 어딜지를 구한다.

			double real_p1_x=m1*j+m2*i+t1;
			double real_p1_y= m3 * j + m4 * i + t2;

			int p1_x = (int)(real_p1_x); //transform을 그대로 적용한다.
			int p1_y = (int)(real_p1_y);

			
			if ((p1_x < 0 || p1_y < 0)  || (p1_x >= output.cols || p1_y >= output.rows)) { //만약 transform 결과, 영역에서 벗어나는 경우 매핑하는 과정을 수행하지 않는다.
				continue;
			}
			
			

			int p2_x = p1_x + 1;
			int p2_y = p1_y;

			int p3_x = p1_x;
			int p3_y = p1_y + 1;

			int p4_x = p1_x + 1;
			int p4_y = p1_y + 1;


			double distance_of_x_from_left = real_p1_x - p1_x; //실제 거리가 아닌 닮음(즉, 비율)을 이용해서 (실수 2차원 공간이었다면 매핑되었을 x 좌표)-(정수 2차원 공간에어서 매핑된 x 좌표)=a 임을 알아낸다.
			double distance_of_x_from_right = 1 - distance_of_x_from_left; // 1-a 

			double distance_of_y_from_top = real_p1_y - p1_y;//실제 거리가 아닌 닮음(즉, 비율)을 이용해서 (실수 2차원 공간이었다면 매핑되었을 y 좌표)-(정수 2차원 공간에어서 매핑된 y 좌표)=b임을 알아낸다.
			double distance_of_y_from_bottom = 1 - distance_of_y_from_top;// 1-b


			double weight_of_p1 = distance_of_x_from_left * distance_of_y_from_top;//(1-a)*b*p1
			double weight_of_p2 = distance_of_x_from_right * distance_of_y_from_top;//a*b*p2
			double weight_of_p3 = distance_of_x_from_left * distance_of_y_from_bottom;//(1-a)*(1-b)*p3
			double weight_of_p4 = distance_of_x_from_right * distance_of_y_from_bottom;//a*(1-b)*p4

			output.data[output.cols * i + j] = weight_of_p1 * target.data[p1_y * target.cols + p1_x] + weight_of_p2 * target.data[p2_y * target.cols + p2_x] + weight_of_p3 * target.data[p3_y * target.cols + p3_x] + weight_of_p4 * target.data[p4_y * target.cols + p4_x];
		}
	}

	cv::imshow("input", target);
	cv::imshow("output", output);
	cv::waitKey(0);

	return 0;
}