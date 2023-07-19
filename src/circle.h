#ifndef CIRCLE_H
#define CIRCLE_H

#include <SFML/Graphics.hpp>

class Circle {
public:
    Circle(float x, float y, float radius, sf::Color color);
    Circle(float radius, sf::Color color);
    Circle(float x, float y, float radius);
    void draw(sf::RenderWindow& window);
    void rotate(float angle);

private:
    sf::CircleShape m_circle;
};

#endif // CIRCLE_H