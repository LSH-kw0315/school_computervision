// ScalingFactor.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "ScalingFactor.h"


// ScalingFactor 대화 상자

IMPLEMENT_DYNAMIC(ScalingFactor, CDialogEx)

ScalingFactor::ScalingFactor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Scaling, pParent)
	, interpolation_select(0)
{
	interpolation = 0;
}

ScalingFactor::~ScalingFactor()
{
}

void ScalingFactor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_Scaling_Bilinear, interpolation_select);
	DDX_Control(pDX, IDC_Scaling_scale, edit_Scale);
}


BEGIN_MESSAGE_MAP(ScalingFactor, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_Scaling_Bilinear, IDC_Scaling_Bicubic, OnClickedRadio)
	ON_BN_CLICKED(IDOK, &ScalingFactor::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ScalingFactor::OnBnClickedCancel)
END_MESSAGE_MAP()


// ScalingFactor 메시지 처리기
void ScalingFactor::OnClickedRadio(UINT msg) {
	UpdateData(TRUE);
	switch (interpolation_select) {
	case 0://bilinear
		interpolation = 0;
		break;
	case 1://bicubic
		interpolation = 1;
		break;
	}
}

void ScalingFactor::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str_scale;
	CString str_interpolation;

	edit_Scale.GetWindowTextA(str_scale);
	
	scale = atof(str_scale);
	CDialogEx::OnOK();
}


void ScalingFactor::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

double ScalingFactor::GetScale() {
	return scale;
}

int ScalingFactor::GetInterpolation() {
	return interpolation;
}
