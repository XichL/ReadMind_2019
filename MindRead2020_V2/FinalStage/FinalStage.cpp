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
				MRFun->NLogMsg(String::Format("雙擊 FinalStage.exe"));

				Console::WriteLine("【這是最後一關，需要輸入含有最終字串(FinalString)的內容的.xml檔案來取得解答】");
				Console::WriteLine("【要挑戰嗎？要請打「Yes」、不要請打「No」】");
				String^ strYesNo = Console::ReadLine();
				if (strYesNo->Equals("Yes"))
				{
					Console::WriteLine("【相信您一定是突破重重機關才來到這裡的……】");
					system("PAUSE");
					Console::WriteLine("【請回顧並展現您所知道的一切，來吧……】");
					system("PAUSE");
					Console::WriteLine("【請輸入「完整檔案名稱」(記得加副檔名喔)：】");
					String^ xmlName = Console::ReadLine();
					MRFun->NLogMsg("輸入「完整檔案名稱」", String::Format("在 FinalStage.exe 中鍵入 {0:0}", xmlName));

					array<String^>^ xmlFileName = xmlName->Split('.');
					String^ xmlExtCheck = xmlFileName[1]->ToUpper();

					if (!xmlExtCheck->Equals("XML")) //檢查副檔名是否為xml
					{
						Console::WriteLine(xmlFileName[0] + " is not xml file.");
						system("PAUSE");
					}
					else
					{
						array<Byte>^ realData;
						try
						{
							Console::WriteLine("【請輸入「寬」：】");
							int width = Convert::ToInt32(Console::ReadLine());

							///Read file
							array<Byte>^ loadData;
							MRFun->DataLoad_AutoSize(IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath) + "\\" + xmlName,
								loadData);

							realData = gcnew array<Byte>(width);
							int idx = 0;
							bool xmlPass = true;
							Console::WriteLine(loadData[loadData->Length - 1]);
							Console::WriteLine(loadData[loadData->Length - 2]);
							system("PAUSE");
							for (int i = 0; i < loadData->Length; i++)
							{
								if (loadData[i] != ' ' && loadData[i] != '\r\n' && loadData[i] != '\r'&& loadData[i] != '\n')
								{
									if (idx >= width)
									{
										Console::WriteLine("【寬好像不合哦？】");
										system("PAUSE");
										xmlPass = false;
										break;
									}
									realData[idx] = loadData[i];
									idx++;
								}
							}

							if (!xmlPass)
							{
								Console::WriteLine("【看來還沒準備好呢∼】 ");
								system("PAUSE");
								break;
							}
							Console::WriteLine("【終於來到最後了呢！】");
							system("PAUSE");
							Console::WriteLine("《請插入鑰匙》");
							MRFun->NLogMsg("《請插入鑰匙》", String::Format("在 FinalStage.exe 中鍵入 {0:0}", xmlName));

							String^ key = Console::ReadLine();
							array<Byte>^ xorKey = gcnew array<Byte>(4);
							if (key->Equals("STOCKING"))
							{
								Console::WriteLine("《密碼正確》");
								//system("PAUSE");
								xorKey[0] = 0;
								xorKey[1] = 1;
								xorKey[2] = 1;
								xorKey[3] = 0;
							}
							else
							{
								Random^ rdm;
								array<Byte>^ randomByte = gcnew array<Byte>(3);
								rdm->NextBytes(randomByte);
								Console::WriteLine("……");
								//system("PAUSE");
								xorKey[0] = randomByte[0];
								xorKey[1] = randomByte[1];
								xorKey[2] = randomByte[2];
								xorKey[3] = 1;
							}

							array<Byte>^ encodeData = gcnew array<Byte>(realData->Length);
							if (realData->Length % 4 != 0)
							{
								Console::WriteLine("《資料與鑰匙不匹配》");
								system("PAUSE");
								break;
							}
							else
							{
								for (int i = 0; i < realData->Length; i += 4)
								{
									encodeData[i] = realData[i] ^ xorKey[0];
									encodeData[i + 1] = realData[i + 1] ^ xorKey[1];
									encodeData[i + 2] = realData[i + 2] ^ xorKey[2];
									encodeData[i + 3] = realData[i + 3] ^ xorKey[3];
								}
							}
							String^ encodeString;
							String^ outString;
							for each(Byte b in encodeData)
							{
								encodeString += b == '0' ? "0" : "1";
							}

							if (encodeData->Length % 8 != 0)
							{
								Console::WriteLine("《輸入資料錯誤》");
								system("PAUSE");
								Console::WriteLine("【看來檔案中的資料是錯的呢，重新再來過吧。】");
								system("PAUSE");
								break;
							}
							MRFun->ASCII8bitToLetter(encodeString, outString);

							MRFun->SaveData_Append("Ans = " + outString, "FinalString.txt");
							MRFun->NLogMsg(String::Format("FinalStage.exe 釋出 FinalString.txt"));

							system("PAUSE");
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
				else if (strYesNo->Equals("No"))
				{
					Console::WriteLine("【不挑戰嗎？真可惜……】");
					system("PAUSE");
				}
				else
				{
					Console::WriteLine("【聽不懂你說甚麼呢∼】");
					system("PAUSE");
				}


				break;
			}
			else if (args->Length > 1)
			{
				MRFun->NLogMsg(String::Format("丟 {0:0}個檔案 到 FinalStage.exe", args->Length));

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

					MRFun->NLogMsg(String::Format("丟 {0:0} 到 FinalStage.exe", FileName[FileName->Length - 1]));

					//若餵ReadMe
					if (FileName[FileName->Length - 1]->Equals("這是一張圖片.txt"))
					{
						///釋出key
						MRFun->GetSourceFile("Key", FILETYPE::FILETYPE_TXT,
							"Key.txt");

						//讀取內容，檢查是否存在H1~3
						//檢查H1~3中是否有Hint
						//"Final，W ? ? ? ? xHeight"
						fs->Close();
						System::IO::StreamReader^ readFile = gcnew System::IO::StreamReader(EXEPath + "\\ReadMe.txt");
						int HintNum = 0;
						bool FindHint = false;
						while (!readFile->EndOfStream)
						{
							String^ LineString = readFile->ReadLine();
							if (LineString->Contains("H" + HintNum + "."))
							{
								FindHint = true;
								array<String^>^ checkString = LineString->Split('.');
								if (checkString[1]->Equals("Final = WPart?xHeight"))
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

								String^ strNewHint = Environment::NewLine + "H" + HintNum + ".Final = WPart?xHeight";
								try
								{
									System::Text::ASCIIEncoding^ asciiEncoding = gcnew System::Text::ASCIIEncoding;
									fs = gcnew IO::FileStream(EXEPath + "\\ReadMe.txt", IO::FileMode::Append);
									fs->Write(asciiEncoding->GetBytes(strNewHint), 0, asciiEncoding->GetByteCount(strNewHint));
									break;
								}
								catch (System::Exception^ e)
								{
									MRFun->NLogMsg("FinalStage",
										String::Format("Modify ReadMe : {0:0}", e));
									return 0;
								}
							}
						}
						break;
					}
					else
					{
						break;
					}
				}
				break;
			}
		} while (0);
	}
	catch (Exception^ e)
	{

	}

	return 0;
}
