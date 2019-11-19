#include "stdafx.h"
#include "CommonFunction.h"


MindReadFunction::CommonFunction::CommonFunction()
{
	//throw gcnew System::NotImplementedException();
}

MindReadFunction::CommonFunction::~CommonFunction()
{
	//throw gcnew System::NotImplementedException();
}

bool MindReadFunction::CommonFunction::NLogMsg(String ^ Message)
{
	logger->Debug(Message);
	return false;
}

bool MindReadFunction::CommonFunction::NLogMsg(String ^ FuncTag, String ^ Message)
{
	String^ LogString = NLOG_DLLTAG + "[" + FuncTag + "]" + " " + Message;
	NLogMsg(LogString);

	return false;
}

void MindReadFunction::CommonFunction::DataLoad(String ^ loadPath, array<Byte>^ loadData)
{
	DateTime dtSFRStartTime = DateTime::Now;
	array<Byte>^ Fin_Byte;
	array<USHORT>^ Fin_Ushort;
	int width, height;

	width = 1924;
	height = 1080;
	String^ file = "C:\\Users\\NST\\Downloads\\SVN\\WorkSpace\\ProjectDocument\\Foxconn-Polight\\SFR Plus-1x-12ms-RGBIR-1000lux\\SFR Plus-1x-12ms-RGBIR-1000lux.raw";
	IO::FileStream^ fs = gcnew IO::FileStream(file, IO::FileMode::Open);

	NLogMsg("RGBIR_Raw12");
	Fin_Ushort = gcnew array<USHORT>(width*height);
	array<Byte>^ tmpByte = gcnew array <Byte>(width*height * 2);
	fs->Read(tmpByte, 0, width*height * 2);

	//_ImageData_12Raw^ raw12 = gcnew _ImageData_12Raw(width, height);
	pin_ptr<Byte> b_ptr = &tmpByte[0];
	//pin_ptr<double> dst_ptr = &raw12->Image[0];
}

//void MindReadFunction::CommonFunction::DataLoad(String^ loadPath, array<Byte>^ loadData)
//{
//
//	DateTime dtSFRStartTime = DateTime::Now;
//	array<Byte>^ Fin_Byte;
//	array<USHORT>^ Fin_Ushort;
//	int width, height;
//
//	String^ dateTime = dtSFRStartTime.ToString("yyyyMMdd_hhmm");
//
//#if (DebguSBS) //Debug單步執行用
//
//	width = 1924;
//	height = 1080;
//	String^ file = "C:\\Users\\NST\\Downloads\\SVN\\WorkSpace\\ProjectDocument\\Foxconn-Polight\\SFR Plus-1x-12ms-RGBIR-1000lux\\SFR Plus-1x-12ms-RGBIR-1000lux.raw";
//	IO::FileStream^ fs = gcnew IO::FileStream(file, IO::FileMode::Open);
//	{
//#else
//	Console::WriteLine("Width:");
//	width = Convert::ToInt32(Console::ReadLine());
//	Console::WriteLine("Height:");
//
//	IO::FileStream^ fs = gcnew IO::FileStream(loadPath, IO::FileMode::Open);
//	array<String^>^ FileName = loadPath->Split('\\');
//	FileName = FileName[FileName->Length - 1]->Split('.');
//	if (FileName[1]->ToUpper() != "RAW") //檢查副檔名是否為raw圖
//	{
//		Console::WriteLine(FileName[0] + " is not raw image.");
//	}
//#endif
//
//	// RGBIR_Raw12 to GRaw12
//	if (1)
//	{
//		NLogMsg("RGBIR_Raw12");
//		Fin_Ushort = gcnew array<USHORT>(width*height);
//		array<Byte>^ tmpByte = gcnew array <Byte>(width*height * 2);
//		fs->Read(tmpByte, 0, width*height * 2);
//
//		//_ImageData_12Raw^ raw12 = gcnew _ImageData_12Raw(width, height);
//		pin_ptr<Byte> b_ptr = &tmpByte[0];
//		//pin_ptr<double> dst_ptr = &raw12->Image[0];
//
//		//demosicSet->RGBIRToG(b_ptr, width, height, 0, true, dst_ptr);
//#if (DebguSBS) //Debug單步執行用
//				//demosicSet->SaveImage_Raw12(raw12, "..\\Demo2_Img2.raw");
//#else
//		demosicSet->SaveImage_Raw12(raw12, String::Format("{0}_{1}_12Raw.raw", dateTime, FileName[0]));
//#endif
//
//	}
//
//}
