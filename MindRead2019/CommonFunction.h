#pragma once
#include "stdafx.h"

#define RELEASE(a) (((a)!=0) ? (delete[] (a),(a) = 0):((a)=0))

#define DebguSBS true
#define ImageFolderPath (System::IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath) + "\\ImageData\\")
#define NLOG_DLLTAG	"[MindRead2019]"

namespace MindReadFunction
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

	public ref class CommonFunction
	{
	public:
		CommonFunction();
		~CommonFunction();

		bool NLogMsg(String^ Message);
		bool NLogMsg(String^ FuncTag, String^ Message);

		void DataLoad(String^ loadPath, array<Byte>^ loadData);
		
		void LoadBMP(unsigned char *_FrameBuffer);
		void LoadBMP(array<Byte>^% _FrameBuffer);
		void getbmpDataWH(int &width, int &height);

		void SaveBmp(Drawing::Bitmap^ bmp, String^ path);

		void SaveData(array<USHORT>^ Data, int nWidth, int nHeight, int channel, String^ fileName);
		void SaveData(array<double>^ Data, int nWidth, int nHeight, int channel, String^ fileName);
		void SaveData(array<Byte>^ Data, int nWidth, int nHeight, int channel, String^ fileName);

		bool BGRtoY(unsigned char *BGRImage, int Width, int Height, unsigned char *YImage);

		void mosaic(array<Byte>^ Src, int width, int height, int channel, array<Byte>^ Dst);
		void demosaic(array<Byte>^ Src, int width, int height, int channel, array<Byte>^ Dst);
	private:
		NLog::Logger^ logger = NLog::LogManager::GetLogger("ProjectName");
		int Width, Height;
		String^ FileName;
		unsigned char *pFrameBuffer;
		ImageData^ bmpData;
	};
}