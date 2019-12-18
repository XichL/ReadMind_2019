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
	//String^ TestString = "1Tu6k4mLULyGMOOA";
	String^ TestString = "PZxOYX6P7tpCNE12";


	array<Byte>^ out;
	String^ dst;
	String^ backString;
	MRFun->TransTo8bitASCII(TestString, dst);

	String^ newStr;
	for (int i = 0; i < dst->Length / 4; i++)
	{
		std::string c1, c2, c3, c4;
		c1 = dst[4 * i + 2];
		c2 = dst[4 * i + 3];
		c3 = dst[4 * i + 0];
		c4 = dst[4 * i + 1];

		String^ s1 = gcnew String(c1.c_str());
		String^ s2 = gcnew String(c2.c_str());
		String^ s3 = gcnew String(c3.c_str());
		String^ s4 = gcnew String(c4.c_str());

		newStr += s1 + s2 + s3 + s4;
	}

	//back
	String^ newStr2;
	for (int i = 0; i < newStr->Length / 4; i++)
	{
		std::string c1, c2, c3, c4;
		c1 = newStr[4 * i + 2];
		c2 = newStr[4 * i + 3];
		c3 = newStr[4 * i + 0];
		c4 = newStr[4 * i + 1];

		String^ s1 = gcnew String(c1.c_str());
		String^ s2 = gcnew String(c2.c_str());
		String^ s3 = gcnew String(c3.c_str());
		String^ s4 = gcnew String(c4.c_str());

		newStr2 += s1 + s2 + s3 + s4;
	}
	MRFun->ASCII8bitToLetter(newStr2, backString);

	MRFun->ASCII8bitToLetter(dst, backString);
	//MRFun->TransTo8bitASCII(TestString, out);
	//MRFun->SaveData(out, out->Length, 1, 1, "Test.txt");


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