// PSNR.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	//HW1-1 ����

	//����� �̹����� ũ�⸦ �Է¹���
	while ((output_size<128 ||output_size>1024)) {
		cout << "output size:";
		cin >> output_size;
		if (!cin) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

	}

	// image �а� gray�� �ٲٱ�
	img_in = imread("Lena_256x256.png");
	cv::cvtColor(img_in, img_in, cv::COLOR_RGB2GRAY);
	cv::imshow("source img", img_in);

	unsigned char *pData;
	pData = (unsigned char *)img_in.data;

	unsigned char* outData = (unsigned char* )malloc(output_size * output_size);

	//���� �ʱ�ȭ
	for (int i = 0; i < output_size * output_size; i++) {
		outData[i] = 0;
	}
	double zoomSize = (double)output_size / (double)256;

	

		///////////////////// ó���ϱ� ///////////////////

		/*
		*
		*�ܼ� Ȯ��
		for (int i = 0; i < output_size; i++) {
			int expected_y = round(i * zoomSize);
			for (int j = 0; j < output_size; j++) {
				int expected_x = round(j * zoomSize);
				outData[expected_y * output_size + expected_x] = pData[i * 256 + j];
			}
		}
		*/

		//bilinear interpolation ó���ϴ� �ڵ�
		for (int i = 0; i < output_size; i++) {
			for (int j = 0; j < output_size; j++) {

				//p1�� ������ǥ�� ��Ī�� ���� ���Ѵٰ� �����ϸ� �ȴ�.
				int p1_x = (int)(j / zoomSize); //Ȯ��ȸ�ŭ �������ؼ� ���� ��ǥ�� ã�´�. ������ �� round�ϹǷ� ����� ���� round.
				int p1_y = (int)(i / zoomSize);

				int p2_x = p1_x+1;
				int p2_y = p1_y;

				int p3_x = p1_x;
				int p3_y = p1_y+1;

				int p4_x = p1_x+1;
				int p4_y = p1_y+1;


				double distance_of_x_from_left = ((double)j / (double)zoomSize) - (double)p1_x; //���� �Ÿ��� �ƴ� ����(��, ����)�� �̿��ؼ� (�Ǽ� 2���� �����̾��ٸ� ���εǾ��� x ��ǥ)-(���� 2���� ������� ���ε� x ��ǥ)=a ���� �˾Ƴ���.
				double distance_of_x_from_right = 1 - distance_of_x_from_left; // 1-a 

				double distance_of_y_from_top = ((double)i / (double)zoomSize) - (double)p1_y;//���� �Ÿ��� �ƴ� ����(��, ����)�� �̿��ؼ� (�Ǽ� 2���� �����̾��ٸ� ���εǾ��� y ��ǥ)-(���� 2���� ������� ���ε� yc ��ǥ)=a ���� �˾Ƴ���.
				double distance_of_y_from_bottom = 1 - distance_of_y_from_top;// 1-b


				double weight_of_p1 = distance_of_x_from_left * distance_of_y_from_top;//(1-a)*b*p1
				double weight_of_p2 = distance_of_x_from_right * distance_of_y_from_top;//a*b*p2
				double weight_of_p3 = distance_of_x_from_left * distance_of_y_from_bottom;//(1-a)*(1-b)*p3
				double weight_of_p4 = distance_of_x_from_right * distance_of_y_from_bottom;//a*(1-b)*p4

				outData[output_size * i + j] = weight_of_p1 * pData[p1_y * 256 + p1_x] + weight_of_p2 * pData[p2_y * 256 + p2_x] + weight_of_p3 * pData[p3_y * 256 + p3_x] + weight_of_p4 * pData[p4_y * 256 + p4_x];
			}	
		}

		
	
	/*
	* �ܼ� ���
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

	//��¿� ���� Mat ���� �� ���
	img_out=Mat(output_size,output_size,CV_8UC1);
	img_out.data = outData;
	cv::imshow("output image", img_out);

	cv::waitKey(0);
	/////////////////////////////
	
	//HW1-2 ����
	Mat img_in2;
	Mat img_out2;

	int output_angle= -1;

	//���� �Է�
	while (output_angle < 0) {
		cout << "angle:";
		cin >> output_angle;
		if (!cin) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

	}

	//�Է� ���� �̹��� ������� ��ȯ
	img_in2 = imread("Lena.png");
	cv::cvtColor(img_in2, img_in2, cv::COLOR_RGB2GRAY);

	cv::imshow("input", img_in2);

	int original_size = img_in2.rows;

	unsigned char* original_data= img_in2.data;

	//���� �ʱ�ȭ
	unsigned char* rotated_data = (unsigned char*)malloc(original_size * original_size);
	for (int i = 0; i < original_size * original_size; i++) {
		rotated_data[i] = 0;
	}

	/*
	 �ܼ��� ��ǥ�� �̵����� �����Ѵ�. ��, �߰��߰� ��� �ȼ��� ������ ���� ���� ����.
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

	////ó���ϱ�

	//rotation ó���ϴ� �ڵ�
	for (int i = 0; i < original_size; i++) {
		for (int j = 0; j < original_size; j++) {

			//�̹����� ������ ȸ���Ǿ��� ��� ���� �Ǽ� ��ǥ�� ������� ���Ѵ�.
			int p1_x = (int)(cos(output_angle * 3.14 / 180) * (j - original_size / 2) - sin(output_angle * 3.14 / 180) * (i - original_size / 2) + original_size / 2); //transform�� �״�� �����Ѵ�.
			int p1_y = (int)(sin(output_angle * 3.14 / 180) * (j - original_size / 2) + cos(output_angle * 3.14 / 180) * (i - original_size / 2) + original_size / 2);

			if ((p1_x < 0 || p1_y < 0) || (p1_x >= original_size || p1_y >= original_size)) { //���� transform ���, �������� ����� ��� �����ϴ� ������ �������� �ʴ´�.
				continue;
			}

			int p2_x = p1_x + 1;
			int p2_y = p1_y;

			int p3_x = p1_x;
			int p3_y = p1_y + 1;

			int p4_x = p1_x + 1;
			int p4_y = p1_y + 1;

			
			double distance_of_x_from_left = cos(output_angle * 3.14 / 180) * (j - original_size / 2) - sin(output_angle * 3.14 / 180) * (i - original_size / 2) + original_size / 2 - (double)p1_x; //���� �Ÿ��� �ƴ� ����(��, ����)�� �̿��ؼ� (�Ǽ� 2���� �����̾��ٸ� ���εǾ��� x ��ǥ)-(���� 2���� ������� ���ε� x ��ǥ)=a ���� �˾Ƴ���.
			double distance_of_x_from_right = 1 - distance_of_x_from_left; // 1-a 

			double distance_of_y_from_top = sin(output_angle * 3.14 / 180) * (j - original_size / 2) + cos(output_angle * 3.14 / 180) * (i - original_size / 2) + original_size / 2 - (double)p1_y;//���� �Ÿ��� �ƴ� ����(��, ����)�� �̿��ؼ� (�Ǽ� 2���� �����̾��ٸ� ���εǾ��� y ��ǥ)-(���� 2���� ������� ���ε� y ��ǥ)=b���� �˾Ƴ���.
			double distance_of_y_from_bottom = 1 - distance_of_y_from_top;// 1-b


			double weight_of_p1 = distance_of_x_from_left * distance_of_y_from_top;//(1-a)*b*p1
			double weight_of_p2 = distance_of_x_from_right * distance_of_y_from_top;//a*b*p2
			double weight_of_p3 = distance_of_x_from_left * distance_of_y_from_bottom;//(1-a)*(1-b)*p3
			double weight_of_p4 = distance_of_x_from_right * distance_of_y_from_bottom;//a*(1-b)*p4

			rotated_data[original_size * i + j] = weight_of_p1 * original_data[p1_y * original_size + p1_x] + weight_of_p2 * original_data[p2_y * original_size + p2_x] + weight_of_p3 *original_data[p3_y * original_size + p3_x] + weight_of_p4 * original_data[p4_y * original_size + p4_x];
		}
	}

	//����ϱ� ���� Mat ������ ���
	img_out2=Mat(original_size, original_size, CV_8UC1);
	img_out2.data = rotated_data;
	cv::imshow("output", img_out2);

	cv::waitKey(0);
	std::free(outData);
	free(rotated_data);
	return 0;
}