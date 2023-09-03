#include "slide.h"

void RandomSpotAnimationSlide::setup(sf::RenderWindow* window)
{
    auto w = this->window = window;
    // NOTE: seed the random number generator with the current time,
    //       so that we get different random numbers every time we run the program.
    srand(time(nullptr));
    //

    this->circle = sf::CircleShape();
    this->circle.setRadius(this->radius);

    float windowWidth  = w->getView().getCenter().x;
    float windowHeight = w->getView().getCenter().y;
    this->circle.setPosition(windowWidth - radius, windowHeight - radius);

    this->circle.setFillColor(sf::Color::Green);
}

void RandomSpotAnimationSlide::performAction()
{
    auto window = this->window;
    
    auto newTime = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(newTime - currentTime).count() / 1000000.0f;
    currentTime = newTime;

    accumulator += deltaTime;
    if (accumulator >= frameTime) {

        accumulator -= frameTime;
        sf::Vector2f position = getRandomPosition(this->radius);

        position = handleWallCollisions(position, this->radius);

        this->circle.setPosition(position);

    }

    // NOTE: render the circle into the window
    window->draw(this->circle);
};


void SideToSideCircleAnimationSlide::setup(sf::RenderWindow* window)
{
    auto w = this->window = window;
    
    this->circle = sf::CircleShape();
    this->circle.setRadius(this->radius);

    float windowWidth  = w->getView().getCenter().x;
    float windowHeight = w->getView().getCenter().y;
    
    this->circle.setPosition(radius, windowHeight - radius);

    this->circle.setFillColor(sf::Color::Green);
}

void SideToSideCircleAnimationSlide::performAction()
{
    auto window = this->window;

    float windowWidth  = window->getSize().x;
    
    this->currentX += speed;
    if (this->currentX + radius > windowWidth) {
        this->currentX = windowWidth - radius;
        speed = -speed;
    } else if (this->currentX - radius < 0) {
        this->currentX = radius;
        speed = -speed;
    }

    // NOTE: render the circle into the window
    this->circle.move(speed, 0);
    window->draw(this->circle);
};

void RandomSpotWithLineAnimationSlide::setup(sf::RenderWindow* window)
{
    auto w = this->window = window;
    // NOTE: seed the random number generator with the current time,
    //       so that we get different random numbers every time we run the program.
    srand(time(nullptr));
    //

    this->circle = sf::CircleShape();
    this->line = sf::RectangleShape(sf::Vector2f(1, w->getSize().y));
    this->circle.setRadius(this->radius);

    float windowWidth  = w->getView().getCenter().x;
    float windowHeight = w->getView().getCenter().y;
    
    this->circle.setPosition(windowWidth - radius, windowHeight - radius);
    this->line.setPosition(windowWidth, 0);

    this->circle.setFillColor(sf::Color::Green);
    this->line.setFillColor(sf::Color::Red);

}

void RandomSpotWithLineAnimationSlide::performAction()
{
    auto window = this->window;
    
    float shapeDeltaTime = shapeClock.restart().asSeconds();
    shapeAccumulator += shapeDeltaTime;
    while (shapeAccumulator >= shapeFrameTime) {
        shapeAccumulator -= shapeFrameTime;

        sf::Vector2f position = getRandomPosition(radius);
        position = handleWallCollisions(position, radius);

        this->circle.setPosition(position);
    }

    // update line position
    float lineDeltaTime = lineClock.restart().asSeconds();
    lineCurrentX += lineSpeed * lineDeltaTime;
    if (lineCurrentX > window->getSize().x) {
        lineCurrentX = window->getSize().x;
        lineSpeed = -lineSpeed;
    } else if (lineCurrentX < 0) {
        lineCurrentX = 0;
        lineSpeed = -lineSpeed;
    }
    line.setPosition(lineCurrentX, 0);

    // NOTE: render the circle into the window
    window->draw(this->circle);
    window->draw(this->line);
};

// Lacks implementation
/*
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
*/