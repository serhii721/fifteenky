// stdafx.cpp : source file that includes just the standard includes
// Sceleton.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information
//

#include "stdafx.h"

extern HINSTANCE hInst;

std::string convertToRoman(int n)
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

void fillTiles(HWND hwnd, HWND hB[], int m[])
{
	int i, j, n;

	do
	{
		// Generating random position
		for (int i = 0; i < TILE_COUNT; i++)
		{
			m[i] = rand() % 16;
			for (int j = 0; j < i; j++)
			{
				if (m[i] == m[j])
				{
					i--;
					break;
				}
			}
		}

		// Counting sum of inversions (sum of tiles with number < current tile number)
		n = 0;
		for (i = 0; i < TILE_COUNT; i++)
		{
			if (m[i] == 0)
				continue;

			for (j = i + 1; j < TILE_COUNT; j++)
			{
				if (m[j] == 0)
					continue;
				if (m[i] > m[j])
					n++;
			}
		}

		// Add row number of empty cell
		n += (findEmptyTile(m) / 4) + 1;

	} while (n % 2 != 0);
}

void showTiles(HWND hwnd, HWND hB[], int m[])
{
	for (int i = 0; i < TILE_COUNT; i++)
	{
		ShowWindow(hB[i], SW_SHOW);
		if (m[i] != 0)
		{
			if (!romanFont)
				SetWindowText(hB[i], convertToRoman(m[i]).c_str());
			else
				SetWindowText(hB[i], std::to_string(m[i]).c_str());
		}
		else
			ShowWindow(hB[i], SW_HIDE);
	}
	UpdateWindow(hwnd);
}

bool isMovementPossible(int mas[], int numb)
{	
	if (numb >= 0 && numb <= 15)
	{
		// Top left corner
		if (numb == 0)
		{
			if (mas[numb + 1] == 0)
			{
				return true;
			}
			if (mas[numb + 4] == 0)
			{
				return true;
			}
		}
		// Top edge
		if (numb > 0 && numb < 3)
		{
			if (mas[numb + 1] == 0)
			{
				return true;
			}
			if (mas[numb + 4] == 0)
			{
				return true;
			}
			if (mas[numb - 1] == 0)
			{
				return true;
			}
		}
		// Top right corner
		if (numb == 3)
		{
			if (mas[numb + 4] == 0)
			{
				return true;
			}
			if (mas[numb - 1] == 0)
			{
				return true;
			}
		}
		// Left edge
		if (numb == 4 || numb == 8)
		{
			if (mas[numb + 1] == 0)
			{
				return true;
			}
			if (mas[numb + 4] == 0)
			{
				return true;
			}
			if (mas[numb - 4] == 0)
			{
				return true;
			}
		}
		// Right edge
		if (numb == 7 || numb == 11)
		{
			if (mas[numb + 4] == 0)
			{
				return true;
			}
			if (mas[numb - 1] == 0)
			{
				return true;
			}
			if (mas[numb - 4] == 0)
			{
				return true;
			}
		}
		// Bottom left corner
		if (numb == 12)
		{
			if (mas[numb + 1] == 0)
			{
				return true;
			}
			if (mas[numb - 4] == 0)
			{
				return true;
			}
		}
		// Bottom edge
		if (numb > 12 && numb < 15)
		{
			if (mas[numb + 1] == 0)
			{
				return true;
			}
			if (mas[numb - 1] == 0)
			{
				return true;
			}
			if (mas[numb - 4] == 0)
			{
				return true;
			}
		}
		// Bottom right corner
		if (numb == 15)
		{
			if (mas[numb - 1] == 0)
			{
				return true;
			}
			if (mas[numb - 4] == 0)
			{
				return true;
			}
		}
		// Middle
		if (numb == 5 || numb == 6 || numb == 9 || numb == 10)
		{
			if (mas[numb + 1] == 0)
			{
				return true;
			}
			if (mas[numb + 4] == 0)
			{
				return true;
			}
			if (mas[numb - 1] == 0)
			{
				return true;
			}
			if (mas[numb - 4] == 0)
			{
				return true;
			}
		}
	}
	return false;
}

int findEmptyTile(const int mas[])
{
	for (int i = 0; i < TILE_COUNT; i++)
		if (mas[i] == 0)
			return i;
	return -1;
}

void movePiece(int mas[], int numb)
{
	if (numb >= 0 && numb <= 15)
	{
		// Top left corner
		if (numb == 0)
		{
			if (mas[numb + 1] == 0)
			{
				swapRight(mas, numb);
				return;
			}
			if (mas[numb + 4] == 0)
			{
				swapBottom(mas, numb);
				return;
			}
		}
		// Top edge
		if (numb > 0 && numb < 3)
		{
			if (mas[numb + 1] == 0)
			{
				swapRight(mas, numb);
				return;
			}
			if (mas[numb + 4] == 0)
			{
				swapBottom(mas, numb);
				return;
			}
			if (mas[numb - 1] == 0)
			{
				swapLeft(mas, numb);
				return;
			}
		}
		// Top right corner
		if (numb == 3)
		{
			if (mas[numb + 4] == 0)
			{
				swapBottom(mas, numb);
				return;
			}
			if (mas[numb - 1] == 0)
			{
				swapLeft(mas, numb);
				return;
			}
		}
		// Left edge
		if (numb == 4 || numb == 8)
		{
			if (mas[numb + 1] == 0)
			{
				swapRight(mas, numb);
				return;
			}
			if (mas[numb + 4] == 0)
			{
				swapBottom(mas, numb);
				return;
			}
			if (mas[numb - 4] == 0)
			{
				swapTop(mas, numb);
				return;
			}
		}
		// Right edge
		if (numb == 7 || numb == 11)
		{
			if (mas[numb + 4] == 0)
			{
				swapBottom(mas, numb);
				return;
			}
			if (mas[numb - 1] == 0)
			{
				swapLeft(mas, numb);
				return;
			}
			if (mas[numb - 4] == 0)
			{
				swapTop(mas, numb);
				return;
			}
		}
		// Bottom left corner
		if (numb == 12)
		{
			if (mas[numb + 1] == 0)
			{
				swapRight(mas, numb);
				return;
			}
			if (mas[numb - 4] == 0)
			{
				swapTop(mas, numb);
				return;
			}
		}
		// Bottom edge
		if (numb > 12 && numb < 15)
		{
			if (mas[numb + 1] == 0)
			{
				swapRight(mas, numb);
				return;
			}
			if (mas[numb - 1] == 0)
			{
				swapLeft(mas, numb);
				return;
			}
			if (mas[numb - 4] == 0)
			{
				swapTop(mas, numb);
				return;
			}
		}
		// Bottom right corner
		if (numb == 15)
		{
			if (mas[numb - 1] == 0)
			{
				swapLeft(mas, numb);
				return;
			}
			if (mas[numb - 4] == 0)
			{
				swapTop(mas, numb);
				return;
			}
		}
		// Middle
		if (numb == 5 || numb == 6 || numb == 9 || numb == 10)
		{
			if (mas[numb + 1] == 0)
			{
				swapRight(mas, numb);
				return;
			}
			if (mas[numb + 4] == 0)
			{
				swapBottom(mas, numb);
				return;
			}
			if (mas[numb - 1] == 0)
			{
				swapLeft(mas, numb);
				return;
			}
			if (mas[numb - 4] == 0)
			{
				swapTop(mas, numb);
				return;
			}
		}
	}
}

bool isMoveUpPossible(int numb)
{
	return numb - 4 >= 0 ? true : false;
}

bool isMoveLeftPossible(int numb)
{
	if (numb != 0 && numb != 4 && numb != 8 && numb != 12)
		return true;
	return false;
}

bool isMoveRightPossible(int numb)
{
	if (numb != 3 && numb != 7 && numb != 11 && numb != 15)
		return true;
	return false;
}

bool isMoveDownPossible(int numb)
{
	return numb + 4 <= 15 ? true : false;
}

void swapTop(int mas[], int numb)
{
	int tmp = mas[numb];
	mas[numb] = mas[numb - 4];
	mas[numb - 4] = tmp;
}

void swapLeft(int mas[], int numb)
{
	int tmp = mas[numb];
	mas[numb] = mas[numb - 1];
	mas[numb - 1] = tmp;
}

void swapRight(int mas[], int numb)
{
	int tmp = mas[numb];
	mas[numb] = mas[numb + 1];
	mas[numb + 1] = tmp;
}

void swapBottom(int mas[], int numb)
{
	int tmp = mas[numb];
	mas[numb] = mas[numb + 4];
	mas[numb + 4] = tmp;
}

State updateState(int mas[])
{
	State currentState;
	for (int i = 0; i < TILE_COUNT; i++)
	{
		currentState.position[i] = i;
		currentState.title[i] = mas[i];
	}

	currentState.cost = 0;
	currentState.level = 0;
	return currentState;
}

int calculateHeuristic(const State& state)
{
	// This function count cost of current board based on number of tiles that are not on it's correct position
	int h = 0;
	for (int i = 0; i < TILE_COUNT; i++)
	{
		// If number and button position don't match - increase heuristic cost 
		if (state.position[i] + 1 != state.title[i])
			h++;
	}
	return h;
}

int calculateManhattanDistance(const State& current)
{
	// This function counts cost of current board based on distance of every tile from it's correct position
	int distance = 0;

	int currentRow, currentCol;
	int correctRow, correctCol;
	int rowDifference, colDifference;

	for (int i = 0; i < TILE_COUNT; i++)
	{
		if (current.title[i] == 0)
			continue;

		currentRow = i / 4;
		currentCol = i % 4;

		correctRow = (current.title[i] - 1) / 4;
		correctCol = (current.title[i] - 1) % 4;

		rowDifference = (int)fabs(currentRow - correctRow);
		colDifference = (int)fabs(currentCol - correctCol);

		distance += rowDifference + colDifference;
	}

	return distance;
}

void calculateNextStates(const State& currentState, std::vector<State>& nextStates)
{
	int id = findEmptyTile(currentState.title);

	// Moving empty tile in all possible directions
	if (isMoveUpPossible(id))
	{
		State nextState = currentState;
		nextState.previousState = new State(currentState);
		swapTop(nextState.title, id);
		nextState.level = currentState.level + 1;
		nextState.cost = calculateStateCost(nextState);
		nextStates.push_back(nextState);
	}
	if (isMoveLeftPossible(id))
	{
		State nextState = currentState;
		nextState.previousState = new State(currentState);
		swapLeft(nextState.title, id);
		nextState.level = currentState.level + 1;
		nextState.cost = calculateStateCost(nextState);
		nextStates.push_back(nextState);
	}
	if (isMoveRightPossible(id))
	{
		State nextState = currentState;
		nextState.previousState = new State(currentState);
		swapRight(nextState.title, id);
		nextState.level = currentState.level + 1;
		nextState.cost = calculateStateCost(nextState);
		nextStates.push_back(nextState);
	}
	if (isMoveDownPossible(id))
	{
		State nextState = currentState;
		nextState.previousState = new State(currentState);
		swapBottom(nextState.title, id);
		nextState.level = currentState.level + 1;
		nextState.cost = calculateStateCost(nextState);
		nextStates.push_back(nextState);
	}
}

int calculateStateCost(const State& state)
{
	// Formula for calculating cost of current position
	// Current level (depth) + Manhattand Distance + Heuristic cost
	int cost = (state.level + (calculateManhattanDistance(state) * 3) + (calculateHeuristic(state) * 5)) * 1000000;

	// If heuristic cost for current position is low - level excluded from formula to encourage algorithm find solve
	if (calculateHeuristic(state) < 5)
		cost = ((calculateManhattanDistance(state) * 3) + (calculateHeuristic(state) * 5)) * 1000000;

	// Reducing cost if pieces are on their corrent positions in order
	if (state.title[0] == 1)
	{
		cost /= 2;
		if (state.title[1] == 2)
		{
			cost /= 2;
			if (state.title[2] == 3 && state.title[3] == 4)
			{
				cost /= 10;
				if (state.title[4] == 5)
				{
					cost /= 2;
					if (state.title[5] == 6)
					{
						cost /= 2;
						if (state.title[6] == 7 && state.title[7] == 8)
							cost /= 100;
					}
				}
			}
		}
		if (state.title[4] == 5 && state.title[8] == 9 && state.title[12] == 13)
		{
			cost /= 10;
			if (
				state.title[1] == 2 &&
				state.title[2] == 3 &&
				state.title[3] == 4 &&
				state.title[5] == 6 &&
				state.title[6] == 7 &&
				state.title[7] == 8
				)
				cost /= 10;
		}
	}

	if (calculateHeuristic(state) < 7)
		cost /= 10;

	// Increasing cost if algorith took a wrong move
	if (
		state.title[0] != 1 &&
		state.title[1] != 2 &&
		state.title[2] != 3 &&
		state.title[3] != 4 &&
		state.previousState->title[0] == 1 &&
		state.previousState->title[1] == 2 &&
		state.previousState->title[2] == 3 &&
		state.previousState->title[3] == 4
		) {
		cost *= 100;
		if (
			state.title[4] != 5 &&
			state.title[5] != 6 &&
			state.previousState->title[4] == 5 &&
			state.previousState->title[5] == 6
			) {
			cost *= 2;
			if (
				state.title[6] != 7 &&
				state.title[7] != 8 &&
				state.previousState->title[6] == 7 &&
				state.previousState->title[7] == 8
				) {
				cost *= 100;
				if (
					state.title[8] != 9 &&
					state.title[12] != 13 &&
					state.previousState->title[8] == 9 &&
					state.previousState->title[12] == 13
					) {
					cost *= 100;
					if (
						state.title[9] != 10 &&
						state.title[13] != 14 &&
						state.previousState->title[9] == 10 &&
						state.previousState->title[13] == 14
						)
						cost *= 100;
				}
			}
		}
	}
	return cost;
}

void checkForRepeats(std::vector<State>& nextStates, std::set<State>& openSet, std::vector<std::array<int, TILE_COUNT>>& visited)
{
	int nextStatesSz = nextStates.size(), visitedSz = visited.size(),
		i, j, k;
	bool toBeAdded;
	bool* isSame = new bool[visitedSz];

	for (i = 0; i < nextStatesSz; i++)
	{
		for (j = 0; j < visitedSz; j++)
			isSame[j] = true;

		toBeAdded = false;
		for (j = 0; j < visitedSz; j++)
			for (k = 0; k < TILE_COUNT; k++)
				if (nextStates[i].title[k] != visited[j][k])
				{
					isSame[j] = false;
					break;
				}

		for (j = 0; j < visitedSz; j++)
			if (isSame[j])
			{
				toBeAdded = false;
				break;
			}
			else
				toBeAdded = true;

		if (toBeAdded)
			openSet.insert(nextStates[i]);
	}
	if (isSame != nullptr)
		delete[] isSame;
}

void solvePuzzle(HWND hwnd, HWND hB[], const State& startState, std::vector<State>& solutionPath)
{
	int i;
	// Container holds every not visited state in priority of increasing cost 
	std::set<State> openSet;

	// Vector holds every visited position
	std::vector<std::array<int, TILE_COUNT>> visited;
	std::array<int, TILE_COUNT> temp;

	// Vector to hold every possible next position from current position
	std::vector<State> nextStates;

	openSet.insert(startState);

	// Variables for additional info for debug purposes
	int minCost = 1000, maxCost = 0;

	while (!openSet.empty())
	{
		State current = *openSet.begin();
		openSet.erase(openSet.begin());

		for (i = 0; i < TILE_COUNT; i++)
			temp[i] = current.title[i];
		visited.push_back(temp);

		// Exit condition - if cost is 0 the puzzle is solved
		if (calculateManhattanDistance(current) == 0)
		{
			// Vector used to save sequence of moves that lead to puzzle solve
			State* currentState = &current;
			while (currentState)
			{
				solutionPath.push_back(*currentState);
				currentState = currentState->previousState;
			}
			return;
		}

		sprintf_s(str, "Calculating. Currently evaluated %d positions", visited.size());
		SetWindowText(hwnd, str);

		// Calculate all possible next moves from current position
		nextStates.clear();
		calculateNextStates(current, nextStates);

		// If next positions weren't visited before they are added to openSet
		checkForRepeats(nextStates, openSet, visited);
	}
}

void executeMove(State& startState, const State& endState)
{
	int id = findEmptyTile(endState.title);

	if (startState.title[id + 1] == 0 && id < 15)
		swapRight(startState.title, id);
	else if (startState.title[id + 4] == 0 && id < 12)
		swapBottom(startState.title, id);
	else if (startState.title[id - 1] == 0 && id > 0)
		swapLeft(startState.title, id);
	else if (startState.title[id - 4] == 0 && id > 3)
		swapTop(startState.title, id);
}

LRESULT CALLBACK WFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hBut[16];
	static int mas[16];
	static State startState;
	static std::vector<State> solutionPath;
	
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
		FF_ROMAN,			// Font family
		"MyFont"				// Name
	);

	int i, numb;
	static int sx, sy;

	switch (message)
	{
	case WM_CREATE:
		srand((unsigned)time(0));

		// Creating tiles
		for (i = 0; i < TILE_COUNT; i++)
			hBut[i] = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd, 0, hInst, 0);

		// Filling random numbers
		fillTiles(hwnd, hBut, mas);

		// Initialize struct that holds information about current position
		startState = updateState(mas);

		// Assigning generated numbers to tiles
		showTiles(hwnd, hBut, startState.title);
		break;

	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;

	case WM_COMMAND:
		// Rearange buttons randomly
		if (wParam == ID_SETTINGS_RESTART)
		{
			fillTiles(hwnd, hBut, mas);
			startState = updateState(mas);
			showTiles(hwnd, hBut, startState.title);
		}

		// Easter egg
		if (wParam == ID_CHEATS_FREECOOKIES)
			SetWindowText(hwnd, "No free cookies for cheaters");

		// Autosolve puzzle
		if (wParam == ID_CHEATS_AUTOASSEMBLE)
		{
			solvePuzzle(hwnd, hBut, startState, solutionPath);
			for (i = solutionPath.size() - 1; i >= 0; i--)
			{
				executeMove(startState, solutionPath[i]);
				showTiles(hwnd, hBut, startState.title);
				sprintf_s(str, "Puzzle solved! Executing move %d / %d", solutionPath[i].level + 1, solutionPath[0].level);
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
		numb = i;

		// Saving the number of the selected button into the buffer
		SendMessage(hBut[numb], WM_GETTEXT, 3, (LPARAM)(TCHAR*)str);

		// Moving pieces
		// numb - button position number
		// mas[numb] - button title number
		if (isMovementPossible(startState.title, numb))
			movePiece(startState.title, numb);
		// Update window after moving a piece
		showTiles(hwnd, hBut, startState.title);
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
		// Releasing memory
		for (i = solutionPath.size() - 1; i >= 0; i--)
			if (solutionPath[i].previousState != nullptr)
				delete solutionPath[i].previousState;
		
		DeleteObject(customFont);

		PostQuitMessage(0); // Корректная обработка окончания сообщения
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam); // Возврат неотработанного сообщения
	}
	return 0L;
}
