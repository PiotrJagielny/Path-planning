#pragma once

#include "State.h"
#include "PathFindingState.h"

class MainMenuState : public State
{
private:
	std::map<sf::String, sf::Text*> m_texts;

	//Button
	sf::RectangleShape m_dynamicModeButton;
	sf::RectangleShape m_staticModeButton;


	void initText();
	void initButtons();
public:
	MainMenuState(sf::RenderTarget* viewPoint, std::stack<State*>* statesPtr);
	virtual ~MainMenuState();

	void endState() override;
	bool buttonHoverAndClickLogic(sf::RectangleShape& button,
		sf::RenderWindow* window, bool& buttonBool);

	void update(sf::RenderWindow* window) override;
	void updateButtons(sf::RenderWindow* window);

	void render(sf::RenderTarget* target = nullptr) override;
	void renderText(sf::RenderTarget* target = nullptr);
	void renderButtons(sf::RenderTarget* target = nullptr);
};

