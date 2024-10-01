// HoughLineP.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "HoughLineP.h"


// HoughLineP 대화 상자

IMPLEMENT_DYNAMIC(HoughLineP, CDialogEx)

HoughLineP::HoughLineP(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HoughLineP, pParent)
{
	rho = 0;
	maxGap = 0;
	theta = 0;
	threshold = 0;
	minLength = 0;
	maxGap = 0;
}

HoughLineP::~HoughLineP()
{
}

void HoughLineP::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HoughLineP_rho, edit_rho);
	DDX_Control(pDX, IDC_HoughLineP_theta, edit_theta);
	DDX_Control(pDX, IDC_HoughLineP_Thresholding, edit_threshold);
	DDX_Control(pDX, IDC_HoughLineP_minLength, edit_minLength);
	DDX_Control(pDX, IDC_HoughLineP_maxGap, edit_maxGap);
	DDX_Control(pDX, IDC_HoughLineP_T1, edit_t1);
	DDX_Control(pDX, IDC_HoughLineP_T2, edit_t2);
}


BEGIN_MESSAGE_MAP(HoughLineP, CDialogEx)
	ON_BN_CLICKED(IDOK, &HoughLineP::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &HoughLineP::OnBnClickedCancel)
END_MESSAGE_MAP()


// HoughLineP 메시지 처리기


void HoughLineP::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str_rho;
	CString str_theta;
	CString str_threshold;
	CString str_minLength;
	CString str_maxGap;
	CString str_T1;
	CString str_T2;

	edit_rho.GetWindowTextA(str_rho);
	edit_theta.GetWindowTextA(str_theta);
	edit_threshold.GetWindowTextA(str_threshold);
	edit_minLength.GetWindowTextA(str_minLength);
	edit_maxGap.GetWindowTextA(str_maxGap);
	edit_t1.GetWindowTextA(str_T1);
	edit_t2.GetWindowTextA(str_T2);

	double temp_rho = atof(str_rho);
	double temp_theta = atof(str_theta);
	int temp_threshold = atoi(str_threshold);
	double temp_minLength = atof(str_minLength);
	double temp_maxGap = atof(str_maxGap);
	int temp_t1 = atoi(str_T1);
	int temp_t2 = atoi(str_T2);

	if (temp_rho < 0 || temp_rho>1 || temp_theta < 0 || temp_theta>180 || temp_threshold <= 0 || temp_minLength <= 0 || temp_maxGap <= 0 || temp_t1 < 0 || temp_t1>255|| temp_t2<0 || temp_t2>255) {
		MessageBox("유효하지 않은 값이 하나 이상 존재합니다.");
		return;
	}
	else if (temp_t1>=temp_t2) {
		MessageBox("T1은 T2보다 작아야 합니다..");
		return;
	}
	else {
		rho = temp_rho;
		theta = temp_theta;
		threshold = temp_threshold;
		minLength = temp_minLength;
		maxGap = temp_maxGap;
		t1 = temp_t1;
		t2 = temp_t2;
		CDialogEx::OnOK();
	}
}


void HoughLineP::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

double HoughLineP::getRho() {
	return rho;
}
double HoughLineP::getTheta() {
	return theta;
}
int HoughLineP::getThreshold() {
	return threshold;
}
double HoughLineP::getMinLength() {
	return minLength;
}
double HoughLineP::getMaxGap() {
	return maxGap;
}
int HoughLineP::getT1() {
	return t1;
}
int HoughLineP::getT2() {
	return t2;
}