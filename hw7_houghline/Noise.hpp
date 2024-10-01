#include <opencv2/opencv.hpp>
#include <math.h>
#include <sysinfoapi.h>
const float PI = 3.14;

void GetGaussianPDF(float* EmptyPDF, int nLength, float fMean, float fStDev)
{
	int n;
	int Center = nLength / 2;
	float x;
	for (n = 0; n < nLength; n++)
	{
		x = (float)(n - Center);
		EmptyPDF[n] = (1 / ((float)sqrt(2 * PI) * fStDev)) * exp(-pow(x - fMean, 2) /
			(2 * fStDev * fStDev));
	}
}

float GetNoise(float* PDF, int nLength)
{
	int n;
	int Center = nLength / 2;
	float fRand, fComp, fTemp = 0;
	float x = 0, fDiff;
	float* CDF = new float[nLength];
	CDF[0] = 0;


	fRand = (float)rand() / (RAND_MAX + 1);
	for (n = 1; n < nLength; n++)
	{
		CDF[n] = (PDF[n] + PDF[n - 1]) / 2 + CDF[n - 1];
		fDiff = fRand - CDF[n];
		if (fDiff < 0)
		{
			x = ((float)n - Center);
			break;
		}
	}
	fComp = (fRand - CDF[n - 1]) / (CDF[n] - CDF[n - 1]);
	delete[] CDF;
	return x + fComp;
}

unsigned char* InputColorGaussianNoise(unsigned char* In, int nHeight,
	int nWidth, float fMean, float fStdev)
{
	unsigned char* Out=(unsigned char*)malloc(sizeof(unsigned char)*3*nHeight*nWidth);
	float fTemp = 0, fPDF[256] = { 0.0f };
	srand(GetTickCount());
	GetGaussianPDF(fPDF, 256, fMean, fStdev);
	for (int h = 0; h <3* nHeight*nWidth; h++)
	{
			fTemp = (float)In[h] + GetNoise(fPDF, 256);
			Out[h] = std::max(0, std::min(255, (int)fTemp));
	}

	return Out;
}

unsigned char* InputGrayGaussianNoise(unsigned char* In, int nHeight,
	int nWidth, float fMean, float fStdev)
{
	unsigned char* Out=(unsigned char*)malloc(sizeof(unsigned char)*nHeight*nWidth);
	float fTemp = 0, fPDF[256] = { 0.0f };
	srand(GetTickCount());
	GetGaussianPDF(fPDF, 256, fMean, fStdev);
	for (int h = 0; h < nHeight*nWidth; h++)
	{
		fTemp = (float)In[h] + GetNoise(fPDF, 256);
		Out[h] = std::max(0, std::min(255, (int)fTemp));
		
	}

	return Out;
}


unsigned char* InputColorSaltPepperNoise(unsigned char* In, int nHeight, int nWidth,
	float fSProb, float fPProb)
{
	unsigned char* Out = (unsigned char*)malloc(sizeof(unsigned char) *3* nHeight * nWidth);
	float Low = fSProb;
	float High = 1.0f - fPProb;
	float fRand;

	srand(GetTickCount());


	for (int h = 0; h < 3*nWidth*nHeight; h+=3)
	{
			fRand = ((float)rand() / RAND_MAX);
			if (fRand < Low)
			{
				Out[h] = 255;
				Out[h+1] = 255;
				Out[h+2] = 255;
			}
			else if (fRand > High)
			{
				Out[h] = 0;
				Out[h+1] = 0;
				Out[h+2] = 0;
			}
			else {
				Out[h] = In[h];
				Out[h+1] = In[h+1];
				Out[h+2] = In[h+2];
			}
	}

	return Out;
	
}

unsigned char* InputGraySaltPepperNoise(unsigned char* In,  int nHeight, int nWidth,
	float fSProb, float fPProb)
{
	unsigned char* Out= (unsigned char*)malloc(sizeof(unsigned char) * nHeight * nWidth);
	float Low = fSProb;
	float High = 1.0f - fPProb;
	float fRand;

	srand(GetTickCount());


	for (int h = 0; h < nHeight*nWidth; h++)
	{

			fRand = ((float)rand() / RAND_MAX);
			if (fRand < Low)
			{
				Out[h] = 255;
			}
			else if (fRand > High)
			{
				Out[h] = 0;
			}
			else {
				Out[h] = In[h];
			}
		
	}

	return Out;
}