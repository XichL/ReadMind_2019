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
				Console::WriteLine("�i�o�O�̫�@���A�ݭn��J�t���̲צr��(FinalString)�����e��.xml�ɮרӨ��o�ѵ��j");
				Console::WriteLine("�i�n�D�ԶܡH�n�Х��uYes�v�B���n�Х��uNo�v�j");
				if (Console::ReadLine()->Equals("Yes"))
				{
					Console::WriteLine("�i�۫H�z�@�w�O��}���������~�Ө�o�̪��K�K�j");
					system("PAUSE");
					Console::WriteLine("�i�Ц^�U�îi�{�z�Ҫ��D���@���A�ӧa�K�K�j");
					system("PAUSE");
					Console::WriteLine("�i�п�J�u�����ɮצW�١v(�O�o�[���ɦW��)�G�j");
					String^ xmlName = Console::ReadLine();

					array<String^>^ xmlFileName = xmlName->Split('.');
					if (xmlFileName[1]->ToUpper()->Equals("XML")) //�ˬd���ɦW�O�_��raw��
					{
						Console::WriteLine(xmlFileName[0] + " is not xml file.");
					}
					else
					{
						array<Byte>^ realData;
						try
						{
							Console::WriteLine("�i�п�J�u�e�v�G�j");
							int width = Convert::ToInt32(Console::ReadLine());

							///Read file
							array<Byte>^ loadData;
							MRFun->DataLoad_AutoSize(IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath) + "\\" + xmlName,
								loadData);

							realData = gcnew array<Byte>(width);
							int idx = 0;
							bool xmlPass = true;
							for (int i = 0; i < loadData->Length; i++)
							{
								if (loadData[i] != ' ')
								{
									if (idx >= width)
									{
										Console::WriteLine("�i�e�n�����X�@�H�j");
										break;
									}
									realData[idx] = loadData[i];
									idx++;
								}
							}

							if (!xmlPass)
							{
								Console::WriteLine("�i�ݨ��٨S�ǳƦn�O��j");
								break;
							}
							Console::WriteLine("�i�ש�Ө�̫�F�O�I�j");
							system("PAUSE");
							Console::WriteLine("�m�д��J�_�͡n");

							String^ key = Console::ReadLine();
							array<Byte>^ xorKey = gcnew array<Byte>(4);
							if (key->Equals("STOCKING"))
							{
								Console::WriteLine("�m�K�X���T�n");
								system("PAUSE");
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
								Console::WriteLine("�K�K");
								system("PAUSE");
								xorKey[0] = randomByte[0];
								xorKey[1] = randomByte[1];
								xorKey[2] = randomByte[2];
								xorKey[3] = 1;
							}

							array<Byte>^ encodeData = gcnew array<Byte>(realData->Length);
							if (realData->Length % 4 != 0)
							{
								Console::WriteLine("�m��ƻP�_�ͤ��ǰt�n");
								system("PAUSE");
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
								Console::WriteLine("�m��J��ƿ��~�n");
								system("PAUSE");
								Console::WriteLine("�i�ݨ��ɮפ�����ƬO�����O�A���s�A�ӹL�a�C�j");
								system("PAUSE");
							}
							MRFun->ASCII8bitToLetter(encodeString, outString);
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
				else if (Console::ReadLine()->Equals("No"))
				{
					Console::WriteLine("�i���D�ԶܡH�u�i���K�K�j");
				}
				else
				{
					Console::WriteLine("�iť�����A���ƻ�O��j");
				}


				break;
			}
			else if (args->Length > 1)
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
			else
			{
				for (int i = 0; i < args->Length; i++)
				{
					IO::FileStream^ fs = gcnew IO::FileStream(args[i], IO::FileMode::Open);
					array<String^>^ FileName = args[i]->Split('\\');

					//�Y��ReadMe
					if (FileName[FileName->Length - 1]->Equals("ReadMe.txt"))
					{
						///���Xkey
						MRFun->GetSourceFile("Key", FILETYPE::FILETYPE_TXT,
							"Key.txt");

						//Ū�����e�A�ˬd�O�_�s�bH1~3
						//�ˬdH1~3���O�_��Hint
						//"Final�AW ? ? ? ? xHeight"
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
									fs = gcnew IO::FileStream(args[i], IO::FileMode::Append);
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
			}
		} while (1);
	}
	catch (Exception^ e)
	{

	}

	return 0;
}
