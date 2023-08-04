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
};

class CircleAnimationSlide : public Slide {
public:
    CircleAnimationSlide(float duration) : Slide(duration) {}
    float speed = 12.0f;
    float radius = 0.0;

    void performAction(sf::RenderWindow& window, sf::Shape& shape) override {
        float x = shape.getPosition().x;
        float y = shape.getPosition().y;
        
        // HACK: tricky way to get the radius of the shape.
        if (auto circle = dynamic_cast<sf::CircleShape*>(&shape)) {
            radius = circle->getRadius();

            // set initial position of the shape to the vertical center of the window, far left horizontally.
            shape.setPosition(radius, window.getSize().y / 2 - radius);

        }
        //

        float windowWidth = window.getSize().x;
        float windowHeight = window.getSize().y;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event) || true) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    break;
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Q) {
                        window.close();
                        break;
                    }
                }

                x += speed;
                if (x + radius > windowWidth) {
                    x = windowWidth - radius;
                    speed = -speed;
                } else if (x - radius < 0) {
                    x = radius;
                    speed = -speed;
                }

                shape.setFillColor(sf::Color::Green);
                shape.move(speed, 0);
                window.clear(sf::Color::Yellow);
                window.draw(shape);
                window.display();
            }
        }
    }
};

class RandomSpotAnimationSlide : public Slide {
public:
    RandomSpotAnimationSlide(float duration) : Slide(duration) {}

    void performAction(sf::RenderWindow& window, sf::Shape& shape) override {
        // NOTE: seed the random number generator with the current time,
        //       so that we get different random numbers every time we run the program.
        srand(time(nullptr));
        //

        float radius = 0.0;
        if (auto circle = dynamic_cast<sf::CircleShape*>(&shape)) {
            radius = circle->getRadius();

            // set initial position of the shape to the center of the window.
            shape.setPosition(window.getSize().x / 2 - radius, window.getSize().y / 2 - radius);
        }

        float windowWidth = window.getSize().x;
        float windowHeight = window.getSize().y;

        float frameTime = 1.0f;
        float accumulator = 0.0f;
        auto currentTime = std::chrono::high_resolution_clock::now();

        while (window.isOpen()) {
            
            sf::Event event;
            while (window.pollEvent(event) || true) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    break;
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Q) {
                        window.close();
                        break;
                    }
                }

                auto newTime = std::chrono::high_resolution_clock::now();
                float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(newTime - currentTime).count() / 1000000.0f;
                currentTime = newTime;

                accumulator += deltaTime;
                while (accumulator >= frameTime) {
                    accumulator -= frameTime;

                    sf::Vector2f position = getRandomPosition(window, radius);

                    position = handleWallCollisions(window, position, radius);

                    shape.setFillColor(sf::Color::Green);
                    shape.setPosition(position);
                    window.clear(sf::Color::Yellow);
                    window.draw(shape);
                    window.display();
                }
            }
        }
    }

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