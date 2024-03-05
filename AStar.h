#pragma once
class AStar
{
public:
	AStar();
	~AStar();

	void CalculateNextStates(vector<State>&, State&);
	void CheckForRepeats(vector<State>&, set<State>&, vector<array<int, TILE_COUNT>>&);
	void SolvePuzzle(HWND, HWND[], const State&, vector<State>&);
	void ExecuteMove(State&, const State&);
};
