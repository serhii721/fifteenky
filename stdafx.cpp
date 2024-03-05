// stdafx.cpp : source file that includes just the standard includes
// Sceleton.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information
//

#include "stdafx.h"

extern HINSTANCE hInst;

string convertToRoman(int n)
{
	switch (n)
	{
	case 1:default: return "I";
	case 2: return "II";
	case 3: return "III";
	case 4: return "IV";
	case 5: return "V";
	case 6: return "VI";
	case 7: return "VII";
	case 8: return "VIII";
	case 9: return "IX";
	case 10: return "X";
	case 11: return "XI";
	case 12: return "XII";
	case 13: return "XIII";
	case 14: return "XIV";
	case 15: return "XV";
	}
}

bool isCompletedPuzzle(State* state)
{
	if (state->GetTitle(0) != 1)
		return false;
	if (state->GetTitle(1) != 2)
		return false;
	if (state->GetTitle(2) != 3)
		return false;
	if (state->GetTitle(3) != 4)
		return false;
	if (state->GetTitle(4) != 5)
		return false;
	if (state->GetTitle(5) != 6)
		return false;
	if (state->GetTitle(7) != 8)
		return false;
	if (state->GetTitle(7) != 8)
		return false;
	if (state->GetTitle(8) != 9)
		return false;
	if (state->GetTitle(9) != 10)
		return false;
	if (state->GetTitle(10) != 11)
		return false;
	if (state->GetTitle(11) != 12)
		return false;
	if (state->GetTitle(12) != 13)
		return false;
	if (state->GetTitle(13) != 14)
		return false;
	if (state->GetTitle(14) != 15)
		return false;
	if (state->GetTitle(15) != 0)
		return false;
	return true;
}

LRESULT CALLBACK WFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hBut[16];
	static State* currentState = new State();
	static vector<State> solutionPath;
	static AStar astar;
	static bool romanFont, nightMode;
	static int delayTime;
	
	static COLORREF day = RGB(240, 240, 240), night = RGB(20, 20, 20);

	static HFONT customFont = CreateFont(
		40,						// Size
		15,						// Width
		0,						// Lean angle
		0,						// Rotation angle
		FW_NORMAL,				// Thickness
		FALSE,					// Cursive
		FALSE,					// Underline
		FALSE,					// Crossed
		DEFAULT_CHARSET,		// Symbol set
		OUT_DEFAULT_PRECIS,		// Output preccision
		CLIP_DEFAULT_PRECIS,	// Clip precission
		DEFAULT_QUALITY,		// Output quality
		DEFAULT_PITCH |			// Pitch
		FF_ROMAN,				// Font family
		"MyFont"				// Name
	);
	static int sx, sy;
	int i;

	switch (message)
	{
	case WM_CREATE:
		srand((unsigned)time(0));

		// Default parameters
		romanFont = true;
		nightMode = true;
		delayTime = 500;

		// Creating tiles
		for (i = 0; i < TILE_COUNT; i++)
			hBut[i] = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd, 0, hInst, 0);

		// Filling random numbers
		currentState->FillTilesRandomly();
		currentState->Show(hwnd, hBut, romanFont);
		break;

	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;

	case WM_COMMAND:
		// Rearange buttons randomly
		if (wParam == ID_SETTINGS_RESTART)
		{
			currentState->FillTilesRandomly();
			currentState->Show(hwnd, hBut, romanFont);
		}

		// Easter egg
		if (wParam == ID_CHEATS_FREECOOKIES)
			SetWindowText(hwnd, "No free cookies for cheaters");

		// Autosolve puzzle
		if (wParam == ID_CHEATS_AUTOASSEMBLE)
		{
			astar.SolvePuzzle(hwnd, hBut, *currentState, solutionPath);
			for (i = solutionPath.size() - 1; i >= 0; i--)
			{
				astar.ExecuteMove(*currentState, solutionPath[i]);
				currentState->Show(hwnd, hBut, romanFont);
				sprintf_s(str, "Puzzle solved! Executing move %d / %d", solutionPath[i].GetLevel() - 1, solutionPath[0].GetLevel() - 1);
				SetWindowText(hwnd, str);
				Sleep(delayTime);
			}
			solutionPath.clear();
			SetWindowText(hwnd, "Fifteenky");
		}
		
		if (wParam == ID_SETTINGS_TOGGLEROMANFONT)
		{
			if (!romanFont)
				romanFont = true;
			else
				romanFont = false;
		}
		
		if (wParam == ID_SETTINGS_NIGHTMODE)
		{
			if (!nightMode)
				nightMode = true;
			else
				nightMode = false;
		}
		
		if (wParam == ID_SLEEPTIME_1000)
			delayTime = 1000;
		if (wParam == ID_SLEEPTIME_500)
			delayTime = 500;
		if (wParam == ID_SLEEPTIME_100)
			delayTime = 100;
		if (wParam == ID_SLEEPTIME_50)
			delayTime = 50;

		// Check which button was pressed
		for (i = 0; i < TILE_COUNT; i++)
			if ((HWND)lParam == hBut[i])
				break;

		// Saving the number of the selected button into the buffer
		SendMessage(hBut[i], WM_GETTEXT, 3, (LPARAM)(TCHAR*)str);

		// Moving pieces
		if (currentState->IsMovementPossible(i))
			currentState->MovePiece(i);
		// Update window after moving a piece
		currentState->Show(hwnd, hBut, romanFont);

		if (isCompletedPuzzle(currentState))
		{
			int msgboxID = MessageBoxA(
				hwnd,
				"Congratulations! You've completed the puzzle!\nDo you want to restart?",
				"Victory",
				MB_YESNOCANCEL  | MB_ICONQUESTION
			);

			if (msgboxID == IDYES)
			{
				currentState->FillTilesRandomly();
				currentState->Show(hwnd, hBut, romanFont);
			}
			if (msgboxID == IDCANCEL)
				DestroyWindow(hwnd);
		}
		break;

	case WM_PAINT:
		for (i = 0; i < TILE_COUNT; i++)
		{
			MoveWindow(hBut[i], (i % 4) * sx / 4, (i / 4) * sy / 4, sx / 4, sy / 4, TRUE);
			UpdateWindow(hBut[i]);
		}
		break;

	case WM_DRAWITEM:
	{
		LPDRAWITEMSTRUCT Item = (LPDRAWITEMSTRUCT)lParam;

		// Set text font and background
		SetBkMode(Item->hDC, TRANSPARENT);
		SelectObject(Item->hDC, customFont);

		// Assing background and text color
		if (!nightMode)
		{
			SetTextColor(Item->hDC, night);
			FillRect(Item->hDC, &Item->rcItem, CreateSolidBrush(day));
		}
		else
		{
			SetTextColor(Item->hDC, day);
			FillRect(Item->hDC, &Item->rcItem, CreateSolidBrush(night));
		}

		DrawEdge(Item->hDC, &Item->rcItem, EDGE_RAISED, BF_RECT);

		// Draw text
		int len = GetWindowTextLength(Item->hwndItem);
		char* buf = new char[len + 1];
		GetWindowTextA(Item->hwndItem, buf, len + 1);
		DrawTextA(Item->hDC, buf, len, &Item->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

		delete[] buf;
		return true;
	}
	break;

	case WM_DESTROY:
		DeleteObject(customFont);

		PostQuitMessage(0); // Корректная обработка окончания сообщения
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam); // Возврат неотработанного сообщения
	}
	return 0L;
}
