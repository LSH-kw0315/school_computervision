// MedianFilterDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "MedianFilterDlg.h"


// MedianFilterDlg 대화 상자

IMPLEMENT_DYNAMIC(MedianFilterDlg, CDialogEx)

MedianFilterDlg::MedianFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MedianFilter, pParent)
{
	nNoise = 0;
	kernelSize = 0;
	radio_Noise = 0;
}

MedianFilterDlg::~MedianFilterDlg()
{
}

void MedianFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_KernelSize);
	DDX_Radio(pDX, IDC_Median_Gaussian, radio_Noise);
}


BEGIN_MESSAGE_MAP(MedianFilterDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &MedianFilterDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &MedianFilterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MedianFilterDlg::OnBnClickedCancel)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_Median_Gaussian,IDC_Median_SaltAndPepper,OnClickedRadio)
END_MESSAGE_MAP()


// MedianFilterDlg 메시지 처리기


void MedianFilterDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void MedianFilterDlg::OnBnClickedOk()
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


void MedianFilterDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

void MedianFilterDlg::OnClickedRadio(UINT msg) {
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

int MedianFilterDlg::GetKernelSize() {
	return kernelSize;
}

int MedianFilterDlg::GetNoiseType() {
	return nNoise;
}