#pragma once
#include "afxdialogex.h"


// MeanFilterDlg 대화 상자

class MeanFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MeanFilterDlg)

public:
	MeanFilterDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MeanFilterDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MeanFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int radio_Noise;
	CEdit edit_KernelSize;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClickedRadio(UINT msg);
	int GetNoiseType();
	int GetKernelSize();
private:
	int kernelSize;
	int nNoise;
};
