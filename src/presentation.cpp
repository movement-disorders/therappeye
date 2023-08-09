#include "presentation.hpp"

void Presentation::runPresentation(sf::RenderWindow& window, sf::Shape& shape) {
    for (auto& scene : scenes) {
        scene.runScene(window, shape);
    }
};

void Scene::runScene(sf::RenderWindow& window, sf::Shape& shape) {
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    while (time.asSeconds() < actionSlide->duration) {
        actionSlide->performAction(window, shape);
        time = clock.getElapsedTime();
    }

    actionSlide->performAction(window, shape);
    clock.restart();
    while (clock.getElapsedTime().asSeconds() < actionSlide->duration) {
        // do nothing
    }
}

void CircleAnimationSlide::performAction(sf::RenderWindow& window, sf::Shape& shape) {
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
};

void RandomSpotAnimationSlide::performAction(sf::RenderWindow& window, sf::Shape& shape) {
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
};