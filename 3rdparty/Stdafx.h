#pragma once
#pragma  warning(disable:4793)
// TODO: 在此參考您的程式所需的其他標頭
#include <windows.h> 
#include <WinBase.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <msclr\marshal.h>
#include <time.h>
#include <math.h>
#include <wchar.h>
#include <map>
#include <vector>

#pragma comment(lib, "user32.lib")

#define ImageFolderPath (System::IO::Path::GetDirectoryName(Windows::Forms::Application::ExecutablePath) + "\\ImageData\\")

inline bool checkFileCount()
{
}