#include "stdafx.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	if (args->Length > 1)
	{
		Console::WriteLine("餵太多囉~");
	}
	IO::FileStream^ fs = gcnew IO::FileStream(args[0], IO::FileMode::Open);
	array<String^>^ FileName = args[0]->Split('\\');
	FileName = FileName[FileName->Length - 1]->Split('.');


	if (FileName[1]->ToUpper() != "RAW") //檢查副檔名是否為raw圖
	{
		Console::WriteLine(FileName[0] + " is not raw image.");
	}
}
