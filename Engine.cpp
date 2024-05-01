#include "Engine.h"

using namespace std;
using namespace sf;

Engine::Engine()
{
	//I took out m_Window.create() and just replaced all the window with m_Window.

	int pixelWidth = sf::VideoMode::getDesktopMode().width;
	int pixelHeight = sf::VideoMode::getDesktopMode().height;
	VideoMode vm(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	RenderWindow m_Window(vm, "Particles", Style::Default);

	View view;
	view.setSize(pixelWidth, pixelHeight);
	view.setCenter(pixelWidth / 2, pixelHeight / 2);
	m_Window.setView(view);


}

void Engine::run()
{
	//local variables
	Clock local_clock;
	Particle local_particle(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 }); //particle for normal use

	//unit test
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 }); //particle for unit tests
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	//game loop
	while (m_Window.isOpen() == true)
	{
		local_clock.restart();
		float dtAsSec = local_clock.getElapsedTime().asSeconds();
		input();
		update(dtAsSec);
		draw();
	}

}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) m_Window.close();
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//create 5 particles on left click
				for (int i = 0; i <= 5; i++)
				{
					Particle new_particle(m_Window, (rand() % 25) + 25, { event.mouseButton.x, event.mouseButton.y });
					m_particles.push_back(new_particle);
				}

			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}
	}
}

void Engine::update(float dtAsSeconds)			//this one still needs work, ill finish this later using a less janky for loop
{
	//attempt 1
	/*for (int i = 0; i < m_particles.size(); )
	{
		if (m_particles.at(i).getTTL() > 0.0)
		{
			i++;
		}
		else
		{
			m_particles.erase(i);
		}
	}

	//attempt 2
	for (auto it = m_particles.begin(); it != m_particles.end(); ++it) {
		//auto i = distance(m_particles.begin(), it);
		if (m_particles.at(it).getTTL() > 0.0)
		{
			i++;
		}
		else
		{
			m_particles.erase(i);
		}
	}*/
}

void Engine::draw()
{
	m_Window.clear();

	for (Particle current_particle : m_particles)
	{
		m_Window.draw(current_particle);
	}

	m_Window.display();
}
