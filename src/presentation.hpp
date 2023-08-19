#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <chrono>
#include <ctime>

class Slide {
public:
    float duration;

    Slide(float duration) : duration(duration) {}

    virtual void performAction(sf::RenderWindow& window, sf::Shape& shape) = 0;

protected:
    sf::Vector2f getRandomPosition(sf::RenderWindow& window, float radius) {
        float windowWidth = window.getSize().x;
        float windowHeight = window.getSize().y;

        return sf::Vector2f(rand() % static_cast<int>(windowWidth - 2 * radius) + radius,
                            rand() % static_cast<int>(windowHeight - 2 * radius) + radius);
    }

    sf::Vector2f handleWallCollisions(sf::RenderWindow& window, sf::Vector2f position, float radius) {
        float windowWidth = window.getSize().x;
        float windowHeight = window.getSize().y;

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

class CircleAnimationSlide : public Slide {
public:
    CircleAnimationSlide(float duration) : Slide(duration) {}
    float speed = 12.0f;
    float radius = 0.0;

    void performAction(sf::RenderWindow& window, sf::Shape& shape) override ;
};

class RandomSpotWithLineAnimationSlide : public Slide {
public:
    RandomSpotWithLineAnimationSlide(float duration) : Slide(duration) {}
    float speed = 12.0f;
    float radius = 0.0;

    void performAction(sf::RenderWindow& window, sf::Shape& shape) override ;
private:
    sf::Vector2f getRandomPosition(sf::RenderWindow& window, float radius) {
        float windowWidth = window.getSize().x;
        float windowHeight = window.getSize().y;

        return sf::Vector2f(rand() % static_cast<int>(windowWidth - 2 * radius) + radius,
                            rand() % static_cast<int>(windowHeight - 2 * radius) + radius);
    }

    sf::Vector2f handleWallCollisions(sf::RenderWindow& window, sf::Vector2f position, float radius) {
        float windowWidth = window.getSize().x;
        float windowHeight = window.getSize().y;

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

class RandomSpotAnimationSlide : public Slide {
public:
    RandomSpotAnimationSlide(float duration) : Slide(duration) {}

    void performAction(sf::RenderWindow& window, sf::Shape& shape) override ;
};

class ContinuousMovingCircleSlide : public Slide {
public:
    ContinuousMovingCircleSlide(float duration) : Slide(duration) {}
    float speed = 12.0f;
    float radius = 0.0;

    void performAction(sf::RenderWindow& window, sf::Shape& shape) override ;
};

class Scene {
private:
    std::unique_ptr<Slide> actionSlide;

public:
    Scene(std::unique_ptr<Slide> action) : actionSlide(std::move(action)) {}

    void runScene(sf::RenderWindow& window, sf::Shape& shape);
};

class Presentation {
private:
    std::vector<Scene> scenes;
    float totalTime;

public:
    Presentation(float totalTime) : totalTime(totalTime) {}

    void addScene(Scene scene) {
        float slideDuration = totalTime / scenes.size();
        scenes.push_back(std::move(scene));
    }

    void runPresentation(sf::RenderWindow& window, sf::Shape& shape);
};