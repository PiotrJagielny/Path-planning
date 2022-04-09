#include "Headers.h"
#include "MainMenuState.h"


void MainMenuState::initText()
{
	m_texts["programTitle"] = new sf::Text;
	m_texts["programTitle"]->setFont(*m_font);
	m_texts["programTitle"]->setPosition(200.0f, 0.0f);
	m_texts["programTitle"]->setCharacterSize(70.0f);
	m_texts["programTitle"]->setString("Shortest Path Finding");

	m_texts["confirmText"] = new sf::Text;
	m_texts["confirmText"]->setFont(*m_font);
	m_texts["confirmText"]->setPosition(10.0f, Constants::windowHeigth - 150.0f);
	m_texts["confirmText"]->setCharacterSize(35.0f);
	m_texts["confirmText"]->setString("Press 'Enter' to confirm");

	m_texts["selectMode"] = new sf::Text;
	m_texts["selectMode"]->setFont(*m_font);
	m_texts["selectMode"]->setPosition(3.0f, 150.0f);
	m_texts["selectMode"]->setCharacterSize(50.0f);
	m_texts["selectMode"]->setString("Select path finding mode:");

	m_texts["staticMode"] = new sf::Text;
	m_texts["staticMode"]->setFont(*m_font);
	m_texts["staticMode"]->setPosition(10.0f, 230.0f);
	m_texts["staticMode"]->setCharacterSize(35.0f);
	m_texts["staticMode"]->setString("- Static mode (With visualization):");

	m_texts["dynamicMode"] = new sf::Text;
	m_texts["dynamicMode"]->setFont(*m_font);
	m_texts["dynamicMode"]->setPosition(10.0f, 300.0f);
	m_texts["dynamicMode"]->setCharacterSize(35.0f);
	m_texts["dynamicMode"]->setString("- Dynamic mode (Without visualization):");



}

void MainMenuState::initButtons()
{
	m_dynamicModeButton.setSize(sf::Vector2f{ 40.0f, 40.0f });
	m_dynamicModeButton.setFillColor(sf::Color(255, 255, 255, 100));
	m_dynamicModeButton.setPosition(550.0f, 300.0f);
	m_dynamicModeButton.setOutlineThickness(2.0f);
	m_dynamicModeButton.setOutlineColor(sf::Color::White);

	m_staticModeButton.setSize(sf::Vector2f{ 40.0f, 40.0f });
	m_staticModeButton.setFillColor(sf::Color(255, 255, 255, 100));
	m_staticModeButton.setPosition(550.0f, 230.0f);
	m_staticModeButton.setOutlineThickness(2.0f);
	m_staticModeButton.setOutlineColor(sf::Color::White);

}

MainMenuState::MainMenuState(sf::RenderTarget* viewPoint, std::stack<State*>* statesPtr) :
	State{ viewPoint, statesPtr}
{
	this->initText();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	delete m_texts["programTitle"];
	delete m_texts["selectMode"];
	delete m_texts["staticMode"];
	delete m_texts["dynamicMode"];
	delete m_texts["confirmText"];
}

void MainMenuState::endState()
{
	std::cout << "Ending MainMenu State\n";

}

void MainMenuState::update(sf::RenderWindow* window)
{
	this->checkForQuit();
	this->updateButtons(window);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		m_statesPtr->push(new PathFindingState{m_vievPoint, m_statesPtr});
	}

}

bool MainMenuState::buttonHoverAndClickLogic(sf::RectangleShape& button, sf::RenderWindow* window, bool& buttonBool)
{
	if (button.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
	{
		button.setFillColor(sf::Color::Green);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			buttonBool = true;
			return true;
		}
	}
	else if(buttonBool == false)
	{
		button.setFillColor(sf::Color{ 255,255,255,100 });
	}

	return false;
}


void MainMenuState::updateButtons(sf::RenderWindow* window)
{
	if (buttonHoverAndClickLogic(m_staticModeButton, window, Constants::isStaticModeSeleceted))
	{
		Constants::isDynamicModeSelected = false;
	}
	else if (buttonHoverAndClickLogic(m_dynamicModeButton, window, Constants::isDynamicModeSelected))
	{
		Constants::isStaticModeSeleceted = false;
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	this->renderText(target);
	this->renderButtons(target);
	
}

void MainMenuState::renderText(sf::RenderTarget* target)
{
	target->draw(*m_texts["programTitle"]);
	target->draw(*m_texts["selectMode"]);
	target->draw(*m_texts["staticMode"]);
	target->draw(*m_texts["dynamicMode"]);
	target->draw(*m_texts["confirmText"]);
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	target->draw(m_dynamicModeButton);
	target->draw(m_staticModeButton);
}
