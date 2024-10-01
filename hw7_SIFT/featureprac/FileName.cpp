#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
using namespace cv;
using std::cout;
using std::endl;
int main(int argc, char* argv[])
{
    Mat img1 = imread("input.jpg");
    Mat img2 = imread("input_resize.jpg");

    resize(img1, img1, Size(0,0), 0.7, 0.7);
    resize(img2, img2, Size(0, 0), 0.7, 0.7);
    // 
    //-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
    int minHessian = 400;
    Ptr<SIFT> detector = SIFT::create(minHessian);
    std::vector<KeyPoint> keypoints1, keypoints2;
    std::vector<Point2f> point1, point2;
    Mat descriptors1, descriptors2;
    detector->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
    detector->detectAndCompute(img2, noArray(), keypoints2, descriptors2);


    KeyPoint::convert(keypoints1, point1);
    KeyPoint::convert(keypoints2, point2);

    Mat img1_copy = img1.clone();
    Mat img2_copy = img2.clone();
    for (int i = 0; i < point1.size(); i++) {
        int x = (int)point1[i].x;
        int y = (int)point1[i].y;
        circle(img1_copy, Point(x, y), 5, Scalar(0), 2, 8, 0);
    }

    for (int i = 0; i < point2.size(); i++) {
        int x = (int)point2[i].x;
        int y = (int)point2[i].y;
        circle(img2_copy, Point(x, y), 5, Scalar(0), 2, 8, 0);
    }

    Mat show_together = Mat(max(img2_copy.rows,img1_copy.rows), img1_copy.cols + img2_copy.cols, CV_8UC3);
    for (int i = 0; i < img1_copy.rows; i++) {
        for (int j = 0; j < img1_copy.cols; j++) {
             show_together.data[3 * (i * show_together.cols + j)] = img1_copy.data[3 * (i * img1_copy.cols + j)];
             show_together.data[3 * (i * show_together.cols + j) + 1] = img1_copy.data[3 * (i * img1_copy.cols + j) + 1];
             show_together.data[3 * (i * show_together.cols + j) + 2] = img1_copy.data[3 * (i * img1_copy.cols + j) + 2];
            
        }
    }

    for (int i = 0; i < img2_copy.rows; i++) {
        for (int j = 0; j < img2_copy.cols; j++) {
            show_together.data[3 * (i * show_together.cols + j+img1_copy.cols)] = img2_copy.data[3 * (i * img2_copy.cols + j)];
            show_together.data[3 * (i * show_together.cols + j + img1_copy.cols) + 1] = img2_copy.data[3 * (i * img2_copy.cols + j) + 1];
            show_together.data[3 * (i * show_together.cols + j + img1_copy.cols) + 2] = img2_copy.data[3 * (i * img2_copy.cols + j) + 2];

        }
    }
    imshow("what i get", show_together);
    waitKey(0);
    //-- Step 2: Matching descriptor vectors with a FLANN based matcher
    // Since SURF is a floating-point descriptor NORM_L2 is used
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
    std::vector< std::vector<DMatch> > knn_matches;//같은 것끼리 vector로 저장
    matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);//vector를 보고 그림을 그림
    //-- Filter matches using the Lowe's ratio test
    float ratio_thresh;
    for (int k = 0; k < 10; k++) {
        ratio_thresh = (k + 1) * 0.1f;
        std::vector<DMatch> good_matches;
        for (size_t i = 0; i < knn_matches.size(); i++)
        {
            if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)//distance: 둘이 얼마나 유사한지 유사도
            {
                good_matches.push_back(knn_matches[i][0]);
            }
        }
        //-- Draw matches
        Mat img_matches;
        drawMatches(img1, keypoints1, img2, keypoints2, good_matches, img_matches, Scalar::all(-1),
            Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
        //-- Show detected matches
        imshow("Good Matches", img_matches);
        waitKey(0);
    }
    return 0;
}