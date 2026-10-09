#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>

#include "State.hpp"

class StateStack
{
public:
    explicit StateStack(State::Context context);
    ~StateStack() = default;

    void handleEvent(const sf::Event& event);
    void update(sf::Time dt);
    void render();

    void push(State::Ptr state);
    void pop();
    void clear();

    bool empty() const noexcept;
    State& top();
    const State& top() const;

private:
    std::stack<State::Ptr> mStack;
    State::Context mContext;
};
