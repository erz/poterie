#pragma once
#include "afxwin.h"
#include <afxstr.h>
#include <iostream>
#include <CString>


inline char* CString2Char(CString chaine)
{
	return (char*)(LPTSTR)(LPCTSTR)chaine;
}

inline CString Char2CString(char * chaine)
{
	return (LPCTSTR) (LPTSTR) chaine;
}