#include "Headers.h"
#include "pathFindingAlgorithms.h"



namespace auxiliaryFunctions
{
	//auxiliary functions
	int getRandomInt(int min, int max)
	{
		static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

		return std::uniform_int_distribution<>{ min, max }(mt);
	}

	void drawShortestPath(Tile* endTile)
	{
		if (endTile != nullptr)
		{
			Tile* tempTile = endTile;
			while (tempTile->getParentTile() != nullptr)
			{
				if (tempTile != endTile)
					tempTile->setFillColor(sf::Color::Magenta);

				tempTile = tempTile->getParentTile();
			}
		}
	}

	void clearOldPath(std::vector<std::vector<Tile>>& tileMap)
	{
		for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
		{
			for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
			{
				if (tileMap[iii][kkk].getFillColor() == sf::Color::Magenta)
					tileMap[iii][kkk].setFillColor(sf::Color::Black);
			}
		}
	}

	void clearOldVisitedTiles(std::vector<std::vector<Tile>>& tileMap)
	{
		for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
		{
			for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
			{
				if (tileMap[iii][kkk].getFillColor() == sf::Color{ 255,94,19,255 })
					tileMap[iii][kkk].setFillColor(sf::Color::Black);
			}
		}
	}

	void updateVisualization(std::vector<std::vector<Tile>>& tileMap, sf::RenderWindow* window)
	{
		window->clear();

		for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
		{
			for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
			{
				window->draw(tileMap[iii][kkk].getRectangle());
			}
		}

		window->display();
	}

	void sortTilesToTest(std::vector<Tile*>& tilesToTest, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int pivotIndex{ partition(tilesToTest, startIndex,endIndex) };

		sortTilesToTest(tilesToTest, startIndex, pivotIndex - 1);
		sortTilesToTest(tilesToTest, pivotIndex + 1, endIndex);
	}

	int partition(std::vector<Tile*>& tilesToTest, int startIndex, int endIndex)
	{
		float pivot{ tilesToTest[endIndex]->getGlobalGoal() };
		int partitionIndex{ startIndex };

		for (int iii{ startIndex }; iii < endIndex; ++iii)
		{
			if (tilesToTest[iii]->getGlobalGoal() <= pivot)
			{
				std::swap(tilesToTest[iii], tilesToTest[partitionIndex]);
				++partitionIndex;
			}

		}
		std::swap(tilesToTest[endIndex], tilesToTest[partitionIndex]);

		return partitionIndex;
	}

	void setTilesDefaultValues(std::vector<std::vector<Tile>>& tileMap)
	{
		for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
		{
			for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
			{
				tileMap[iii][kkk].setDistanceToStart(INFINITY);
				tileMap[iii][kkk].setGlobalGoal(INFINITY);
				tileMap[iii][kkk].setParent(nullptr);
				tileMap[iii][kkk].setVisit(false);

			}
		}
	}

	void setTilesToTestColor(std::vector<Tile*>& tilesToTest, Tile* startTile, Tile* endTile)
	{
		for (int iii{ 0 }; iii < tilesToTest.size(); ++iii)
		{
			if (tilesToTest[iii]->getFillColor() != sf::Color{ 255,200,200,200 })
			{
				if (tilesToTest[iii] != startTile && tilesToTest[iii] != endTile)
					tilesToTest[iii]->setFillColor(sf::Color{ 255,200,200,200 });
			}
		}



	}

	void setVisitedTilesColor(std::vector<std::vector<Tile>>& tileMap, Tile* startTile, Tile* endTile)
	{
		for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
		{
			for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
			{
				if (&tileMap[iii][kkk] != startTile && &tileMap[iii][kkk] != endTile &&
					tileMap[iii][kkk].isVisited() == true && tileMap[iii][kkk].getFillColor() != sf::Color::Magenta)
				{
					tileMap[iii][kkk].setFillColor(sf::Color{ 255,94,19,255 });
				}

			}
		}
	}

	void visualizationMode(std::vector<std::vector<Tile>>& tileMap, sf::RenderWindow* window,
		std::vector<Tile*>& tilesToTest, Tile* currentTile, Tile* startTile, Tile* endTile)
	{
		setTilesToTestColor(tilesToTest, startTile, endTile);
		setVisitedTilesColor(tileMap, startTile, endTile);
		updateVisualization(tileMap, window);
	}
}


namespace pathFindingAlgorithms
{
	//Path finding functions
	void A_STAR_ALGORITHM(std::vector<std::vector<Tile>>& tileMap, Tile* startTile, Tile* endTile,
		sf::RenderWindow* window)
	{
		auxiliaryFunctions::setTilesDefaultValues(tileMap);

		Tile* currentTile = startTile;
		startTile->setGlobalGoal(Tile::distanceBetweenTiles(*startTile,*endTile));
		startTile->setDistanceToStart(0.0f);

		std::vector<Tile*> tilesToTest;
		tilesToTest.push_back(startTile);

		

		while (!tilesToTest.empty() && currentTile != endTile)
		{
			auxiliaryFunctions::sortTilesToTest(tilesToTest, 0, tilesToTest.size() - 1);

			while (!tilesToTest.empty() && tilesToTest[0]->isVisited() == true)
			{
				tilesToTest.erase(tilesToTest.begin() + 0);
			}

			if (tilesToTest.empty())
			{
				break;
			}

			currentTile = tilesToTest[0];
			currentTile->setVisit(true);
			
			

			for (int iii{ 0 } ; iii<currentTile->getNeighborVector().size() ; ++iii)
			{
				Tile* neighbourTile{ currentTile->getNeighborVector().at(iii) };

				if (neighbourTile->isVisited() == false && neighbourTile->isObsticle() == false)
					tilesToTest.push_back(neighbourTile);

				float lowestLocalGoal =
					(currentTile->getDistanceToStart() + Tile::distanceBetweenTiles(*currentTile, *neighbourTile));

				if (lowestLocalGoal < neighbourTile->getDistanceToStart())
				{
					neighbourTile->setParent(currentTile);
					neighbourTile->setDistanceToStart(lowestLocalGoal);

					neighbourTile->setGlobalGoal(
						neighbourTile->getDistanceToStart() + Tile::distanceBetweenTiles(*neighbourTile, *endTile));
				}
			}
			
			if (Constants::isStaticModeSeleceted == true)
				auxiliaryFunctions::visualizationMode(tileMap, window, tilesToTest, currentTile, startTile, endTile);
			
			
		}
		if(Constants::isStaticModeSeleceted == true)
			Constants::isPathFound = true;
	}
}