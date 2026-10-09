#pragma once

#include <SFML/Graphics.hpp>
#include "StateStack.hpp"

class Engine
{
public:
    Engine();
    ~Engine() = default;

    void run();

private:
    void handleEvents();
    void update(sf::Time dt);
    void render();

private:
    sf::RenderWindow mWindow;
    StateStack mStateStack;
};
