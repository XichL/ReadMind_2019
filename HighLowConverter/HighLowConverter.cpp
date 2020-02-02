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

	try {
		do
		{
			if (args->Length == 0)
			{
				///output what is HLConverter
				MRFun->GetSourceFile("HighLow�ഫ���ηN", FILETYPE::FILETYPE_TXT,
					"HighLow�ഫ���ηN.txt");
				break;
			}
			else if (args->Length > 1)
			{
				Console::WriteLine("���Ӧh�o~");
				system("PAUSE");
				break;
			}
			else
			{
				for (int i = 0; i < args->Length; i++)
				{
					IO::FileStream^ fs = gcnew IO::FileStream(args[i], IO::FileMode::Open);
					array<String^>^ FileName = args[i]->Split('\\');
					fs->Close();

					//�Y��ReadMe
					if (FileName[FileName->Length - 1]->Equals("ReadMe.txt"))
					{
						///���XTreasureImagePart1.raw
						MRFun->GetSourceFile("TreasureImagePart1", FILETYPE::FILETYPE_RAW,
							"TreasureImagePart1.raw");

						//Ū�����e�A�ˬd�O�_�s�bH1~3
						//�ˬdH1~3���O�_��Hint
						//"Part2�AWPart1x1200"
						break;
					}
					else
					{
						try {
							array<Byte>^ readByte;
							
							MRFun->DataLoad_AutoSize(args[i], readByte);
							MRFun->SaveData(readByte, readByte->Length, 0, 1, "Test");
						}
						catch (...)
						{
							Windows::Forms::MessageBox::Show("�ګ��������S P:",
								"UCCU",
								MessageBoxButtons::OK,
								MessageBoxIcon::Stop
							);
						}
					}
				}
			}

		} while (0);

	}
	catch(...)
	{
		MRFun->NLogMsg("HighLowConverter exception.");
	}
	return 0;

}
