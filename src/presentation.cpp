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

// another animation slide. This time, the shape moves randomly throughout the window, while a vertical line (top to bottom) moves side to side.
void RandomSpotWithLineAnimationSlide::performAction(sf::RenderWindow& window, sf::Shape& shape) {
    // seed the random number generator with the current time,
    // so that we get different random numbers every time we run the program.
    srand(time(nullptr));

    float radius = 0.0;
    if (auto circle = dynamic_cast<sf::CircleShape*>(&shape)) {
        radius = circle->getRadius();

        // set initial position of the shape to the center of the window.
        shape.setPosition(window.getSize().x / 2 - radius, window.getSize().y / 2 - radius);
    }

    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    // set frame time for shape animation to 1 second
    float shapeFrameTime = 1.0f;
    float shapeAccumulator = 0.0f;
    auto shapeClock = sf::Clock();

    // set frame time for line animation to 0.01 seconds
    float lineFrameTime = 0.01f;
    auto lineClock = sf::Clock();

    sf::RectangleShape line(sf::Vector2f(1, windowHeight));
    line.setPosition(windowWidth / 2, 0);
    line.setFillColor(sf::Color::Green); // set line color to green

    float lineSpeed = 100.0f; // set line speed to 100 pixels per second
    float linePositionX = windowWidth / 2; // set initial line position to the center of the window

    line.setFillColor(sf::Color::Green);

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

            // update shape position
            float shapeDeltaTime = shapeClock.restart().asSeconds();
            shapeAccumulator += shapeDeltaTime;
            while (shapeAccumulator >= shapeFrameTime) {
                shapeAccumulator -= shapeFrameTime;

                sf::Vector2f position = getRandomPosition(window, radius);
                position = handleWallCollisions(window, position, radius);

                shape.setFillColor(sf::Color::Red);
                shape.setPosition(position);
            }

            // update line position
            float lineDeltaTime = lineClock.restart().asSeconds();
            linePositionX += lineSpeed * lineDeltaTime;
            if (linePositionX > windowWidth) {
                linePositionX = windowWidth;
                lineSpeed = -lineSpeed;
            } else if (linePositionX < 0) {
                linePositionX = 0;
                lineSpeed = -lineSpeed;
            }
            line.setPosition(linePositionX, 0);

            // draw everything to the window
            window.clear(sf::Color::Black);
            window.draw(shape);
            window.draw(line);
            window.display();
        }
    }
}

void ContinuousMovingCircleSlide::performAction(sf::RenderWindow& window, sf::Shape& shape) {
    // seed the random number generator with the current time,
    // so that we get different random numbers every time we run the program.
    srand(time(nullptr));

    float radius = 0.0;
    if (auto circle = dynamic_cast<sf::CircleShape*>(&shape)) {
        radius = circle->getRadius();

        // set initial position of the shape to the center of the window.
        shape.setPosition(window.getSize().x / 2 - radius, window.getSize().y / 2 - radius);
    }

    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    // set frame time for shape animation to 0.01 seconds
    float shapeFrameTime = 0.01f;
    auto shapeClock = sf::Clock();

    // set frame time for line animation to 0.01 seconds
    float lineFrameTime = 0.01f;
    auto lineClock = sf::Clock();

    sf::RectangleShape line(sf::Vector2f(1, windowHeight));
    line.setPosition(windowWidth / 2, 0);
    line.setFillColor(sf::Color::Green); // set line color to green

    float lineSpeed = 100.0f; // set line speed to 100 pixels per second
    float linePositionX = windowWidth / 2; // set initial line position to the center of the window

    line.setFillColor(sf::Color::Green);

    float circleSpeed = 100.0f; // set circle speed to 100 pixels per second
    float circlePositionX = windowWidth / 2; // set initial circle position to the center of the window
    float circlePositionY = windowHeight / 2;

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

            // update shape position
            float shapeDeltaTime = shapeClock.restart().asSeconds();

            sf::Vector2f position = sf::Vector2f(circlePositionX, circlePositionY);
            position = handleWallCollisions(window, position, radius);

            shape.setFillColor(sf::Color::Red);
            shape.setPosition(position);

            // update circle position
            circlePositionX += circleSpeed * shapeDeltaTime;
            circlePositionY += circleSpeed * shapeDeltaTime;
            if (circlePositionX > windowWidth) {
                circlePositionX = windowWidth;
                circleSpeed = -circleSpeed;
            } else if (circlePositionX < 0) {
                circlePositionX = 0;
                circleSpeed = -circleSpeed;
            }
            if (circlePositionY > windowHeight) {
                circlePositionY = windowHeight;
                circleSpeed = -circleSpeed;
            } else if (circlePositionY < 0) {
                circlePositionY = 0;
                circleSpeed = -circleSpeed;
            }

            // update line position
            float lineDeltaTime = lineClock.restart().asSeconds();
            linePositionX += lineSpeed * lineDeltaTime;
            if (linePositionX > windowWidth) {
                linePositionX = windowWidth;
                lineSpeed = -lineSpeed;
            } else if (linePositionX < 0) {
                linePositionX = 0;
                lineSpeed = -lineSpeed;
            }
            line.setPosition(linePositionX, 0);

            // draw everything to the window
            window.clear(sf::Color::Black);
            window.draw(shape);
            window.draw(line);
            window.display();
        }
    }
}


