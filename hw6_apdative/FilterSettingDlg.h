#pragma once
#include "afxdialogex.h"
#include "KernelInputDlg.h"
// FilterSettingDlg 대화 상자

class FilterSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FilterSettingDlg)

public:
	FilterSettingDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~FilterSettingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FilterSetting };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit edit_kernel;
	CEdit edit_sigma;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	float getSigma();
	int getKernelSize();
	double* getKernel();

private:
	int kernel_size;
	float sigma;
	double* kernel;
};
