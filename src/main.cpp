#include <SFML/Graphics.hpp>
#include <chrono>
#include "presentation.hpp"

int main(int argc, char ** argv){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Vision Therapy");
    window.setFramerateLimit(60);
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    
    Presentation presentation(10.0f);
    // TODO: as transition between scenes is not quite yet working (Issue #9),
    //       we will only have one scene for now.
    //       Manually switch between scenes by commenting/uncommenting the lines below.
    //
    //presentation.addScene(Scene(std::make_unique<CircleAnimationSlide>(10.0f)));
    //presentation.addScene(Scene(std::make_unique<RandomSpotAnimationSlide>(10.0f)));
    
    presentation.addScene(Scene(std::make_unique<RandomSpotWithLineAnimationSlide>(10.0f)));
    //presentation.addScene(Scene(std::make_unique<ContinuousMovingCircleSlide>(10.0f)));
    //

    presentation.runPresentation(window, shape);
    
    return 0;
}
