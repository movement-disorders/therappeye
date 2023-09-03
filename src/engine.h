#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>

#include "slide.h"

class Engine
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	sf::Event sfEvent;

	std::vector<Slide*> slides;
	unsigned short currentSlide = 0;

	//Initialization
	void initVariables();
	void initWindow();

public:
	//Constructors/Destructors
	Engine();
	virtual ~Engine();

	//Accessors
	const bool running() const;

	//Update
	void updateSFMLEvents();
	void update();

	void nextSlide();

	//Render
	void render();

};

#endif