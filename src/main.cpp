//**********************************************
//
// Project: therappeye
// File: src/main.cpp
//
// Compiler Command: clang++ -g -Wall -std=c++17 -framework sfml-window -framework sfml-graphics -framework sfml-system
//                   src/main.cpp -o main
//
// Date Created: 
// Date Modified: 
//
// Description: 
//
//**********************************************



#include <SFML/Graphics.hpp>
#include <chrono>
#include "presentation.hpp"

int main(int argc, const char* argv[]){

    // NOTE:
    // Using sf::VideoMode now requires sf::Vector2u(u_int, u_int) as the parameter
    // not sf::VideoMode(u_int, u_int)
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "Vision Therapy");

    window.setFramerateLimit(60);
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    
    // TODO: a better implementation of this
    // setPosition now requires sf::Vector2f(float, float) as the parameter
    shape.setPosition(sf::Vector2f(25.f, 275.f));
    //

    Presentation presentation(10.0f);
    // TODO: as transition between scenes is not quite yet working (Issue #9),
    //       we will only have one scene for now.
    //       Manually switch between scenes by commenting/uncommenting the lines below.
    //
    //presentation.addScene(Scene(std::make_unique<CircleAnimationSlide>(10.0f)));
    presentation.addScene(Scene(std::make_unique<RandomSpotAnimationSlide>(10.0f))); // This one is buggy (Issue #4)
    //

    presentation.runPresentation(window, shape);
    
    return 0;
}