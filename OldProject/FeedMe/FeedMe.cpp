#include "stdafx.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace MindRead_FunctionSet;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	AppDomain::CurrentDomain->AppendPrivatePath("Miscellaneous");
	String^ strPath = IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath) + "\\Miscellaneous";
	IO::Directory::SetCurrentDirectory(strPath);

	String^ ExecutePath = IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath);

	FunctionSet^ MRFun = gcnew FunctionSet();
	//----------------------------------------------------
	do {
		if (args->Length > 1)
		{
			Console::WriteLine("���Ӧh�o~");
			system("PAUSE");
			//Windows::Forms::MessageBox::Show("���Ӧh�o~",
			//	"",
			//	MessageBoxButtons::OK,
			//	MessageBoxIcon::Stop
			//);

			break;
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
				MRFun->GetSourceFile("TreasureImage", FILETYPE::FILETYPE_RAW,
					"TreasureImage.raw");

				break;
			}
			else if (FileName[FileName->Length - 1]->Equals("�o�O�@�i�Ϥ�.txt"))
			{
				///���XTreasureImageFinal.raw
				MRFun->GetSourceFile("TreasureImageFinal", FILETYPE::FILETYPE_RAW,
					"TreasureImageFinal.raw");
				break;
			}
			else if (FileName[FileName->Length - 1]->Equals("Key.txt"))
			{
				Windows::Forms::MessageBox::Show("��H�o�OKEY�ܡH�O�o�Ȯu�j�H���d�U�@�ǩM���������T���O~�N�e�A�a�C",
					"Gift",
					MessageBoxButtons::OK,
					MessageBoxIcon::None
				);
				MRFun->GetSourceFile("KEY����Ū", FILETYPE::FILETYPE_TXT,
					"KEY����Ū.txt");
				break;
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
					MRFun->GetSourceFile("TraesureImage", FILETYPE::FILETYPE_BMP,
						"TraesureImage");
					break;
				}
				break;
			}
		}
	} while (0);
	return 0;
}
