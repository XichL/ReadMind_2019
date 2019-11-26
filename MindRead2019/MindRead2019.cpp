#pragma once
#include "stdafx.h"
#include "CommonFunction.h"

using namespace MindReadFunction;
using namespace System;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	CommonFunction^ CFunc = gcnew CommonFunction();
	
	
	//Byte* bufferPtr;
	array<Byte>^ SrcByteBuffer;
	CFunc->LoadBMP(SrcByteBuffer);

	int nWidth, nHeight;
	CFunc->getbmpDataWH(nWidth, nHeight);

	array<Byte>^ Bit16Buffer = gcnew array<Byte>(nWidth*nHeight*2);
	CFunc->mosaic(SrcByteBuffer, nWidth, nHeight, 3, Bit16Buffer);

	CFunc->SaveData(Bit16Buffer, nWidth, nHeight, 2, "To16Buffer.raw");

	array<Byte>^ outputDemosaic = gcnew array<Byte>(nWidth*nHeight);
	CFunc->demosaic(Bit16Buffer, nWidth, nHeight, 2, outputDemosaic);
	CFunc->SaveData(outputDemosaic, nWidth, nHeight, 1, "Demosaic.raw");

    return 0;
}

