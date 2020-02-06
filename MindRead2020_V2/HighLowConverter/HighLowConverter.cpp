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
				MRFun->NLogMsg(String::Format("���� HighLowConverter.exe"));

				///output what is HLConverter
				MRFun->GetSourceFile("HighLow�ഫ���ηN", FILETYPE::FILETYPE_TXT,
					"HighLow�ഫ���ηN.txt");
				MRFun->NLogMsg(String::Format("HighLowConverter.exe ���X HighLow�ഫ���ηN.txt"));

				break;
			}
			else if (args->Length > 1)
			{
				MRFun->NLogMsg(String::Format("�� {0:0}���ɮ� �� HighLowConverter.exe", args->Length));

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

					MRFun->NLogMsg(String::Format("�� {0:0} �� HighLowConverter.exe", FileName[FileName->Length - 1]));

					//�Y��ReadMe
					if (FileName[FileName->Length - 1]->Equals("ReadMe.txt"))
					{
						///���XTreasureImagePart1.raw
						MRFun->GetSourceFile("TreasureImage1", FILETYPE::FILETYPE_RAW,
							"TreasureImagePart1.raw");
						MRFun->NLogMsg(String::Format("HighLowConverter.exe ���X TreasureImagePart1.raw"));

						//Ū�����e�A�ˬd�O�_�s�bH1~3
						//�ˬdH1~3���O�_��Hint
						//"Part2�AWPart1x1200"
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
						if (!EXName->Equals("RAW")) //�ˬd���ɦW�O�_��raw��
						{
							Console::WriteLine(FileName[0] + " is not raw image.");
							system("PAUSE");
						}

						try 
						{
							array<Byte>^ readByte;

							String^ outputName;
							if (FileName[0]->Contains("HLOut"))
							{
								outputName = FileName[0]->Split('.')[0] + ".raw";
							}
							else
							{
								outputName = FileName[0]->Split('.')[0] + "HLOut.raw";
							}

							//Ū��(�۰ʦY����)
							MRFun->DataLoad_AutoSize(args[i], readByte);
							//�ھڪ��שw�qoutputArray
							array<Byte>^ outputHLByte = gcnew array<Byte>(readByte->Length);
							MRFun->HLConverter(readByte, 2, outputHLByte);
							//�x�sHLConvert�����G
							MRFun->SaveData(outputHLByte, readByte->Length, 1, 1, true, outputName);
							MRFun->NLogMsg(String::Format("HighLowConverter.exe ���X {0:0}", outputName));

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
	catch (...)
	{
		MRFun->NLogMsg("HighLowConverter exception.");
	}
	return 0;

}
