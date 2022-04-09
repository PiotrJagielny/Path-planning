#include "Headers.h"
#include "PathFindingState.h"



void PathFindingState::initGrid()
{
	m_tileMap.resize(Constants::mapSizeY, std::vector<Tile>());

	m_endGridPosition = sf::Vector2i{ 3,3 };
	m_startGridPosition = sf::Vector2i{ 2,3 };

	for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
	{
		m_tileMap[iii].resize(Constants::mapSizeX, Tile{});
		for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
		{
			m_tileMap[iii][kkk].setSize(sf::Vector2f{ Constants::gridSizeFloat, Constants::gridSizeFloat });
			if (iii == 0 || kkk == 0 || iii == Constants::mapSizeY - 1 || kkk == Constants::mapSizeX - 1)
			{
				m_tileMap[iii][kkk].setFillColor(sf::Color::White);
				m_tileMap[iii][kkk].setOutlineThickness(1.0f);
				m_tileMap[iii][kkk].setOutlineColor(sf::Color::Black);
				m_tileMap[iii][kkk].setTileObsticle(true);
			}
			else
			{
				m_tileMap[iii][kkk].setFillColor(sf::Color::Black);
				m_tileMap[iii][kkk].setOutlineThickness(1.0f);
				m_tileMap[iii][kkk].setOutlineColor(sf::Color::White);
			}
			m_tileMap[iii][kkk].setPosition(kkk * Constants::gridSizeFloat, iii * Constants::gridSizeFloat);
			m_tileMap[iii][kkk].setGridPosition(kkk, iii);

		}
	}
}

void PathFindingState::initNeighboors()
{

	//Pêtle które id¹ przez wszystkie elemanty 
	for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
	{
		for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
		{
			//pêtle które id¹ przez wszystkich s¹siadów konkretnego kwadratu
			for (int ii{ iii - 1 }, counteri{ 0 }; counteri < 3; ++ii, ++counteri)
			{
				for (int kk{ kkk - 1 }, counterk{ 0 }; counterk < 3; ++kk, ++counterk)
				{
					if ( (ii!= iii || kk != kkk) && ii >= 0 && kk >= 0 && 
						ii<Constants::mapSizeY&&kk<Constants::mapSizeY)
					{
						m_tileMap[iii][kkk].pushNeighboor(&m_tileMap[ii][kk]);
					}
				}
			}
			
		}
	}
}

void PathFindingState::initTileSelector()
{
	m_tileSelector.setSize(sf::Vector2f{ Constants::gridSizeFloat, Constants::gridSizeFloat });
	m_tileSelector.setFillColor(sf::Color::Transparent);
	m_tileSelector.setOutlineThickness(1.0f);
	m_tileSelector.setOutlineColor(sf::Color::Green);
}

PathFindingState::PathFindingState(sf::RenderTarget* viewPoint, std::stack<State*>* statesPtr) :
	State{viewPoint, statesPtr}
{
	m_startTile = nullptr;
	m_endTile = nullptr;

	this->initGrid();
	this->initNeighboors();
	this->initTileSelector();
}

PathFindingState::~PathFindingState()
{


}

void PathFindingState::endState()
{
	std::cout << "Ending Main menu State\n";

}

void PathFindingState::updateMousePosition(sf::RenderWindow* window)
{
	m_mousePositionWindow = sf::Mouse::getPosition(*window);
	m_mousePositionGrid.x = m_mousePositionWindow.x / Constants::gridSizeFloat;
	m_mousePositionGrid.y = m_mousePositionWindow.y / Constants::gridSizeFloat;


	m_tileSelector.setPosition(m_mousePositionGrid.x * Constants::gridSizeFloat,
		m_mousePositionGrid.y * Constants::gridSizeFloat);
}

void PathFindingState::setObsticlesStartEnd(sf::RenderWindow* window, bool isObsticle,
	sf::Color innerColor, sf::Color outlineColor, std::string setStartOrEndTile)
{
	for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
	{
		for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
		{
			if (m_tileMap[iii][kkk].getGlobalBounds().contains(
				sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y) &&
				iii != 0 && kkk != 0 && iii != Constants::mapSizeY - 1 && kkk != Constants::mapSizeX - 1)
			{

				m_tileMap[iii][kkk].setFillColor(innerColor);
				m_tileMap[iii][kkk].setOutlineThickness(1.0f);
				m_tileMap[iii][kkk].setOutlineColor(outlineColor);
				m_tileMap[iii][kkk].setTileObsticle(isObsticle);

				if (setStartOrEndTile == "setStartTile")
				{
					m_startTile = &m_tileMap[iii][kkk];

					m_tileMap[m_startGridPosition.x][m_startGridPosition.y].setFillColor(sf::Color::Black);
					m_tileMap[m_startGridPosition.x][m_startGridPosition.y].setOutlineColor(sf::Color::White);

					m_startGridPosition = sf::Vector2i{ iii,kkk };
				}
				else if (setStartOrEndTile == "setEndTile")
				{
					m_endTile = &m_tileMap[iii][kkk];

					m_tileMap[m_endGridPosition.x][m_endGridPosition.y].setFillColor(sf::Color::Black);
					m_tileMap[m_endGridPosition.x][m_endGridPosition.y].setOutlineColor(sf::Color::White);

					m_endGridPosition = sf::Vector2i{ iii,kkk };
				}

			}
		}
	}
}

void PathFindingState::updateTileConfigurating(sf::RenderWindow* window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		setObsticlesStartEnd(window, true, sf::Color::White, sf::Color::Black);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		setObsticlesStartEnd(window, false, sf::Color::Black, sf::Color::White);
	}
	else if (Constants::insertStartPosition == true && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		setObsticlesStartEnd(window, false, sf::Color::Green, sf::Color::Green, "setStartTile");
	}
	else if (Constants::insertEndPosition == true && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		setObsticlesStartEnd(window, false, sf::Color::Red, sf::Color::Red, "setEndTile");
	}

	Constants::insertEndPosition = false;
	Constants::insertStartPosition = false;
}

void PathFindingState::update(sf::RenderWindow* window)
{
	this->checkForQuit();
	this->updateMousePosition(window);
	this->updateTileConfigurating(window);

	if (m_startTile != nullptr && m_endTile != nullptr && sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		pathFindingAlgorithms::A_STAR_ALGORITHM(m_tileMap, m_startTile, m_endTile);
	
}


void PathFindingState::renderTiles(sf::RenderTarget* target)
{
	for (int iii{ 0 }; iii < Constants::mapSizeY; ++iii)
	{
		for (int kkk{ 0 }; kkk < Constants::mapSizeX; ++kkk)
		{
			target->draw(m_tileMap[iii][kkk].getRectangle());
		}
	}
}

void PathFindingState::render(sf::RenderTarget* target)
{
	this->renderTiles(target);

	pathFindingAlgorithms::drawShortestPath(m_endTile);

	target->draw(m_tileSelector);
}

