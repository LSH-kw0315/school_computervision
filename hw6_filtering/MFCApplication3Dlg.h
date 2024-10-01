
// MFCApplication3Dlg.h: 헤더 파일
//

#pragma once

#include "RawInfo.h"
#include "ScalingFactor.h"
#include <opencv2/opencv.hpp>
#include "SaveDialog.h"
#include "forDrawing.hpp"
#include "FilterSettingDlg.h"
#include "PieseWiseDlg.h"

// CMFCApplication3Dlg 대화 상자
class CMFCApplication3Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication3Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMainRawinfo();
	afx_msg void OnBnClickedMainOpen();
	RawInfo rawInfo_dlg;
	ScalingFactor scaling_dlg;
	FilterSettingDlg filterSetting_dlg;
	PieseWiseDlg pieseWise_dlg;
	void UpdateInfo();
	afx_msg void OnBnClickedMainUpdateinfo();
	afx_msg void OnBnClickedMainScaleinfo();
	cv::Mat original_Image;

	cv::Mat progressiveRGB_Mat;
	cv::Mat YUV_Mat;
	cv::Mat GrayScale_Mat;
	

	afx_msg void OnBnClickedMainImagedisplay();

	afx_msg void OnBnClickedMainCheckhistogram();
	afx_msg void OnBnClickedMainHistogramEqualization();
	afx_msg void OnBnClickedMainHistogramMatching();
	afx_msg void OnBnClickedMainFiltersetting();
	afx_msg void OnBnClickedMainSmoothing();
	afx_msg void OnBnClickedMainGaussian();
	afx_msg void OnBnClickedMainAvearge();
	afx_msg void OnBnClickedMainSharpening();

	afx_msg void OnBnClickedMainFilter();
	afx_msg void OnBnClickedMainPiesewise();
};
