#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <chrono>

class Slide {
public:
    
    sf::RenderWindow* window;
    
    Slide() {}
    virtual ~Slide() {}

    virtual void setup(sf::RenderWindow* window) = 0;
    virtual void performAction() = 0;

protected:
    
    sf::Vector2f getRandomPosition(float radius) {
        auto window = this->window;
        float windowWidth = window->getSize().x;
        float windowHeight = window->getSize().y;

        return sf::Vector2f(rand() % static_cast<int>(windowWidth - 2 * radius) + radius,
                            rand() % static_cast<int>(windowHeight - 2 * radius) + radius);
    }

    sf::Vector2f handleWallCollisions(sf::Vector2f position, float radius) {
        float windowWidth = window->getSize().x;
        float windowHeight = window->getSize().y;

        if (position.x + radius > windowWidth) {
            position.x = windowWidth - radius;
        } else if (position.x - radius < 0) {
            position.x = radius;
        }
        
        if (position.y + radius > windowHeight) {
            position.y = windowHeight - radius;
        } else if (position.y - radius < 0) {
            position.y = radius;
        }

        return position;
    }
};

/**
 * Slide definitions
 */

class RandomSpotAnimationSlide : public Slide {
private:
    sf::CircleShape circle;
    float radius = 25.f;

    float frameTime = 1.0f;
    float accumulator = 0.0f;
    std::chrono::_V2::system_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
    
public:
    RandomSpotAnimationSlide() : Slide() {}
    ~RandomSpotAnimationSlide() {}

    void setup(sf::RenderWindow* window) override;

    void performAction() override ;
};

class SideToSideCircleAnimationSlide : public Slide {
private:
    sf::CircleShape circle;
    float radius = 25.f;
    float speed = 12.f;
    float currentX = 0.f;

public:
    SideToSideCircleAnimationSlide() : Slide() {}
    ~SideToSideCircleAnimationSlide() {}

    void setup(sf::RenderWindow* window) override;

    void performAction() override ;
};

class RandomSpotWithLineAnimationSlide : public Slide {
private:
    sf::CircleShape circle;
    sf::RectangleShape line;
    float radius = 25.f;

    float shapeFrameTime = 1.0f;
    float shapeAccumulator = 0.0f;
    sf::Clock shapeClock = sf::Clock();

    float lineFrameTime = 0.01f;
    sf::Clock lineClock = sf::Clock();

    float lineSpeed = 100.f;
    float lineCurrentX = 0.f;
    
public:
    RandomSpotWithLineAnimationSlide() : Slide() {}
    ~RandomSpotWithLineAnimationSlide() {}

    void setup(sf::RenderWindow* window) override;

    void performAction() override ;
};

#endif