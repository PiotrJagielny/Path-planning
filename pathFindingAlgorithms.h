#pragma once

#include "Tile.h"

namespace auxiliaryFunctions
{

	//auxiliary functions
	int getRandomInt(int min, int max);

	void drawShortestPath(Tile* endTile);

	void clearOldPath(std::vector<std::vector<Tile>>& tileMap);

	void clearOldVisitedTiles(std::vector<std::vector<Tile>>& tileMap);

	void updateVisualization(std::vector<std::vector<Tile>>& tileMap,
		sf::RenderWindow* window);

	void sortTilesToTest(std::vector<Tile*>& tilesToTest, int startIndex,
		int endIndex);

	int partition(std::vector<Tile*>& tilesToTest, int startIndex,
		int endIndex);

	void setTilesDefaultValues(std::vector<std::vector<Tile>>& tileMap);

	void setTilesToTestColor(std::vector<Tile*>& tilesToTest,
		Tile* startTile, Tile* endTile);

	void setVisitedTilesColor(std::vector<std::vector<Tile>>& tileMap,
		Tile* startTile, Tile* endTile);

	void visualizationMode(std::vector<std::vector<Tile>>& tileMap,
		sf::RenderWindow* window, std::vector<Tile*>& tilesToTest,
		Tile* currentTile, Tile* startTile, Tile* endTile);
}


namespace pathFindingAlgorithms
{
	//Path finding functions
	void A_STAR_ALGORITHM(std::vector<std::vector<Tile>>& tileMap,
		Tile* startTile, Tile* endTile, sf::RenderWindow* window);

}

