#pragma once
#include "stdafx.h"

#define RELEASE(a) (((a)!=0) ? (delete[] (a),(a) = 0):((a)=0))

#define String2string(a) (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(a)).ToPointer();

#define DebguSBS true
//#define ImageFolderPath (System::IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath) + "\\ImageData\\")
#define ImageFolderPath (System::IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath) + "\\")
#define NLOG_DLLTAG	"[MindReadFunctionSet]"

namespace MindRead_FunctionSet
{
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace System::Windows::Forms;
	using namespace System::IO;

	public ref struct ImageData
	{
		ImageData(int width, int height, int channel)
		{
			this->width = width;
			this->height = height;
			imgData = gcnew array<Byte>(width * height * channel);
		}
		int width;
		int height;
		array<Byte>^ imgData;
	};

	public enum class FILETYPE
	{
		FILETYPE_TXT,
		FILETYPE_RAW,
		FILETYPE_BMP,
		FILETYPE_OTHER
	};

	public ref class FunctionSet
	{
	public:
		FunctionSet();
		~FunctionSet();

		//寫Log用
		bool NLogMsg(String^ Message);
		bool NLogMsg(String^ FuncTag, String^ Message);

		//讀檔專用
		void DataLoad(String^ loadPath, array<Byte>^ loadData);
		void DataLoad_TXT(String^ loadPath, array<Byte>^% loadData);
		void DataLoad_AutoSize(String^ loadPath, array<Byte>^% loadData);

		void LoadBMP(unsigned char *_FrameBuffer);
		void LoadBMP(array<Byte>^% _FrameBuffer);

		//存檔專用
		void SaveBmp(Drawing::Bitmap^ bmp, bool cover, String^ fileName);

		void SaveData(array<USHORT>^ Data, int nWidth, int nHeight, int channel, String^ fileName);
		void SaveData(array<double>^ Data, int nWidth, int nHeight, int channel, String^ fileName);
		void SaveData(array<Byte>^ Data, int nWidth, int nHeight, int channel, String^ fileName);

		void SaveData_Append(String^ Data, String^ fileName);

		void SaveStringData_Encoding(String^ strMessage ,String^ fileName);

		//各種轉換工具
		void mosaic(array<Byte>^ Src, int width, int height, int channel, array<Byte>^% Dst);
		void demosaic(array<Byte>^ Src, int width, int height, int channel, array<Byte>^% Dst);
		void getbmpDataWH(int &width, int &height);
		bool BGRtoY(unsigned char *BGRImage, int Width, int Height, unsigned char *YImage);

		void Raw2Bmp(array<Byte>^ Src, Drawing::Bitmap^ bmp);

		void HLConverter(array<Byte>^ Src, int byteNum, array<Byte>^% Dst);

		void TransTo8bitASCII(String^ inputData, String^% outputData);
		void ASCII8bitToLetter(String^ inputData, String^% outputData);

		void String2Byte(String^ inputData ,array<Byte>^% outputData);

		//取得資源檔內容
		void GetSourceFile(String^ FileName, FILETYPE^ type, String^ saveName);

	private:
		NLog::Logger^ logger = NLog::LogManager::GetLogger("ProjectName");
		System::Text::ASCIIEncoding^ asciiEncoding = gcnew System::Text::ASCIIEncoding;
		int Width, Height;
		String^ FileName;
		unsigned char *pFrameBuffer;
		ImageData^ bmpData;

		System::Resources::ResourceManager^ mng = gcnew System::Resources::ResourceManager("MindReadFunctionSet.Resource",
			this->GetType()->Assembly);
	};
}