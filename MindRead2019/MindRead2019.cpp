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


#pragma region 測試文字內容
#if 0
	array<UCHAR>^ testLoadUchar;
	MRFun->DataLoad_TXT("C://Users//may31//Documents//GitHub//ReadMind_2019//3rdparty//Resource//這是一張圖片(第一1第五0).txt", testLoadUchar);
	bool checkRight = true;
	for (int i = 0; i < testLoadUchar->Length; i += 4)
	{
		if ((i / 4) % 2 == 0)
		{
			if (testLoadUchar[i] != '1')
			{
				checkRight = false;
				break;
			}
		}
		if ((i / 4) % 2 == 1)
		{
			if (testLoadUchar[i] != '0')
			{
				checkRight = false;
				break;
			}
		}
	}
	Diagnostics::Trace::WriteLine(checkRight ? "Pass" : "Fail");
#endif
#pragma endregion

#pragma region 測試讀資源內容
#if 0 //測試讀資源內容
	MRFun->GetSourceFile("TraesureImage", FILETYPE::FILETYPE_BMP, "TraesureImage");
	return 2;

	//從dll取資源中的檔案並存檔
	MRFun->GetSourceFile("EasyDecryption_ASCII的用途", FILETYPE::FILETYPE_TXT,
		"EasyDecryption_ASCII的用途.txt");
	return 1;

	//從.exe資源內容resx讀取
	System::Resources::ResXResourceReader^ reader = gcnew System::Resources::ResXResourceReader(
		"Resource.resx");
		//"C:\\Users\\may31\\Documents\\GitHub\\ReadMind_2019\\MindRead2019\\Resource.resx");
	for each(System::Collections::DictionaryEntry entry in reader)
	{
		array<byte>^ a = (array<byte>^)entry.Value;
		//Console::WriteLine("  {0}={1}", entry.Key, entry.Value);
		for (int i = 0; i < 100; i++)
		{
			Console::Write("{0}", a[i]);
		}
	}
	system("PAUSE");
#endif
#pragma endregion


#pragma region 測試存中文
#if 0 //測試存中文
	String^ TestString = "中文字";

	MRFun->SaveStringData_cover(TestString, "test.txt");
#endif
#pragma endregion

#pragma region 測試ASCII
#if 0 //測試ASCII
//String^ TestString = "1Tu6k4mLULyGMOOA";
	//String^ TestString = "PZxOYX6P7tpCNE12";
	String^ TestString = "STOCKING";

	array<Byte>^ out;
	String^ dst;
	String^ backString;
	//轉成8bit二進位
	MRFun->TransTo8bitASCII(TestString, dst);

	String^ newStr;
	//高2低2互換
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

	//back，轉回
	String^ newStr2;
	//高2低2互換
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
	//將8bit轉為文字
	MRFun->ASCII8bitToLetter(newStr2, backString);

	//測試若沒有高2低2互換的話
	MRFun->ASCII8bitToLetter(dst, backString);
	//MRFun->TransTo8bitASCII(TestString, out);
	//MRFun->SaveData(out, out->Length, 1, 1, "Test.txt");

#endif	
#pragma endregion

#pragma region 測試圖片轉換
#if 0
	array<Byte>^ SrcByteBuffer;
	MRFun->LoadBMP(SrcByteBuffer);

	int nWidth, nHeight;
	MRFun->getbmpDataWH(nWidth, nHeight);

	//彩圖轉灰階並拓展成16bit長度格式
	array<Byte>^ Bit16Buffer = gcnew array<Byte>(nWidth*nHeight * 2);
	MRFun->mosaic(SrcByteBuffer, nWidth, nHeight, 3, Bit16Buffer);
	MRFun->SaveData(Bit16Buffer, nWidth, nHeight, 2, "To16Buffer.raw");

	//高低位元轉換
	array<Byte>^ HVConvert = gcnew array<Byte>(nWidth*nHeight * 2);
	MRFun->HLConverter(Bit16Buffer, 2, HVConvert);
	MRFun->SaveData(HVConvert, nWidth, nHeight, 2, "HLConvert.raw");

	array<Byte>^ HVConvert_back = gcnew array<Byte>(nWidth*nHeight * 2);
	MRFun->HLConverter(HVConvert, 2, HVConvert_back);
	MRFun->SaveData(HVConvert_back, nWidth, nHeight, 2, "HLConvert_Back.raw");

	//測試若沒有高低位退回8bit結果
	array<Byte>^ outputDemosaic_NoHLBack = gcnew array<Byte>(nWidth*nHeight);
	MRFun->demosaic(HVConvert, nWidth, nHeight, 2, outputDemosaic_NoHLBack);
	MRFun->SaveData(outputDemosaic_NoHLBack, nWidth, nHeight, 1, "Demosaic_NoHLBack.raw");

	//高低位元後
	array<Byte>^ outputDemosaic_HLBack = gcnew array<Byte>(nWidth*nHeight);
	MRFun->demosaic(HVConvert_back, nWidth, nHeight, 2, outputDemosaic_HLBack);
	MRFun->SaveData(outputDemosaic_HLBack, nWidth, nHeight, 1, "Demosaic_HLBack.raw");

	//將16bit格式退回8bit
	array<Byte>^ outputDemosaic = gcnew array<Byte>(nWidth*nHeight);
	MRFun->demosaic(Bit16Buffer, nWidth, nHeight, 2, outputDemosaic);
	MRFun->SaveData(outputDemosaic, nWidth, nHeight, 1, "Demosaic.raw");

	Drawing::Bitmap^ outBmp = gcnew Drawing::Bitmap(nWidth, nHeight, Drawing::Imaging::PixelFormat::Format8bppIndexed);
	MRFun->Raw2Bmp(outputDemosaic, outBmp);
	MRFun->SaveBmp(outBmp, false, "outTest");
#endif
#pragma endregion
	//----------------------------------------------------
	return 0;
}

namespace MindRead2019Test
{

}