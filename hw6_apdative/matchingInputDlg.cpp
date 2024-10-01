// matchingInputDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "matchingInputDlg.h"
#include "forDrawing.hpp"


// matchingInputDlg 대화 상자

IMPLEMENT_DYNAMIC(matchingInputDlg, CDialogEx)

void onMouse(int ev, int x, int y, int flags, void* param) {
	if (ev == cv::EVENT_LBUTTONDOWN) {
		if (count >= 2) {
			matching_target = cv::Mat::zeros(256, 256, CV_8UC1);
			count = 0;
		}
		saved_x = x;
		saved_y = y;
		button_down = true;

	}
	if (ev == cv::EVENT_LBUTTONUP) {
		button_down = false;
		if (matching_target_onwork.empty()) {
			return;
		}
		for (int i = 0; i < matching_target.cols * matching_target.rows; i++) {
			matching_target.data[i] = matching_target_onwork.data[i];
			(*(cv::Mat*)param).data[i] = matching_target_onwork.data[i];;
		}
		cv::imshow("frame", matching_target);
		count++;
	}
	if (ev == cv::EVENT_MOUSEMOVE && button_down) {
		if (saved_x != x && saved_y != y) {
			for (int i = 0; i < matching_target.cols * matching_target.rows; i++) {
				matching_target_onwork.data[i] = matching_target.data[i];
			}
			cv::line(matching_target_onwork, cv::Point(saved_x, saved_y), cv::Point(x, y), cv::Scalar(255, 255, 255), 1);
			cv::imshow("frame", matching_target_onwork);
		}
	}
}

matchingInputDlg::matchingInputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ForDrawing, pParent)
{
	draw_output = cv::Mat::zeros(256, 256,CV_8UC1);
}

matchingInputDlg::~matchingInputDlg()
{
}

void matchingInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(matchingInputDlg, CDialogEx)
	ON_WM_ACTIVATE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDR_Input_Draw, &matchingInputDlg::OnBnClickedInputDraw)
END_MESSAGE_MAP()


// matchingInputDlg 메시지 처리기

void matchingInputDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

}


void matchingInputDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	cv::destroyAllWindows();
	CDialogEx::OnClose();
}

cv::Mat matchingInputDlg::getDrawoutput() {
	return draw_output;
}

void matchingInputDlg::OnBnClickedInputDraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cv::destroyAllWindows();
	button_down = false;
	matching_target = cv::Mat::zeros(256, 256, CV_8UC1);
	matching_target_onwork = cv::Mat::zeros(256, 256, CV_8UC1);
	cv::namedWindow("frame");
	cv::setMouseCallback("frame", onMouse, &draw_output);
	
}
