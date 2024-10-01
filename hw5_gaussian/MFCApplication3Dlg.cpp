
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
			GrayScale_Mat.data = GrayScaleReturner(original_Image.data, original_Image.rows, original_Image.cols);

			progressiveRGB_Mat = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
			progressiveRGB_Mat.data = ProgressiveReturner(original_Image.data, original_Image.rows, original_Image.cols);

			YUV_Mat =cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
			YUV_Mat.data = YUVReturner(original_Image.data, original_Image.rows, original_Image.cols);
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
			unsigned char* for_write = ProgressiveReturner(output_image.data,output_image.rows,output_image.cols);
			fopen_s(&fp,"output.rgb", "wb");
			fwrite(for_write, sizeof(unsigned char), 3 * output_width * output_height, fp);
			fclose(fp);

		}else if(rawInfo_dlg.GetRawFormat()==ImageFormat::YUV){
			unsigned char* YUV = YUVReturner(output_image.data, output_image.rows, output_image.cols);

			fopen_s(&fp,"output.yuv", "wb");
			fwrite(YUV, sizeof(unsigned char), 3 * output_width * output_height, fp);
			fclose(fp);
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
		int* bin=GetGrayHistogram(GrayScale_Mat.data,GrayScale_Mat.rows,GrayScale_Mat.cols);
		ShowHistogram(bin,"gray histogram");

	}
	else {
		int* bin_red=GetColorHistogram(original_Image.data,original_Image.rows,original_Image.cols,ColorType::Red);
		int* bin_green = GetColorHistogram(original_Image.data, original_Image.rows, original_Image.cols, ColorType::Green);
		int* bin_blue = GetColorHistogram(original_Image.data, original_Image.rows, original_Image.cols, ColorType::Blue);
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
		output.data = GrayHistogramEqualiztion(GrayScale_Mat.data, GrayScale_Mat.rows, GrayScale_Mat.cols);

	}
	else {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
		output.data = ColorHistogramEqualiztion(original_Image.data, original_Image.rows, original_Image.cols);
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
			output_image.data = GrayHistogramMatching(GrayScale_Mat.data, dlg.getDrawoutput().data, GrayScale_Mat.rows, GrayScale_Mat.cols, 256, 256);
			

		}
		else{
			output_image = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
			output_image.data = ColorHistogramMatching(original_Image.data, dlg.getDrawoutput().data, original_Image.rows, original_Image.cols, 256, 256);

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
		Pad = cv::Mat(original_Image.rows + 2 * N, original_Image.cols + 2 * N, CV_8UC1);
		Pad.data = GrayPadding(GrayScale_Mat.data, GrayScale_Mat.rows, GrayScale_Mat.cols, N);
		output.data = GraySmoothing(Pad.data, Pad.rows, Pad.cols, N);

	}
	else {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
		Pad = cv::Mat(original_Image.rows + 2 * N, original_Image.cols + 2 * N, CV_8UC3);
		Pad.data = ColorPadding(original_Image.data, original_Image.rows, original_Image.cols, N);
		output.data = ColorSmoothing(Pad.data, Pad.rows, Pad.cols, N);
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
		Pad = cv::Mat(original_Image.rows + 2*N, original_Image.cols +2*N, CV_8UC1);
		Pad.data = GrayPadding(GrayScale_Mat.data, GrayScale_Mat.rows, GrayScale_Mat.cols, N);
		output.data = GrayAverage(Pad.data, Pad.rows, Pad.cols, N);
		
	}
	else {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
		Pad = cv::Mat(original_Image.rows +2*N, original_Image.cols + 2*N, CV_8UC3);
		Pad.data = ColorPadding(original_Image.data, original_Image.rows, original_Image.cols, N);
		output.data = ColorAverage(Pad.data, Pad.rows, Pad.cols, N);
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
		output.data = GraySharpening(GrayScale_Mat.data, GrayScale_Mat.rows, GrayScale_Mat.cols, filterSetting_dlg.getKernel(), N);

	}
	else {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
		output.data = ColorSharpening(original_Image.data, original_Image.rows, original_Image.cols, filterSetting_dlg.getKernel(),N);
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
		output.data = GrayFiltering(GrayScale_Mat.data, GrayScale_Mat.rows, GrayScale_Mat.cols, filterSetting_dlg.getKernel(), N);

	}
	else {
		output = cv::Mat(original_Image.rows, original_Image.cols, CV_8UC3);
		output.data = ColorFiltering(original_Image.data, original_Image.rows, original_Image.cols, filterSetting_dlg.getKernel(), N);
	}
	cv::imshow("output", output);

}
