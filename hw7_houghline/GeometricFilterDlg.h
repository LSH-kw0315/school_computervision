#pragma once
#include "afxdialogex.h"


// GeometricFilterDlg 대화 상자

class GeometricFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GeometricFilterDlg)

public:
	GeometricFilterDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~GeometricFilterDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GeometricFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit edit_kernelSize;
	afx_msg void OnClickedRadio(UINT msg);
	int GetKernelSize();
	int GetNoiseType();
	int radio_Noise;
private:
	int kernelSize;
	int nNoise;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
