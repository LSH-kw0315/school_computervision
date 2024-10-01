// SaltandPepperNoiseDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "SaltandPepperNoiseDlg.h"


// SaltandPepperNoiseDlg 대화 상자

IMPLEMENT_DYNAMIC(SaltandPepperNoiseDlg, CDialogEx)

SaltandPepperNoiseDlg::SaltandPepperNoiseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SaltandPepperNoise, pParent)
{

}

SaltandPepperNoiseDlg::~SaltandPepperNoiseDlg()
{
}

void SaltandPepperNoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_whiteNoise);
	DDX_Control(pDX, IDC_EDIT2, edit_blackNoise);

}


BEGIN_MESSAGE_MAP(SaltandPepperNoiseDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &SaltandPepperNoiseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &SaltandPepperNoiseDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// SaltandPepperNoiseDlg 메시지 처리기


void SaltandPepperNoiseDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str_whiteNoise;
	CString str_blackNoise;
	edit_whiteNoise.GetWindowTextA(str_whiteNoise);
	edit_blackNoise.GetWindowTextA(str_blackNoise);

	whitenoise_Prob = atof(str_whiteNoise);
	blacknoise_Prob = atof(str_blackNoise);

	if (whitenoise_Prob <= 0 || whitenoise_Prob >= 1 || blacknoise_Prob <= 0 || blacknoise_Prob >= 1) {
		MessageBox("확률이 1 이상이거나 0 이하일 수 없습니다.");
		return;
	}

	CDialogEx::OnOK();
}


void SaltandPepperNoiseDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

double SaltandPepperNoiseDlg::GetWhiteNoiseProb() {
	return whitenoise_Prob;
}

double SaltandPepperNoiseDlg::GetBlackNoiseProb() {
	return blacknoise_Prob;
}