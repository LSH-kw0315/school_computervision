// PieseWiseDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "PieseWiseDlg.h"


// PieseWiseDlg 대화 상자

IMPLEMENT_DYNAMIC(PieseWiseDlg, CDialogEx)

PieseWiseDlg::PieseWiseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PiesewiseSetting, pParent)
{

}

PieseWiseDlg::~PieseWiseDlg()
{
}

void PieseWiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_r1);
	DDX_Control(pDX, IDC_EDIT2, edit_s1);
	DDX_Control(pDX, IDC_EDIT3, edit_r2);
	DDX_Control(pDX, IDC_EDIT4, edit_s2);
}


BEGIN_MESSAGE_MAP(PieseWiseDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &PieseWiseDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &PieseWiseDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// PieseWiseDlg 메시지 처리기


void PieseWiseDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CDialogEx::OnCancel();
}


void PieseWiseDlg::OnBnClickedOk()
{
	CString r1_str;
	edit_r1.GetWindowTextA(r1_str);

	CString s1_str;
	edit_s1.GetWindowTextA(s1_str);

	CString r2_str;
	edit_r2.GetWindowTextA(r2_str);

	CString s2_str;
	edit_s2.GetWindowTextA(s2_str);

	r1 = atoi(r1_str);
	s1 = atoi(s1_str);
	r2 = atoi(r2_str);
	s2 = atoi(s2_str);

	if (r1 < 0 || r1>255 || s1 < 0 || s1>255 || r2 < 0 || r2>255 || s2 < 0 || s2>255) {
		return;
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
