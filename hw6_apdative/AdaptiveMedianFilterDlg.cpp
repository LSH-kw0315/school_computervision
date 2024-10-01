// AdaptiveMedianFilterDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "AdaptiveMedianFilterDlg.h"


// AdaptiveMedianFilterDlg 대화 상자

IMPLEMENT_DYNAMIC(AdaptiveMedianFilterDlg, CDialogEx)

AdaptiveMedianFilterDlg::AdaptiveMedianFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AdaptiveMedianFilter, pParent)
{
	radio_Noise = 0;
	nNoise = 2;
}

AdaptiveMedianFilterDlg::~AdaptiveMedianFilterDlg()
{
}

void AdaptiveMedianFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_windowsize);
	DDX_Radio(pDX, IDC_Adaptive_Gaussian, radio_Noise);
}


BEGIN_MESSAGE_MAP(AdaptiveMedianFilterDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_Adaptive_Gaussian, IDC_Adaptive_SaltAndPepper,OnClickedRadio)
	ON_BN_CLICKED(IDCANCEL, &AdaptiveMedianFilterDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &AdaptiveMedianFilterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AdaptiveMedianFilterDlg 메시지 처리기
void AdaptiveMedianFilterDlg:: OnClickedRadio(UINT msg) {
	UpdateData(TRUE);
	switch (radio_Noise)
	{
		case 0://가우시안
			nNoise = 0;
			break;
		case 1://소금후추
			nNoise = 1;
			break;
	}
}

int AdaptiveMedianFilterDlg::GetNoiseType() {
	return nNoise;
}

int AdaptiveMedianFilterDlg::GetMaxWindowSize() {
	return maxWindowSize;
}

void AdaptiveMedianFilterDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void AdaptiveMedianFilterDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str_windowsize;
	edit_windowsize.GetWindowTextA(str_windowsize);
	maxWindowSize = atoi(str_windowsize);
	if (maxWindowSize <= 0) {
		MessageBox("1 이상의 정수만 입력 가능합니다.");
		return;
	}
	CDialogEx::OnOK();
}
