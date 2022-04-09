#pragma once

class State
{
private:


	bool m_getQuit;

protected:
	sf::Font* m_font;
	std::stack<State*>* m_statesPtr;
	sf::RenderTarget* m_vievPoint;

public:
	State(sf::RenderTarget* vievPoint, std::stack<State*>* statesPtr);
	virtual ~State();

	virtual void checkForQuit();

	const bool& getQuit() const;

	virtual void update(sf::RenderWindow* window) = 0;
	virtual void endState() = 0;

	virtual void render(sf::RenderTarget* target = nullptr) = 0;

};

