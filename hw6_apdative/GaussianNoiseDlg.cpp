// GaussianNoiseDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "GaussianNoiseDlg.h"


// GaussianNoiseDlg 대화 상자

IMPLEMENT_DYNAMIC(GaussianNoiseDlg, CDialogEx)

GaussianNoiseDlg::GaussianNoiseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GaussianNoise, pParent)
{

}

GaussianNoiseDlg::~GaussianNoiseDlg()
{
}

void GaussianNoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_mean);
	DDX_Control(pDX, IDC_EDIT2, edit_stddev);
}


BEGIN_MESSAGE_MAP(GaussianNoiseDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &GaussianNoiseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &GaussianNoiseDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// GaussianNoiseDlg 메시지 처리기

double GaussianNoiseDlg::GetMean() {
	return mean;
}

double GaussianNoiseDlg::GetStdDev() {
	return stddev;
}

void GaussianNoiseDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str_mean;
	CString str_stddev;

	edit_mean.GetWindowTextA(str_mean);
	edit_stddev.GetWindowTextA(str_stddev);

	mean = atof(str_mean);
	stddev = atof(str_stddev);

	CDialogEx::OnOK();
}


void GaussianNoiseDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
