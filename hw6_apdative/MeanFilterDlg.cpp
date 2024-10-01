// MeanFilterDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "MeanFilterDlg.h"


// MeanFilterDlg 대화 상자

IMPLEMENT_DYNAMIC(MeanFilterDlg, CDialogEx)

MeanFilterDlg::MeanFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MeanFilter, pParent)
	, radio_Noise(0)
{
	nNoise = 0;
}

MeanFilterDlg::~MeanFilterDlg()
{
}

void MeanFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_Mean_Gaussian, radio_Noise);
	DDX_Control(pDX, IDC_EDIT1, edit_KernelSize);
}


BEGIN_MESSAGE_MAP(MeanFilterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &MeanFilterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MeanFilterDlg::OnBnClickedCancel)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_Mean_Gaussian,IDC_Mean_SaltAndPepper,OnClickedRadio)
END_MESSAGE_MAP()


// MeanFilterDlg 메시지 처리기


void MeanFilterDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str_kernelSize;
	edit_KernelSize.GetWindowTextA(str_kernelSize);
	kernelSize = atoi(str_kernelSize);
	if (kernelSize <= 0) {
		MessageBox("커널의 크기는 1 이상이어야 합니다.");
		return;
	}
	CDialogEx::OnOK();
}


void MeanFilterDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void MeanFilterDlg::OnClickedRadio(UINT msg) {
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

int MeanFilterDlg::GetKernelSize() {
	return kernelSize;
}

int MeanFilterDlg::GetNoiseType() {
	return nNoise;
}
