#pragma once


class Tile
{
private:
	sf::RectangleShape m_kwadrat;


	//A* variables
	bool m_isObsticle;
	bool m_isVisited;
	float m_distanceToStart;
	float m_globalGoal;
	sf::Vector2i m_tilePositionInGrid;
	std::vector<Tile*> m_neighbors;
	Tile* m_parentTile;


public:
	Tile();
	~Tile();

	void setFillColor(sf::Color color);
	void setPosition(const float X, const float Y);
	void setOutlineThickness(const float outlineSize);
	void setOutlineColor(sf::Color color);
	void setSize(sf::Vector2f size);
	void setGridPosition(int gridPositionX, int gridPositionY);
	void setTileObsticle(bool isObsticle);
	void setDistanceToStart(float distance);
	void setGlobalGoal(float globalGoal);
	void setParent(Tile* parent);
	void setVisit(bool visit);
	void pushNeighboor(Tile* tileToPush);
	

	const sf::RectangleShape& getRectangle() const;
	const sf::FloatRect& getGlobalBounds() const;
	Tile* getParentTile() const;
	const float& getGlobalGoal() const;
	const float& getDistanceToStart() const;
	const bool& isVisited() const;
	const bool& isObsticle() const;
	const std::vector<Tile*> getNeighborVector() const;
	const sf::Vector2f& getPosition() const;

	static float distanceBetweenTiles(const Tile& firstTile, const Tile& secoundTile);
};

