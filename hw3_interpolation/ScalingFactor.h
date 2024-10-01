#pragma once
#include "afxdialogex.h"


// ScalingFactor 대화 상자

class ScalingFactor : public CDialogEx
{
	DECLARE_DYNAMIC(ScalingFactor)

public:
	ScalingFactor(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ScalingFactor();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Scaling };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int interpolation_select;
	afx_msg void OnClickedRadio(UINT msg);
	int GetInterpolation();
	double GetScale();

private:
	double scale;
	int interpolation;
public:
	CEdit edit_Scale;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
