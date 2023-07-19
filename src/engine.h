#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "circle.h"

class Engine {
public:
    Engine();
    void run();
    void processEvents();
    void update();
    void render();
    bool isRunning();
    void addObject(Circle* circle);

private:
    sf::RenderWindow window;
    sf::CircleShape circle;
};

#endif  // ENGINE_H