// GeometricFilterDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "GeometricFilterDlg.h"


// GeometricFilterDlg 대화 상자

IMPLEMENT_DYNAMIC(GeometricFilterDlg, CDialogEx)

GeometricFilterDlg::GeometricFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GeometricFilter, pParent)
{
	radio_Noise = 0;
	kernelSize = 0;
	nNoise = 0;

}

GeometricFilterDlg::~GeometricFilterDlg()
{
}

void GeometricFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_kernelSize);
	DDX_Radio(pDX, IDC_Geometric_Gaussian, radio_Noise);
}


BEGIN_MESSAGE_MAP(GeometricFilterDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_Geometric_Gaussian,IDC_Geometric_SaltAndPepper,OnClickedRadio)
	ON_BN_CLICKED(IDOK, &GeometricFilterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &GeometricFilterDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// GeometricFilterDlg 메시지 처리기

void GeometricFilterDlg::OnClickedRadio(UINT msg) {
	UpdateData(TRUE);
	switch (radio_Noise) {
		case 0:
			nNoise = 0;
			break;
		case 1:
			nNoise = 1;
			break;
	}
}

int GeometricFilterDlg::GetKernelSize() {
	return kernelSize;
}

int GeometricFilterDlg::GetNoiseType() {
	return nNoise;
}

void GeometricFilterDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str_kernelSize;
	edit_kernelSize.GetWindowTextA(str_kernelSize);
	kernelSize = atoi(str_kernelSize);
	if (kernelSize <= 0) {
		MessageBox("커널의 크기는 1 이상이어야 합니다.");
		return;
	}
	CDialogEx::OnOK();
}


void GeometricFilterDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
