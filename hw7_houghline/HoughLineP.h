#pragma once
#include "afxdialogex.h"


// HoughLineP 대화 상자

class HoughLineP : public CDialogEx
{
	DECLARE_DYNAMIC(HoughLineP)

public:
	HoughLineP(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~HoughLineP();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HoughLineP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit edit_rho;
	CEdit edit_theta;
	CEdit edit_threshold;
	CEdit edit_minLength;
	CEdit edit_maxGap;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	double getRho();
	double getTheta();
	int getThreshold();
	double getMinLength();
	double getMaxGap();
	int getT1();
	int getT2();
private:
	double rho;
	double theta;
	int threshold;
	double minLength;
	double maxGap;
	int t1;
	int t2;
public:
	CEdit edit_t1;
	CEdit edit_t2;
};
