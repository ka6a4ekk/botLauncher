#include "stdafx.h"
#include "TopPanel.hpp"

#include <iostream>
#include <stdexcept>

static const sf::Color kPanelColor(25, 25, 26);
static const sf::Color kPanelOutline(54, 54, 54);

static const sf::Color kTextIdle(230, 230, 230, 255);
static const sf::Color kTextHover(255, 255, 255, 255);
static const sf::Color kTextActive(255, 255, 255, 255);

static const sf::Color kButtonIdle(42, 42, 42, 255);
static const sf::Color kButtonHover(54, 54, 54, 255);
static const sf::Color kButtonActive(70, 70, 70, 255);

static const sf::Color kButtonOutlineIdle(60, 60, 60, 255);
static const sf::Color kButtonOutlineHover(90, 90, 90, 255);
static const sf::Color kButtonOutlineActive(120, 120, 120, 255);

static constexpr unsigned kFontSize = 16;

static std::unique_ptr<gui::Button> makeButton(sf::Font& font, const std::string& text)
{
	return std::make_unique<gui::Button>(
		0.f, 0.f, 10.f, 10.f,
		font, text, kFontSize,
		kTextIdle, kTextHover, kTextActive,
		kButtonIdle, kButtonHover, kButtonActive,
		kButtonOutlineIdle, kButtonOutlineHover, kButtonOutlineActive
	);
}

TopPanel::TopPanel(sf::RenderWindow& window)
	: m_window(window)
	, m_panel(nullptr)
	, m_startButton(nullptr)
	, m_padding(8.f)
	, m_height(48.f)
{
	if(!m_font.openFromFile("res/fonts/font.ttf"))
		throw std::runtime_error("Failed to load font: res/fonts/font.ttf");

	m_panel = std::make_unique<gui::Panel>(0.f, 0.f, 10.f, m_height, kPanelColor, kPanelOutline, 1.f);

	m_tabs.push_back({makeButton(m_font, "General"), AppStateId::GeneralSettings});
	m_tabs.push_back({makeButton(m_font, "Rotation"), AppStateId::Rotation});

	m_startButton = makeButton(m_font, "Start");
	m_startButton->setToggleMode(false);
	m_tabActions.clear();
	m_tabActions.reserve(m_tabs.size());
	m_startAction = []() {
		std::cout << "CALLBACK\n";
	};

	for(auto& tab : m_tabs)
	{
		tab.button->setToggleMode(true);
		m_tabActions.push_back([this, id = tab.id]() {
			setActiveState(id);
			m_requestedState = id;
		});
	}

	layout();
}

void TopPanel::layout()
{
	const auto size = m_window.getSize();
	const float width = static_cast<float>(size.x);

	m_panel->setPosition(0.f, 0.f);
	m_panel->setSize(width, m_height);

	const float buttonHeight = m_height - m_padding * 2.f;
	const float tabWidth = 160.f;
	const float gap = 8.f;
	const float y = m_padding;

	float x = m_padding;
	for(auto& tab : m_tabs)
	{
		tab.button->setPosition(x, y);
		tab.button->setSize(tabWidth, buttonHeight);
		x += tabWidth + gap;
	}

	const float startWidth = 120.f;
	float startX = width - m_padding - startWidth;
	if(startX < x)
		startX = x + gap;
	m_startButton->setPosition(startX, y);
	m_startButton->setSize(startWidth, buttonHeight);
}

void TopPanel::update(float dt)
{
	layout();

	const sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	for(std::size_t i = 0; i < m_tabs.size(); ++i)
	{
		m_tabs[i].button->update(mousePos);
		if(m_tabs[i].button->isPressed() && m_tabActions[i])
			m_tabActions[i]();
	}

	m_startButton->update(mousePos);
	if(m_startButton->isPressed() && m_startAction)
		m_startAction();
}

void TopPanel::render(sf::RenderTarget& target)
{
	m_panel->render(target);
	for(auto& tab : m_tabs)
		tab.button->render(target);
	m_startButton->render(target);
}

std::optional<AppStateId> TopPanel::takeRequestedState()
{
	const auto requested = m_requestedState;
	m_requestedState.reset();
	return requested;
}

void TopPanel::setActiveState(AppStateId stateId)
{
	for(auto& tab : m_tabs)
	{
		const bool active = tab.id == stateId;
		tab.button->setToggled(active);
	}
}
