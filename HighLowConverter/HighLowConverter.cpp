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
				strMessage += "raw即代表原始圖檔，包含從數位相機、掃描器或電影膠片掃描器的圖像感測器所處理資料。";
				strMessage += Environment::NewLine;
				strMessage += "之所以這樣命名，是因為他們尚未被處理，未被列印或用於編輯。...取自wiki";
				strMessage += Environment::NewLine;
				strMessage += Environment::NewLine;

				strMessage += "raw檔含有影像(Image)最原始的資料，通常是一長串數字序列。";
				strMessage += Environment::NewLine;
				strMessage += "根據影像(Image)的解析度(也就是寬、高)，經過特定的手續重組，就是所謂的去馬賽克(Demosic)。";
				strMessage += Environment::NewLine;
				strMessage += Environment::NewLine;

				strMessage += "不一樣的手續去馬賽克的結果不盡相同，但為了取得讓一般人也可以觀看的圖片，去馬賽克的動作是必須的。";

				//MRFun->SaveStringData_cover(strMessage, "raw檔是什麼.txt");

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
