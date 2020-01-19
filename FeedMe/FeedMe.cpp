#include "stdafx.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace MindRead_FunctionSet;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	if (args->Length > 1)
	{
		Console::WriteLine("���Ӧh�o~");
		system("PAUSE");
		//Windows::Forms::MessageBox::Show("���Ӧh�o~",
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

		//�Y��ReadMe
		if (FileName[FileName->Length - 1]->Equals("ReadMe.txt"))
		{
			Windows::Forms::MessageBox::Show("���§A���ڡC",
				"Thank you~",
				MessageBoxButtons::OK,
				MessageBoxIcon::Stop
			);
			Windows::Forms::MessageBox::Show("�o�O�Ȯu�j�H�d�U�Ӫ��A�N�e���A�a~",
				"Gift",
				MessageBoxButtons::OK,
				MessageBoxIcon::None
			);
			///���XTreasureImage.raw
			return 0;
		}
		else if (FileName[FileName->Length - 1]->Equals("�o�O�@�i�Ϥ�.txt"))
		{
			///���XTreasureImageFinal.raw
			return 0;
		}
		else
		{
			FileName = FileName[FileName->Length - 1]->Split('.');
			if (FileName[1]->ToUpper() != "RAW") //�ˬd���ɦW�O�_��raw��
			{
				Console::WriteLine(FileName[0] + " is not raw image.");
			}
			else
			{
				///���XTr[ae]sureImage.bmp
			}
			return 0;
		}
	}
}
