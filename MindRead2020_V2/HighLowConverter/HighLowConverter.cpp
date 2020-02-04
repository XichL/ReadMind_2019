#include "stdafx.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace MindRead_FunctionSet;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	//AppDomain::CurrentDomain->AppendPrivatePath("Miscellaneous");
	//String^ strPath = IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath) + "\\Miscellaneous";
	//IO::Directory::SetCurrentDirectory(strPath);

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
						MRFun->GetSourceFile("TreasureImage1", FILETYPE::FILETYPE_RAW,
							"TreasureImagePart1.raw");

						//讀取內容，檢查是否存在H1~3
						//檢查H1~3中是否有Hint
						//"Part2，WPart1x1200"
						fs->Close();
						System::IO::StreamReader^ readFile = gcnew System::IO::StreamReader(args[i]);
						int HintNum = 0;
						bool FindHint = false;
						while (!readFile->EndOfStream)
						{
							String^ LineString = readFile->ReadLine();
							if (LineString->Contains("H" + HintNum + "."))
							{
								FindHint = true;
								array<String^>^ checkString = LineString->Split('.');
								if (checkString[1]->Equals("Part2 = WPart1x1200"))
								{
									readFile->Close();
									break;
								}
								else
								{
									HintNum++;
								}
							}
							if (FindHint&&readFile->EndOfStream)
							{
								readFile->Close();

								String^ strNewHint = Environment::NewLine + "H" + HintNum + ".Part2 = WPart1x1200";
								try
								{
									System::Text::ASCIIEncoding^ asciiEncoding = gcnew System::Text::ASCIIEncoding;
									fs = gcnew IO::FileStream(args[i], IO::FileMode::Append);
									fs->Write(asciiEncoding->GetBytes(strNewHint), 0, asciiEncoding->GetByteCount(strNewHint));
									break;
								}
								catch (System::Exception^ e)
								{
									MRFun->NLogMsg("HLConverter",
										String::Format("Modify ReadMe : {0:0}", e));
									return 0;
								}
							}
						}
						break;
					}
					else
					{
						try 
						{
							array<Byte>^ readByte;

							String^ outputName;
							if (FileName[FileName->Length - 1]->Contains("HLOut"))
							{
								outputName = FileName[FileName->Length - 1]->Split('.')[0] + ".raw";
							}
							else
							{
								outputName = FileName[FileName->Length - 1]->Split('.')[0] + "HLOut.raw";
							}

							//讀檔(自動吃長度)
							MRFun->DataLoad_AutoSize(args[i], readByte);
							//根據長度定義outputArray
							array<Byte>^ outputHLByte = gcnew array<Byte>(readByte->Length);
							MRFun->HLConverter(readByte, 2, outputHLByte);
							//儲存HLConvert的結果
							MRFun->SaveData(outputHLByte, readByte->Length, 1, 1, true, outputName);
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
	catch (...)
	{
		MRFun->NLogMsg("HighLowConverter exception.");
	}
	return 0;

}
