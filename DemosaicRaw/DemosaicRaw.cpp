#include "stdafx.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	DemosicSet^ demosicSet = gcnew DemosicSet();

	//Console::WriteLine(args[0]);
	DateTime dtSFRStartTime = DateTime::Now;
	array<Byte>^ Fin_Byte;
	array<USHORT>^ Fin_Ushort;
	int width, height;
	bool demosicHighLowExchange, outputHighLowExchange;

	String^ dateTime = dtSFRStartTime.ToString("yyyyMMdd_hhmm");


	Console::WriteLine("Width:");
	width = Convert::ToInt32(Console::ReadLine());
	Console::WriteLine("Height:");
	height = Convert::ToInt32(Console::ReadLine());
	Console::WriteLine("Is Source image High-Low exchange? (Input 0~1): 0:No ,1:Yes");
	int tmpInput = Convert::ToInt32(Console::ReadLine());
	Console::WriteLine("Do Output image High-Low exchange? (Input 0~1): 0:No ,1:Yes");
	int tmpInput2 = Convert::ToInt32(Console::ReadLine());
	if ((tmpInput != 0 && tmpInput != 1) || (tmpInput2 != 0 && tmpInput2 != 1))
	{
		Console::WriteLine("Error input ,program end.");
		system("PAUSE");
	}
	demosicHighLowExchange = tmpInput == 0 ? false : true;
	outputHighLowExchange = tmpInput2 == 0 ? false : true;
	for (int i = 0; i < args->Length; i++)
	{
		IO::FileStream^ fs = gcnew IO::FileStream(args[i], IO::FileMode::Open);
		array<String^>^ FileName = args[i]->Split('\\');
		FileName = FileName[FileName->Length - 1]->Split('.');
		if (FileName[1]->ToUpper() != "RAW") //檢查副檔名是否為raw圖
		{
			Console::WriteLine(FileName[0] + " is not raw image.");
			continue;
		}
	}

	demosicSet->SaveImage_Raw12(raw12, String::Format("{0}_{1}_Raw12Double.raw", dateTime, FileName[0]));

	dst_ptr = &raw12->Image[0];
	array<Byte>^ demosicByte = gcnew array<Byte>(width*height * 2);
	b_ptr = &demosicByte[0];

	demosicSet->RawDoubleToByte(dst_ptr, width, height, b_ptr);
	if (outputHighLowExchange)demosicSet->HighLowExchange(b_ptr, width, height, b_ptr);
	demosicSet->SaveData(demosicByte, width, height, 2, String::Format("{0}_{1}_Raw12Byte.raw", dateTime, FileName[0]));

    return 0;
}
