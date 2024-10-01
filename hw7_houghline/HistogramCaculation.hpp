#include <opencv2/opencv.hpp>
#include "FormatAndInterPolation.h"

void GetGrayHistogram(unsigned char* img_data, int* bin,int rows,int cols) {
	for (int i = 0; i < 256; i++) {
		bin[i] = 0;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			bin[img_data[i * cols + j]]++;
		}
	}

}

void GetColorHistogram(unsigned char* img_data,int* bin,int rows,int cols,int ColorType){
	for (int i = 0; i < 256; i++) {
		bin[i] = 0;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			bin[img_data[3*(i * cols + j)+ColorType]]++;
		}
	}

}

void ShowHistogram(int* bin,char* string) {
	int max = -1;

	for (int i = 0; i < 256; i++) {
		if (bin[i] > max) {
			max = bin[i];
		}
	}

	cv::Mat output = cv::Mat::zeros(256, 256, CV_8UC1);


	for (int i = 0; i < output.cols; i++) {
		for (int j = 0; j < 256 * ((double)bin[i] / (double)max); j++) {
			output.data[(255 - j) * output.cols + i] = 255;
		}
	}

	cv::imshow(string, output);

}

void GrayHistogramEqualiztion(unsigned char* img_data,unsigned char* hist,int rows,int cols) {


	int* bin = (int*)malloc(sizeof(int) * 256);

	double pdf[256];

	double cdf[256];


	for (int i = 0; i < 256; i++) {
		pdf[i] = 0;
		cdf[i] = 0;

	}

	GetGrayHistogram(img_data,bin, rows, cols);


	pdf[0] = bin[0];
	for (int i = 1; i < 256; i++) {
		pdf[i] = pdf[i - 1] + bin[i];
	}


	for (int i = 0; i < 256; i++) {
		pdf[i] /= (rows * cols);
	}

	for (int i = 0; i < 256; i++) {
		cdf[i] = pdf[i] * 255;
	}

	for (int i = 0; i < rows * cols; i++) {
		hist[i] = cdf[img_data[i]];
	}

	free(bin);

}

void ColorHistogramEqualiztion(unsigned char* img_data,unsigned char* hist,int rows, int cols) {


	int* bin_red=(int*)malloc(sizeof(int)*256);
	int* bin_green = (int*)malloc(sizeof(int) * 256);
	int* bin_blue = (int*)malloc(sizeof(int) * 256);

	double pdf_red[256];
	double pdf_green[256];
	double pdf_blue[256];

	double cdf_red[256];
	double cdf_green[256];
	double cdf_blue[256];

	GetColorHistogram(img_data, bin_red,rows, cols, ColorType::Red);
	GetColorHistogram(img_data, bin_green,rows, cols, ColorType::Green);
	GetColorHistogram(img_data, bin_blue,rows, cols, ColorType::Blue);
	

	pdf_red[0] = bin_red[0];
	pdf_green[0] = bin_green[0];
	pdf_blue[0] = bin_blue[0];

	for (int i = 1; i < 256; i++) {
		pdf_red[i] = pdf_red[i - 1] + bin_red[i];
		pdf_green[i] = pdf_green[i - 1] + bin_green[i];
		pdf_blue[i] = pdf_blue[i - 1] + bin_blue[i];
	}


	for (int i = 0; i < 256; i++) {
		pdf_red[i] /= (rows * cols);
		pdf_green[i] /= (rows * cols);
		pdf_blue[i] /= (rows * cols);
	}

	for (int i = 0; i < 256; i++) {
		cdf_red[i] = pdf_red[i] * 255;
		cdf_green[i] = pdf_green[i] * 255;
		cdf_blue[i] = pdf_blue[i] * 255;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			hist[3*(i*cols+j)+ ColorType::Red] = cdf_red[img_data[3*(i * cols+j)+ ColorType::Red]];
			hist[3 * (i * cols + j) + ColorType::Green] = cdf_green[img_data[3 * (i * cols + j) + ColorType::Green]];
			hist[3 * (i * cols + j)+ ColorType::Blue] = cdf_blue[img_data[3 * (i * cols + j)+ ColorType::Blue]];
		}
	}

	free(bin_blue);
	free(bin_green);
	free(bin_red);
}

void GetLookupTable(unsigned char* target,unsigned char* lookup,int target_rows,int target_cols) {
	int bin_t[256];
	double pdf_t[256];
	double cdf_t[256];

	for (int i = 0; i < 256; i++) {
		bin_t[i] = 0;
		pdf_t[i] = 0;
		cdf_t[i] = 0;
	}

	for (int i = 0; i < target_cols; i++) {
		int white_cnt = 0;
		for (int j = 0; j < target_rows; j++) {
			if (target[(255 - j) * target_cols + i] == 0) {
				bin_t[i]++;
			}
			else {
				bin_t[i]++;
				white_cnt = 1;
				break;
			}
		}
		if (white_cnt == 0 && bin_t[i] >= target_rows) {
			bin_t[i] = 0;
		}

	}

	int hist_size = 0;
	for (int i = 0; i < 256; i++) {
		hist_size += bin_t[i];
	}

	pdf_t[0] = bin_t[0];
	for (int i = 1; i < 256; i++) {
		pdf_t[i] = pdf_t[i - 1] + bin_t[i];
	}
	for (int i = 0; i < 256; i++) {
		pdf_t[i] /= (double)hist_size;
	}

	for (int i = 1; i < 256; i++) {
		cdf_t[i] = pdf_t[i] * 255;
	}

	for (int i = 0; i < 256; i++) {

		int lower = std::floor(cdf_t[i]);
		int upper = std::ceil(cdf_t[i]);

		lookup[lower] =i;
		lookup[upper] =i;

	}


}

void ColorHistogramMatching(unsigned char* src, unsigned char* target,unsigned char* hist_final, int src_rows, int src_cols, int target_rows, int target_cols) {
	unsigned char* equal_src = MemAlloc(3*src_rows*src_cols,0);
		
	ColorHistogramEqualiztion(src, equal_src,src_rows, src_cols);

	unsigned char* lookup = MemAlloc(target_rows, target_cols);
		
	GetLookupTable(target,lookup, target_rows, target_cols);
	
	//역평활화한다. 기존 평활화가 cdf[타겟영상원래픽셀값]=해당 픽셀 값이 정규화된 후 스케일링된 값 이라고 한다면
	//역평활화는 lookup[해당 픽셀이 정규화된 후 스케일링된 값의 내림/올림값]=타겟영상 원래 픽셀값 이 된다.
	//입력 영상 쪽에서 타겟 영상의 히스토그램 분포에 따라 매핑하기 위한 매핑 테이블을 만드는 것이라고 보면 된다.

	for (int i = 0; i < 3*src_rows * src_cols; i++) {
		hist_final[i] = lookup[equal_src[i]];
	}

}

void GrayHistogramMatching(unsigned char* src,unsigned char* target,unsigned char* hist_final,int src_rows,int src_cols,int target_rows,int target_cols) {

	unsigned char* equal_src = MemAlloc(src_rows * src_cols, 0);

	GrayHistogramEqualiztion(src, equal_src, src_rows, src_cols);

	unsigned char* lookup = MemAlloc(target_rows, target_cols);

	GetLookupTable(target, lookup, target_rows, target_cols);



	//역평활화한다. 기존 평활화가 cdf[타겟영상원래픽셀값]=해당 픽셀 값이 정규화된 후 스케일링된 값 이라고 한다면
	//역평활화는 lookup[해당 픽셀이 정규화된 후 스케일링된 값의 내림/올림값]=타겟영상 원래 픽셀값 이 된다.
	//입력 영상 쪽에서 타겟 영상의 히스토그램 분포에 따라 매핑하기 위한 매핑 테이블을 만드는 것이라고 보면 된다.


	for (int i = 0; i < src_rows * src_cols; i++) {
		hist_final[i] = lookup[equal_src[i]];
	}

}