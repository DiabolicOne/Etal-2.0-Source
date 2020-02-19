//////////////////////////////////////////////////////////////////////
// Common.cpp
//////////////////////////////////////////////////////////////////////
#include "Common.h"
wchar_t* char_to_wchart(const char* str)
{
	wchar_t* buf = NULL;
	int len = MultiByteToWideChar(CP_ACP, 0, str, -1, buf, 0);
	buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, str, -1, buf, len);
	return buf;
}

char* wchart_to_char(const wchar_t* str)
{
	char* buf = NULL;
	int len = WideCharToMultiByte(CP_ACP, 0, str, -1, buf, 0, "?", NULL);
	buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, str, -1, buf, len, "?", NULL);
	return buf;
}

int char_to_int(char* str)
{
	char * pEnd;
	int i = strtol(str, &pEnd, 10);//10 is the base (decimal in this case)

	return i;
}

int char_to_int(char txt)// returns a string eg "1" to an integer
{
	int i = txt - '0';
	return i;
}

//const char* int_to_char(int i)
//{
//	char buf[100];
//	_itoa_s(i, buf, 10);//10 is the base (decimal in this case)
//
//	return buf;
//}