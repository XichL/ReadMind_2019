#pragma once
#include "stdafx.h"
#include "MindRead2019.h"

using namespace MindRead_FunctionSet;
using namespace MindRead2019Test;
using namespace System;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	FunctionSet^ MRFun = gcnew FunctionSet();
	//----------------------------------------------------
#if 1
	String^ TestString = "K";

	array<Byte>^ out;
	MRFun->TransTo8bitASCII(TestString, out);

	return 0;
#endif	

	array<Byte>^ SrcByteBuffer;
	MRFun->LoadBMP(SrcByteBuffer);

	int nWidth, nHeight;
	MRFun->getbmpDataWH(nWidth, nHeight);

	array<Byte>^ Bit16Buffer = gcnew array<Byte>(nWidth*nHeight * 2);
	MRFun->mosaic(SrcByteBuffer, nWidth, nHeight, 3, Bit16Buffer);

	MRFun->SaveData(Bit16Buffer, nWidth, nHeight, 2, "To16Buffer.raw");

	array<Byte>^ outputDemosaic = gcnew array<Byte>(nWidth*nHeight);
	MRFun->demosaic(Bit16Buffer, nWidth, nHeight, 2, outputDemosaic);
	MRFun->SaveData(outputDemosaic, nWidth, nHeight, 1, "Demosaic.raw");

	//----------------------------------------------------
	return 0;
}

namespace MindRead2019Test
{

}