#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main() {

	Mat img;
	img = imread("Lena.png");
	
	unsigned char* Y = (unsigned char*)malloc(sizeof(unsigned char)*img.rows * img.cols);
	unsigned char* YUV = (unsigned char*)malloc(sizeof(unsigned char)*3*img.rows * img.cols);
	
	memset(Y, 0, img.rows * img.cols);
	memset(YUV, 0, 3*img.rows * img.cols);

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			double conv_blue_Y = 0.114 * img.data[3 * (img.rows * i + j)];
			double conv_green_Y = 0.587 * img.data[3 * (img.rows * i + j) + 1];
			double conv_red_Y = 0.299 * img.data[3 * (img.rows * i + j) + 2];

			double conv_blue_U = 0.499 * img.data[3 * (img.rows * i + j)];
			double conv_green_U = -0.331 * img.data[3 * (img.rows * i + j) + 1];
			double conv_red_U = -0.169 * img.data[3 * (img.rows * i + j) + 2];

			double conv_blue_V = -0.081 * img.data[3 * (img.rows * i + j)];
			double conv_green_V = -0.418 * img.data[3 * (img.rows * i + j) + 1];
			double conv_red_V = 0.499 * img.data[3 * (img.rows * i + j) + 2];

			Y[img.rows * i + j] = conv_blue_Y + conv_green_Y + conv_red_Y;
			/*
			//이 포맷대로 저장할 경우 녹색으로 칠해진 영상만 나옴
			YUV[3 * (img.rows * i + j)] = max(0,min(255,(int)(conv_blue_Y + conv_green_Y + conv_red_Y)));
			YUV[3 * (img.rows * i + j)+1] = max(0,min(255,(int)(conv_blue_U + conv_green_U + conv_red_U)));
			YUV[3 * (img.rows * i + j)+2] = max(0,min(255,(int)(conv_blue_V + conv_green_V + conv_red_V)));
			*/
			
			YUV[3 * (img.rows * i + j)] = max(0,min(255,(int)(conv_blue_Y + conv_green_Y + conv_red_Y)));
			YUV[3 * (img.rows * i + j)+1] = max(0,min(255,(int)(conv_blue_U + conv_green_U + conv_red_U)+128));
			YUV[3 * (img.rows * i + j)+2] = max(0,min(255,(int)(conv_blue_V + conv_green_V + conv_red_V)+128));
			
		}
	}


	FILE* fp1;
	fopen_s(&fp1,"lena.y", "wb");
	fwrite(Y, sizeof(unsigned char), img.rows * img.cols, fp1);
	fclose(fp1);

	FILE* fp2;
	fopen_s(&fp2, "lena.yuv", "wb");
	fwrite(YUV, sizeof(unsigned char), 3*img.rows * img.cols, fp2);
	fclose(fp2);

	FILE* fp3;
	fopen_s(&fp3, "lena.yuv", "rb");
	unsigned char* Buf = (unsigned char*)malloc(sizeof(unsigned char)*3 * img.rows * img.cols);
	memset(Buf, 0, 3 * img.rows * img.cols);
	fread(Buf, sizeof(char),3*img.rows*img.cols,fp3);
	fclose(fp3);

	unsigned char* RGB = (unsigned char*)malloc(3 * img.rows * img.cols);
	memset(RGB, 0, 3 * img.rows * img.cols);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {

			/*
			
			RGB[3 * (img.rows * i + j)] = max(0,min(255,(int)(Buf[3 * (img.rows * i + j)]+1.402*Buf[3*(img.rows*i+j)+2])));
			RGB[3 * (img.rows * i + j)+1] = max(0,min(255,(int)(Buf[3 * (img.rows * i + j)] - 0.344 * Buf[3 * (img.rows * i + j) + 1] -0.714 * Buf[3 * (img.rows * i + j) + 2])));
			RGB[3 * (img.rows * i + j)+2] = max(0,min(255,(int)(Buf[3 * (img.rows * i + j)] + 1.772 * Buf[3 * (img.rows * i + j) + 1])));

			*/

			
			RGB[3 * (img.rows * i + j)] = max(0,min(255,(int)(Buf[3 * (img.rows * i + j)]+1.402*(Buf[3*(img.rows*i+j)+2]-128))));
			RGB[3 * (img.rows * i + j)+1] = max(0,min(255,(int)(Buf[3 * (img.rows * i + j)] - 0.344 * (Buf[3 * (img.rows * i + j) + 1]-128) -0.714 * (Buf[3 * (img.rows * i + j) + 2]-128))));
			RGB[3 * (img.rows * i + j)+2] = max(0,min(255,(int)(Buf[3 * (img.rows * i + j)] + 1.772 * (Buf[3 * (img.rows * i + j) + 1]-128))));
			
		}
	}

	FILE* fp4;
	fopen_s(&fp4, "lena.rgb", "wb");
	fwrite(RGB, sizeof(unsigned char), 3 * img.rows * img.cols, fp2);
	fclose(fp4);

	
	free(Y);
	free(YUV);
	free(Buf);
	free(RGB);

	return 0;
}