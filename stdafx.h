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

#include "resource.h"

const int TILE_COUNT = 16;
#include "State.h"

int delayTime = 1000;
bool romanFont = false, nightMode = true;

std::string convertToRoman(int);
void fillTiles(HWND, HWND[], int[]);
void showTiles(HWND, HWND[], int[]);

bool isMovementPossible(int[], int);
int findEmptyTile(const int[]);
void movePiece(int[], int);

bool isMoveUpPossible(int);
bool isMoveLeftPossible(int);
bool isMoveRightPossible(int);
bool isMoveDownPossible(int);
void swapTop(int[], int);
void swapLeft(int[], int);
void swapRight(int[], int);
void swapBottom(int[], int);

State updateState(int[]);
int calculateHeuristic(const State&);
int calculateManhattanDistance(const State&);
void calculateNextStates(const State&, std::vector<State>&);
int calculateStateCost(const State&);
void checkForRepeats(std::vector<State>&, std::set<State>&, std::vector<std::array<int, TILE_COUNT>>&);
void solvePuzzle(HWND, HWND[], const State&, std::vector<State>&);
void executeMove(State&, const State&);

LRESULT CALLBACK WFunc(HWND, UINT, WPARAM, LPARAM);

// Buffer.
TCHAR str[256] = "";

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
