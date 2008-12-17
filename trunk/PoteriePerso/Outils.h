#pragma once
#include "afxwin.h"
#include <afxstr.h>
#include <iostream>
#include <CString>


inline char* CString2Char(CString chaine)
{
	char *sz= new char [chaine.GetLength()+1] ;
	WideCharToMultiByte( CP_ACP, 0, chaine, -1, sz, chaine.GetLength()+1, NULL, NULL );
	return sz;
}

inline CString Char2CString(char * chaine)
{
	return (LPCTSTR) (LPTSTR) chaine;
}