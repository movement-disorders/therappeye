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