#pragma once
#include "afxdialogex.h"


// RawInfo 대화 상자

class RawInfo : public CDialogEx
{
	DECLARE_DYNAMIC(RawInfo)

public:
	RawInfo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~RawInfo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RawInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int radio_RawFileInfo;
	bool isTrue;

	int GetRawFormat();

	afx_msg void OnBnClickedRawinfoOk();
	afx_msg void OnBnClickedRawinfoCancel();
	afx_msg void OnClickedRadio(UINT msg);

private:
	int nHeight;
	int nWidth;
	int nFormat;
};
