#include "engine.h"
#include "slide.h"

void Engine::initVariables()
{
    this->window = nullptr;
    this->sfEvent = sf::Event();
    this->slides.push_back(new RandomSpotAnimationSlide());
    this->slides.push_back(new SideToSideCircleAnimationSlide());
    this->slides.push_back(new RandomSpotWithLineAnimationSlide());
    this->slides.push_back(new CountTilesAnimationSlide());
}

void Engine::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Eye Therapy");
    this->window->setFramerateLimit(60);
}

Engine::Engine()
{
    this->initVariables();
    this->initWindow();
    this->slides[currentSlide]->setup(this->window);
}

Engine::~Engine()
{
    for (auto slide : this->slides) {
        delete slide;
    }
    delete this->window;
}

const bool Engine::running() const
{
    return this->window->isOpen();
}

void Engine::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent)) {
            switch (this->sfEvent.type)
            {
            case sf::Event::KeyPressed:
                if (this->sfEvent.key.code == sf::Keyboard::Q)
                    this->window->close();
                if (this->sfEvent.key.code == sf::Keyboard::N)
                    this->nextSlide();
                break;
            case sf::Event::Closed:
                this->window->close();
                break;
            default:
                break;
            }
        }
}

void Engine::update()
{
    this->updateSFMLEvents();
}

void Engine::nextSlide()
{
    this->currentSlide++;
    if (this->currentSlide >= this->slides.size()) {
        this->currentSlide = 0;
    }
    this->slides[this->currentSlide]->setup(this->window);
}

void Engine::render()
{
    this->window->clear();
    
    // Current slide rendering happens here (performAction).
    // Each slide has a reference to the window, so it can render itself.
    // TODO: put in place a better way to deal with multiple references
    // to the window at closing time. Ditching raw pointers for `shared_ptr` might a way.
    this->slides[currentSlide]->performAction();
    //
    
    this->window->display();
}
