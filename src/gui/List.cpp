#include "stdafx.h"
#include "List.hpp"

#include "GuiCommon.hpp"

namespace gui
{
	List::List(float x, float y, float width, float height, float itemHeight, sf::Font& font, const std::vector<std::string>& items)
		: m_font(font)
		, m_items(items)
		, m_itemHeight(itemHeight)
		, m_selectedIndex(-1)
		, m_scroll01(0.f)
		, m_state(ButtonState::IDLE)
	{
		m_bounds.setPosition({x, y});
		m_bounds.setSize({width, height});
		m_bounds.setFillColor(sf::Color(30, 30, 30, 255));
		m_bounds.setOutlineThickness(1.f);
		m_bounds.setOutlineColor(sf::Color(120, 120, 120, 255));

		m_boundsIdleColor = m_bounds.getFillColor();
		m_boundsHoverColor = m_bounds.getFillColor();
		m_boundsActiveColor = m_bounds.getFillColor();
		m_outlineIdleColor = m_bounds.getOutlineColor();
		m_outlineHoverColor = m_bounds.getOutlineColor();
		m_outlineActiveColor = m_bounds.getOutlineColor();
		m_textIdleColor = sf::Color(230, 230, 230, 255);
		m_textHoverColor = m_textIdleColor;
		m_textActiveColor = m_textIdleColor;
		m_highlightIdleColor = sf::Color(50, 50, 50, 200);
		m_highlightHoverColor = m_highlightIdleColor;
		m_highlightActiveColor = m_highlightIdleColor;
	}

	void List::addItem(const std::string& item)
	{
		m_items.push_back(item);
	}

	void List::clear()
	{
		m_items.clear();
		m_selectedIndex = -1;
		m_scroll01 = 0.f;
	}

	void List::setItems(const std::vector<std::string>& items)
	{
		m_items = items;
		if (m_selectedIndex >= static_cast<int>(m_items.size()))
			m_selectedIndex = -1;
	}

	void List::setScroll(float t01)
	{
		if (t01 < 0.f) t01 = 0.f;
		if (t01 > 1.f) t01 = 1.f;
		m_scroll01 = t01;
	}

	const int List::getSelectedIndex() const
	{
		return m_selectedIndex;
	}

	void List::setSelectedIndex(int index)
	{
		if (index < -1 || index >= static_cast<int>(m_items.size()))
			return;
		m_selectedIndex = index;
	}

	int List::hitTest(const sf::Vector2f& pos) const
	{
		if (!m_bounds.getGlobalBounds().contains(pos))
			return -1;

		const float localY = pos.y - m_bounds.getPosition().y;
		const int visibleCount = static_cast<int>(m_bounds.getSize().y / m_itemHeight);
		const int maxStart = std::max(0, static_cast<int>(m_items.size()) - visibleCount);
		const int startIndex = static_cast<int>(std::round(maxStart * m_scroll01));
		const int index = startIndex + static_cast<int>(localY / m_itemHeight);
		if (index < 0 || index >= static_cast<int>(m_items.size()))
			return -1;
		return index;
	}

	int List::getItemCount() const
	{
		return static_cast<int>(m_items.size());
	}

	float List::getItemHeight() const
	{
		return m_itemHeight;
	}

	const std::string& List::getItem(std::size_t index) const
	{
		return m_items.at(index);
	}

	void List::setBoundsIdleColor(const sf::Color& color)
	{
		m_boundsIdleColor = color;
		applyDisplayColors();
	}

	void List::setBoundsHoverColor(const sf::Color& color)
	{
		m_boundsHoverColor = color;
		applyDisplayColors();
	}

	void List::setBoundsActiveColor(const sf::Color& color)
	{
		m_boundsActiveColor = color;
		applyDisplayColors();
	}

	sf::Color List::getBoundsIdleColor() const
	{
		return m_boundsIdleColor;
	}

	sf::Color List::getBoundsHoverColor() const
	{
		return m_boundsHoverColor;
	}

	sf::Color List::getBoundsActiveColor() const
	{
		return m_boundsActiveColor;
	}

	void List::setOutlineIdleColor(const sf::Color& color)
	{
		m_outlineIdleColor = color;
		applyDisplayColors();
	}

	void List::setOutlineHoverColor(const sf::Color& color)
	{
		m_outlineHoverColor = color;
		applyDisplayColors();
	}

	void List::setOutlineActiveColor(const sf::Color& color)
	{
		m_outlineActiveColor = color;
		applyDisplayColors();
	}

	sf::Color List::getOutlineIdleColor() const
	{
		return m_outlineIdleColor;
	}

	sf::Color List::getOutlineHoverColor() const
	{
		return m_outlineHoverColor;
	}

	sf::Color List::getOutlineActiveColor() const
	{
		return m_outlineActiveColor;
	}

	void List::setTextIdleColor(const sf::Color& color)
	{
		m_textIdleColor = color;
	}

	void List::setTextHoverColor(const sf::Color& color)
	{
		m_textHoverColor = color;
	}

	void List::setTextActiveColor(const sf::Color& color)
	{
		m_textActiveColor = color;
	}

	sf::Color List::getTextIdleColor() const
	{
		return m_textIdleColor;
	}

	sf::Color List::getTextHoverColor() const
	{
		return m_textHoverColor;
	}

	sf::Color List::getTextActiveColor() const
	{
		return m_textActiveColor;
	}

	void List::setHighlightIdleColor(const sf::Color& color)
	{
		m_highlightIdleColor = color;
	}

	void List::setHighlightHoverColor(const sf::Color& color)
	{
		m_highlightHoverColor = color;
	}

	void List::setHighlightActiveColor(const sf::Color& color)
	{
		m_highlightActiveColor = color;
	}

	sf::Color List::getHighlightIdleColor() const
	{
		return m_highlightIdleColor;
	}

	sf::Color List::getHighlightHoverColor() const
	{
		return m_highlightHoverColor;
	}

	sf::Color List::getHighlightActiveColor() const
	{
		return m_highlightActiveColor;
	}

	void List::setBoundsColor(const sf::Color& color)
	{
		m_boundsIdleColor = color;
		m_boundsHoverColor = color;
		m_boundsActiveColor = color;
		applyDisplayColors();
	}

	void List::setTextColor(const sf::Color& color)
	{
		m_textIdleColor = color;
		m_textHoverColor = color;
		m_textActiveColor = color;
	}

	void List::setHighlightColor(const sf::Color& color)
	{
		m_highlightIdleColor = color;
		m_highlightHoverColor = color;
		m_highlightActiveColor = color;
	}

	void List::setPosition(float x, float y)
	{
		m_bounds.setPosition({x, y});
	}

	void List::move(float dx, float dy)
	{
		m_bounds.move({dx, dy});
	}

	void List::setSize(float width, float height)
	{
		m_bounds.setSize({width, height});
	}

	void List::setScale(float scaleX, float scaleY)
	{
		m_bounds.setScale({scaleX, scaleY});
	}

	void List::setFillColor(const sf::Color& color)
	{
		setBoundsColor(color);
	}

	sf::Color List::getFillColor() const
	{
		return m_bounds.getFillColor();
	}

	void List::setOutlineColor(const sf::Color& color)
	{
		m_outlineIdleColor = color;
		m_outlineHoverColor = color;
		m_outlineActiveColor = color;
		applyDisplayColors();
	}

	sf::Color List::getOutlineColor() const
	{
		return m_bounds.getOutlineColor();
	}

	void List::setOutlineThickness(float thickness)
	{
		m_bounds.setOutlineThickness(thickness);
	}

	float List::getOutlineThickness() const
	{
		return m_bounds.getOutlineThickness();
	}

	void List::setRotation(float degrees)
	{
		m_bounds.setRotation(sf::degrees(degrees));
	}

	float List::getRotation() const
	{
		return m_bounds.getRotation().asDegrees();
	}

	void List::setOpacity(std::uint8_t alpha)
	{
		m_opacity = alpha;
		m_bounds.setFillColor(detail::withAlpha(m_bounds.getFillColor(), alpha));
		m_bounds.setOutlineColor(detail::withAlpha(m_bounds.getOutlineColor(), alpha));
	}

	std::uint8_t List::getOpacity() const
	{
		return m_bounds.getFillColor().a;
	}

	sf::Vector2f List::getPosition() const
	{
		return m_bounds.getPosition();
	}

	sf::Vector2f List::getSize() const
	{
		return m_bounds.getGlobalBounds().size;
	}

	sf::Vector2f List::getScale() const
	{
		return m_bounds.getScale();
	}

	sf::FloatRect List::getBounds() const
	{
		return m_bounds.getGlobalBounds();
	}

	void List::applyDisplayColors()
	{
		switch (m_state)
		{
		case ButtonState::IDLE:
			m_bounds.setFillColor(m_boundsIdleColor);
			m_bounds.setOutlineColor(m_outlineIdleColor);
			break;
		case ButtonState::HOVER:
			m_bounds.setFillColor(m_boundsHoverColor);
			m_bounds.setOutlineColor(m_outlineHoverColor);
			break;
		case ButtonState::ACTIVATE:
			m_bounds.setFillColor(m_boundsActiveColor);
			m_bounds.setOutlineColor(m_outlineActiveColor);
			break;
		}
	}

	void List::update(const sf::Vector2i& mousePosWindow, const float)
	{
		if (!m_enabled)
			return;
		const bool hovered = m_bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow));
		const bool pressed = hovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		if (pressed)
			m_state = ButtonState::ACTIVATE;
		else if (hovered)
			m_state = ButtonState::HOVER;
		else
			m_state = ButtonState::IDLE;

		applyDisplayColors();

		if (!hovered || !pressed)
			return;

		const float localY = static_cast<float>(mousePosWindow.y) - m_bounds.getPosition().y;
		const int visibleCount = static_cast<int>(m_bounds.getSize().y / m_itemHeight);
		const int maxStart = std::max(0, static_cast<int>(m_items.size()) - visibleCount);
		const int startIndex = static_cast<int>(std::round(maxStart * m_scroll01));
		const int index = startIndex + static_cast<int>(localY / m_itemHeight);
		if (index >= 0 && index < static_cast<int>(m_items.size()))
			m_selectedIndex = index;
	}

	void List::handleEvent(const sf::Event& event)
	{
		if(!m_enabled)
			return;

		if(const auto* wheel = event.getIf<sf::Event::MouseWheelScrolled>())
		{
			const sf::Vector2f position(static_cast<float>(wheel->position.x), static_cast<float>(wheel->position.y));
			if(!m_bounds.getGlobalBounds().contains(position))
				return;

			const int visibleCount = std::max(1, static_cast<int>(m_bounds.getSize().y / m_itemHeight));
			const int hiddenCount = std::max(0, static_cast<int>(m_items.size()) - visibleCount);
			if(hiddenCount == 0)
				return;

			const float scrollStep = 1.f / static_cast<float>(hiddenCount);
			setScroll(m_scroll01 - wheel->delta * scrollStep);
		}
	}


	void List::render(sf::RenderTarget& target)
	{
		if (!m_visible)
			return;
		target.draw(m_bounds);

		const int visibleCount = static_cast<int>(m_bounds.getSize().y / m_itemHeight);
		const int maxStart = std::max(0, static_cast<int>(m_items.size()) - visibleCount);
		const int startIndex = static_cast<int>(std::round(maxStart * m_scroll01));
		const int endIndex = std::min(static_cast<int>(m_items.size()), startIndex + visibleCount);

		float y = m_bounds.getPosition().y;
		for (int i = startIndex; i < endIndex; ++i)
		{
			if (i == m_selectedIndex)
			{
				sf::RectangleShape highlight({m_bounds.getSize().x, m_itemHeight});
				highlight.setPosition({m_bounds.getPosition().x, y});
				sf::Color highlightColor = m_highlightIdleColor;
				if (m_state == ButtonState::HOVER)
					highlightColor = m_highlightHoverColor;
				else if (m_state == ButtonState::ACTIVATE)
					highlightColor = m_highlightActiveColor;
				highlight.setFillColor(highlightColor);
				target.draw(highlight);
			}

			sf::Text line(m_font.get(), m_items[i], static_cast<unsigned>(m_itemHeight * 0.6f));
			sf::Color textColor = m_textIdleColor;
			if (m_state == ButtonState::HOVER)
				textColor = m_textHoverColor;
			else if (m_state == ButtonState::ACTIVATE)
				textColor = m_textActiveColor;
			line.setFillColor(textColor);
			line.setPosition({m_bounds.getPosition().x + 6.f, y + 2.f});
			target.draw(line);
			y += m_itemHeight;
		}
	}
}
