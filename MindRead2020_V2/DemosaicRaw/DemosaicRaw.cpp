#include "stdafx.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace MindRead_FunctionSet;

bool ImageCompareByString(Drawing::Bitmap^ firstImage, Drawing::Bitmap^ secondImage);

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

								if (fs->Length != nWidth * nHeight * 2)
								{
									Console::WriteLine(String::Format("nWidth or nHeight wrong"));
									system("pause");
									break;
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

								//part1 = part1
								if (ImageCompareByString(MRFun->GetSourceFile_BMP("TreasureImagePart1HLOut"), outBmp))
								{
									String^ strID1 = "ID1 = 01010111001100100001001101010000000011010101001000001011001010100011001100101010000111110010000100101011001010010010100100100111";
									MRFun->SaveData_Append(strID1, "Log\\TreasureImageContent.txt");
									MRFun->NLogMsg(String::Format("將 [TreasureImageContent.txt] 存在 [Log資料夾]", FileName[0]));

									Console::WriteLine(String::Format("為方便檢查，在Log新增一個檔案"));
									system("PAUSE");
								}
								//part2 = part2
								if (ImageCompareByString(MRFun->GetSourceFile_BMP("TreasureImagePart2HLOut"), outBmp))
								{
									String^ strID2 = "ID2 = 00110110001111000001111000101001001111110011111001010000001101100101000100010010000101100010010100101000001000110101011101010100";
									MRFun->SaveData_Append(strID2, "Log\\TreasureImageContent.txt");
									MRFun->NLogMsg(String::Format("將 [TreasureImageContent.txt] 存在 [Log資料夾]", FileName[0]));
									
									Console::WriteLine(String::Format("為方便檢查，在Log新增一個檔案"));
									system("PAUSE");
								}
								MRFun->SaveBmp(outBmp, true, FileName[0]);


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

bool ImageCompareByString(Drawing::Bitmap^ firstImage, Drawing::Bitmap^ secondImage)
{
	IO::MemoryStream^ ms = gcnew IO::MemoryStream();
	firstImage->Save(ms, Drawing::Imaging::ImageFormat::Bmp);
	String^ firstBitmap = Convert::ToBase64String(ms->ToArray());
	ms->Position = 0;
	secondImage->Save(ms, Drawing::Imaging::ImageFormat::Bmp);
	String^ secondBitmap = Convert::ToBase64String(ms->ToArray());
	if (firstBitmap->Equals(secondBitmap))
	{
		return true;
	}
	else
	{
		return false;
	}
}