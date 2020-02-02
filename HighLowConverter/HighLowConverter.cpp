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
				MRFun->GetSourceFile("HighLow轉換的用意", FILETYPE::FILETYPE_TXT,
					"HighLow轉換的用意.txt");
				break;
			}
			else if (args->Length > 1)
			{
				Console::WriteLine("餵太多囉~");
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

					//若餵ReadMe
					if (FileName[FileName->Length - 1]->Equals("ReadMe.txt"))
					{
						///釋出TreasureImagePart1.raw
						MRFun->GetSourceFile("TreasureImagePart1", FILETYPE::FILETYPE_RAW,
							"TreasureImagePart1.raw");

						//讀取內容，檢查是否存在H1~3
						//檢查H1~3中是否有Hint
						//"Part2，WPart1x1200"
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
							Windows::Forms::MessageBox::Show("啊哈哈掛掉惹 P:",
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
