#pragma once
#include "afxdialogex.h"


// GaussianNoiseDlg 대화 상자

class GaussianNoiseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GaussianNoiseDlg)

public:
	GaussianNoiseDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~GaussianNoiseDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GaussianNoise };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit edit_mean;
	CEdit edit_stddev;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	double GetMean();
	double GetStdDev();
private:
	double mean;
	double stddev;
};
