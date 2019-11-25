#include "stdafx.h"
#include "CommonFunction.h"

namespace MindReadFunction
{
	CommonFunction::CommonFunction()
	{
		//throw gcnew System::NotImplementedException();
	}

	CommonFunction::~CommonFunction()
	{
		//throw gcnew System::NotImplementedException();
	}

	bool CommonFunction::NLogMsg(String ^ Message)
	{
		logger->Debug(Message);
		return false;
	}

	bool CommonFunction::NLogMsg(String ^ FuncTag, String ^ Message)
	{
		String^ LogString = NLOG_DLLTAG + "[" + FuncTag + "]" + " " + Message;
		NLogMsg(LogString);

		return false;
	}

	void CommonFunction::DataLoad(String^ loadPath, array<Byte>^ loadData)
	{
		DateTime dtSFRStartTime = DateTime::Now;
		array<Byte>^ Fin_Byte;
		array<USHORT>^ Fin_Ushort;
		int width, height;

		width = 1924;
		height = 1080;
		String^ file = "C:\\Users\\NST\\Downloads\\SVN\\WorkSpace\\ProjectDocument\\Foxconn-Polight\\SFR Plus-1x-12ms-RGBIR-1000lux\\SFR Plus-1x-12ms-RGBIR-1000lux.raw";
		IO::FileStream^ fs = gcnew IO::FileStream(file, IO::FileMode::Open);

		NLogMsg("RGBIR_Raw12");
		Fin_Ushort = gcnew array<USHORT>(width*height);
		array<Byte>^ tmpByte = gcnew array <Byte>(width*height * 2);
		fs->Read(tmpByte, 0, width*height * 2);

		//_ImageData_12Raw^ raw12 = gcnew _ImageData_12Raw(width, height);
		pin_ptr<Byte> b_ptr = &tmpByte[0];
		//pin_ptr<double> dst_ptr = &raw12->Image[0];
	}

	void CommonFunction::LoadBMP(unsigned char *_FrameBuffer)
	{

#pragma region BMP_Get

		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();

		openFileDialog1->Title = L"Select a Image File";
		openFileDialog1->Filter = "BMP Image|*.bmp|Jpg Image|*.jpg|Png Image|*.png";

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			Bitmap ^Bmp = gcnew Bitmap(openFileDialog1->FileName);
			Width = Bmp->Width;
			Height = Bmp->Height;
			//this->FileName = openFileDialog1->SafeFileName;
			this->FileName = Path::GetFileNameWithoutExtension(openFileDialog1->SafeFileName);

			RELEASE(pFrameBuffer);
			pFrameBuffer = new unsigned char[Width*Height * 3];

			// Lock the bitmap's bits.  
			Drawing::Rectangle rect = Drawing::Rectangle(0, 0, Bmp->Width, Bmp->Height);
			BitmapData^ bmpData = Bmp->LockBits(rect, ImageLockMode::ReadWrite, PixelFormat::Format24bppRgb);

			// Get the address of the first line.
			UCHAR *Source = (UCHAR*)(void*)bmpData->Scan0;
			UCHAR *Target = pFrameBuffer;

			// Copy the value.  
			int offset = bmpData->Stride - Bmp->Width * 3;
			if (offset == 0)
			{
				memcpy(Target, Source, Bmp->Width*Bmp->Height * 3);
			}
			else
			{
				for (int y = 0; y < Bmp->Height; y++)
				{
					memcpy(Target, Source, Bmp->Width * 3);
					Target += Bmp->Width * 3;
					Source += Bmp->Width * 3 + offset;
				}
			}

			// Unlock the bits.
			Bmp->UnlockBits(bmpData);

			this->bmpData = gcnew ImageData(Width, Height, 3);
			pin_ptr<Byte> bufferPtr = &this->bmpData->imgData[0];
			//memcpy(_FrameBuffer, pFrameBuffer, Width*Height * 3);
			memcpy(bufferPtr, pFrameBuffer, Width*Height * 3);
		}
#pragma endregion


	}

	void CommonFunction::getbmpDataWH(int & width, int & height)
	{
		width = this->Width;
		height = this->Height;
	}

	//void CommonFunction::DataLoad(String^ loadPath, array<Byte>^ loadData)
	//{
	//
	//	DateTime dtSFRStartTime = DateTime::Now;
	//	array<Byte>^ Fin_Byte;
	//	array<USHORT>^ Fin_Ushort;
	//	int width, height;
	//
	//	String^ dateTime = dtSFRStartTime.ToString("yyyyMMdd_hhmm");
	//
	//#if (DebguSBS) //Debug單步執行用
	//
	//	width = 1924;
	//	height = 1080;
	//	String^ file = "C:\\Users\\NST\\Downloads\\SVN\\WorkSpace\\ProjectDocument\\Foxconn-Polight\\SFR Plus-1x-12ms-RGBIR-1000lux\\SFR Plus-1x-12ms-RGBIR-1000lux.raw";
	//	IO::FileStream^ fs = gcnew IO::FileStream(file, IO::FileMode::Open);
	//	{
	//#else
	//	Console::WriteLine("Width:");
	//	width = Convert::ToInt32(Console::ReadLine());
	//	Console::WriteLine("Height:");
	//
	//	IO::FileStream^ fs = gcnew IO::FileStream(loadPath, IO::FileMode::Open);
	//	array<String^>^ FileName = loadPath->Split('\\');
	//	FileName = FileName[FileName->Length - 1]->Split('.');
	//	if (FileName[1]->ToUpper() != "RAW") //檢查副檔名是否為raw圖
	//	{
	//		Console::WriteLine(FileName[0] + " is not raw image.");
	//	}
	//#endif
	//
	//	// RGBIR_Raw12 to GRaw12
	//	if (1)
	//	{
	//		NLogMsg("RGBIR_Raw12");
	//		Fin_Ushort = gcnew array<USHORT>(width*height);
	//		array<Byte>^ tmpByte = gcnew array <Byte>(width*height * 2);
	//		fs->Read(tmpByte, 0, width*height * 2);
	//
	//		//_ImageData_12Raw^ raw12 = gcnew _ImageData_12Raw(width, height);
	//		pin_ptr<Byte> b_ptr = &tmpByte[0];
	//		//pin_ptr<double> dst_ptr = &raw12->Image[0];
	//
	//		//demosicSet->RGBIRToG(b_ptr, width, height, 0, true, dst_ptr);
	//#if (DebguSBS) //Debug單步執行用
	//				//demosicSet->SaveImage_Raw12(raw12, "..\\Demo2_Img2.raw");
	//#else
	//		demosicSet->SaveImage_Raw12(raw12, String::Format("{0}_{1}_12Raw.raw", dateTime, FileName[0]));
	//#endif
	//
	//	}
	//
	//}

}