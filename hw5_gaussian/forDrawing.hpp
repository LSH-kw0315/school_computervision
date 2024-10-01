#include <opencv2/opencv.hpp>
static int saved_x=0;
static int saved_y=0;
static bool button_down;
static cv::Mat matching_target;
static cv::Mat matching_target_onwork;
static int count = 0;