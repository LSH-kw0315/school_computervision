#pragma once
#include "afxdialogex.h"


// SaveDialog 대화 상자

class SaveDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SaveDialog)

public:
	SaveDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SaveDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Save };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CStatic interpolation_type;
	CStatic image_width;
	CStatic image_height;
	CStatic rawFile_format;

	int val_interpolation_type;
	int val_image_width;
	int val_image_height;
	int val_rawFile_width;
	int val_rawFile_height;
	int val_rawFile_format;

	void setInterpolation(int mode);
	void setImageWidth(int width);
	void setImageHeight(int height);
	void setRawFileFormat(int mode);
	void updateInfo();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
