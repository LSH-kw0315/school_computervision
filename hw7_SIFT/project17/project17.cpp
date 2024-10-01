
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
Mat src, src_gray;
int thresh = 120;
int max_thresh = 255;

double Flat=pow(10,-2)*7.3;
const char* source_window = "Source image";
const char* corners_window = "Corners detected";
void cornerHarris_demo(int, void*,const char*);
int main(int argc, char** argv)
{
    
    src = imread("image1.jpg");
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    //namedWindow(source_window);
    //createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);//�Դٰ��� ������ �Ǵ� �ٸ� source ���� â�� ����. ������ ���ڴ� �ݹ��Լ� ����̶�� ���� ��
    imshow(source_window, src);
    cornerHarris_demo(0, 0,corners_window);
    
    resize(src, src, Size(0,0),1.3, 1.3, InterpolationFlags::INTER_CUBIC);
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    imshow("resized", src);
    cornerHarris_demo(0, 0, "resized_corner");
    

    waitKey();
    return 0;
}
void cornerHarris_demo(int, void*,const char* str)
{
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;
    Mat dst = Mat::zeros(src.size(), CV_32FC1);
    cornerHarris(src_gray, dst, blockSize, apertureSize, k);

    Mat corner_check = src.clone();

    double max = dst.at<float>(0, 0);
    double min = dst.at<float>(0, 0);

    for (int i = 0; i < dst.rows; i++) {
        for (int j = 0; j < dst.cols; j++) {
            double val = dst.at<float>(i, j);
            if (max < val) {
                max = val;
            }
            if (min > val) {
                min = val;
            }
        }
    }

    printf("dst max:%e\ndst min:%e\n", max, min);

    /*
    Mat dst_norm, dst_norm_scaled;
    //����ȭ�� �ϰڴ�.

    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    //dst_norm�� dst�� 0~255�� ����ȭ�� ���� �ȴ�. ���� 32FC1��
    

    //�� ����ȭ �ڵ��� ������:
    //�� ���󸶴� Harris Corner�� R ���� �ּ�, �ִ밪�� �ٸ���.
    //��, ���󸶴� ���� R ���̾ �ǹ̰� �ٸ��� �װ� ����ȭ�ؼ� �ϰ� �����ϴ� ���� ���� �����̶�� �� �� ����.
    //�ƹ�ư, �̷� ���·� ¥�� k ������ ��� �� ���� ����.
    //���������� ����ȭ�� ���� �ʰ� ��� �� �� �� ����� ��������.

    
    for (int i = 0; i < dst_norm.rows; i++)
    {
        for (int j = 0; j < dst_norm.cols; j++)
        {
            if ((int)dst_norm.at<float>(i, j) > thresh)
            {
                circle(corner_check, Point(j, i), 3, Scalar(255,0,0), 2, 8, 0);
            }
        }
    }
    imshow(str, corner_check);
    */

    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            double val=dst.at<float>(i, j);
            if (abs(val) > Flat && val>0)
            {
                circle(corner_check, Point(j, i), 3, Scalar(255, 0, 0), 2, 8, 0);
            }
        }
    }
    imshow(str, corner_check);
    
}
