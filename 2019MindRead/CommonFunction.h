#pragma once
#include "stdafx.h"

#define RELEASE(a) (((a)!=0) ? (delete[] (a),(a) = 0):((a)=0))

#define DebguSBS true

#define NLOG_DLLTAG	"[2019MindRead]"

using namespace System;

namespace MindReadFunction
{
	public ref class CommonFunction
	{
	public:
		CommonFunction();
		~CommonFunction();

		bool NLogMsg(String^ Message);
		bool NLogMsg(String^ FuncTag, String^ Message);

		void DataLoad(String^ loadPath, array<Byte>^ loadData);

	private:
		NLog::Logger^ logger = NLog::LogManager::GetLogger("ProjectName");
	};
}