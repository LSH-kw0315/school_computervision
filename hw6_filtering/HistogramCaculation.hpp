#include <opencv2/opencv.hpp>
#include "FormatAndInterPolation.h"

int* GetGrayHistogram(unsigned char* img_data,int rows,int cols) {
	int* bin=(int*)malloc(sizeof(int)*256);
	for (int i = 0; i < 256; i++) {
		bin[i] = 0;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			bin[img_data[i * cols + j]]++;
		}
	}

	return bin;
}

int* GetColorHistogram(unsigned char* img_data,int rows,int cols,int ColorType){
	int* bin = (int*)malloc(sizeof(int) * 256);
	for (int i = 0; i < 256; i++) {
		bin[i] = 0;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			bin[img_data[3*(i * cols + j)+ColorType]]++;
		}
	}

	return bin;
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

unsigned char* GrayHistogramEqualiztion(unsigned char* img_data,int rows,int cols) {

	unsigned char* hist = MemAlloc(rows*cols,0);

	int* bin;

	double pdf[256];

	double cdf[256];


	for (int i = 0; i < 256; i++) {
		pdf[i] = 0;
		cdf[i] = 0;

	}

	bin = GetGrayHistogram(img_data, rows, cols);


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

	return hist;


}

unsigned char* ColorHistogramEqualiztion(unsigned char* img_data, int rows, int cols) {


	unsigned char* hist = MemAlloc(3 * rows * cols, 0);

	int* bin_red;
	int* bin_green;
	int* bin_blue;

	double pdf_red[256];
	double pdf_green[256];
	double pdf_blue[256];

	double cdf_red[256];
	double cdf_green[256];
	double cdf_blue[256];

	bin_red = GetColorHistogram(img_data, rows, cols, ColorType::Red);
	bin_green = GetColorHistogram(img_data, rows, cols, ColorType::Green);
	bin_blue = GetColorHistogram(img_data, rows, cols, ColorType::Blue);
	

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

	return hist;


}

unsigned char* GetLookupTable(unsigned char* target,int target_rows,int target_cols) {
	int bin_t[256];
	double pdf_t[256];
	double cdf_t[256];
	unsigned char* lookup=MemAlloc(256,0);

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

	return lookup;

}

unsigned char* ColorHistogramMatching(unsigned char* src, unsigned char* target, int src_rows, int src_cols, int target_rows, int target_cols) {
	unsigned char* hist_final = MemAlloc(3*src_rows * src_cols, 0);

	unsigned char* equal_src = ColorHistogramEqualiztion(src, src_rows, src_cols);

	unsigned char* lookup = GetLookupTable(target, target_rows, target_cols);
	
	//역평활화한다. 기존 평활화가 cdf[타겟영상원래픽셀값]=해당 픽셀 값이 정규화된 후 스케일링된 값 이라고 한다면
	//역평활화는 lookup[해당 픽셀이 정규화된 후 스케일링된 값의 내림/올림값]=타겟영상 원래 픽셀값 이 된다.
	//입력 영상 쪽에서 타겟 영상의 히스토그램 분포에 따라 매핑하기 위한 매핑 테이블을 만드는 것이라고 보면 된다.

	for (int i = 0; i < 3*src_rows * src_cols; i++) {
		hist_final[i] = lookup[equal_src[i]];
	}

	return hist_final;
}

unsigned char* GrayHistogramMatching(unsigned char* src,unsigned char* target,int src_rows,int src_cols,int target_rows,int target_cols) {


	unsigned char* hist_final = MemAlloc(src_rows * src_cols, 0);

	unsigned char* lookup = GetLookupTable(target, target_rows, target_cols);

	unsigned char* equal_src = GrayHistogramEqualiztion(src, src_rows, src_cols);



	//역평활화한다. 기존 평활화가 cdf[타겟영상원래픽셀값]=해당 픽셀 값이 정규화된 후 스케일링된 값 이라고 한다면
	//역평활화는 lookup[해당 픽셀이 정규화된 후 스케일링된 값의 내림/올림값]=타겟영상 원래 픽셀값 이 된다.
	//입력 영상 쪽에서 타겟 영상의 히스토그램 분포에 따라 매핑하기 위한 매핑 테이블을 만드는 것이라고 보면 된다.


	for (int i = 0; i < src_rows * src_cols; i++) {
		hist_final[i] = lookup[equal_src[i]];
	}

	return hist_final;
}