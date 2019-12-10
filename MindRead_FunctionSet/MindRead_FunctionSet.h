#pragma once
#include "stdafx.h"

#define RELEASE(a) (((a)!=0) ? (delete[] (a),(a) = 0):((a)=0))

#define DebguSBS true
#define ImageFolderPath (System::IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath) + "\\ImageData\\")
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

	public ref class FunctionSet
	{
	public:
		FunctionSet();
		~FunctionSet();

		bool NLogMsg(String^ Message);
		bool NLogMsg(String^ FuncTag, String^ Message);

		//Load Data相關
		void DataLoad(String^ loadPath, array<Byte>^ loadData);

		void LoadBMP(unsigned char *_FrameBuffer);
		void LoadBMP(array<Byte>^% _FrameBuffer);


		//Save Data相關
		void SaveBmp(Drawing::Bitmap^ bmp, String^ path);

		void SaveData(array<USHORT>^ Data, int nWidth, int nHeight, int channel, String^ fileName);
		void SaveData(array<double>^ Data, int nWidth, int nHeight, int channel, String^ fileName);
		void SaveData(array<Byte>^ Data, int nWidth, int nHeight, int channel, String^ fileName);

		//Mosaic相關
		void mosaic(array<Byte>^ Src, int width, int height, int channel, array<Byte>^ Dst);
		void demosaic(array<Byte>^ Src, int width, int height, int channel, array<Byte>^ Dst);

		//影像處理相關
		void getbmpDataWH(int &width, int &height);
		bool BGRtoY(unsigned char *BGRImage, int Width, int Height, unsigned char *YImage);


		//ASCII 相關
		void TransTo8bitASCII(String^ inputData ,array<Byte>^ outputData);
		void ASCII8bitToLetter(array<Byte>^ outputData, String^ inputData);

	private:
		NLog::Logger^ logger = NLog::LogManager::GetLogger("ProjectName");
		int Width, Height;
		String^ FileName;
		unsigned char *pFrameBuffer;
		ImageData^ bmpData;
	};
}