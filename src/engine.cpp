// #include <SFML/Graphics.hpp>
// #include "engine.h"
// #include "circle.h"

// // implement `circle` pointer
// Circle* circle;

// Engine::Engine() {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "2D Engine");
//     window.setFramerateLimit(60);
//     // initialize circle pointer
//     circle = new Circle(400, 300, 50, sf::Color::Green);
// }

// // implement isRunning()
// bool Engine::isRunning() const {
//     return window.isOpen();
// }

// void Engine::run() {
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//         }
//         window.clear(sf::Color::Yellow);
//         circle*->rotate(1);
//         window.draw(circle->getShape());
//         window.display();
//     }
// }

// // implement addObject()
// void Engine::addObject(Circle* circle) {
//     this->circle = circle;
// }

// Engine::~Engine() {
//     delete circle;
// }