#include "stdafx.h"

using namespace System;
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
				String^ strMessage;
				strMessage += "raw�Y�N���l���ɡA�]�t�q�Ʀ�۾��B���y���ιq�v�������y�����Ϲ��P�����ҳB�z��ơC";
				strMessage += Environment::NewLine;
				strMessage += "���ҥH�o�˩R�W�A�O�]���L�̩|���Q�B�z�A���Q�C�L�ΥΩ�s��C...����wiki";
				strMessage += Environment::NewLine;
				strMessage += Environment::NewLine;

				strMessage += "raw�ɧt���v��(Image)�̭�l����ơA�q�`�O�@����Ʀr�ǦC�C";
				strMessage += Environment::NewLine;
				strMessage += "�ھڼv��(Image)���ѪR��(�]�N�O�e�B��)�A�g�L�S�w�����򭫲աA�N�O�ҿת��h���ɧJ(Demosic)�C";
				strMessage += Environment::NewLine;
				strMessage += Environment::NewLine;

				strMessage += "���@�˪�����h���ɧJ�����G���ɬۦP�A�����F���o���@��H�]�i�H�[�ݪ��Ϥ��A�h���ɧJ���ʧ@�O�������C";

				//MRFun->SaveStringData_cover(strMessage, "raw�ɬO����.txt");

				break;
			}
			else if (args->Length > 1)
			{
				Console::WriteLine("���Ӧh�o~");
				system("PAUSE");
				break;
			}
			else
			{
				IO::FileStream^ fs = gcnew IO::FileStream(args[0], IO::FileMode::Open);
				array<String^>^ FileName = args[0]->Split('\\');
				FileName = FileName[FileName->Length - 1]->Split('.');

				if (FileName[0] == "ReadMe" &&FileName[1] == "txt")
				{
					
				}
				else
				{

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
