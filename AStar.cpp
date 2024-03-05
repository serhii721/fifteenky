#include "stdafx.h"
#include "AStar.h"

AStar::AStar() { }

AStar::~AStar() { }

void AStar::CalculateNextStates(vector<State>& nextStates, State& currentState)
{
	int id = currentState.FindEmptyTile();

	// Moving empty tile in all possible directions
	if (currentState.IsMoveUpPossible(id))
	{
		State nextState = currentState;
		nextState.SetPreviousState(&currentState);
		nextState.SetLevel(currentState.GetLevel() + 1);
		nextState.SwapTop(id);
		nextState.CalculateStateCost();
		nextStates.push_back(nextState);
	}
	if (currentState.IsMoveLeftPossible(id))
	{
		State nextState = currentState;
		nextState.SetPreviousState(&currentState);
		nextState.SetLevel(currentState.GetLevel() + 1);
		nextState.SwapLeft(id);
		nextState.CalculateStateCost();
		nextStates.push_back(nextState);
	}
	if (currentState.IsMoveRightPossible(id))
	{
		State nextState = currentState;
		nextState.SetPreviousState(&currentState);
		nextState.SetLevel(currentState.GetLevel() + 1);
		nextState.SwapRight(id);
		nextState.CalculateStateCost();
		nextStates.push_back(nextState);
	}
	if (currentState.IsMoveDownPossible(id))
	{
		State nextState = currentState;
		nextState.SetPreviousState(&currentState);
		nextState.SetLevel(currentState.GetLevel() + 1);
		nextState.SwapBottom(id);
		nextState.CalculateStateCost();
		nextStates.push_back(nextState);
	}
}

void AStar::CheckForRepeats(vector<State>& nextStates, set<State>& openSet, vector<array<int, TILE_COUNT>>& visited)
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
				if (nextStates[i].GetTitle(k) != visited[j][k])
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

void AStar::SolvePuzzle(HWND hwnd, HWND hB[], const State& startState, vector<State>& solutionPath)
{
	TCHAR buffer[256] = "";
	int i;
	// Container holds every not visited state in priority of increasing cost 
	set<State> openSet;

	// Vector holds every visited position
	vector<array<int, TILE_COUNT>> visited;
	array<int, TILE_COUNT> temp;

	// Vector to hold every possible next position from current position
	vector<State> nextStates;

	openSet.insert(startState);

	// Variables for additional info for debug purposes
	int minCost = 1000, maxCost = 0;

	while (!openSet.empty())
	{
		State currentState = *openSet.begin();
		openSet.erase(openSet.begin());

		for (i = 0; i < TILE_COUNT; i++)
			temp[i] = currentState.GetTitle(i);
		visited.push_back(temp);

		// Exit condition - if cost is 0 the puzzle is solved
		if (currentState.CalculateManhattanDistance() == 0)
		{
			State* currentStatePtr = &currentState;
			while (currentStatePtr)
			{
				solutionPath.push_back(*currentStatePtr);
				currentStatePtr = currentStatePtr->GetPreviousState();
			}
			return;
		}

		sprintf_s(buffer, "Calculating. Currently evaluated %d positions", visited.size());
		SetWindowText(hwnd, buffer);

		// Calculate all possible next moves from current position
		nextStates.clear();
		CalculateNextStates(nextStates, currentState);

		// If next positions weren't visited before they are added to openSet
		CheckForRepeats(nextStates, openSet, visited);
	}
}

void AStar::ExecuteMove(State& startState, const State& endState)
{
	int id = endState.FindEmptyTile();

	if (startState.GetTitle(id + 1) == 0 && id < 15)
		startState.SwapRight(id);
	else if (startState.GetTitle(id + 4) == 0 && id < 12)
		startState.SwapBottom(id);
	else if (startState.GetTitle(id - 1) == 0 && id > 0)
		startState.SwapLeft(id);
	else if (startState.GetTitle(id - 4) == 0 && id > 3)
		startState.SwapTop(id);
}
