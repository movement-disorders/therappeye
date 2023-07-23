#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <chrono>

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

class RandommSpotAnimationSlide : public Slide {
public:
    RandommSpotAnimationSlide(float duration) : Slide(duration) {}

    void performAction(sf::RenderWindow& window, sf::Shape& shape) override {
        sf::Vector2f position = sf::Vector2f(rand() % 100, rand() % 100);
        
        // HACK: tricky way to get the radius of the shape.
        float radius = 0.0;
        if (auto circle = dynamic_cast<sf::CircleShape*>(&shape)) {
            radius = circle->getRadius();
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

                shape.setFillColor(sf::Color::Green);
                shape.setPosition(position);
                window.clear(sf::Color::Yellow);

                static auto lastTime = std::chrono::high_resolution_clock::now();
                auto currentTime = std::chrono::high_resolution_clock::now();
                float elapsedSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count() / 1000.0f;
                if (elapsedSeconds < 1.0f) {
                    window.draw(shape);
                }
                if (elapsedSeconds > 2.0f) {
                    lastTime = currentTime;
                }
                
                window.display();
            }
        }
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