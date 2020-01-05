#include "stdafx.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace MindRead_FunctionSet;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	if (args->Length > 1)
	{
		Console::WriteLine("���Ӧh�o~");
		system("PAUSE");
		return 0;
	}

	Windows::Forms::MessageBox::Show("���Ӧh�o~",
		"",
		MessageBoxButtons::OK,
		MessageBoxIcon::Stop
	);

	for (int i = 0; i < args->Length; i++)
	{
		IO::FileStream^ fs = gcnew IO::FileStream(args[i], IO::FileMode::Open);
		array<String^>^ FileName = args[i]->Split('\\');
		FileName = FileName[FileName->Length - 1]->Split('.');
		if (FileName[1]->ToUpper() != "RAW") //�ˬd���ɦW�O�_��raw��
		{
			Console::WriteLine(FileName[0] + " is not raw image.");
			continue;
		}
	}
}
