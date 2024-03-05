#pragma once
class State
{
private:
	// State holds information about previous state so that sequence of the moves can be traced
	State* previousState;
	// Title holds number which tile has on it
	int title[TILE_COUNT];
	// Position holds tile ID in order
	const int POSITION[TILE_COUNT] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	// Depth
	int level;
	// Total cost = current level + current cost
	int cost;

public:
	State();
	State(State*, int[], int, int);
	State(const State&);
	~State();
	State operator=(const State&);
	// Overloading the operator < for priority queue
	bool operator<(const State& other) const;

	void SetPreviousState(State*);
	void SetTitle(int, int);
	void SetLevel(int);
	void SetCost(int);

	State* GetPreviousState() const;
	int GetPosition(int) const;
	int GetTitle(int) const;
	int GetLevel() const;
	int GetCost() const;

	bool IsMovementPossible(int) const;
	bool IsMoveUpPossible(int) const;
	bool IsMoveLeftPossible(int) const;
	bool IsMoveRightPossible(int) const;
	bool IsMoveDownPossible(int) const;

	void MovePiece(int);
	void SwapTop(int);
	void SwapLeft(int);
	void SwapRight(int);
	void SwapBottom(int);

	void FillTilesRandomly();
	void FillTiles(int[]);
	void Show(HWND, HWND[], bool);
	int FindEmptyTile() const;
	int CalculateHeuristic() const;
	int CalculateManhattanDistance() const;
	void CalculateStateCost();
};
