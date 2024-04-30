#include "Engine.h"
<<<<<<< HEAD

=======
using namespace std;
using namespace sf;
>>>>>>> 237c44046e17274f7424499f0a21940c2aed1505

Engine::Engine()
{
	m_Window.create();

	int pixelWidth = sf::VideoMode::getDesktopMode().width;
	int pixelHeight = sf::VideoMode::getDesktopMode().height;
	VideoMode vm(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	RenderWindow window(vm, "Particles", Style::Default);

	View view;
	view.setSize(pixelWidth, pixelHeight);
	view.setCenter(pixelWidth / 2, pixelHeight / 2);
	window.setView(view);
}

void Engine::run()
{
	Particle local_particle;
}

void Engine::input()
{

}

void Engine::update(float drAsSeconds)
{

}

void Engine::draw()
{

}
