// PSNR.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <math.h>

#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main()
{
	Mat img_in;
	Mat img_out;

	
	int output_size=0;
	//HW1-1 시작

	//출력할 이미지의 크기를 입력받음
	while ((output_size<128 ||output_size>1024)) {
		cout << "output size:";
		cin >> output_size;
		if (!cin) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

	}

	// image 읽고 gray로 바꾸기
	img_in = imread("Lena_256x256.png");
	cv::cvtColor(img_in, img_in, cv::COLOR_RGB2GRAY);
	cv::imshow("source img", img_in);

	unsigned char *pData;
	pData = (unsigned char *)img_in.data;

	unsigned char* outData = (unsigned char* )malloc(output_size * output_size);

	//변수 초기화
	for (int i = 0; i < output_size * output_size; i++) {
		outData[i] = 0;
	}
	double zoomSize = (double)output_size / (double)256;

	

		///////////////////// 처리하기 ///////////////////

		/*
		*
		*단순 확대
		for (int i = 0; i < output_size; i++) {
			int expected_y = round(i * zoomSize);
			for (int j = 0; j < output_size; j++) {
				int expected_x = round(j * zoomSize);
				outData[expected_y * output_size + expected_x] = pData[i * 256 + j];
			}
		}
		*/

		//bilinear interpolation 처리하는 코드
		for (int i = 0; i < output_size; i++) {
			for (int j = 0; j < output_size; j++) {

				//p1의 실제좌표에 매칭될 것을 구한다고 가정하면 된다.
				int p1_x = (int)(j / zoomSize); //확대된만큼 나누기해서 원래 좌표를 찾는다. 매핑할 때 round하므로 축소할 때도 round.
				int p1_y = (int)(i / zoomSize);

				int p2_x = p1_x+1;
				int p2_y = p1_y;

				int p3_x = p1_x;
				int p3_y = p1_y+1;

				int p4_x = p1_x+1;
				int p4_y = p1_y+1;


				double distance_of_x_from_left = ((double)j / (double)zoomSize) - (double)p1_x; //실제 거리가 아닌 닮음(즉, 비율)을 이용해서 (실수 2차원 공간이었다면 매핑되었을 x 좌표)-(정수 2차원 공간에어서 매핑된 x 좌표)=a 임을 알아낸다.
				double distance_of_x_from_right = 1 - distance_of_x_from_left; // 1-a 

				double distance_of_y_from_top = ((double)i / (double)zoomSize) - (double)p1_y;//실제 거리가 아닌 닮음(즉, 비율)을 이용해서 (실수 2차원 공간이었다면 매핑되었을 y 좌표)-(정수 2차원 공간에어서 매핑된 yc 좌표)=a 임을 알아낸다.
				double distance_of_y_from_bottom = 1 - distance_of_y_from_top;// 1-b


				double weight_of_p1 = distance_of_x_from_left * distance_of_y_from_top;//(1-a)*b*p1
				double weight_of_p2 = distance_of_x_from_right * distance_of_y_from_top;//a*b*p2
				double weight_of_p3 = distance_of_x_from_left * distance_of_y_from_bottom;//(1-a)*(1-b)*p3
				double weight_of_p4 = distance_of_x_from_right * distance_of_y_from_bottom;//a*(1-b)*p4

				outData[output_size * i + j] = weight_of_p1 * pData[p1_y * 256 + p1_x] + weight_of_p2 * pData[p2_y * 256 + p2_x] + weight_of_p3 * pData[p3_y * 256 + p3_x] + weight_of_p4 * pData[p4_y * 256 + p4_x];
			}	
		}

		
	
	/*
	* 단순 축소
	else {
		for (int i = 0; i < img_in.cols; i++) {
			int expected_y = floor(i * zoomSize);
			for (int j = 0; j < img_in.rows; j++) {
				int expected_x = floor(j * zoomSize);
				outData[expected_y * output_size + expected_x] = pData[i * 256 + j];
			}
		}
	}
	*/

	//출력에 쓰일 Mat 생성 및 출력
	img_out=Mat(output_size,output_size,CV_8UC1);
	img_out.data = outData;
	cv::imshow("output image", img_out);

	cv::waitKey(0);
	/////////////////////////////
	
	//HW1-2 시작
	Mat img_in2;
	Mat img_out2;

	int output_angle= -1;

	//각도 입력
	while (output_angle < 0) {
		cout << "angle:";
		cin >> output_angle;
		if (!cin) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

	}

	//입력 받은 이미지 흑백으로 변환
	img_in2 = imread("Lena.png");
	cv::cvtColor(img_in2, img_in2, cv::COLOR_RGB2GRAY);

	cv::imshow("input", img_in2);

	int original_size = img_in2.rows;

	unsigned char* original_data= img_in2.data;

	//변수 초기화
	unsigned char* rotated_data = (unsigned char*)malloc(original_size * original_size);
	for (int i = 0; i < original_size * original_size; i++) {
		rotated_data[i] = 0;
	}

	/*
	 단순히 좌표의 이동만을 생각한다. 즉, 중간중간 비는 픽셀의 보정은 하지 않은 상태.
	for (int i = 0; i < original_size; i++) {
		for (int j = 0; j < original_size; j++) {
			int x = cos(output_angle * 3.14 / 180) * (j - original_size / 2) - sin(output_angle * 3.14 / 180) * (i - original_size / 2) + original_size / 2;
			int y = sin(output_angle * 3.14 / 180) * (j - original_size / 2) +cos(output_angle * 3.14 / 180) * (i - original_size / 2) + original_size / 2;
			if (x >= 0 && y >= 0) {
				rotated_data[y * original_size + x] = original_data[i * original_size + j];
			}

		}
	}
	*/

	////처리하기

	//rotation 처리하는 코드
	for (int i = 0; i < original_size; i++) {
		for (int j = 0; j < original_size; j++) {

			//이번에는 원본이 회전되었을 경우 실제 실수 좌표가 어딜지를 구한다.
			int p1_x = (int)(cos(output_angle * 3.14 / 180) * (j - original_size / 2) - sin(output_angle * 3.14 / 180) * (i - original_size / 2) + original_size / 2); //transform을 그대로 적용한다.
			int p1_y = (int)(sin(output_angle * 3.14 / 180) * (j - original_size / 2) + cos(output_angle * 3.14 / 180) * (i - original_size / 2) + original_size / 2);

			if ((p1_x < 0 || p1_y < 0) || (p1_x >= original_size || p1_y >= original_size)) { //만약 transform 결과, 영역에서 벗어나는 경우 매핑하는 과정을 수행하지 않는다.
				continue;
			}

			int p2_x = p1_x + 1;
			int p2_y = p1_y;

			int p3_x = p1_x;
			int p3_y = p1_y + 1;

			int p4_x = p1_x + 1;
			int p4_y = p1_y + 1;

			
			double distance_of_x_from_left = cos(output_angle * 3.14 / 180) * (j - original_size / 2) - sin(output_angle * 3.14 / 180) * (i - original_size / 2) + original_size / 2 - (double)p1_x; //실제 거리가 아닌 닮음(즉, 비율)을 이용해서 (실수 2차원 공간이었다면 매핑되었을 x 좌표)-(정수 2차원 공간에어서 매핑된 x 좌표)=a 임을 알아낸다.
			double distance_of_x_from_right = 1 - distance_of_x_from_left; // 1-a 

			double distance_of_y_from_top = sin(output_angle * 3.14 / 180) * (j - original_size / 2) + cos(output_angle * 3.14 / 180) * (i - original_size / 2) + original_size / 2 - (double)p1_y;//실제 거리가 아닌 닮음(즉, 비율)을 이용해서 (실수 2차원 공간이었다면 매핑되었을 y 좌표)-(정수 2차원 공간에어서 매핑된 y 좌표)=b임을 알아낸다.
			double distance_of_y_from_bottom = 1 - distance_of_y_from_top;// 1-b


			double weight_of_p1 = distance_of_x_from_left * distance_of_y_from_top;//(1-a)*b*p1
			double weight_of_p2 = distance_of_x_from_right * distance_of_y_from_top;//a*b*p2
			double weight_of_p3 = distance_of_x_from_left * distance_of_y_from_bottom;//(1-a)*(1-b)*p3
			double weight_of_p4 = distance_of_x_from_right * distance_of_y_from_bottom;//a*(1-b)*p4

			rotated_data[original_size * i + j] = weight_of_p1 * original_data[p1_y * original_size + p1_x] + weight_of_p2 * original_data[p2_y * original_size + p2_x] + weight_of_p3 *original_data[p3_y * original_size + p3_x] + weight_of_p4 * original_data[p4_y * original_size + p4_x];
		}
	}

	//출력하기 위한 Mat 생성과 출력
	img_out2=Mat(original_size, original_size, CV_8UC1);
	img_out2.data = rotated_data;
	cv::imshow("output", img_out2);

	cv::waitKey(0);
	std::free(outData);
	free(rotated_data);
	return 0;
}