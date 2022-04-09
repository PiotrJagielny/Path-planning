#include "Headers.h"
#include "Gra.h"


//INITALIZATION FUNCTIONS
void Gra::initWindow()
{
	m_window = new sf::RenderWindow{ sf::VideoMode{Constants::windowWidth, Constants::windowHeigth},
	"Path Finding", sf::Style::Close | sf::Style::Titlebar};
}

void Gra::initStates()
{
	m_states.push(new MainMenuState{ m_window, &m_states});
}


//CONSTRUCTORS / DESRUCTORS
Gra::Gra()
{
	this->initWindow();
	this->initStates();
}

Gra::~Gra()
{
	delete m_window;

	while (!m_states.empty())
	{
		delete m_states.top();
		m_states.pop();
	}

}


//PUBLIC FUNCTIONS
void Gra::updateEvents()
{
	while (m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_window->close();
		else if (m_event.type == sf::Event::KeyReleased && m_event.key.code == sf::Keyboard::Escape)
			Constants::singleQuitClickDetection = true;
		else if (m_event.type == sf::Event::MouseButtonReleased &&
			m_event.mouseButton.button == sf::Mouse::Left)
		{
			Constants::insertStartPosition = true;
		}
		else if (m_event.type == sf::Event::MouseButtonReleased &&
			m_event.mouseButton.button == sf::Mouse::Right)
		{
			Constants::insertEndPosition = true;
		}
	}
}

void Gra::endApplication()
{
	std::cout << "Ending app";
}

void Gra::update()
{
	this->updateEvents();

	if (!m_states.empty())
	{
		m_states.top()->update(m_window);

		if (m_states.top()->getQuit())
		{
			m_states.top()->endState();

			delete m_states.top();
			m_states.pop();
		}
	}
	else //End application if m_states is empty
	{
		m_window->close();
		this->endApplication();
	}
}

void Gra::render()
{
	m_window->clear();

	if (!m_states.empty())
	{
		m_states.top()->render(m_window);
	}

	m_window->display();
}

void Gra::runGame()
{
	while (m_window->isOpen())
	{
		this->update();
		this->render();
	}
}
