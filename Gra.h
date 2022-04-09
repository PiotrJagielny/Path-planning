#pragma once

#include "State.h"
#include "PathFindingState.h"
#include "MainMenuState.h"

class Gra
{
private:
	sf::RenderWindow* m_window;
	sf::Event m_event;

	std::stack<State*> m_states;

	void initWindow();
	void initStates();

public:
	Gra();
	~Gra();
	

	
	void endApplication();

	//Update
	void update();
	void updateEvents();

	//Render
	void render();

	//Game Loop
	void runGame();
};

