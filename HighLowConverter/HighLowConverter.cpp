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

	FunctionSet^ MRFun = gcnew FunctionSet();
	//----------------------------------------------------

	try {
		do
		{
			if (args->Length == 0)
			{
				//output what is HLConverter
				break;
			}
			else if (args->Length > 1)
			{
				Console::WriteLine("Áý¤Ó¦hÅo~");
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

					//­YÁýReadMe
					if (FileName[FileName->Length - 1]->Equals("ReadMe.txt"))
					{
						///ÄÀ¥XTreasureImagePart1.raw
						return 0;
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
							Windows::Forms::MessageBox::Show("°Ú«¢«¢±¾±¼·S P:",
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
