#pragma once

#include "AppStateId.hpp"
#include "gui/Button.hpp"
#include "gui/Panel.hpp"

#include <SFML/Graphics.hpp>

#include <functional>
#include <memory>
#include <optional>
#include <vector>

class TopPanel
{
public:
	explicit TopPanel(sf::RenderWindow& window);

	void update(float dt);
	void render(sf::RenderTarget& target);
	std::optional<AppStateId> takeRequestedState();
	void setActiveState(AppStateId stateId);

private:
	struct Tab
	{
		std::unique_ptr<gui::Button> button;
		AppStateId id;
	};

	sf::RenderWindow& m_window;
	sf::Font m_font;
	std::unique_ptr<gui::Panel> m_panel;
	std::vector<Tab> m_tabs;
	std::vector<std::function<void()>> m_tabActions;
	std::unique_ptr<gui::Button> m_startButton;
	std::function<void()> m_startAction;
	float m_padding;
	float m_height;
	std::optional<AppStateId> m_requestedState;

	void layout();
};
