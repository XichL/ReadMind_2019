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
		//Windows::Forms::MessageBox::Show("餵太多囉~",
		//	"",
		//	MessageBoxButtons::OK,
		//	MessageBoxIcon::Stop
		//);

		return 0;
	}

	for (int i = 0; i < args->Length; i++)
	{
		IO::FileStream^ fs = gcnew IO::FileStream(args[i], IO::FileMode::Open);
		array<String^>^ FileName = args[i]->Split('\\');

		//若餵ReadMe
		if (FileName[FileName->Length - 1]->Equals("ReadMe.txt"))
		{
			Windows::Forms::MessageBox::Show("謝謝你餵我。",
				"Thank you~",
				MessageBoxButtons::OK,
				MessageBoxIcon::Stop
			);
			Windows::Forms::MessageBox::Show("這是亞席大人留下來的，就送給你吧~",
				"Gift",
				MessageBoxButtons::OK,
				MessageBoxIcon::None
			);
			///釋出TreasureImage.raw
			return 0;
		}
		else if (FileName[FileName->Length - 1]->Equals("這是一張圖片.txt"))
		{
			///釋出TreasureImageFinal.raw
			return 0;
		}
		else
		{
			FileName = FileName[FileName->Length - 1]->Split('.');
			if (FileName[1]->ToUpper() != "RAW") //檢查副檔名是否為raw圖
			{
				Console::WriteLine(FileName[0] + " is not raw image.");
			}
			else
			{
				///釋出Tr[ae]sureImage.bmp
			}
			return 0;
		}
	}
}
