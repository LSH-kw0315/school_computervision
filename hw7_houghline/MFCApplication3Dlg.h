
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
#include "AdaptiveMedianFilterDlg.h"
#include "GaussianNoiseDlg.h"
#include "GeometricFilterDlg.h"
#include "MedianFilterDlg.h"
#include "SaltandPepperNoiseDlg.h"
#include "MeanFilterDlg.h"
#include "HoughLineP.h"
#include "MultiThresholdingDlg.h"

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
	AdaptiveMedianFilterDlg adaptiveMedian_dlg;
	GaussianNoiseDlg gaussianNoise_dlg;
	GeometricFilterDlg geometricFilter_dlg;
	MedianFilterDlg medianFilter_dlg;
	SaltandPepperNoiseDlg saltandpepperNoise_dlg;
	MeanFilterDlg meanFilter_dlg;
	HoughLineP houghlinep_dlg;
	MultiThresholdingDlg multiThresholding_dlg;

	void UpdateInfo();
	afx_msg void OnBnClickedMainUpdateinfo();
	afx_msg void OnBnClickedMainScaleinfo();
	cv::Mat original_Image;

	cv::Mat progressiveRGB_Mat;
	cv::Mat YUV_Mat;
	cv::Mat GrayScale_Mat;
	
	cv::Mat GaussianNoiseImage=cv::Mat();
	cv::Mat SaltAndPepperNoiseImage=cv::Mat();

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
	afx_msg void OnBnClickedMainAddgaussian();
	afx_msg void OnBnClickedMainAddsaltandpepper();
	afx_msg void OnBnClickedMainGeometricfilter();
	afx_msg void OnBnClickedMainMedianfilter();
	afx_msg void OnBnClickedMainAdaptivemedianfilter();
	afx_msg void OnBnClickedMainMeanfilter();
	afx_msg void OnBnClickedMainMultithresholding();
	afx_msg void OnBnClickedMainHounglinep();
};
