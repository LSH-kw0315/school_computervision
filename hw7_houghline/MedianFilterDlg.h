#pragma once
#include "afxdialogex.h"


// MedianFilterDlg 대화 상자

class MedianFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MedianFilterDlg)

public:
	MedianFilterDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MedianFilterDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MedianFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CEdit edit_KernelSize;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClickedRadio(UINT msg);
	int radio_Noise;
	int GetNoiseType();
	int GetKernelSize();
private:
	int kernelSize;
	int nNoise;
};
