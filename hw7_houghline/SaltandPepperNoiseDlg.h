#pragma once
#include "afxdialogex.h"


// SaltandPepperNoiseDlg 대화 상자

class SaltandPepperNoiseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SaltandPepperNoiseDlg)

public:
	SaltandPepperNoiseDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SaltandPepperNoiseDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SaltandPepperNoise };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit edit_whiteNoise;
	CEdit edit_blackNoise;
	double GetWhiteNoiseProb();
	double GetBlackNoiseProb();
private:
	double whitenoise_Prob;
	double blacknoise_Prob;
};
