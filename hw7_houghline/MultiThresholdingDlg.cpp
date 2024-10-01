// MultiThresholdingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "MultiThresholdingDlg.h"


// MultiThresholdingDlg 대화 상자

IMPLEMENT_DYNAMIC(MultiThresholdingDlg, CDialogEx)

MultiThresholdingDlg::MultiThresholdingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MultiThresholding, pParent)
{
	t1 = 0;
	t2 = 0;
}

MultiThresholdingDlg::~MultiThresholdingDlg()
{
}

void MultiThresholdingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MultiThresholding_T1, edit_t1);
	DDX_Control(pDX, IDC_MultiThresholding_T2, edit_t2);
	DDX_Control(pDX, IDC_MultiThresholding_Low, edit_low);
	DDX_Control(pDX, IDC_MultiThresholding_Middle, edit_middle);
	DDX_Control(pDX, IDC_MultiThresholding_High, edit_high);
}


BEGIN_MESSAGE_MAP(MultiThresholdingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &MultiThresholdingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MultiThresholdingDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// MultiThresholdingDlg 메시지 처리기


void MultiThresholdingDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str_t1;
	CString str_t2;
	CString str_low;
	CString str_middle;
	CString str_high;

	edit_t1.GetWindowTextA(str_t1);
	edit_t2.GetWindowTextA(str_t2);
	edit_low.GetWindowTextA(str_low);
	edit_middle.GetWindowTextA(str_middle);
	edit_high.GetWindowTextA(str_high);


	int temp_t1 = atoi(str_t1);
	int temp_t2 = atoi(str_t2);
	int temp_low = atoi(str_low);
	int temp_middle = atoi(str_middle);
	int temp_high = atoi(str_high);

	if (temp_t1 < 0 || temp_t2 < 0|| temp_t1>255 || temp_t2>255 || temp_low<0 || temp_low>255 || temp_middle<0 || temp_middle>255 || temp_high<0 || temp_high>255) {
		MessageBox("유효하지 않은 값입니다.");
		return;
	}
	else if (temp_t1 >= temp_t2) {
		MessageBox("T1이 T2보다 큽니다..");
		return;
	}
	else {
		t1 = temp_t1;
		t2=temp_t2;
		low = temp_low;
		middle = temp_middle;
		high = temp_high;
		CDialogEx::OnOK();
	}

}


void MultiThresholdingDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

int MultiThresholdingDlg::GetT1() {
	return t1;
}

int MultiThresholdingDlg::GetT2() {
	return t2;
}

int MultiThresholdingDlg::GetHigh() {
	return high;
}

int MultiThresholdingDlg::GetMiddle() {
	return middle;
}

int MultiThresholdingDlg::GetLow() {
	return low;
}

