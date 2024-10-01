
// MFCApplication3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include <string>

#include "InterpolationCalCulator.hpp"
#include "FormatChanger.hpp"
#include "HistogramCaculation.hpp"
#include "matchingInputDlg.h"
#include "Filtering.hpp"
#include "PieseWiseLinearCaculator.hpp"
#include "Noise.hpp"
#include "PSNRCaculator.hpp"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 대화 상자



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Main_Rawinfo, &CMFCApplication3Dlg::OnBnClickedMainRawinfo)
	ON_BN_CLICKED(IDC_Main_Open, &CMFCApplication3Dlg::OnBnClickedMainOpen)
	ON_BN_CLICKED(IDC_Main_Updateinfo, &CMFCApplication3Dlg::OnBnClickedMainUpdateinfo)
	ON_BN_CLICKED(IDC_Main_ScaleInfo, &CMFCApplication3Dlg::OnBnClickedMainScaleinfo)
	ON_BN_CLICKED(IDC_Main_ImageDisplay, &CMFCApplication3Dlg::OnBnClickedMainImagedisplay)
	ON_BN_CLICKED(IDC_Main_CheckHistogram, &CMFCApplication3Dlg::OnBnClickedMainCheckhistogram)
	ON_BN_CLICKED(IDC_Main_Histogram_Equalization, &CMFCApplication3Dlg::OnBnClickedMainHistogramEqualization)
	ON_BN_CLICKED(IDC_Main_Histogram_Matching, &CMFCApplication3Dlg::OnBnClickedMainHistogramMatching)
	ON_BN_CLICKED(IDC_Main_FilterSetting, &CMFCApplication3Dlg::OnBnClickedMainFiltersetting)
	ON_BN_CLICKED(IDC_Main_Smoothing, &CMFCApplication3Dlg::OnBnClickedMainSmoothing)
	ON_BN_CLICKED(IDC_Main_Gaussian, &CMFCApplication3Dlg::OnBnClickedMainGaussian)
	ON_BN_CLICKED(IDC_Main_Avearge, &CMFCApplication3Dlg::OnBnClickedMainAvearge)
	ON_BN_CLICKED(IDC_Main_Sharpening, &CMFCApplication3Dlg::OnBnClickedMainSharpening)
	ON_BN_CLICKED(IDC_Main_Filter, &CMFCApplication3Dlg::OnBnClickedMainFilter)
	ON_BN_CLICKED(IDC_Main_PieseWise, &CMFCApplication3Dlg::OnBnClickedMainPiesewise)
	ON_BN_CLICKED(IDC_Main_AddGaussian, &CMFCApplication3Dlg::OnBnClickedMainAddgaussian)
	ON_BN_CLICKED(IDC_Main_AddSaltandPepper, &CMFCApplication3Dlg::OnBnClickedMainAddsaltandpepper)
	ON_BN_CLICKED(IDC_Main_GeometricFilter, &CMFCApplication3Dlg::OnBnClickedMainGeometricfilter)
	ON_BN_CLICKED(IDC_Main_MedianFilter, &CMFCApplication3Dlg::OnBnClickedMainMedianfilter)
	ON_BN_CLICKED(IDC_Main_AdaptiveMedianFilter, &CMFCApplication3Dlg::OnBnClickedMainAdaptivemedianfilter)
	ON_BN_CLICKED(IDC_Main_MeanFilter, &CMFCApplication3Dlg::OnBnClickedMainMeanfilter)
	ON_BN_CLICKED(IDC_Main_MultiThresholding, &CMFCApplication3Dlg::OnBnClickedMainMultithresholding)
	ON_BN_CLICKED(IDC_Main_HounglineP, &CMFCApplication3Dlg::OnBnClickedMainHounglinep)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 메시지 처리기

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnBnClickedMainRawinfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	rawInfo_dlg.DoModal();
}


void CMFCApplication3Dlg::OnBnClickedMainOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK) {
		cv::Mat test_image = cv::imread((const char*)dlg.GetPathName());
		if (test_image.empty()) {
			MessageBox("지원하지 않는 이미지거나 이미지가 아닙니다.");
			return;
		}
		else {
			original_Image = test_image;

			GrayScale_Mat = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC1);
			GrayScaleReturner(original_Image.data, GrayScale_Mat.data, original_Image.rows, original_Image.cols);

			progressiveRGB_Mat = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
			ProgressiveReturner(original_Image.data, progressiveRGB_Mat.data, original_Image.rows, original_Image.cols);

			YUV_Mat =cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
			YUVReturner(original_Image.data, YUV_Mat.data,original_Image.rows, original_Image.cols);
		}
		
	}
	


}

void CMFCApplication3Dlg::UpdateInfo() {

	if (!original_Image.empty()) {
		cv::imshow("image", original_Image);
	}
	else {
		MessageBox("업로드된 이미지가 없습니다.");
	}
}



void CMFCApplication3Dlg::OnBnClickedMainUpdateinfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateInfo();
}


void CMFCApplication3Dlg::OnBnClickedMainScaleinfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	scaling_dlg.DoModal();
}


void CMFCApplication3Dlg::OnBnClickedMainImagedisplay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//이미지 처리 및 출력

	if (original_Image.empty()) {
		MessageBox("이미지를 업로드 해주시기 바랍니다.");
		return;
	}
	else if (scaling_dlg.GetScale()<=0) {
		MessageBox("비율을 제대로 입력해주시기 바랍니다.");
		return;
	}
	else if (rawInfo_dlg.GetRawFormat()>2) {
		MessageBox("RAW 정보를 제대로 입력해주시기 바랍니다.");
		return;
	}
	
	int output_width=original_Image.cols*scaling_dlg.GetScale();
	int output_height= original_Image.rows* scaling_dlg.GetScale();
	int output_channels;

	cv::Mat clone_of_original;

	cv::Mat output_image;

	if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
		output_image = cv::Mat(output_width, output_height, CV_8UC1);
		output_channels = 1;
	}
	else {
		output_image = cv::Mat(output_width, output_height, CV_8UC3);
		output_channels = 3;
	}

	if (original_Image.channels()==3&&rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) { //회색조 변환
		clone_of_original = GrayScale_Mat.clone();
	}
	else {
		clone_of_original = original_Image.clone();
	}
	

	unsigned char* output_image_data;
	
	if (scaling_dlg.GetInterpolation()==InterpolationMode::BiLinear) {//바이리니어
		if (output_channels == 1) {//회색조 영상 보간
			output_image_data = MemAlloc(output_width*output_height,0);
			for (int cur_y = 0; cur_y < output_height; cur_y++) {
				for (int cur_x = 0; cur_x < output_width; cur_x++) {
					double exactly_input_x=cur_x/scaling_dlg.GetScale();
					double exactly_input_y=cur_y/scaling_dlg.GetScale();
					output_image_data[(cur_y * output_width)+cur_x] = Billinearinterpolation(clone_of_original.data, original_Image.rows, original_Image.cols, exactly_input_x, exactly_input_y, 1,ColorType::Gray);
				}
			}
		}
		else {//3색 영상 변환
			output_image_data = MemAlloc(3*output_width*output_height, 0);
			for (int cur_y = 0; cur_y < output_height; cur_y++) {
				for (int cur_x = 0; cur_x < output_width; cur_x++) {
					double exactly_input_x = cur_x / scaling_dlg.GetScale();
					double exactly_input_y = cur_y / scaling_dlg.GetScale();
					output_image_data[(3*(cur_y * output_width + cur_x))] = Billinearinterpolation(clone_of_original.data, original_Image.rows, original_Image.cols, exactly_input_x, exactly_input_y, 3, ColorType::Blue);
					output_image_data[(3*(cur_y * output_width + cur_x)) + 1] = Billinearinterpolation(clone_of_original.data, original_Image.rows, original_Image.cols, exactly_input_x, exactly_input_y, 3, ColorType::Green);
					output_image_data[(3 * (cur_y * output_width + cur_x)) + 2] = Billinearinterpolation(clone_of_original.data, original_Image.rows, original_Image.cols, exactly_input_x, exactly_input_y, 3, ColorType::Red);
				}
			}
		}


	}else{//바이큐빅

		if (output_channels == 1) {//회색조 영상 보간
			output_image_data = MemAlloc(output_width * output_height, 0);
			for (int cur_y = 0; cur_y < output_height; cur_y++) {
				for (int cur_x = 0; cur_x < output_width; cur_x++) {
					double exactly_input_x = cur_x / scaling_dlg.GetScale();
					double exactly_input_y = cur_y / scaling_dlg.GetScale();
					output_image_data[cur_y * output_width + cur_x] = Bicubicinterpolation(clone_of_original.data, original_Image.rows, original_Image.cols, exactly_input_x, exactly_input_y, 1, ColorType::Gray);
				}
			}
		}
		else {//3색 영상 보간
			
			output_image_data = MemAlloc(3 * output_width * output_height, 0);
			for (int cur_y = 0; cur_y < output_height; cur_y++) {
				for (int cur_x = 0; cur_x < output_width; cur_x++) {
					double exactly_input_x = cur_x / scaling_dlg.GetScale();
					double exactly_input_y = cur_y / scaling_dlg.GetScale();
					output_image_data[(3 * (cur_y * output_width + cur_x))] = Bicubicinterpolation(clone_of_original.data, original_Image.rows, original_Image.cols, exactly_input_x, exactly_input_y, 3, ColorType::Blue);
					output_image_data[(3 * (cur_y * output_width + cur_x)) + 1] = Bicubicinterpolation(clone_of_original.data, original_Image.rows, original_Image.cols, exactly_input_x, exactly_input_y, 3, ColorType::Green);
					output_image_data[(3 * (cur_y * output_width + cur_x)) + 2] = Bicubicinterpolation(clone_of_original.data, original_Image.rows, original_Image.cols, exactly_input_x, exactly_input_y, 3, ColorType::Red);
				}
			}
		}


		
	}

	output_image.data = output_image_data;
	cv::namedWindow("output", cv::WINDOW_AUTOSIZE);
	cv::imshow("output", output_image);

	//이미지 데이터 확인 및 저장
	SaveDialog save_dlg;
	save_dlg.setImageHeight(output_height);
	save_dlg.setImageWidth(output_width);
	save_dlg.setRawFileFormat(rawInfo_dlg.GetRawFormat());
	save_dlg.setInterpolation(scaling_dlg.GetInterpolation());


	if (save_dlg.DoModal() ==IDOK) {
		FILE* fp;
		if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
			fopen_s(&fp,"output.y", "wb");
			fwrite(output_image.data, sizeof(unsigned char), output_width * output_height, fp);
			fclose(fp);
		}
		else if (rawInfo_dlg.GetRawFormat() == ImageFormat::RGB) {
			unsigned char* for_write = MemAlloc(3 * output_width * output_height, 0);
			ProgressiveReturner(output_image.data, for_write,output_image.rows,output_image.cols);
			fopen_s(&fp,"output.rgb", "wb");
			fwrite(for_write, sizeof(unsigned char), 3 * output_width * output_height, fp);
			fclose(fp);
			MemFree(for_write);

		}else if(rawInfo_dlg.GetRawFormat()==ImageFormat::YUV){
			unsigned char* YUV = MemAlloc(3 * output_width * output_height, 0);
			YUVReturner(output_image.data,YUV, output_image.rows, output_image.cols);

			fopen_s(&fp,"output.yuv", "wb");
			fwrite(YUV, sizeof(unsigned char), 3 * output_width * output_height, fp);
			fclose(fp);
			MemFree(YUV);
		}
	}

	output_image.release();
	clone_of_original.release();
	MemFree(output_image_data);
}




void CMFCApplication3Dlg::OnBnClickedMainCheckhistogram()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다.");
		return;
	}

	if (rawInfo_dlg.GetRawFormat()==ImageFormat::GRAY) {
		int bin[256];
		GetGrayHistogram(GrayScale_Mat.data,bin,GrayScale_Mat.rows,GrayScale_Mat.cols);
		ShowHistogram(bin,"gray histogram");

	}
	else {
		int bin_red[256]; 
		GetColorHistogram(original_Image.data, bin_red, original_Image.rows, original_Image.cols, ColorType::Red);
		int bin_green[256]; 
		GetColorHistogram(original_Image.data, bin_green, original_Image.rows, original_Image.cols, ColorType::Green);
		int bin_blue[256];
		GetColorHistogram(original_Image.data, bin_blue,original_Image.rows, original_Image.cols, ColorType::Blue);
		ShowHistogram(bin_red, "red histogram");
		ShowHistogram(bin_green, "green histogram");
		ShowHistogram(bin_blue, "blue histogram");
	}
	
}


void CMFCApplication3Dlg::OnBnClickedMainHistogramEqualization()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다.");
		return;
	}
	cv::Mat output;
	if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
		output = cv::Mat(GrayScale_Mat.rows, GrayScale_Mat.cols, CV_8UC1);
		GrayHistogramEqualiztion(GrayScale_Mat.data, output.data,GrayScale_Mat.rows, GrayScale_Mat.cols);

	}
	else {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
		ColorHistogramEqualiztion(original_Image.data, output.data,original_Image.rows, original_Image.cols);
	}

	cv::imshow("histogram equlization",output);

}


void CMFCApplication3Dlg::OnBnClickedMainHistogramMatching()
{
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다.");
		return;
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	matchingInputDlg dlg;
	if (dlg.DoModal() == IDOK) {
		cv::Mat output_image;
		if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
			output_image = cv::Mat(GrayScale_Mat.rows, GrayScale_Mat.cols, CV_8UC1);
			GrayHistogramMatching(GrayScale_Mat.data, dlg.getDrawoutput().data, output_image.data,GrayScale_Mat.rows, GrayScale_Mat.cols, 256, 256);
			

		}
		else{
			output_image = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
			ColorHistogramMatching(original_Image.data, dlg.getDrawoutput().data, output_image.data,original_Image.rows, original_Image.cols, 256, 256);

		}

		cv::imshow("histogram matching",output_image);
	}
	

}


void CMFCApplication3Dlg::OnBnClickedMainFiltersetting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	filterSetting_dlg.DoModal();	
}


void CMFCApplication3Dlg::OnBnClickedMainSmoothing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다");
		return;
	}


	cv::Mat Pad;
	cv::Mat output;
	int N = filterSetting_dlg.getKernelSize();
	if (N <= 0) {
		MessageBox("커널 사이즈가 올바르지 않습니다.");
		return;
	}

	if (N > 1) {
		N = 1;
	}
	if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC1);
		GraySmoothing(GrayScale_Mat.data, output.data,GrayScale_Mat.rows, GrayScale_Mat.cols, N);

	}
	else {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
		ColorSmoothing(original_Image.data, output.data,original_Image.rows, original_Image.cols, N);
	}
	cv::imshow("output", output);
	
}


void CMFCApplication3Dlg::OnBnClickedMainGaussian()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다");
		return;
	}

	cv::Mat output;
	int N = filterSetting_dlg.getKernelSize();
	double Sigma = filterSetting_dlg.getSigma();
	if (N <= 0) {
		MessageBox("커널 사이즈가 올바르지 않습니다.");
		return;
	}
	if (Sigma <=0) {
		MessageBox("시그마가 올바르지 않습니다.");
		return;
	}
	if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
		cv::GaussianBlur(GrayScale_Mat, output, cv::Point(2*N+1, 2*N+1), Sigma, Sigma,cv::BorderTypes::BORDER_REFLECT);
	}
	else {
		cv::GaussianBlur(original_Image, output, cv::Point(2*N+1, 2*N+1), Sigma, Sigma, cv::BorderTypes::BORDER_REFLECT);
	}

	cv::imshow("output", output);
	
}


void CMFCApplication3Dlg::OnBnClickedMainAvearge()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다");
		return;
	}
	

	cv::Mat Pad;
	cv::Mat output;
	int N = filterSetting_dlg.getKernelSize();
	if (N <= 0) {
		MessageBox("커널 사이즈가 올바르지 않습니다.");
		return;
	}
	if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC1);
		GrayAverage(GrayScale_Mat.data, output.data,GrayScale_Mat.rows, GrayScale_Mat.cols, N);
		
	}
	else {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
		ColorAverage(original_Image.data, output.data,original_Image.rows, original_Image.cols, N);
	}
	cv::imshow("output", output);
	


}


void CMFCApplication3Dlg::OnBnClickedMainSharpening()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다");
		return;
	}


	cv::Mat Pad;
	cv::Mat output;
	int N = filterSetting_dlg.getKernelSize();
	if (N <= 0) {
		MessageBox("커널 사이즈가 올바르지 않습니다.");
		return;
	}

	if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC1);
		GraySharpening(GrayScale_Mat.data, output.data,GrayScale_Mat.rows, GrayScale_Mat.cols, filterSetting_dlg.getKernel(), N);

	}
	else {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
		ColorSharpening(original_Image.data, output.data,original_Image.rows, original_Image.cols, filterSetting_dlg.getKernel(),N);
	}
	cv::imshow("output", output);
}


void CMFCApplication3Dlg::OnBnClickedMainFilter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다");
		return;
	}


	cv::Mat output;
	int N = filterSetting_dlg.getKernelSize();
	if (N <= 0) {
		MessageBox("커널 사이즈가 올바르지 않습니다.");
		return;
	}

	if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC1);
		GrayFiltering(GrayScale_Mat.data, output.data,GrayScale_Mat.rows, GrayScale_Mat.cols, filterSetting_dlg.getKernel(), N);

	}
	else {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
		ColorFiltering(original_Image.data, output.data,original_Image.rows, original_Image.cols, filterSetting_dlg.getKernel(), N);
	}
	cv::imshow("output", output);

}


void CMFCApplication3Dlg::OnBnClickedMainPiesewise()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다");
		return;
	}
	if (pieseWise_dlg.DoModal() == IDOK) {
		double r1 = pieseWise_dlg.getR1();
		double s1 = pieseWise_dlg.getS1();

		double r2 = pieseWise_dlg.getR2();
		double s2 = pieseWise_dlg.getS2();

		cv::Mat output;
		if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
			output = cv::Mat(GrayScale_Mat.rows,GrayScale_Mat.cols,CV_8UC1);
			GrayPieseWiseLinear(GrayScale_Mat.data, output.data,GrayScale_Mat.rows, GrayScale_Mat.cols, r1, s1, r2, s2);
		}
		else {
			output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
			ColorPieseWiseLinear(original_Image.data, output.data,original_Image.rows, original_Image.cols, r1, s1, r2, s2);
		}

		cv::imshow("output", output);

	}
}




void CMFCApplication3Dlg::OnBnClickedMainAddgaussian()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다.");
		return;
	}

	GaussianNoiseImage = cv::Mat();
	if (gaussianNoise_dlg.DoModal() == IDOK) {
		double mean = gaussianNoise_dlg.GetMean();
		double stddev = gaussianNoise_dlg.GetStdDev();

		if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
			GaussianNoiseImage = cv::Mat(GrayScale_Mat.rows, GrayScale_Mat.cols, CV_8UC1);
			GaussianNoiseImage.data = InputGrayGaussianNoise(GrayScale_Mat.data, GrayScale_Mat.rows, GrayScale_Mat.cols, mean, stddev);

		}
		else {
			GaussianNoiseImage = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
			GaussianNoiseImage.data = InputColorGaussianNoise(original_Image.data, original_Image.rows, original_Image.cols, mean, stddev);
		}

		cv::imshow("Gaussian Noise", GaussianNoiseImage);
	}
}


void CMFCApplication3Dlg::OnBnClickedMainAddsaltandpepper()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다.");
		return;
	}

	SaltAndPepperNoiseImage = cv::Mat();
	if (saltandpepperNoise_dlg.DoModal() == IDOK) {
		double whiteProb = saltandpepperNoise_dlg.GetWhiteNoiseProb();
		double blackProb = saltandpepperNoise_dlg.GetBlackNoiseProb();

		if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
			SaltAndPepperNoiseImage = cv::Mat(GrayScale_Mat.rows, GrayScale_Mat.cols, CV_8UC1);
			SaltAndPepperNoiseImage.data = InputGraySaltPepperNoise(GrayScale_Mat.data, GrayScale_Mat.rows, GrayScale_Mat.cols, whiteProb, blackProb);

		}
		else {
			SaltAndPepperNoiseImage = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
			SaltAndPepperNoiseImage.data = InputColorSaltPepperNoise(original_Image.data, original_Image.rows, original_Image.cols, whiteProb, blackProb);
		}

		cv::imshow("Gaussian Noise", SaltAndPepperNoiseImage);
	}
}


void CMFCApplication3Dlg::OnBnClickedMainGeometricfilter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다.");
		return;
	}


	if (geometricFilter_dlg.DoModal() == IDOK) {
		int kernel_size = geometricFilter_dlg.GetKernelSize();
		int noiseType = geometricFilter_dlg.GetNoiseType();
		double psnr;
		if (noiseType > 1) {
			MessageBox("노이즈 타입 오류입니다.");
			return;
		}
		cv::Mat output;
		if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
			if (noiseType == NoiseType::Gaussian && GaussianNoiseImage.empty()) {
				MessageBox("가우시안 노이즈 이미지가 없습니다.");
				return;
			}
			else if(noiseType==NoiseType::Gaussian) {
				output = cv::Mat(GrayScale_Mat.rows, GrayScale_Mat.cols, CV_8UC1);
				GrayGeometricMeanFilter(GaussianNoiseImage.data, output.data,GaussianNoiseImage.rows, GaussianNoiseImage.cols, kernel_size);
				psnr = GetGrayPSNR(GrayScale_Mat.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

			else if (noiseType == NoiseType::SaltAndPepper && SaltAndPepperNoiseImage.empty()) {
				MessageBox("소금과 후추 노이즈 이미지가 없습니다..");
				return;
			}
			else {
				output = cv::Mat(GrayScale_Mat.rows, GrayScale_Mat.cols, CV_8UC1);
				GrayGeometricMeanFilter(SaltAndPepperNoiseImage.data, output.data,SaltAndPepperNoiseImage.rows, SaltAndPepperNoiseImage.cols, kernel_size);
				psnr = GetGrayPSNR(GrayScale_Mat.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

		}
		else {
			if (noiseType == NoiseType::Gaussian && GaussianNoiseImage.empty()) {
				MessageBox("가우시안 노이즈 이미지가 없습니다.");
				return;
			}
			else if (noiseType == NoiseType::Gaussian) {
				output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
				ColorGeometricMeanFilter(GaussianNoiseImage.data, output.data, GaussianNoiseImage.rows, GaussianNoiseImage.cols, kernel_size);
				psnr = GetColorPSNR(original_Image.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

			else if (noiseType == NoiseType::SaltAndPepper && SaltAndPepperNoiseImage.empty()) {
				MessageBox("소금과 후추 노이즈 이미지가 없습니다.");
				return;
			}
			else {
				output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
				ColorGeometricMeanFilter(SaltAndPepperNoiseImage.data, output.data,SaltAndPepperNoiseImage.rows, SaltAndPepperNoiseImage.cols, kernel_size);
				psnr = GetColorPSNR(original_Image.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

		}
		cv::imshow("output", output);
		std::string message;
		message = "PSRN:" + std::to_string(psnr) + "DB";
		MessageBox(message.c_str());
	}
}


void CMFCApplication3Dlg::OnBnClickedMainMedianfilter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다.");
		return;
	}


	if (medianFilter_dlg.DoModal() == IDOK) {
		int kernel_size = medianFilter_dlg.GetKernelSize();
		int noiseType = medianFilter_dlg.GetNoiseType();
		double psnr;
		if (noiseType > 1) {
			MessageBox("노이즈 타입 오류입니다.");
			return;
		}
		cv::Mat output;
		if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
			if (noiseType == NoiseType::Gaussian && GaussianNoiseImage.empty()) {
				MessageBox("가우시안 노이즈 이미지가 없습니다.");
				return;
			}
			else if (noiseType == NoiseType::Gaussian) {
				output = cv::Mat(GrayScale_Mat.rows, GrayScale_Mat.cols, CV_8UC1);
				GrayMedianFilter(GaussianNoiseImage.data, output.data, GaussianNoiseImage.rows, GaussianNoiseImage.cols, kernel_size);
				psnr = GetGrayPSNR(GrayScale_Mat.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

			else if (noiseType == NoiseType::SaltAndPepper && SaltAndPepperNoiseImage.empty()) {
				MessageBox("소금과 후추 노이즈 이미지가 없습니다..");
				return;
			}
			else {
				output = cv::Mat(GrayScale_Mat.rows, GrayScale_Mat.cols, CV_8UC1);
				GrayMedianFilter(SaltAndPepperNoiseImage.data, output.data, SaltAndPepperNoiseImage.rows, SaltAndPepperNoiseImage.cols, kernel_size);
				psnr = GetGrayPSNR(GrayScale_Mat.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

		}
		else {
			if (noiseType == NoiseType::Gaussian && GaussianNoiseImage.empty()) {
				MessageBox("가우시안 노이즈 이미지가 없습니다.");
				return;
			}
			else if (noiseType == NoiseType::Gaussian) {
				output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
				ColorMedianFilter(GaussianNoiseImage.data, output.data, GaussianNoiseImage.rows, GaussianNoiseImage.cols, kernel_size);
				psnr = GetColorPSNR(original_Image.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

			else if (noiseType == NoiseType::SaltAndPepper && SaltAndPepperNoiseImage.empty()) {
				MessageBox("소금과 후추 노이즈 이미지가 없습니다.");
				return;
			}
			else {
				output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
				ColorMedianFilter(SaltAndPepperNoiseImage.data, output.data, SaltAndPepperNoiseImage.rows, SaltAndPepperNoiseImage.cols, kernel_size);
				psnr = GetColorPSNR(original_Image.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

		}
		cv::imshow("output", output);
		std::string message;
		message = "PSRN:" + std::to_string(psnr) + "DB";
		MessageBox(message.c_str());
	}
}


void CMFCApplication3Dlg::OnBnClickedMainAdaptivemedianfilter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다.");
		return;
	}


	if (adaptiveMedian_dlg.DoModal() == IDOK) {
		int kernel_size = adaptiveMedian_dlg.GetMaxWindowSize();
		int noiseType = adaptiveMedian_dlg.GetNoiseType();
		double psnr;
		if (noiseType > 1) {
			MessageBox("노이즈 타입 오류입니다.");
			return;
		}
		cv::Mat output;
		if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
			if (noiseType == NoiseType::Gaussian && GaussianNoiseImage.empty()) {
				MessageBox("가우시안 노이즈 이미지가 없습니다.");
				return;
			}
			else if (noiseType == NoiseType::Gaussian) {
				output = cv::Mat(GrayScale_Mat.rows, GrayScale_Mat.cols, CV_8UC1);
				GrayAdaptiveMedianFilter(GaussianNoiseImage.data, output.data, GaussianNoiseImage.rows, GaussianNoiseImage.cols, kernel_size);
				psnr = GetGrayPSNR(GrayScale_Mat.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

			else if (noiseType == NoiseType::SaltAndPepper && SaltAndPepperNoiseImage.empty()) {
				MessageBox("소금과 후추 노이즈 이미지가 없습니다..");
				return;
			}
			else {
				output = cv::Mat(GrayScale_Mat.rows, GrayScale_Mat.cols, CV_8UC1);
				GrayAdaptiveMedianFilter(SaltAndPepperNoiseImage.data, output.data, SaltAndPepperNoiseImage.rows, SaltAndPepperNoiseImage.cols, kernel_size);
				psnr = GetGrayPSNR(GrayScale_Mat.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

		}
		else {
			if (noiseType == NoiseType::Gaussian && GaussianNoiseImage.empty()) {
				MessageBox("가우시안 노이즈 이미지가 없습니다.");
				return;
			}
			else if (noiseType == NoiseType::Gaussian) {
				output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
				ColorAdaptiveMedianFilter(GaussianNoiseImage.data, output.data, GaussianNoiseImage.rows, GaussianNoiseImage.cols, kernel_size);
				psnr = GetColorPSNR(original_Image.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

			else if (noiseType == NoiseType::SaltAndPepper && SaltAndPepperNoiseImage.empty()) {
				MessageBox("소금과 후추 노이즈 이미지가 없습니다.");
				return;
			}
			else {
				output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
				ColorAdaptiveMedianFilter(SaltAndPepperNoiseImage.data, output.data, SaltAndPepperNoiseImage.rows, SaltAndPepperNoiseImage.cols, kernel_size);
				psnr = GetColorPSNR(original_Image.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

		}
		cv::imshow("output", output);
		std::string message;
		message = "PSRN:" + std::to_string(psnr) + "DB";
		MessageBox(message.c_str());
	}
}

void CMFCApplication3Dlg::OnBnClickedMainMeanfilter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다.");
		return;
	}


	if (meanFilter_dlg.DoModal() == IDOK) {
		int kernel_size = meanFilter_dlg.GetKernelSize();
		int noiseType = meanFilter_dlg.GetNoiseType();
		double psnr;
		if (noiseType > 1) {
			MessageBox("노이즈 타입 오류입니다.");
			return;
		}
		cv::Mat output;
		if (rawInfo_dlg.GetRawFormat() == ImageFormat::GRAY) {
			if (noiseType == NoiseType::Gaussian && GaussianNoiseImage.empty()) {
				MessageBox("가우시안 노이즈 이미지가 없습니다.");
				return;
			}
			else if (noiseType == NoiseType::Gaussian) {
				output = cv::Mat(GrayScale_Mat.rows, GrayScale_Mat.cols, CV_8UC1);
				GrayAverage(GaussianNoiseImage.data, output.data, GaussianNoiseImage.rows, GaussianNoiseImage.cols, kernel_size);
				psnr = GetGrayPSNR(GrayScale_Mat.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

			else if (noiseType == NoiseType::SaltAndPepper && SaltAndPepperNoiseImage.empty()) {
				MessageBox("소금과 후추 노이즈 이미지가 없습니다..");
				return;
			}
			else {
				output = cv::Mat(GrayScale_Mat.rows, GrayScale_Mat.cols, CV_8UC1);
				GrayAverage(SaltAndPepperNoiseImage.data, output.data, SaltAndPepperNoiseImage.rows, SaltAndPepperNoiseImage.cols, kernel_size);
				psnr = GetGrayPSNR(GrayScale_Mat.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

		}
		else {
			if (noiseType == NoiseType::Gaussian && GaussianNoiseImage.empty()) {
				MessageBox("가우시안 노이즈 이미지가 없습니다.");
				return;
			}
			else if (noiseType == NoiseType::Gaussian) {
				output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
				ColorAverage(GaussianNoiseImage.data, output.data, GaussianNoiseImage.rows, GaussianNoiseImage.cols, kernel_size);
				psnr = GetColorPSNR(original_Image.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

			else if (noiseType == NoiseType::SaltAndPepper && SaltAndPepperNoiseImage.empty()) {
				MessageBox("소금과 후추 노이즈 이미지가 없습니다.");
				return;
			}
			else {
				output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
			ColorAverage(SaltAndPepperNoiseImage.data, output.data, SaltAndPepperNoiseImage.rows, SaltAndPepperNoiseImage.cols, kernel_size);
				psnr = GetColorPSNR(original_Image.data, output.data, GrayScale_Mat.rows, GrayScale_Mat.cols);
			}

		}
		cv::imshow("output", output);
		std::string message;
		message = "PSRN:" + std::to_string(psnr) + "DB";
		MessageBox(message.c_str());
	}
}


void CMFCApplication3Dlg::OnBnClickedMainMultithresholding()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다.");
		return;
	}

	if (multiThresholding_dlg.DoModal() == IDOK) {
		cv::Mat output=cv::Mat(original_Image.rows,original_Image.cols,CV_8UC1);
	
		int T1 = multiThresholding_dlg.GetT1();
		int T2 = multiThresholding_dlg.GetT2();
		int LOW_VALUE = multiThresholding_dlg.GetLow();
		int MIDDLE_VALUE = multiThresholding_dlg.GetMiddle();
		int HIGH_VALUE = multiThresholding_dlg.GetHigh();
		cv::Mat gray=cv::Mat(original_Image.rows,original_Image.cols,CV_8UC1);
		cv::cvtColor(original_Image, gray, cv::COLOR_BGR2GRAY);
		int bin[256];
		GetGrayHistogram(gray.data, bin, gray.rows, gray.cols);
		ShowHistogram(bin, "Histogram");
		for (int i = 0; i < GrayScale_Mat.rows * GrayScale_Mat.cols; i++) {
			if (GrayScale_Mat.data[i] < T1) {
				output.data[i] = LOW_VALUE;
			}
			else if (GrayScale_Mat.data[i] >= T1 && GrayScale_Mat.data[i] < T2) {
				output.data[i] = MIDDLE_VALUE;
			}
			else {
				output.data[i] = HIGH_VALUE;
			}
		}

		
		cv::imshow("output", output);
	}
}


void CMFCApplication3Dlg::OnBnClickedMainHounglinep()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (original_Image.empty()) {
		MessageBox("업로드된 이미지가 없습니다.");
		return;
	}

	if (houghlinep_dlg.DoModal() == IDOK) {
		double rho = houghlinep_dlg.getRho();
		double theta = houghlinep_dlg.getTheta();
		int threshold = houghlinep_dlg.getThreshold();
		double minLength = houghlinep_dlg.getMinLength();
		double maxGap = houghlinep_dlg.getMaxGap();
		int T1 = houghlinep_dlg.getT1();
		int T2 = houghlinep_dlg.getT2();

		cv::Mat gray = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC1);
		cv::cvtColor(original_Image, gray, cv::COLOR_BGR2GRAY);
		cv::Mat dst = gray.clone();
		cv::Mat color_dst = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
		Canny(original_Image, dst, T1, T2, 3); //여기에서 약한 엣지를 어디까지로 잡을지, 강한 엣지를 어디까지로 잡을지 정할 수 있다.
		cvtColor(dst, color_dst, cv::COLOR_GRAY2BGR);
		std::vector<cv::Vec4i> lines;
		HoughLinesP(dst, lines, rho, theta*CV_PI / 180, threshold, minLength, maxGap);//rho와 theta는 해상도와 관련있음.
		for (size_t i = 0; i < lines.size(); i++)
		{
			line(color_dst, cv::Point(lines[i][0], lines[i][1]),
				cv::Point(lines[i][2], lines[i][3]), cv::Scalar(0, 0, 255), 3, 8);
		}
		cv::imshow("Source", original_Image);
		cv::imshow("Lines", dst);
		cv::imshow("Detected Lines", color_dst);
	}

}
