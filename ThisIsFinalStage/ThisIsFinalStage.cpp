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
				Console::WriteLine("�i�o�O�̫�@���A�ݭn��J�t���̲צr��(FinalString)�����e��.xml�ɮרӨ��o�ѵ��j");
				Console::WriteLine("�i�n�D�ԶܡH�n�Х��uYes�v�B���n�Х��uNo�v�j");
				if (Console::ReadLine()->Equals("Yes"))
				{
					Console::WriteLine("�i�۫H�z�@�w�O��}���������~�Ө�o�̪��K�K�j");
					system("PAUSE");
					Console::WriteLine("�i�Ц^�U�îi�{�z�Ҫ��D���@���A�ӧa�K�K�j");
					system("PAUSE");
					Console::WriteLine("�i�п�J�u�����ɮצW�١v(�O�o�[���ɦW��)�G�j");
					system("PAUSE");
				}
				else if (Console::ReadLine()->Equals("No"))
				{
					Console::WriteLine("�i�A���D�ԶܡH�u�i���K�K�j");
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
						return;
					}
					else
					{
						FileName = FileName[FileName->Length - 1]->Split('.');
						if (FileName[1]->ToUpper()->Equals("XML")) //�ˬd���ɦW�O�_��raw��
						{
							Console::WriteLine(FileName[0] + " is not xml image.");
						}
						else
						{
							try {

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
