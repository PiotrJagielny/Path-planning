#include "Headers.h"
#include "pathFindingAlgorithms.h"



namespace pathFindingAlgorithms
{
	//auxiliary functions
	void drawShortestPath(Tile* endTile)
	{
		if (endTile != nullptr)
		{
			Tile* tempTile = endTile;
			while (tempTile->getParentTile() != nullptr)
			{
				if(tempTile != endTile)
					tempTile->setFillColor(sf::Color::Blue);

				tempTile = tempTile->getParentTile();
			}
		}
	}

	void sortTilesToTest(std::vector<Tile*>& tilesToTest,int startIndex,int endIndex)
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

	//Path finding functions
	void A_STAR_ALGORITHM(std::vector<std::vector<Tile>>& tileMap, Tile* startTile, Tile* endTile)
	{
		

		Tile* currentTile = startTile;
		startTile->setGlobalGoal(Tile::distanceBetweenTiles(*startTile,*endTile));
		startTile->setDistanceToStart(0.0f);

		std::vector<Tile*> tilesToTest;
		tilesToTest.push_back(startTile);

		

		while (!tilesToTest.empty() && currentTile != endTile)
		{
			sortTilesToTest(tilesToTest, 0, tilesToTest.size() - 1);

			/*for (int iii{ 0 }; iii < tilesToTest.size(); ++iii)
			{
				std::cout << "iii: " << iii << " global goal: " << tilesToTest[iii]->getGlobalGoal() << '\n';
			}
			std::cout << std::endl;*/

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
			//currentTile->setFillColor(sf::Color::Yellow);

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
			

			
		}

	}
}