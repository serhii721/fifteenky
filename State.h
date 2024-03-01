#pragma once
struct State
{
	// State holds information about previous state so that sequence of the moves can be traced
	State* previousState;

	// Position holds tile ID in order
	int position[TILE_COUNT];

	// Title holds number which tile has on it
	int title[TILE_COUNT];

	// Depth
	int level;

	// Total cost (g + h) = current level + current heuristic cost
	int cost;

	State();

	// Overloading the operator for future priority queue
	bool operator<(const State& other) const
	{
		return cost < other.cost;
	}
};
