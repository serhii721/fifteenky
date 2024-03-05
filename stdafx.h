// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <stdio.h>
#include <string>
#include <ctime>
#include <vector>
#include <array>
#include <set>
using namespace std;

#include "resource.h"

const int TILE_COUNT = 16;
#include "State.h"
#include "AStar.h"

string convertToRoman(int);
bool isCompletedPuzzle(State*);

LRESULT CALLBACK WFunc(HWND, UINT, WPARAM, LPARAM);

// Buffer.
TCHAR str[256] = "";

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
