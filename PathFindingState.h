#pragma once

#include "State.h"
#include "Tile.h"

class PathFindingState : public State
{
private:
	sf::RectangleShape m_tileSelector;
	sf::Vector2u m_mousePositionGrid;
	sf::Vector2i m_mousePositionWindow;

	std::vector<std::vector<Tile>> m_tileMap;
	Tile* m_startTile;
	Tile* m_endTile;

	sf::Vector2i m_startGridPosition;
	sf::Vector2i m_endGridPosition;

	void initGrid();
	void initNeighboors();
	void initTileSelector();

public:
	PathFindingState(sf::RenderTarget* viewPoint, std::stack<State*>* statesPtr);
	virtual ~PathFindingState();

	void endState() override;

	void update(sf::RenderWindow* window) override;
	void updateMousePosition(sf::RenderWindow* window);
	void setObsticlesStartEnd(sf::RenderWindow* window, bool isObsticle,
		sf::Color innerColor, sf::Color outlineColor,
		std::string setStartOrEndTile = "");
	void updateTileConfigurating(sf::RenderWindow* window);
	void updatePathFinding(sf::RenderWindow* window);

	void render(sf::RenderTarget* target = nullptr) override;
	void renderTiles(sf::RenderTarget* target = nullptr);
};

