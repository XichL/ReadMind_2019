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

	String^ CheckFileExist(int overlappingCount, String ^ strName)
	{
		String^ SrcName = strName;
		if (IO::File::Exists(strName))
		{
			array<String^>^ SplitString = strName->Split('.');
			String^ extension = SplitString[SplitString->Length - 1];
			strName = strName->Replace("." + extension, ("(" + overlappingCount + ")" + "." + extension));

			overlappingCount++;
			return (IO::File::Exists(strName)) ?
				CheckFileExist(overlappingCount, SrcName) : CheckFileExist(overlappingCount, strName);
		}
		else
		{
			return strName;
		}

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

	void CommonFunction::LoadBMP(array<Byte>^% _FrameBuffer)
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

			_FrameBuffer = gcnew array<Byte>(Width*Height * 3);
			pin_ptr<Byte> bufferPtr = &_FrameBuffer[0];
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

	void CommonFunction::SaveBmp(Drawing::Bitmap ^ bmp, String ^ path)
	{
		bmp->Save(CheckFileExist(0, path), Drawing::Imaging::ImageFormat::Bmp);
	}

	void CommonFunction::SaveData(array<USHORT>^ Data, int nWidth, int nHeight, int channel, String ^ fileName)
	{
		IO::FileStream^ fs;
		String^ FilePath = ImageFolderPath;
		IO::Directory::CreateDirectory(FilePath);
		FilePath += fileName;

		try
		{
			fs = gcnew IO::FileStream(CheckFileExist(0, FilePath), IO::FileMode::CreateNew);

			IO::BinaryWriter^ TW = gcnew IO::BinaryWriter(fs);
			for (int i = 0; i < nWidth*nHeight; i++)
			{
				TW->Write(Data[i]);
			}
			fs->Close();
			TW->Close();
		}
		catch (System::Exception^ e)
		{
			logger->Debug(e);
		}
	}

	void CommonFunction::SaveData(array<double>^ Data, int nWidth, int nHeight, int channel, String ^ fileName)
	{
		IO::FileStream^ fs;
		String^ FilePath = ImageFolderPath;
		IO::Directory::CreateDirectory(FilePath);
		FilePath += fileName;

		try
		{
			fs = gcnew IO::FileStream(CheckFileExist(0, FilePath), IO::FileMode::CreateNew);

			IO::BinaryWriter^ TW = gcnew IO::BinaryWriter(fs);
			for (int i = 0; i < nWidth*nHeight; i++)
			{
				TW->Write(Data[i]);
			}
			fs->Close();
			TW->Close();
		}
		catch (System::Exception^ e)
		{
			logger->Debug(e);
		}
	}

	void CommonFunction::SaveData(array<Byte>^ Data, int nWidth, int nHeight, int channel, String ^ fileName)
	{
		IO::FileStream^ fs;
		String^ FilePath = ImageFolderPath;
		IO::Directory::CreateDirectory(FilePath);
		FilePath += fileName;

		try
		{
			fs = gcnew IO::FileStream(CheckFileExist(0, FilePath), IO::FileMode::CreateNew);

			IO::BinaryWriter^ TW = gcnew IO::BinaryWriter(fs);
			for (int i = 0; i < nWidth*nHeight * channel; i++)
			{
				TW->Write(Data[i]);
			}
			fs->Close();
			TW->Close();
		}
		catch (System::Exception^ e)
		{
			logger->Debug(e);
		}
	}

	bool CommonFunction::BGRtoY(unsigned char * BGRImage, int Width, int Height, unsigned char * YImage)
	{
		bool bRes = true;
		//-------------------------------------------------
		UCHAR R, G, B;

		if ((Width == 0) || (Height == 0))
		{
			return false;
		}

		double R_Table[256];
		double G_Table[256];
		double B_Table[256];

		for (int i = 0; i < 256; i++)
		{
			R_Table[i] = 0.299 * i;
			G_Table[i] = 0.587 * i;
			B_Table[i] = 0.114 * i + 0.5;	//+0.5 for 四捨五入
		}

		for (int i = 0; i < Width*Height; i++)
		{
			B = *BGRImage++;
			G = *BGRImage++;
			R = *BGRImage++;
			*YImage++ = (unsigned char)(R_Table[R] + G_Table[G] + B_Table[B]);
			//*YImage++ = YPIXEL(R, G, B);
		}
		//-------------------------------------------------
		return bRes;
	}

	void CommonFunction::mosaic(array<Byte>^ Src, int width, int height, int channel, array<Byte>^ Dst)
	{
		array<Byte>^ YBuffer = gcnew array<Byte>(width*height);
		if (channel == 3)
		{
			pin_ptr<Byte> ptrSrc = &Src[0];
			pin_ptr<Byte> ptrYBuffer = &YBuffer[0];
			BGRtoY(ptrSrc, width, height, ptrYBuffer);
			//SaveData(YBuffer, width, height, 1, "TestY.raw");
		}

		//array<Byte>^ BChannel = gcnew array<Byte>(width*height);
		//array<Byte>^ GChannel = gcnew array<Byte>(width*height);
		//array<Byte>^ RChannel = gcnew array<Byte>(width*height);

		//for (int i = 0; i < width*height; i++)
		//{
		//	BChannel[i] = Src[i * 3];
		//	GChannel[i] = Src[i * 3 + 1];
		//	RChannel[i] = Src[i * 3 + 2];
		//}
		//SaveData(GChannel, width, height, 1, "Test.bmp");

		array<USHORT>^ tmpMosaic = gcnew array<USHORT>(width*height);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				//if ((y % 2 == 0) && (x % 2 == 1))
				//	tmpMosaic[y*width + x] = RChannel[y*width + x];
				//else if ((y % 2 == 1) && (x % 2 == 0))
				//	tmpMosaic[y*width + x] = BChannel[y*width + x];
				//else
				//	tmpMosaic[y*width + x] = GChannel[y*width + x];
				tmpMosaic[y*width + x] = YBuffer[y*width + x];

				Dst[y*width + x * 2] = tmpMosaic[y*width + x] >> 8;
				Dst[y*width + (x * 2) + 1] = tmpMosaic[y*width + x] & 0xff;
			}
		}

		SaveData(tmpMosaic, width, height, 1, "UCHARData.raw");
		int a = 0;
		a + 1;
	}

	void CommonFunction::demosaic(array<Byte>^ Src, int width, int height, int channel, array<Byte>^ Dst)
	{
		array<Byte>^ lowOrder = gcnew array<Byte>(width*height);
		for (int i = 0; i < width*height; i++)
		{
			Dst[i] = Src[i * 2 + 1];
		}
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