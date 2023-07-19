#include <SFML/Graphics.hpp>
#include <chrono>

void animateCircle(sf::CircleShape& circleShape, sf::RenderWindow& renderWindow) {
    float speed = 1.0f;
    float x = circleShape.getPosition().x;
    float y = circleShape.getPosition().y;
    float radius = circleShape.getRadius();
    float windowWidth = renderWindow.getSize().x;
    float windowHeight = renderWindow.getSize().y;

    while (renderWindow.isOpen()) {
        sf::Event event;
        while (renderWindow.pollEvent(event) || true) {
            
            if (event.type == sf::Event::Closed) {
                renderWindow.close();
                break;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) {
                    renderWindow.close();
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
            circleShape.setPosition(x - circleShape.getRadius(), y + windowHeight / 2 - (circleShape.getRadius() * 1.5f));
            renderWindow.clear(sf::Color::Yellow);
            renderWindow.draw(circleShape);
            renderWindow.display();
        }
    }
}

void animateShapeRandomAppear(sf::CircleShape& circleShape, sf::RenderWindow& renderWindow) {
    
    while (renderWindow.isOpen()) {
        sf::Event event;
        while (renderWindow.pollEvent(event) || true) {
            
            if (event.type == sf::Event::Closed) {
                renderWindow.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::N) {
                    break;
                }
            }

            sf::Vector2f position = sf::Vector2f(rand() % 100, rand() % 100);
            float radius = circleShape.getRadius();

            if (position.x + radius > renderWindow.getSize().x) {
                position.x = renderWindow.getSize().x - radius;
            } else if (position.x - radius < 0) {
                position.x = radius;
            }
            if (position.y + radius > renderWindow.getSize().y) {
                position.y = renderWindow.getSize().y - radius;
            } else if (position.y - radius < 0) {
                position.y = radius;
            }
            circleShape.setPosition(position);

            renderWindow.clear(sf::Color::Yellow);
            
            static auto lastTime = std::chrono::high_resolution_clock::now();
            auto currentTime = std::chrono::high_resolution_clock::now();
            float elapsedSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count() / 1000.0f;
            if (elapsedSeconds < 1.0f) {
                renderWindow.draw(circleShape);
            }
            if (elapsedSeconds > 2.0f) {
                lastTime = currentTime;
            }
            
            renderWindow.display();
        }
        break;
    }

}



int main(int argc, char ** argv){
  sf::RenderWindow renderWindow(sf::VideoMode(1920, 1080), "Demo Game");
  
  sf::CircleShape circleShape(100);
  circleShape.setFillColor(sf::Color::Blue);

  animateShapeRandomAppear(circleShape, renderWindow);
  animateCircle(circleShape, renderWindow);

  return 0;
}