#include "Headers.h"
#include "Tile.h"


Tile::Tile()
{
	m_isObsticle = false;
	m_isVisited = false;
	m_parentTile = nullptr;
	m_distanceToStart = 9999999;
	m_globalGoal = 9999999;

}

Tile::~Tile()
{
}


//Functions
void Tile::setFillColor(sf::Color color)
{
	m_kwadrat.setFillColor(color);
}

void Tile::setPosition(const float X, const float Y)
{
	m_kwadrat.setPosition(X, Y);
}

void Tile::setOutlineThickness(const float outlineSize)
{
	m_kwadrat.setOutlineThickness(outlineSize);
}

void Tile::setOutlineColor(sf::Color color)
{
	m_kwadrat.setOutlineColor(color);
}

void Tile::setSize(sf::Vector2f size)
{
	m_kwadrat.setSize(size);
}

void Tile::setGridPosition(int gridPositionX, int gridPositionY)
{
	m_tilePositionInGrid.x = gridPositionX;
	m_tilePositionInGrid.y = gridPositionY;
}

void Tile::setTileObsticle(bool isObsticle)
{
	m_isObsticle = isObsticle;
}

void Tile::setDistanceToStart(float distance)
{
	m_distanceToStart = distance;
}

void Tile::setGlobalGoal(float globalGoal)
{
	m_globalGoal = globalGoal;
}

void Tile::setParent(Tile* parent)
{
	m_parentTile = parent;
}

void Tile::setVisit(bool visit)
{
	m_isVisited = visit;
}

void Tile::pushNeighboor(Tile* tileToPush)
{
	m_neighbors.push_back(tileToPush);
}


const sf::RectangleShape& Tile::getRectangle() const
{
	return m_kwadrat;
}

const sf::FloatRect& Tile::getGlobalBounds() const
{
	return m_kwadrat.getGlobalBounds();
}

Tile* Tile::getParentTile() const
{
	return m_parentTile;
}

const float& Tile::getGlobalGoal() const
{
	return m_globalGoal;
}

const float& Tile::getDistanceToStart() const
{
	return m_distanceToStart;
}

const bool& Tile::isVisited() const
{
	return m_isVisited;
}

const bool& Tile::isObsticle() const
{
	return m_isObsticle;
}

const std::vector<Tile*> Tile::getNeighborVector() const
{
	return m_neighbors;
}

const sf::Vector2f& Tile::getPosition() const
{
	return m_kwadrat.getPosition();
}

float Tile::distanceBetweenTiles(const Tile& firstTile, const Tile& secoundTile)
{
	float distance{0.0f};

	sf::Vector2f vectorComponents{};
	vectorComponents.x = secoundTile.getPosition().x - firstTile.getPosition().x;
	vectorComponents.y = secoundTile.getPosition().y - firstTile.getPosition().y;

	distance = sqrt( (vectorComponents.x*vectorComponents.x) + (vectorComponents.y*vectorComponents.y) );

	return distance;
}
