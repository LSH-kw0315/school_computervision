// SaveDialog.cpp: 구현 파일
//

#ifndef HHHH
#define HHHH

#endif // !

#include "pch.h"
#include "MFCApplication3.h"
#include "afxdialogex.h"
#include "SaveDialog.h"
#include "FormatAndInterPolation.h"
#include <string>

// SaveDialog 대화 상자

IMPLEMENT_DYNAMIC(SaveDialog, CDialogEx)

SaveDialog::SaveDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Save, pParent)
{

}

SaveDialog::~SaveDialog()
{
}

void SaveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Save_Interpolation, interpolation_type);
	DDX_Control(pDX, IDC_Save_ImageWidth, image_width);
	DDX_Control(pDX, IDC_Save_Imageheight, image_height);
	DDX_Control(pDX, IDC_Save_Outputformat, rawFile_format);
}


BEGIN_MESSAGE_MAP(SaveDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &SaveDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &SaveDialog::OnBnClickedCancel)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// SaveDialog 메시지 처리기


void SaveDialog::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void SaveDialog::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

void SaveDialog::setInterpolation(int mode) {
	val_interpolation_type = mode;
}

void SaveDialog::setImageHeight(int height) {
	val_image_height = height;
}

void SaveDialog::setImageWidth(int width) {
	val_image_width = width;
}

void SaveDialog::setRawFileFormat(int mode) {
	val_rawFile_format = mode;
}

void SaveDialog::updateInfo() {
	image_height.SetWindowTextA(std::to_string(val_image_height).c_str());
	image_width.SetWindowTextA(std::to_string(val_image_width).c_str());

	switch (val_interpolation_type)
	{
	case InterpolationMode::BiCubic:
		interpolation_type.SetWindowTextA("Bicubic Interpolation");
		break;
	case InterpolationMode::BiLinear:
		interpolation_type.SetWindowTextA("Bilinear Interpolation");
		break;
	default:
		break;
	}

	switch (val_rawFile_format)
	{
	case ImageFormat::GRAY:
		rawFile_format.SetWindowTextA("Y(Gray Scale)");
		break;
	case ImageFormat::YUV:
		rawFile_format.SetWindowTextA("YUV");
		break;
	case ImageFormat::RGB:
		rawFile_format.SetWindowTextA("RGB");
		break;
	default:
		break;
	}

}


void SaveDialog::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	updateInfo();
}
