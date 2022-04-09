#include "Headers.h"
#include "State.h"

State::State(sf::RenderTarget* vievPoint, std::stack<State*>* statesPtr) :
	m_vievPoint{ vievPoint }, m_statesPtr{statesPtr}
{

	m_font = new sf::Font;
	if (!m_font->loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "FONT COULD NOT LOAD";
	}

	m_getQuit = false;
}

State::~State()
{
	delete m_font;
}

void State::checkForQuit()
{

	if (Constants::singleQuitClickDetection == true)
	{
		m_getQuit = true;
		Constants::singleQuitClickDetection = false;
	}

}

const bool& State::getQuit() const
{
	return m_getQuit;
}
