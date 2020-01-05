#include "stdafx.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace MindRead_FunctionSet;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	if (args->Length > 1)
	{
		Console::WriteLine("餵太多囉~");
		system("PAUSE");
		return 0;
	}

	Windows::Forms::MessageBox::Show("餵太多囉~",
		"",
		MessageBoxButtons::OK,
		MessageBoxIcon::Stop
	);

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
}
