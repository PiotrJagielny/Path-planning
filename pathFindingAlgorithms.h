#pragma once

#include "Tile.h"

namespace pathFindingAlgorithms
{
	//auxiliary functions
	void drawShortestPath(Tile* endTile);

	void sortTilesToTest(std::vector<Tile*>& tilesToTest, int startIndex,
		int endIndex);

	int partition(std::vector<Tile*>& tilesToTest, int startIndex,
		int endIndex);


	//Path finding functions
	void A_STAR_ALGORITHM(std::vector<std::vector<Tile>>& tileMap,
		Tile* startTile, Tile* endTile);

}

