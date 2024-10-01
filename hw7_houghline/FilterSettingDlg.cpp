// FilterSettingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "FilterSettingDlg.h"


// FilterSettingDlg 대화 상자

IMPLEMENT_DYNAMIC(FilterSettingDlg, CDialogEx)

FilterSettingDlg::FilterSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FilterSetting, pParent)
{
	kernel_size = -1;
	sigma = -1;
}

FilterSettingDlg::~FilterSettingDlg()
{
}

void FilterSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FilterSetting_Kernel, edit_kernel);
	DDX_Control(pDX, IDC_FilterSetting_Sigma, edit_sigma);
}


BEGIN_MESSAGE_MAP(FilterSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &FilterSettingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &FilterSettingDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// FilterSettingDlg 메시지 처리기


void FilterSettingDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str_kernel;
	CString str_sigma;

	edit_kernel.GetWindowTextA(str_kernel);
	edit_sigma.GetWindowTextA(str_sigma);

	kernel_size = atoi(str_kernel);
	sigma = atof(str_sigma);
	KernelInputDlg dlg;
	dlg.setKernelSize(kernel_size);
	if (dlg.DoModal() == IDOK) {
		kernel = dlg.getKernel();
		CDialogEx::OnOK();
	}
	else {
		return;
	}
	
}


void FilterSettingDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

int FilterSettingDlg::getKernelSize() {
	return kernel_size;
}

float FilterSettingDlg::getSigma() {
	return sigma;
}

double* FilterSettingDlg::getKernel() {
	return kernel;
}