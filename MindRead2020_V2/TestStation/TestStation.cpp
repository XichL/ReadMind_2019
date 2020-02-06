#pragma once
#include "stdafx.h"
#include "TestStation.h"

using namespace MindRead_FunctionSet;
using namespace TestStationTest;
using namespace System;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	//System::Configuration::ConfigurationManager::AppSettings["app"];

	//Windows::Forms::Application::EnableVisualStyles();
	//Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	//AppDomain::CurrentDomain->AppendPrivatePath("Miscellaneous");
	//AppDomain::CurrentDomain->CreateDomain("Miscellaneous");
	//String^ strPath = IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath) + "\\Miscellaneous";
	//IO::Directory::SetCurrentDirectory(strPath);

	//Reflection::Assembly::Load(strPath + "\\MindRead_FunctionSet.dll")->CreateInstance("MindRead_FunctionSet.Operation.E5003Handler", true);

	//AppDomainSetup^ setup = gcnew AppDomainSetup();
	//setup->ApplicationBase = IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath) + "\\";
	//setup->PrivateBinPath = "Miscellaneous";
	//AppDomain^ currentDomain = AppDomain::CreateDomain("NewDomain", nullptr, setup);
	//currentDomain->Load("MindRead_FunctionSet");

	FunctionSet^ MRFun = gcnew FunctionSet();
	//----------------------------------------------------

#pragma region 修改ReadMe內容測試
#if 0

	String^ ReadMePath = EXEPath + "\\ReadMe.txt";

	System::IO::StreamReader^ readFile = gcnew System::IO::StreamReader(ReadMePath);
	int HintNum = 0;
	bool FindHint = false;
	while (!readFile->EndOfStream)
	{
		String^ LineString = readFile->ReadLine();
		if (LineString->Contains("H" + HintNum + "."))
		{
			FindHint = true;
			array<String^>^ checkString = LineString->Split('.');
			if (checkString[1]->Equals("Part1 = W1920x1080"))
			//if (checkString[1]->Equals("Part2 = WPart1x1200"))
			//if (checkString[1]->Equals("Final = W????xHeight"))
			{
				readFile->Close();
				break;
			}
			else
			{
				HintNum++;
			}
		}
		if (FindHint&&readFile->EndOfStream)
		{
			readFile->Close();

			String^ strNewHint = Environment::NewLine + "H" + HintNum + ".Part1 = W1920x1080";
			//String^ strNewHint = Environment::NewLine + "H" + HintNum + ".Part2 = WPart1x1200";
			//String^ strNewHint = Environment::NewLine + "H" + HintNum + ".Final = W????xHeight";
			try
			{
				IO::FileStream^ fs;
				System::Text::ASCIIEncoding^ asciiEncoding = gcnew System::Text::ASCIIEncoding;
				fs = gcnew IO::FileStream(ReadMePath, IO::FileMode::Append);
				fs->Write(asciiEncoding->GetBytes(strNewHint), 0, asciiEncoding->GetByteCount(strNewHint));
				break;
			}
			catch (System::Exception^ e)
			{
				MRFun->NLogMsg("DemosaicRaw",
					String::Format("Modify ReadMe : {0:0}", e));
				return 0;
			}
		}
	}
#endif
#pragma endregion

#pragma region DllPathTest
#if 0
	MRFun->GetSourceFile("這是一張圖片", FILETYPE::FILETYPE_TXT, "這是一張圖片");
	Console::WriteLine("Pass~");
	MRFun->NLogMsg("PassMsg");
	system("PAUSE");
#endif
#pragma endregion

#pragma region MyRegion
#if 0
	//IO::FileStream^ fs = gcnew IO::FileStream(
	//	L"C:/Users/NST/Downloads/SVN/WorkSpace/VersionControl/Controller/Xich_Collect/test.xml", IO::FileMode::Open);
	array<Byte>^ loadData;
	//MRFun->DataLoad_AutoSize(L"C:/Users/NST/Downloads/SVN/WorkSpace/VersionControl/Controller/Xich_Collect/test.xml",
	//	loadData);
	MRFun->DataLoad_AutoSize(L"C:/Users/NST/Downloads/SVN/WorkSpace/VersionControl/Controller/Xich_Collect/GitRepository/ReadMind_2019/OldProject/test.xml",
		loadData);

	int length = loadData->Length;
	array<Byte>^ realData = gcnew array<Byte>(length);
	int count = 0;
	for (int i = 0; i < loadData->Length; i++)
	{
		if (loadData[i] != ' ')
		{
			if (count >= 128)
				break;
			realData[count] = loadData[i];
			count++;
		}
	}

	array<Byte>^ encodeData = gcnew array<Byte>(length);
	for (int i = 0; i < realData->Length; i += 4)
	{
		encodeData[i] = realData[i] ^ 0;
		encodeData[i + 1] = realData[i + 1] ^ 1;
		encodeData[i + 2] = realData[i + 2] ^ 1;
		encodeData[i + 3] = realData[i + 3] ^ 0;
	}

	String^ encodeString;
	String^ outString;
	for each(Byte b in encodeData)
	{
		encodeString += b == '0' ? "0" : "1";
	}
	MRFun->ASCII8bitToLetter(encodeString, outString);

	int a = 0;
	a = 1 + 1;
	return 0;
	
#endif
#pragma endregion


#pragma region 測試讀檔
#if 0
	System::IO::StreamReader^ readFile = gcnew System::IO::StreamReader(
		L"C:/Users/NST/Downloads/SVN/WorkSpace/VersionControl/Controller/Xich_Collect/ReadMind_2019/3rdparty/Resource/TraesureImage.raw");

	Collections::Generic::List<Byte>^ tmpByte = gcnew Collections::Generic::List<Byte>();
	String^ test;

	int ALength = readFile->BaseStream->Length;
	array<Byte>^ testArray = gcnew array<Byte>(ALength);

	readFile->Close();
	String^ file = L"C:/Users/NST/Downloads/SVN/WorkSpace/VersionControl/Controller/Xich_Collect/ReadMind_2019/3rdparty/Resource/TraesureImage.raw";
	IO::FileStream^ fs = gcnew IO::FileStream(file, IO::FileMode::Open);
	fs->Read(testArray, 0, ALength);

	//int Count = 0;
	//while (!readFile->EndOfStream)
	//{
	//	//test = readFile->ReadLine();
	//	tmpByte->Add(readFile->Read());
	//	Count++;
	//}

	int a = 0;
	a = a + 1;
	return 0;
#endif
#pragma endregion


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
		//"C:\\Users\\may31\\Documents\\GitHub\\ReadMind_2019\\TestStation\\Resource.resx");
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
	String^ truePart1 = "1Tu6k4mLULyGMOOA";
	String^ trueMiddle = "h";
	String^ truePart2 = "PZxOYX6P7tpCNE12";

	array<Byte>^ out;
	String^ dst;
	String^ backString;
	//轉成8bit二進位
	MRFun->TransTo8bitASCII(truePart1, dst);

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
#if 1
	array<Byte>^ SrcByteBuffer;
	MRFun->LoadBMP(SrcByteBuffer);

	int nWidth, nHeight;
	MRFun->getbmpDataWH(nWidth, nHeight);

	//彩圖轉灰階並拓展成16bit長度格式
	array<Byte>^ Bit16Buffer = gcnew array<Byte>(nWidth*nHeight * 2);
	MRFun->mosaic(SrcByteBuffer, nWidth, nHeight, 3, Bit16Buffer);
	MRFun->SaveData(Bit16Buffer, nWidth, nHeight, 2, false, "To16Buffer.raw");

	//高低位元轉換
	array<Byte>^ HVConvert = gcnew array<Byte>(nWidth*nHeight * 2);
	MRFun->HLConverter(Bit16Buffer, 2, HVConvert);
	MRFun->SaveData(HVConvert, nWidth, nHeight, 2, false, "HLConvert.raw");

	array<Byte>^ HVConvert_back = gcnew array<Byte>(nWidth*nHeight * 2);
	MRFun->HLConverter(HVConvert, 2, HVConvert_back);
	MRFun->SaveData(HVConvert_back, nWidth, nHeight, 2, false, "HLConvert_Back.raw");

	//測試若沒有高低位退回8bit結果
	array<Byte>^ outputDemosaic_NoHLBack = gcnew array<Byte>(nWidth*nHeight);
	MRFun->demosaic(HVConvert, nWidth, nHeight, 2, outputDemosaic_NoHLBack);
	MRFun->SaveData(outputDemosaic_NoHLBack, nWidth, nHeight, 1, false, "Demosaic_NoHLBack.raw");

	//高低位元後
	array<Byte>^ outputDemosaic_HLBack = gcnew array<Byte>(nWidth*nHeight);
	MRFun->demosaic(HVConvert_back, nWidth, nHeight, 2, outputDemosaic_HLBack);
	MRFun->SaveData(outputDemosaic_HLBack, nWidth, nHeight, 1, false, "Demosaic_HLBack.raw");

	//將16bit格式退回8bit
	array<Byte>^ outputDemosaic = gcnew array<Byte>(nWidth*nHeight);
	MRFun->demosaic(Bit16Buffer, nWidth, nHeight, 2, outputDemosaic);
	MRFun->SaveData(outputDemosaic, nWidth, nHeight, 1, false, "Demosaic.raw");

	Drawing::Bitmap^ outBmp = gcnew Drawing::Bitmap(nWidth, nHeight, Drawing::Imaging::PixelFormat::Format8bppIndexed);
	MRFun->Raw2Bmp(outputDemosaic, outBmp);
	MRFun->SaveBmp(outBmp, false, "outTest");
#endif
#pragma endregion
	//----------------------------------------------------
	return 0;
}
