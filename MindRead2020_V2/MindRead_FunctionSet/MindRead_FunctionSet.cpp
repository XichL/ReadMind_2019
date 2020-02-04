// MindRead_FunctionSet.cpp : 定義 DLL 應用程式的匯出函式。
//

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

	void FunctionSet::DataLoad_TXT(String ^ loadPath, array<Byte>^% loadData)
	{
		DateTime dtSFRStartTime = DateTime::Now;

		IO::FileStream^ fs = gcnew IO::FileStream(loadPath, IO::FileMode::Open);

		NLogMsg("TXT UCHAR Load");
		loadData = gcnew array <Byte>(fs->Length);
		fs->Read(loadData, 0, fs->Length);
	}

	void FunctionSet::DataLoad_AutoSize(String ^ loadPath, array<Byte>^% loadData)
	{

		System::IO::StreamReader^ readFile = gcnew System::IO::StreamReader(loadPath);
		int ALength = readFile->BaseStream->Length;
		loadData = gcnew array<Byte>(ALength);
		readFile->Close();

		IO::FileStream^ fs = gcnew IO::FileStream(loadPath, IO::FileMode::Open);
		fs->Read(loadData, 0, ALength);
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

	void FunctionSet::SaveBmp(Drawing::Bitmap ^ bmp, bool cover, String ^ fileName)
	{
		String^ FilePath = ImageFolderPath;
		IO::Directory::CreateDirectory(FilePath);

		FilePath += fileName + ".bmp";
		if (!cover)
			FilePath = CheckFileExist(0, FilePath);

		bmp->Save(FilePath, Drawing::Imaging::ImageFormat::Bmp);
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

	void FunctionSet::SaveData_Append(String ^ Data, String ^ fileName)
	{
		IO::FileStream^ fs;
		String^ FilePath = ImageFolderPath;
		IO::Directory::CreateDirectory(FilePath);
		FilePath += fileName;

		String^ FILE_NAME = FilePath;
		String^ str = Environment::NewLine + "解=" + Data;
		try
		{
			if (!File::Exists(FILE_NAME))
			{
				fs = gcnew FileStream(FILE_NAME, FileMode::CreateNew);
			}
			else
			{
				fs = gcnew FileStream(FILE_NAME, FileMode::Append);
			}
			fs->Write(asciiEncoding->GetBytes(str), 0, asciiEncoding->GetByteCount(str));
		}
		catch (System::Exception^ e)
		{
			logger->Debug(e);
		}
	}

	void FunctionSet::SaveStringData_Encoding(String ^ strMessage, String ^ fileName)
	{
		IO::FileStream^ fs;
		String^ FilePath = ImageFolderPath;
		IO::Directory::CreateDirectory(FilePath);
		FilePath += fileName;

		String^ FILE_NAME = FilePath;
		try
		{
			fs = gcnew FileStream(FILE_NAME, FileMode::Create);
			fs->Close();

			IO::StreamWriter^ TW = gcnew IO::StreamWriter(FILE_NAME, false, System::Text::Encoding::Default);
			TW->Write(strMessage);
			TW->Close();
		}
		catch (System::Exception^ e)
		{
			logger->Debug(e);
		}


		//try
		//{
		//	fs = gcnew IO::FileStream(CheckFileExist(0, FilePath), IO::FileMode::CreateNew);

		//	IO::BinaryWriter^ TW = gcnew IO::BinaryWriter(fs);
		//	for (int i = 0; i < nWidth*nHeight; i++)
		//	{
		//		TW->Write(Data[i]);
		//	}
		//	fs->Close();
		//	TW->Close();
		//}
		//catch (System::Exception^ e)
		//{
		//	logger->Debug(e);
		//}
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

	void FunctionSet::Raw2Bmp(array<Byte>^ Src, Drawing::Bitmap ^ Bmp)
	{
		// Lock the bitmap's bits.  
		Drawing::Rectangle rect = Drawing::Rectangle(0, 0, Bmp->Width, Bmp->Height);
		Drawing::Imaging::BitmapData^ bmpData = Bmp->LockBits(rect, Drawing::Imaging::ImageLockMode::ReadWrite, Drawing::Imaging::PixelFormat::Format8bppIndexed);

		// Get the address of the first line.
		pin_ptr<byte> ptr = &Src[0];
		UCHAR *Source = ptr;
		UCHAR *Target = (UCHAR*)(void*)bmpData->Scan0;

		// Copy the value.  
		int offset = bmpData->Stride - Bmp->Width;
		if (offset == 0)
		{
			memcpy(Target, Source, Bmp->Width*Bmp->Height);
		}
		else
		{
			for (int y = 0; y < Bmp->Height; y++)
			{
				memcpy(Target, Source, Bmp->Width);
				Target += Bmp->Width + offset;
				Source += Bmp->Width;
			}
		}

		// Unlock the bits.
		Bmp->UnlockBits(bmpData);

		Drawing::Imaging::ColorPalette^ pal = Bmp->Palette;
		for (int i = 0; i < 256; i++)
		{
			pal->Entries[i] = Drawing::Color::FromArgb(i, i, i);
		}
		Bmp->Palette = pal;
	}

	void FunctionSet::HLConverter(array<Byte>^ Src, int byteNum, array<Byte>^% Dst)
	{
		pin_ptr<Byte> ptrSrc = &Src[0];
		pin_ptr<Byte> ptrDst = &Dst[0];

		if (byteNum == 2)
		{
			for (int i = 0; i < Src->Length / 2; i++)
			{
				*ptrDst++ = ptrSrc[i * 2 + 1];
				*ptrDst++ = ptrSrc[i * 2];
			}
		}
		else //byteNum == 1
		{

		}
	}

	void FunctionSet::mosaic(array<Byte>^ Src, int width, int height, int channel, array<Byte>^% Dst)
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

		//SaveData(tmpMosaic, width, height, 1, "USHORT.raw");
	}

	void FunctionSet::demosaic(array<Byte>^ Src, int width, int height, int channel, array<Byte>^% Dst)
	{
		array<Byte>^ lowOrder = gcnew array<Byte>(width*height);
		for (int i = 0; i < width*height; i++)
		{
			Dst[i] = Src[i * 2 + 1];
		}
	}

	void FunctionSet::TransTo8bitASCII(String ^ inputData, String^% outputData)
	{
		for each(UCHAR c in inputData)
		{
			String^ tmp = Convert::ToString(c, 2);

			int gapSize = 8 - tmp->Length;
			for (int i = 0; i < gapSize; i++)
			{
				outputData += "0";
			}
			outputData += tmp;
		}

	}

	void FunctionSet::ASCII8bitToLetter(String^ inputData, String^% outputData)
	{
		array<int>^ str8bit = gcnew array<int>(8);
		pin_ptr<int> ptrInt = &str8bit[0];

		int bitCount = 0;
		for each(UCHAR c in inputData)
		{
			if (c != '0'&&c != '1')
			{
				continue;
			}
			else
			{
				*ptrInt++ = (c == '0' ? 0 : 1);
				bitCount++;
			}

			if (bitCount == 8)
			{
				int sum = 0;
				sum = ((str8bit[0] * 8) +
					(str8bit[1] * 4) +
					(str8bit[2] * 2) +
					(str8bit[3] * 1)) * 16;

				sum += (str8bit[4]) * 8 +
					(str8bit[5] * 4) +
					(str8bit[6] * 2) +
					(str8bit[7] * 1);

				std::string strTmp;
				strTmp.push_back((char)sum);
				String^ ascii = gcnew String(strTmp.c_str());

				outputData += ascii;
				ptrInt = &str8bit[0];
				bitCount = 0;
			}
		}
	}

	void FunctionSet::String2Byte(String^ inputData, array<Byte>^% outputData)
	{
		outputData = gcnew array<Byte>(inputData->Length * 8);
		pin_ptr<Byte> ptr = &outputData[0];
		for each(char c in inputData)
		{
			String^ tmp = Convert::ToString(c, 2);
			int gapSize = 8 - tmp->Length;
			for (int i = 0; i < 8; i++)
			{
				if (gapSize - i > 0)
				{
					*ptr++ = '0';
				}
				else
				{
					*ptr++ = tmp[i - gapSize];
				}
			}

			//String^ tmpString = Convert::ToString(a, 16);
			//std::string Tstring = String2string(tmpString);

			//Byte ss = Convert::ToByte(tmpString);

			//Byte ss = Convert::ToByte(a);
			//UCHAR ss = Convert::ToByte(Convert::ToString(a,8), 8);

			//String^ tt = Convert::ToString(a, 2);
			//UCHAR ss = (Convert::ToByte(Convert::ToString(a, 8), 8) >> 4)|(Convert::ToByte(Convert::ToString(a, 8), 8) << 4);
			//outputData[count] = ss;


			//count++;
		}
		//throw gcnew System::NotImplementedException();
	}
	void FunctionSet::GetSourceFile(String ^ FileName, FILETYPE^ type, String ^ saveName)
	{
		if (type->Equals(FILETYPE::FILETYPE_TXT))
		{
			String^ message = (String^)this->mng->GetObject(FileName);
			SaveStringData_Encoding(message, saveName);
		}
		else if (type->Equals(FILETYPE::FILETYPE_RAW))
		{
			array<byte>^ rawByte = (array<byte>^)this->mng->GetObject(FileName);
			SaveData(rawByte, rawByte->Length, 1, 1, saveName);
		}
		else if (type->Equals(FILETYPE::FILETYPE_BMP))
		{
			Bitmap^ img = (Bitmap^)this->mng->GetObject(FileName);
			SaveBmp(img, 1, saveName);
		}
		(array<byte>^)this->mng->GetObject("HLConvert");
	}

}

