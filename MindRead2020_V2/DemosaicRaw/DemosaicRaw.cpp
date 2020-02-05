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
				MRFun->NLogMsg(String::Format("雙擊 DemosaicRaw.exe"));

				///Out put What is demosaic
				MRFun->GetSourceFile("raw檔是什麼", FILETYPE::FILETYPE_TXT,
					"raw檔是什麼.txt");
				MRFun->NLogMsg(String::Format("DemosaicRaw.exe 釋出 raw檔是什麼.txt"));

				break;
			}
			else if (args->Length > 1)
			{
				MRFun->NLogMsg(String::Format("丟 {0:0}個檔案 到 DemosaicRaw.exe", args->Length));

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
					//MRFun->NLogMsg("Demosaic", String::Format("args length = {0:0}", args->Length));

					IO::FileStream^ fs = gcnew IO::FileStream(args[i], IO::FileMode::Open);
					array<String^>^ FileName = args[i]->Split('\\');

					MRFun->NLogMsg(String::Format("丟 {0:0} 到 DemosaicRaw.exe", FileName[FileName->Length - 1]));

					//若餵ReadMe
					if (FileName[FileName->Length - 1]->Equals("ReadMe.txt"))
					{
						///釋出TreasureImagePart2.raw
						MRFun->GetSourceFile("TreasureImage2", FILETYPE::FILETYPE_RAW,
							"TreasureImagePart2.raw");
						MRFun->NLogMsg(String::Format("DemosaicRaw.exe 釋出 TreasureImagePart2.raw"));

						//讀取內容，檢查是否存在H1~3
						//檢查H1~3中是否有Hint
						//"Part1，W1920x1080"
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
								if (checkString[1]->Equals("Part1 = W1920x1080"))
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

								String^ strNewHint = Environment::NewLine + "H" + HintNum + ".Part1 = W1920x1080";
								try
								{
									System::Text::ASCIIEncoding^ asciiEncoding = gcnew System::Text::ASCIIEncoding;
									fs = gcnew IO::FileStream(args[i], IO::FileMode::Append);
									fs->Write(asciiEncoding->GetBytes(strNewHint), 0, asciiEncoding->GetByteCount(strNewHint));
									break;
								}
								catch (System::Exception^ e)
								{
									MRFun->NLogMsg("DemosaicRaw",
										String::Format("Modify content error : {0:0}", e));
									return 0;
								}
							}
						}
						break;
					}
					else
					{
						MRFun->NLogMsg(String::Format("丟 {0:0} 到 DemosaicRaw.exe", FileName));

						FileName = FileName[FileName->Length - 1]->Split('.');
						String^ EXName = FileName[1]->ToUpper();
						if (!EXName->Equals("RAW")) //檢查副檔名是否為raw圖
						{
							Console::WriteLine(FileName[0] + " is not raw image.");
							system("PAUSE");
						}
						else
						{
							try {
								int nWidth, nHeight;
								if (FileName[0]->Equals("TreasureImage") || FileName[0]->Contains("TreasureImageHLOut"))
								{
									Console::WriteLine("殺斃死");
									Console::WriteLine("nWidth = 1920");
									Console::WriteLine("nHeight = 960");
									system("PAUSE");
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
								array<Byte>^ outData = gcnew array<Byte>(nWidth*nHeight);
								//MRFun->NLogMsg("Demosaic", "fs->Read start");
								fs->Read(srcData, 0, nWidth*nHeight * 2);
								fs->Close();
								//MRFun->NLogMsg("Demosaic", "fs->Read pass");

								//將16bit解為8bit的解碼
								//MRFun->NLogMsg("Demosaic", "demosica start");
								MRFun->demosaic(srcData, nWidth, nHeight, 1, outData);
								//MRFun->NLogMsg("Demosaic", "demosica pass");

								Drawing::Bitmap^ outBmp = gcnew Drawing::Bitmap(nWidth, nHeight, Drawing::Imaging::PixelFormat::Format8bppIndexed);
								MRFun->Raw2Bmp(outData, outBmp);
								//MRFun->NLogMsg("Demosaic", "Raw2Bmp pass");
								MRFun->SaveBmp(outBmp, true, FileName[0]);
								//MRFun->NLogMsg("Demosaic", "SaveBmp pass");

								MRFun->NLogMsg(String::Format("DemosaicRaw.exe 釋出 {0:0}.bmp", FileName[0]));
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
						break; //break for loop
					}
				}
				break; //break while loop
			}
		} while (1);
	}
	catch (Exception^ e)
	{

	}

	return 0;
}
