// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

VideoCapture cap;
std::vector<Mat> frames;
std::vector<Mat> frames_backup;
Mat frame;
Mat frame_onwork;
int saved_x;
int saved_y;
bool button_down;
double totalFrame;
double currentFrame;

void onMouse(int ev, int x, int y, int flags, void* param) {
    if (ev == cv::EVENT_LBUTTONDOWN) {
        saved_x = x;
        saved_y = y;
        button_down = true;
        
    }
    if (ev == cv::EVENT_LBUTTONUP) {
        button_down = false;
        if (frame_onwork.empty()) {
            return;
        }
        frame = frame_onwork.clone();
        frame_onwork = Mat();
        frames[currentFrame] = frame;
        imshow("frame", frame);
    }
    if (ev == cv::EVENT_MOUSEMOVE && button_down) {
        if (saved_x != x && saved_y != y) {
            frames[currentFrame] = frames_backup[currentFrame];
            frame = frames[currentFrame];
            frame_onwork = frame.clone();
            rectangle(frame_onwork, Point(saved_x, saved_y), Point(x, y), Scalar(0, 0, 255), 1);
            imshow("frame", frame_onwork);
        }
    }
}

int main()
{
    cap.open("video.mp4");
    if (!cap.isOpened()) {
        std::cout << "video cannot be found!\n";
        return -1;
    }

    totalFrame = cap.get(cv::CAP_PROP_FRAME_COUNT);
    currentFrame = 0;
    frames.resize(totalFrame);
    frames_backup.resize(totalFrame);


    for (int i = 0; i < totalFrame; i++) {
        cap >> frames[i];
        frames_backup[i] = frames[i];
    }

    frame = frames[0];


    bool isStop = true;
    int keyCode=-1;

    namedWindow("frame");

    setMouseCallback("frame", onMouse, &frame);


    while (1) {
        int64 start = getTickCount();
        if (currentFrame >= totalFrame) {
            break;
        }
        frame = frames[currentFrame];
        if (frame.empty()) {
            break;
        }

        
        imshow("frame", frame);

        if (isStop) {
            keyCode = waitKey(0);
            if (currentFrame<totalFrame &&(keyCode == 'N' || keyCode == 'n')) {
                currentFrame++;
            }
            else if (currentFrame>0 && (keyCode == 'P' || keyCode == 'p')) {
                currentFrame--;
            }
            else if (currentFrame<totalFrame && keyCode == ' ') {
                isStop = false;
                currentFrame++;
            }

        }
        else {
            currentFrame++;
            int64 end = getTickCount();
            double delay = ((end - start) / getTickFrequency()) * 1000;
            std::cout << "start:" << start << ", end:" << end << ", end-start:"<<end-start<<", ms:"<<delay<< std::endl;
            keyCode=waitKey(33-delay);
            if (keyCode == ' ') {
                isStop = true;
            }

        }



    }

}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
