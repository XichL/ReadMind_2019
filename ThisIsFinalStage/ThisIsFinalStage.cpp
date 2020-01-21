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
				Console::WriteLine("【這是最後一關，需要丟入含有最終字串(FinalString)的內容的.xml檔案來取得解答】");
				Console::WriteLine("【要挑戰嗎？要請打「Yes」、不要請打「No」】");
				if (Console::ReadLine()->Equals("Yes"))
				{
					Console::WriteLine("【相信您一定是突破重重機關才來到這裡的……】");
					system("PAUSE");
					Console::WriteLine("【請回顧並展現您所知道的一切，來吧……】");
					system("PAUSE");
					Console::WriteLine("【請輸入「完整檔案名稱」(記得加副檔名喔)：】");
					system("PAUSE");
				}
				else if (Console::ReadLine()->Equals("No"))
				{
					Console::WriteLine("【你不挑戰嗎？真可惜……】");
				}
				else
				{
					Console::WriteLine("【聽不懂你說甚麼呢～】");
				}


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
						///釋出key
						return;
					}
					else
					{
						FileName = FileName[FileName->Length - 1]->Split('.');
						if (FileName[1]->ToUpper()->Equals("XML")) //檢查副檔名是否為raw圖
						{
							Console::WriteLine(FileName[0] + " is not xml image.");
						}
						else
						{
							try {

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
