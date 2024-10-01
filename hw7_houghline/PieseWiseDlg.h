#pragma once
#include "afxdialogex.h"


// PieseWiseDlg 대화 상자

class PieseWiseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PieseWiseDlg)

public:
	PieseWiseDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~PieseWiseDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PiesewiseSetting };
#endif



private:
	int r1=-1;
	int s1=-1;
	int r2=-1;
	int s2=-1;
public:
	int getR1() {
		return r1;
	}
	int getR2() {
		return r2;
	}
	int getS1() {
		return s1;
	}
	int getS2() {
		return s2;
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CEdit edit_r1;
	CEdit edit_s1;
	CEdit edit_r2;
	CEdit edit_s2;
};
