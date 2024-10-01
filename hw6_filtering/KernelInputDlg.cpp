// KernelInputDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "KernelInputDlg.h"


// KernelInputDlg 대화 상자

IMPLEMENT_DYNAMIC(KernelInputDlg, CDialogEx)

KernelInputDlg::KernelInputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KernelInput, pParent)
{

}

KernelInputDlg::~KernelInputDlg()
{
}

void KernelInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
void KernelInputDlg::setKernelSize(int size) {
	kernel_size = size;
}


BEGIN_MESSAGE_MAP(KernelInputDlg, CDialogEx)
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDOK, &KernelInputDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &KernelInputDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// KernelInputDlg 메시지 처리기
void KernelInputDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) {
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
	list = (HWND*)malloc(sizeof(HWND) * (2 * kernel_size + 1) * (2 * kernel_size + 1));
	for (int i = 0; i < (2 * kernel_size + 1); i++) {
		for (int j = 0; j < 2 * kernel_size + 1; j++) {
			HWND edit = ::CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE, (j) * 60, (i) * 30, 55, 20, m_hWnd, NULL, NULL, NULL);
			list[i * (2 * kernel_size+1) + j] = edit;
		}
	}
}



void KernelInputDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	kernel = (double*)malloc(sizeof(double) * (2 * kernel_size + 1) * (2 * kernel_size + 1));
	for (int i = 0; i < (2 * kernel_size + 1) * (2 * kernel_size + 1); i++) {
		kernel[i] = 0;
	}
	for (int i = 0; i < (2 * kernel_size + 1) * (2 * kernel_size+1); i++) {
		
		int len=::SendMessage(list[i], WM_GETTEXTLENGTH, 0, 0);
		char* tmp = (char*)malloc(len + 1);
		::SendMessage(list[i], WM_GETTEXT, len+1, (LPARAM)tmp);	
		kernel[i]=atof(tmp);

	}

	CDialogEx::OnOK();
}

double* KernelInputDlg::getKernel() {
	return kernel;
}

void KernelInputDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
