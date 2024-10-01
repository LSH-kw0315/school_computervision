// RawInfo.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "RawInfo.h"


// RawInfo 대화 상자

IMPLEMENT_DYNAMIC(RawInfo, CDialogEx)

RawInfo::RawInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RawInfo, pParent)
	, radio_RawFileInfo(0)
{
	nFormat = 2;
}

RawInfo::~RawInfo()
{
}

void RawInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RawInfo_Gray, radio_RawFileInfo);

}


BEGIN_MESSAGE_MAP(RawInfo, CDialogEx)
	ON_BN_CLICKED(IDC_RawInfo_OK, &RawInfo::OnBnClickedRawinfoOk)
	ON_BN_CLICKED(IDC_RawInfo_Cancel, &RawInfo::OnBnClickedRawinfoCancel)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_RawInfo_Gray,IDC_RawInfo_YUV444,OnClickedRadio)
END_MESSAGE_MAP()


// RawInfo 메시지 처리기


void RawInfo::OnBnClickedRawinfoOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	CDialogEx::OnOK();
}


void RawInfo::OnBnClickedRawinfoCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
	
}

void RawInfo::OnClickedRadio(UINT msg) {
	UpdateData(TRUE);
	switch (radio_RawFileInfo) {
	case 0://gray
		nFormat = 2;
		break;
	case 1://yuv444
		nFormat = 0;
		break;
	case 2://rgb
		nFormat = 1;
		break;
	}

}

int RawInfo::GetRawFormat() {
	return nFormat;
}