#include "stdafx.h"
#include "State.h"

State::State() : previousState(nullptr), level(1)
{ 
	FillTilesRandomly();
	CalculateStateCost();
}

State::State(State* ppreviousState, int ttitle[], int llevel, int ccost) :
	previousState(ppreviousState),
	level(llevel),
	cost(ccost)
{
	for (int i = 0; i < TILE_COUNT; i++)
	{
		title[i] = ttitle[i];
	}
}

State::State(const State& other) :
	level(other.level),
	cost(other.cost)
{
	previousState = other.previousState ? new State(*other.previousState) : nullptr;
	for (int i = 0; i < TILE_COUNT; i++)
	{
		title[i] = other.title[i];
	}
}

State::~State()
{
	if (previousState)
		delete previousState;
}

State State::operator=(const State& other)
{
	if (this == &other)
		return *this;

	if (previousState)
		delete previousState;
	previousState = other.previousState ? new State(*other.previousState) : nullptr;

	for (int i = 0; i < TILE_COUNT; i++)
	{
		title[i] = other.title[i];
	}
	level = other.level;
	cost = other.cost;

	return *this;
}

bool State::operator<(const State & other) const
{
	return cost < other.cost;
}

void State::SetPreviousState(State* other)
{
	if (previousState)
		delete previousState;
	previousState = other ? new State(*other) : nullptr;
}

void State::SetTitle(int index, int newValue)
{
	title[index] = newValue;
}

void State::SetLevel(int newLevel)
{
	level = newLevel;
}

void State::SetCost(int newCost)
{
	cost = newCost;
}

State* State::GetPreviousState() const
{
	return previousState;
}

int State::GetPosition(int index) const
{
	return POSITION[index];
}

int State::GetTitle(int index) const
{
	return title[index];
}

int State::GetLevel() const
{
	return level;
}

int State::GetCost() const
{
	return cost;
}

bool State::IsMovementPossible(int n) const
{
	if (n >= 0 && n <= 15)
	{
		// Top left corner
		if (n == 0)
		{
			if (title[n + 1] == 0)
			{
				return true;
			}
			if (title[n + 4] == 0)
			{
				return true;
			}
		}
		// Top edge
		if (n > 0 && n < 3)
		{
			if (title[n + 1] == 0)
			{
				return true;
			}
			if (title[n + 4] == 0)
			{
				return true;
			}
			if (title[n - 1] == 0)
			{
				return true;
			}
		}
		// Top right corner
		if (n == 3)
		{
			if (title[n + 4] == 0)
			{
				return true;
			}
			if (title[n - 1] == 0)
			{
				return true;
			}
		}
		// Left edge
		if (n == 4 || n == 8)
		{
			if (title[n + 1] == 0)
			{
				return true;
			}
			if (title[n + 4] == 0)
			{
				return true;
			}
			if (title[n - 4] == 0)
			{
				return true;
			}
		}
		// Right edge
		if (n == 7 || n == 11)
		{
			if (title[n + 4] == 0)
			{
				return true;
			}
			if (title[n - 1] == 0)
			{
				return true;
			}
			if (title[n - 4] == 0)
			{
				return true;
			}
		}
		// Bottom left corner
		if (n == 12)
		{
			if (title[n + 1] == 0)
			{
				return true;
			}
			if (title[n - 4] == 0)
			{
				return true;
			}
		}
		// Bottom edge
		if (n > 12 && n < 15)
		{
			if (title[n + 1] == 0)
			{
				return true;
			}
			if (title[n - 1] == 0)
			{
				return true;
			}
			if (title[n - 4] == 0)
			{
				return true;
			}
		}
		// Bottom right corner
		if (n == 15)
		{
			if (title[n - 1] == 0)
			{
				return true;
			}
			if (title[n - 4] == 0)
			{
				return true;
			}
		}
		// Middle
		if (n == 5 || n == 6 || n == 9 || n == 10)
		{
			if (title[n + 1] == 0)
			{
				return true;
			}
			if (title[n + 4] == 0)
			{
				return true;
			}
			if (title[n - 1] == 0)
			{
				return true;
			}
			if (title[n - 4] == 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool State::IsMoveUpPossible(int n) const
{
	return n - 4 >= 0 ? true : false;
}

bool State::IsMoveLeftPossible(int n) const
{
	if (n != 0 && n != 4 && n != 8 && n != 12)
		return true;
	return false;
}

bool State::IsMoveRightPossible(int n) const
{
	if (n != 3 && n != 7 && n != 11 && n != 15)
		return true;
	return false;
}

bool State::IsMoveDownPossible(int n) const
{
	return n + 4 <= 15 ? true : false;
}

void State::MovePiece(int n)
{
	if (n >= 0 && n <= 15)
	{
		// Top left corner
		if (n == 0)
		{
			if (title[n + 1] == 0)
			{
				SwapRight(n);
				return;
			}
			if (title[n + 4] == 0)
			{
				SwapBottom(n);
				return;
			}
		}
		// Top edge
		if (n > 0 && n < 3)
		{
			if (title[n + 1] == 0)
			{
				SwapRight(n);
				return;
			}
			if (title[n + 4] == 0)
			{
				SwapBottom(n);
				return;
			}
			if (title[n - 1] == 0)
			{
				SwapLeft(n);
				return;
			}
		}
		// Top right corner
		if (n == 3)
		{
			if (title[n + 4] == 0)
			{
				SwapBottom(n);
				return;
			}
			if (title[n - 1] == 0)
			{
				SwapLeft(n);
				return;
			}
		}
		// Left edge
		if (n == 4 || n == 8)
		{
			if (title[n + 1] == 0)
			{
				SwapRight(n);
				return;
			}
			if (title[n + 4] == 0)
			{
				SwapBottom(n);
				return;
			}
			if (title[n - 4] == 0)
			{
				SwapTop(n);
				return;
			}
		}
		// Right edge
		if (n == 7 || n == 11)
		{
			if (title[n + 4] == 0)
			{
				SwapBottom(n);
				return;
			}
			if (title[n - 1] == 0)
			{
				SwapLeft(n);
				return;
			}
			if (title[n - 4] == 0)
			{
				SwapTop(n);
				return;
			}
		}
		// Bottom left corner
		if (n == 12)
		{
			if (title[n + 1] == 0)
			{
				SwapRight(n);
				return;
			}
			if (title[n - 4] == 0)
			{
				SwapTop(n);
				return;
			}
		}
		// Bottom edge
		if (n > 12 && n < 15)
		{
			if (title[n + 1] == 0)
			{
				SwapRight(n);
				return;
			}
			if (title[n - 1] == 0)
			{
				SwapLeft(n);
				return;
			}
			if (title[n - 4] == 0)
			{
				SwapTop(n);
				return;
			}
		}
		// Bottom right corner
		if (n == 15)
		{
			if (title[n - 1] == 0)
			{
				SwapLeft(n);
				return;
			}
			if (title[n - 4] == 0)
			{
				SwapTop(n);
				return;
			}
		}
		// Middle
		if (n == 5 || n == 6 || n == 9 || n == 10)
		{
			if (title[n + 1] == 0)
			{
				SwapRight(n);
				return;
			}
			if (title[n + 4] == 0)
			{
				SwapBottom(n);
				return;
			}
			if (title[n - 1] == 0)
			{
				SwapLeft(n);
				return;
			}
			if (title[n - 4] == 0)
			{
				SwapTop(n);
				return;
			}
		}
	}
}

void State::SwapTop(int n)
{
	int tmp = title[n];
	title[n] = title[n - 4];
	title[n - 4] = tmp;
}

void State::SwapLeft(int n)
{
	int tmp = title[n];
	title[n] = title[n - 1];
	title[n - 1] = tmp;
}

void State::SwapRight(int n)
{
	int tmp = title[n];
	title[n] = title[n + 1];
	title[n + 1] = tmp;
}

void State::SwapBottom(int n)
{
	int tmp = title[n];
	title[n] = title[n + 4];
	title[n + 4] = tmp;
}

void State::FillTilesRandomly()
{
	int i, j, n;

	do
	{
		// Generating random position
		for (int i = 0; i < TILE_COUNT; i++)
		{
			title[i] = rand() % 16;
			for (int j = 0; j < i; j++)
			{
				if (title[i] == title[j])
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
			if (title[i] == 0)
				continue;

			for (j = i + 1; j < TILE_COUNT; j++)
			{
				if (title[j] == 0)
					continue;
				if (title[i] > title[j])
					n++;
			}
		}

		// Add row number of empty cell
		n += (FindEmptyTile() / 4) + 1;

	} while (n % 2 != 0);
}

void State::FillTiles(int mas[])
{
	for (int i = 0; i < TILE_COUNT; i++)
		title[i] = mas[i];
}

void State::Show(HWND hwnd, HWND hB[], bool romanFont)
{
	for (int i = 0; i < TILE_COUNT; i++)
	{
		ShowWindow(hB[i], SW_SHOW);
		if (title[i] != 0)
		{
			if (romanFont)
				SetWindowText(hB[i], convertToRoman(title[i]).c_str());
			else
				SetWindowText(hB[i], to_string(title[i]).c_str());
		}
		else
			ShowWindow(hB[i], SW_HIDE);
	}
	UpdateWindow(hwnd);
}

int State::FindEmptyTile() const
{
	for (int i = 0; i < TILE_COUNT; i++)
		if (title[i] == 0)
			return i;
	return -1;
}

int State::CalculateHeuristic() const
{
	// This function count cost of current board based on number of tiles that are not on it's correct position
	// If number and button position don't match - increase heuristic cost by 1
	int h = 0;
	for (int i = 0; i < TILE_COUNT; i++)
		if (POSITION[i] + 1 != title[i])
			h++;
	return h;
}

int State::CalculateManhattanDistance() const
{
	// This function counts cost of current board based on distance of every tile from it's correct position
	int distance = 0;

	int currentRow, currentCol,
		correctRow, correctCol,
		rowDifference, colDifference;

	for (int i = 0; i < TILE_COUNT; i++)
	{
		if (title[i] == 0)
			continue;

		currentRow = i / 4;
		currentCol = i % 4;

		correctRow = (title[i] - 1) / 4;
		correctCol = (title[i] - 1) % 4;

		rowDifference = (int)fabs(currentRow - correctRow);
		colDifference = (int)fabs(currentCol - correctCol);

		distance += rowDifference + colDifference;
	}
	return distance;
}

void State::CalculateStateCost()
{
	// Formula for calculating cost of current position
	// If heuristic cost for current position is low - level excluded from formula to encourage algorithm find solve
	if (CalculateHeuristic() < 5)
		cost = ((CalculateManhattanDistance() * 3) + (CalculateHeuristic() * 5)) * 1000000;
	// Current level (depth) + Manhattand Distance + Heuristic cost
	cost = (level + (CalculateManhattanDistance() * 3) + (CalculateHeuristic() * 5)) * 1000000;

	// Reducing cost if pieces are on their corrent positions in order
	if (title[0] == 1)
	{
		cost /= 2;
		if (title[1] == 2)
		{
			cost /= 2;
			if (title[2] == 3 && title[3] == 4)
			{
				cost /= 10;
				if (title[4] == 5)
				{
					cost /= 2;
					if (title[5] == 6)
					{
						cost /= 2;
						if (title[6] == 7 && title[7] == 8)
							cost /= 100;
					}
				}
			}
		}
		if (title[4] == 5 && title[8] == 9 && title[12] == 13)
		{
			cost /= 10;
			if (
				title[1] == 2 &&
				title[2] == 3 &&
				title[3] == 4 &&
				title[5] == 6 &&
				title[6] == 7 &&
				title[7] == 8
				)
				cost /= 10;
		}
	}

	if (CalculateHeuristic() < 7)
		cost /= 10;

	if (!previousState)
		return;

	// Increasing cost if algorith took a wrong move
	if (
		title[0] != 1 &&
		title[1] != 2 &&
		title[2] != 3 &&
		title[3] != 4 &&
		previousState->title[0] == 1 &&
		previousState->title[1] == 2 &&
		previousState->title[2] == 3 &&
		previousState->title[3] == 4
		) {
		cost *= 100;
		if (
			title[4] != 5 &&
			title[5] != 6 &&
			previousState->title[4] == 5 &&
			previousState->title[5] == 6
			) {
			cost *= 2;
			if (
				title[6] != 7 &&
				title[7] != 8 &&
				previousState->title[6] == 7 &&
				previousState->title[7] == 8
				) {
				cost *= 100;
				if (
					title[8] != 9 &&
					title[12] != 13 &&
					previousState->title[8] == 9 &&
					previousState->title[12] == 13
					) {
					cost *= 100;
					if (
						title[9] != 10 &&
						title[13] != 14 &&
						previousState->title[9] == 10 &&
						previousState->title[13] == 14
						)
						cost *= 100;
				}
			}
		}
	}
}