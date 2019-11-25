#pragma once
#include "stdafx.h"
#include "CommonFunction.h"

using namespace MindReadFunction;
using namespace System;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	CommonFunction^ CFunc = gcnew CommonFunction();

	Byte* bufferPtr;
	CFunc->LoadBMP(bufferPtr);

    return 0;
}
