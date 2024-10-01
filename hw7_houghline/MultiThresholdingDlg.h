#pragma once
#include "afxdialogex.h"


// MultiThresholdingDlg 대화 상자

class MultiThresholdingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MultiThresholdingDlg)

public:
	MultiThresholdingDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MultiThresholdingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MultiThresholding };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit edit_t1;
	CEdit edit_t2;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int GetT1();
	int GetT2();
	int GetLow();
	int GetMiddle();
	int GetHigh();
private:
	int t1;
	int t2;
	int low;
	int middle;
	int high;
public:
	CEdit edit_low;
	CEdit edit_middle;
	CEdit edit_high;
};
