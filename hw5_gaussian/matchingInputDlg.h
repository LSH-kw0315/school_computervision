#pragma once
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>

// matchingInputDlg 대화 상자

class matchingInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(matchingInputDlg)

public:
	matchingInputDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~matchingInputDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ForDrawing };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnClose();
	afx_msg void OnBnClickedInputDraw();

	cv::Mat getDrawoutput();
private:
	cv::Mat draw_output;


};
