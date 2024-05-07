#include "Engine.h"

using namespace std;
using namespace sf;

Engine::Engine()
{
	//I took out m_Window.create() and just replaced all the window with m_Window.

	int pixelWidth = sf::VideoMode::getDesktopMode().width;
	int pixelHeight = sf::VideoMode::getDesktopMode().height;
	VideoMode vm(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	
	View view;
	view.setSize(pixelWidth, pixelHeight);
	view.setCenter(pixelWidth / 2, pixelHeight / 2);
	m_Window.setView(view);
	
	m_Window.create(vm, "Particles", Style::Default);
}

void Engine::run()
{
	//local variables
	Clock local_clock;

	//unit test
	
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 }); //particle for unit tests
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;
	
	//game loop
	while (m_Window.isOpen() == true)
	{
		float dtAsSec = local_clock.restart().asSeconds();
		input();
		//cout << "input" << endl;
		update(dtAsSec);
		//cout << "update" << endl;
		draw();
		//cout << "draw" << endl;
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
				for (int i = 0; i < 5; i++)
				{
					Particle new_particle(m_Window, 25 + (rand() % 25), { event.mouseButton.x, event.mouseButton.y });
					//Particle new_particle(m_Window, 28, { 960, 540 });
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

void Engine::update(float dtAsSeconds)	
{
	//Maybe push_back something
	//iteratres through the vector
	for (auto it = m_particles.begin(); it != m_particles.end();) 
	{
		//if it the TTL hasnt expired, update and go to the next particle
		if (it->getTTL() > 0.0)
		{
			it->update(dtAsSeconds);
			it++;
		}
		//if it has expired, erase that particle, and keep the it so that it hits whatever particle takes the spot of the one just erased, this should avoid it going out of bounds.
		else
		{
			it = m_particles.erase(it);
		}
	}
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
