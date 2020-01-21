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
				//Out put What is demosaic
				break;
			}
			else if (args->Length > 1)
			{
				Console::WriteLine("餵太多囉~");
				system("PAUSE");
				//Windows::Forms::MessageBox::Show("餵太多囉~",
				//	"",
				//	MessageBoxButtons::OK,
				//	MessageBoxIcon::Stop
				//);

				break;
			}
			else
			{
				for (int i = 0; i < args->Length; i++)
				{
					IO::FileStream^ fs = gcnew IO::FileStream(args[i], IO::FileMode::Open);
					array<String^>^ FileName = args[i]->Split('\\');

					//若餵ReadMe
					if (FileName[FileName->Length - 1]->Equals("ReadMe.txt"))
					{
						///釋出TreasureImagePart2.raw
						return;
					}
					else
					{
						FileName = FileName[FileName->Length - 1]->Split('.');
						if (FileName[1]->ToUpper()->Equals("RAW")) //檢查副檔名是否為raw圖
						{
							Console::WriteLine(FileName[0] + " is not raw image.");
						}
						else
						{
							try {
								int nWidth, nHeight;
								if (FileName[0]->Equals("TreasureImage"))
								{
									nWidth = 1920;
									nHeight = 960;
								}
								else
								{
									Console::WriteLine("nWidth");
									nWidth = Convert::ToInt32(Console::ReadLine());
									Console::WriteLine("nHeight");
									nHeight = Convert::ToInt32(Console::ReadLine());
								}

								array<Byte>^ srcData = gcnew array<Byte>(nWidth*nHeight * 2);
								array<Byte>^ outData = gcnew array<Byte>(nWidth*nHeight * 2);
								fs->Read(srcData, 0, nWidth*nHeight * 2);
								fs->Close();

								MRFun->demosaic(srcData, nWidth, nHeight, 1, outData);
								MRFun->SaveData(outData, nWidth, nHeight, 2, "Test");
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
						break;
					}
				}
			}
		} while (1);
	}
	catch (Exception^ e)
	{

	}

	return 0;
}
