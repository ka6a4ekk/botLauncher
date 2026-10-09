#include "StateStack.hpp"

StateStack::StateStack(State::Context context)
    : mContext(context)
{
}

void StateStack::handleEvent(const sf::Event& event)
{
    if (!mStack.empty())
        mStack.top()->handleEvent(event);
}

void StateStack::update(sf::Time dt)
{
    if (!mStack.empty())
        mStack.top()->update(dt);
}

void StateStack::render()
{
    if (!mStack.empty())
        mStack.top()->render();
}

void StateStack::push(State::Ptr state)
{
    mStack.push(std::move(state));
}

void StateStack::pop()
{
    if (!mStack.empty())
        mStack.pop();
}

void StateStack::clear()
{
    while (!mStack.empty())
        mStack.pop();
}

bool StateStack::empty() const noexcept
{
    return mStack.empty();
}

State& StateStack::top()
{
    return *mStack.top();
}

const State& StateStack::top() const
{
    return *mStack.top();
}
