// Prg1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	int Width = 176;
	int Height = 144;
	float FrameRate = 30000 / 1001;
	int OneFrameSize = Width * Height;
	int FrameSize = (OneFrameSize * 3) / 2;
	int FrameNo = 0;
	char *PrevFrame;
	char *NewFrame;
	char *TempFrame, *DiffFrame;
	char temp;
	char **r_prev, **g_prev, **b_prev;
	PrevFrame = new char [FrameSize];
	NewFrame = new char [FrameSize];
	TempFrame = new char [FrameSize];
	DiffFrame = new char [FrameSize];
	r_prev = new char * [2];
	r_prev[0] = new char [OneFrameSize];
	r_prev[1] = new char [OneFrameSize];
	g_prev = new char * [2];
	g_prev[0] = new char [OneFrameSize];
	g_prev[1] = new char [OneFrameSize];
	b_prev = new char * [2];
	b_prev[0] = new char [OneFrameSize];
	b_prev[0] = new char [OneFrameSize];
	FILE *Infile;
	FILE *OutFile;
	Infile = fopen("coastguard_qcif.yuv", "rb");
	OutFile = fopen("Diff_coast.yuv", "wb");

	fread(PrevFrame, 1, FrameSize, Infile);
	fread(NewFrame, 1, FrameSize, Infile);

	for(unsigned int i=0; i<OneFrameSize; i++)
	{
		b_prev[0][i] = 1.164 * (PrevFrame[i] - 16) + 2.018 * (PrevFrame[(i/4) + OneFrameSize] - 128);
		g_prev[0][i] = 1.164 * (PrevFrame[i] - 16) - 0.813 * (PrevFrame[OneFrameSize + (OneFrameSize/4) + (i/4)] - 128) - 0.391 * (PrevFrame[(i/4) + OneFrameSize] - 128);
		r_prev[0][i] = 1.164 * (PrevFrame[i] - 16) + 1.596 * (PrevFrame[OneFrameSize + (OneFrameSize/4) + (i/4)] - 128);
	}

	for(unsigned int FrameNo = 0; FrameNo < 299; FrameNo++)
	{

		for(unsigned int i=0; i<OneFrameSize; i++)
		{
			b_prev[1][i] = 1.164 * (NewFrame[i] - 16) + 2.018 * (NewFrame[(i/4) + OneFrameSize] - 128);
			g_prev[1][i] = 1.164 * (NewFrame[i] - 16) - 0.813 * (NewFrame[OneFrameSize + (OneFrameSize/4) + (i/4)] - 128) - 0.391 * (NewFrame[(i/4) + OneFrameSize] - 128);
			r_prev[1][i] = 1.164 * (NewFrame[i] - 16) + 1.596 * (NewFrame[OneFrameSize + (OneFrameSize/4) + (i/4)] - 128);
		}

/*
		for(int i=0; i<FrameSize; i++)
		{	

			temp = NewFrame[i] - PrevFrame[i];
			if(temp >= 0)
				TempFrame[i] = temp;
			else TempFrame[i] = -1 * temp;
			PrevFrame[i] = NewFrame[i];
		}
		
*/		
		
		for(unsigned int i=0; i<OneFrameSize; i++)
		{	
			b_prev[1][i] = b_prev[0][i];
			g_prev[1][i] = g_prev[0][i];
			r_prev[1][i] = r_prev[0][i];
		}
		//fputs(TempFrame, OutFile);
		fwrite(TempFrame, 1, FrameSize, OutFile);
		fread(NewFrame, 1, FrameSize, Infile);
		// read TempFrame and make it NewFrame
		// Do DiffFrame = NewFrame - PrevFrame
		// overwrite PrevFrame with NewFrame
		//save DiffFrame

	}
	fflush(OutFile);
	fclose(Infile);
	fclose(OutFile);

	return 1;
}
/*
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
*/
