#include "stdafx.h"
#include "MindRead_FunctionSet.h"

using namespace System;



namespace MindRead_FunctionSet
{
	FunctionSet::FunctionSet()
	{
		//throw gcnew System::NotImplementedException();
	}

	FunctionSet::~FunctionSet()
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

	bool FunctionSet::NLogMsg(String ^ Message)
	{
		logger->Debug(Message);
		return false;
	}

	bool FunctionSet::NLogMsg(String ^ FuncTag, String ^ Message)
	{
		String^ LogString = NLOG_DLLTAG + "[" + FuncTag + "]" + " " + Message;
		NLogMsg(LogString);

		return false;
	}

	void FunctionSet::DataLoad(String^ loadPath, array<Byte>^ loadData)
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

	void FunctionSet::LoadBMP(unsigned char *_FrameBuffer)
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

	void FunctionSet::LoadBMP(array<Byte>^% _FrameBuffer)
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

	void FunctionSet::getbmpDataWH(int & width, int & height)
	{
		width = this->Width;
		height = this->Height;
	}

	void FunctionSet::SaveBmp(Drawing::Bitmap ^ bmp, String ^ path)
	{
		bmp->Save(CheckFileExist(0, path), Drawing::Imaging::ImageFormat::Bmp);
	}

	void FunctionSet::SaveData(array<USHORT>^ Data, int nWidth, int nHeight, int channel, String ^ fileName)
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

	void FunctionSet::SaveData(array<double>^ Data, int nWidth, int nHeight, int channel, String ^ fileName)
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

	void FunctionSet::SaveData(array<Byte>^ Data, int nWidth, int nHeight, int channel, String ^ fileName)
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

	bool FunctionSet::BGRtoY(unsigned char * BGRImage, int Width, int Height, unsigned char * YImage)
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
			B_Table[i] = 0.114 * i + 0.5;	//+0.5 for ¥|±Ë¤­¤J
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

	void FunctionSet::mosaic(array<Byte>^ Src, int width, int height, int channel, array<Byte>^ Dst)
	{
		array<Byte>^ YBuffer = gcnew array<Byte>(width*height);
		if (channel == 3)
		{
			pin_ptr<Byte> ptrSrc = &Src[0];
			pin_ptr<Byte> ptrYBuffer = &YBuffer[0];
			BGRtoY(ptrSrc, width, height, ptrYBuffer);
			//SaveData(YBuffer, width, height, 1, "TestY.raw");
		}

		array<USHORT>^ tmpMosaic = gcnew array<USHORT>(width*height);

		pin_ptr<UCHAR> ptrDst = &Dst[0];
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				tmpMosaic[y*width + x] = YBuffer[y*width + x];

				*ptrDst++ = tmpMosaic[y*width + x] >> 8;
				*ptrDst++ = tmpMosaic[y*width + x];
			}
		}

		SaveData(tmpMosaic, width, height, 1, "USHORT.raw");
	}

	void FunctionSet::demosaic(array<Byte>^ Src, int width, int height, int channel, array<Byte>^ Dst)
	{
		array<Byte>^ lowOrder = gcnew array<Byte>(width*height);
		for (int i = 0; i < width*height; i++)
		{
			Dst[i] = Src[i * 2 + 1];
		}
	}
	void FunctionSet::TransTo8bitASCII(String^ inputData, array<Byte>^ outputData)
	{
		outputData = gcnew array<Byte>(inputData->Length);
		int count = 0;
		for each(char a in inputData)
		{
			outputData[count] = a;
			count++;
		}
		//throw gcnew System::NotImplementedException();
	}
	void FunctionSet::ASCII8bitToLetter(array<Byte>^ outputData, String^ inputData)
	{
		//throw gcnew System::NotImplementedException();
	}
}