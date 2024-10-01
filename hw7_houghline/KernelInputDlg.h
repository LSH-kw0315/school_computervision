#pragma once
#include "afxdialogex.h"


// KernelInputDlg 대화 상자

class KernelInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(KernelInputDlg)

public:
	KernelInputDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~KernelInputDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KernelInput };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void setKernelSize(int size);
	double* getKernel();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
private:
	int kernel_size;
	HWND* list;
	double* kernel;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
