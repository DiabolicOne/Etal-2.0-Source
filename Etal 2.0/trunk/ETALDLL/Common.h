//////////////////////////////////////////////////////////////////////
// Common.h
//////////////////////////////////////////////////////////////////////
#pragma once
#include <Windows.h>

wchar_t* char_to_wchart(const char* str);
char* wchart_to_char(const wchar_t* str);
int char_to_int(char*);
int char_to_int(char);
const char* int_to_char(int);