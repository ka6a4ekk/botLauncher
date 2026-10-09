#include "Engine.hpp"

#include "AppStateId.hpp"
#include "ConfigParser.hpp"
#include "TopPanel.hpp"
#include "states/GeneralSettingsState.hpp"
#include "states/RotationState.hpp"

#include <cstdlib>
#include <memory>
#include <unordered_map>

namespace
{
std::unique_ptr<TopPanel> g_topPanel;

int getCvarInt(const std::unordered_map<std::string, std::string>& cvars, const std::string& name, int fallback)
{
	const auto it = cvars.find(name);
	if (it == cvars.end())
		return fallback;
	return std::atoi(it->second.c_str());
}

State::Context makeContext(sf::RenderWindow& window)
{
	return State::Context{&window};
}

void switchToState(StateStack& stateStack, sf::RenderWindow& window, AppStateId stateId)
{
	if (g_topPanel)
		g_topPanel->setActiveState(stateId);

	if (stateId == AppStateId::GeneralSettings)
	{
		if (stateStack.empty() || dynamic_cast<GeneralSettingsState*>(&stateStack.top()) == nullptr)
		{
			stateStack.clear();
			stateStack.push(std::make_unique<GeneralSettingsState>(stateStack, makeContext(window)));
		}
		return;
	}

	if (stateId == AppStateId::Rotation)
	{
		if (stateStack.empty() || dynamic_cast<RotationState*>(&stateStack.top()) == nullptr)
		{
			stateStack.clear();
			stateStack.push(std::make_unique<RotationState>(stateStack, makeContext(window)));
		}
	}
}
}

Engine::Engine()
	: mWindow(sf::VideoMode({1280u, 720u}), "Bot Launcher")
	, mStateStack(makeContext(mWindow))
{
	ConfigParser::Data config;
	ConfigParser parser;
	const auto loadResult = parser.load("config.cfg", config);
	if (loadResult == ConfigParser::LoadResult::MISSING) {}
	else if (loadResult == ConfigParser::LoadResult::ERROR) {}

	const int width = getCvarInt(config.m_cvars, "r_width", 1280);
	const int height = getCvarInt(config.m_cvars, "r_height", 720);
	const int fps = getCvarInt(config.m_cvars, "r_fps", 144);
	const int vsync = getCvarInt(config.m_cvars, "r_vsync", 0);

	sf::ContextSettings settings;
	mWindow.create(sf::VideoMode({static_cast<unsigned>(width), static_cast<unsigned>(height)}), "Bot Launcher", sf::State::Windowed, settings);
	mWindow.setFramerateLimit(static_cast<unsigned>(fps));
	mWindow.setVerticalSyncEnabled(vsync != 0);

	g_topPanel = std::make_unique<TopPanel>(mWindow);
	g_topPanel->setActiveState(AppStateId::GeneralSettings);
	switchToState(mStateStack, mWindow, AppStateId::GeneralSettings);
}

void Engine::run()
{
	sf::Clock clock;

	while (mWindow.isOpen() && !mStateStack.empty())
	{
		const sf::Time dt = clock.restart();
		handleEvents();
		update(dt);
		render();
	}
}

void Engine::handleEvents()
{
	while (const std::optional event = mWindow.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			mWindow.close();

		mStateStack.handleEvent(*event);
	}
}

void Engine::update(sf::Time dt)
{
	if (g_topPanel)
	{
		g_topPanel->update(dt.asSeconds());
		if (const auto requested = g_topPanel->takeRequestedState())
			switchToState(mStateStack, mWindow, *requested);
	}

	mStateStack.update(dt);
}

void Engine::render()
{
	mWindow.clear();
	mStateStack.render();
	if (g_topPanel)
		g_topPanel->render(mWindow);
	mWindow.display();
}