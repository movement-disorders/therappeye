#include <SFML/Graphics.hpp>
#include <chrono>
#include "presentation.hpp"

int main(int argc, char ** argv){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Vision Threrapy");
    window.setFramerateLimit(60);
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    
    // TODO: a better implementation of this
    shape.setPosition(25.f, 275.f);
    //

    Presentation presentation(10.0f);
    // TODO: as transition between scenes is not quite yet working (Issue #pending),
    //       we will only have one scene for now.
    //       Manually switch between scenes by commenting/uncommenting the lines below.
    //
    //presentation.addScene(Scene(std::make_unique<CircleAnimationSlide>(10.0f)));
    presentation.addScene(Scene(std::make_unique<RandommSpotAnimationSlide>(10.0f))); // This one is buggy (Issue #4)
    //

    presentation.runPresentation(window, shape);
    
    return 0;
}