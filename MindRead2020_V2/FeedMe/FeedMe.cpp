#include "stdafx.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace MindRead_FunctionSet;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	//AppDomain::CurrentDomain->AppendPrivatePath("Miscellaneous");
	//String^ strPath = IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath) + "\\Miscellaneous\\";
	//IO::Directory::SetCurrentDirectory(strPath);

	String^ ExecutePath = IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath);

	FunctionSet^ MRFun = gcnew FunctionSet();
	//----------------------------------------------------
	do {
		if (args->Length > 1)
		{
			MRFun->NLogMsg(String::Format("丟 {0:0}個檔案 到 FeedMe.exe", args->Length));

			Console::WriteLine("餵太多囉~");
			system("PAUSE");
			//Windows::Forms::MessageBox::Show("餵太多囉~",
			//	"",
			//	MessageBoxButtons::OK,
			//	MessageBoxIcon::Stop
			//);

			break;
		}

		if (args->Length != 1)
		{
			MRFun->NLogMsg(String::Format("雙擊 FeedMe.exe"));

			if (Windows::Forms::MessageBox::Show("您好，可以叫我餵餵，我有著亞席大人的藏寶箱密碼，您想知道嗎？",
				"想知道嗎",
				MessageBoxButtons::YesNo,
				MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
			{
				Windows::Forms::MessageBox::Show("才不告訴您咧呸∼",
					"想知道嗎",
					MessageBoxButtons::OK,
					MessageBoxIcon::Information);
			}
			else
			{
				Windows::Forms::MessageBox::Show("哼∼您不想知道啊∼那就不告訴您嚕！",
					"想知道嗎",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}

			break;
		}

		for (int i = 0; i < args->Length; i++)
		{
			IO::FileStream^ fs = gcnew IO::FileStream(args[i], IO::FileMode::Open);
			array<String^>^ FileName = args[i]->Split('\\');

			MRFun->NLogMsg(String::Format("丟 {0:0} 到 FeedMe.exe", FileName[FileName->Length - 1]));

			//若餵ReadMe
			if (FileName[FileName->Length - 1]->Equals("ReadMe.txt"))
			{

				Windows::Forms::MessageBox::Show("謝謝您餵我。",
					"Thank you~",
					MessageBoxButtons::OK,
					MessageBoxIcon::Stop
				);
				Windows::Forms::MessageBox::Show("這是亞席大人留下來的，就送給您吧~",
					"Gift",
					MessageBoxButtons::OK,
					MessageBoxIcon::None
				);
				///釋出TreasureImage.raw
				MRFun->GetSourceFile("TreasureImage", FILETYPE::FILETYPE_RAW,
					"TreasureImage.raw");
				MRFun->NLogMsg(String::Format("FeedMe.exe 釋出 TreasureImage.raw"));

				break;
			}
			else if (FileName[FileName->Length - 1]->Equals("這是一張圖片.txt"))
			{
				///釋出TreasureImageFinal.raw
				MRFun->GetSourceFile("TreasureImageFinal", FILETYPE::FILETYPE_RAW,
					"TreasureImageFinal.raw");
				MRFun->NLogMsg(String::Format("FeedMe.exe 釋出 TreasureImageFinal.raw"));

				break;
			}
			else if (FileName[FileName->Length - 1]->Equals("Key.txt"))
			{
				Windows::Forms::MessageBox::Show("嗯？這是KEY嗎？記得亞席大人有留下一些和它相關的訊息呢~就送您吧。",
					"Gift",
					MessageBoxButtons::OK,
					MessageBoxIcon::None
				);
				MRFun->GetSourceFile("KEY的解讀", FILETYPE::FILETYPE_TXT,
					"KEY的解讀.txt");
				MRFun->NLogMsg(String::Format("FeedMe.exe 釋出 KEY的解讀.txt"));
				break;
			}
			else
			{
				FileName = FileName[FileName->Length - 1]->Split('.');
				if (FileName[1]->ToUpper() != "RAW") //檢查副檔名是否為raw圖
				{
					Windows::Forms::MessageBox::Show("(嚼嚼∼",
						"什麼也沒留下",
						MessageBoxButtons::OK,
						MessageBoxIcon::None);
				}
				else
				{
					///釋出Tr[ae]sureImage.bmp
					MRFun->GetSourceFile("TraesureImage", FILETYPE::FILETYPE_BMP,
						"TraesureImage");
					MRFun->NLogMsg(String::Format("FeedMe.exe 釋出 TraesureImage.bmp"));

					break;
				}
				break;
			}
		}
	} while (0);
	return 0;
}
