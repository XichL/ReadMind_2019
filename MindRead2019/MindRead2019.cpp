#pragma once
#include "stdafx.h"
#include "MindRead2019.h"

using namespace MindRead_FunctionSet;
using namespace MindRead2019Test;
using namespace System;

namespace MindRead2019Test
{

	[STAThreadAttribute]
	int main(array<System::String ^> ^args)
	{
		MindRead2019Test::CMindRead2019Test^ funcTest = gcnew MindRead2019Test::CMindRead2019Test();
		//----------------------------------------------------
#if 1
		String^ TestString = "ASCKB";

		

		return 0;
#endif	


		array<Byte>^ SrcByteBuffer;
		funcTest->MRFun->LoadBMP(SrcByteBuffer);

		int nWidth, nHeight;
		funcTest->MRFun->getbmpDataWH(nWidth, nHeight);

		array<Byte>^ Bit16Buffer = gcnew array<Byte>(nWidth*nHeight * 2);
		funcTest->MRFun->mosaic(SrcByteBuffer, nWidth, nHeight, 3, Bit16Buffer);

		funcTest->MRFun->SaveData(Bit16Buffer, nWidth, nHeight, 2, "To16Buffer.raw");

		array<Byte>^ outputDemosaic = gcnew array<Byte>(nWidth*nHeight);
		funcTest->MRFun->demosaic(Bit16Buffer, nWidth, nHeight, 2, outputDemosaic);
		funcTest->MRFun->SaveData(outputDemosaic, nWidth, nHeight, 1, "Demosaic.raw");



		//----------------------------------------------------
		return 0;
	}

}