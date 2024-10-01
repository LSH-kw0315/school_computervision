#pragma once
#include "afxdialogex.h"


// AdaptiveMedianFilterDlg 대화 상자

class AdaptiveMedianFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AdaptiveMedianFilterDlg)

public:
	AdaptiveMedianFilterDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AdaptiveMedianFilterDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AdaptiveMedianFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit edit_windowsize;
	afx_msg void OnClickedRadio(UINT msg);
	int radio_Noise;
	int GetNoiseType();
	int GetMaxWindowSize();
private:
	int nNoise;
	int maxWindowSize;
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
