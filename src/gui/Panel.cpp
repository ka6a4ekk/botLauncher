#include "stdafx.h"
#include "Panel.hpp"

#include "GuiCommon.hpp"

namespace gui
{
	Panel::Panel(float x, float y, float width, float height, sf::Color fill, sf::Color outline, float outlineThickness)
	{
		m_shape.setPosition({x, y});
		m_shape.setSize({width, height});
		m_shape.setFillColor(fill);
		m_shape.setOutlineColor(outline);
		m_shape.setOutlineThickness(outlineThickness);
	}

	void Panel::setPosition(float x, float y)
	{
		m_shape.setPosition({x, y});
	}

	void Panel::move(float dx, float dy)
	{
		m_shape.move({dx, dy});
	}

	void Panel::setSize(float width, float height)
	{
		m_shape.setSize({width, height});
	}

	void Panel::setScale(float scaleX, float scaleY)
	{
		m_shape.setScale({scaleX, scaleY});
	}

	void Panel::setFillColor(const sf::Color& color)
	{
		m_shape.setFillColor(color);
	}

	sf::Color Panel::getFillColor() const
	{
		return m_shape.getFillColor();
	}

	void Panel::setOutlineColor(const sf::Color& color)
	{
		m_shape.setOutlineColor(color);
	}

	sf::Color Panel::getOutlineColor() const
	{
		return m_shape.getOutlineColor();
	}

	void Panel::setOutlineThickness(float thickness)
	{
		m_shape.setOutlineThickness(thickness);
	}

	float Panel::getOutlineThickness() const
	{
		return m_shape.getOutlineThickness();
	}

	void Panel::setRotation(float degrees)
	{
		m_shape.setRotation(sf::degrees(degrees));
	}

	float Panel::getRotation() const
	{
		return m_shape.getRotation().asDegrees();
	}

	void Panel::setOpacity(std::uint8_t alpha)
	{
		m_opacity = alpha;
		m_shape.setFillColor(detail::withAlpha(m_shape.getFillColor(), alpha));
		m_shape.setOutlineColor(detail::withAlpha(m_shape.getOutlineColor(), alpha));
	}

	std::uint8_t Panel::getOpacity() const
	{
		return m_shape.getFillColor().a;
	}

	sf::Vector2f Panel::getPosition() const
	{
		return m_shape.getPosition();
	}

	sf::Vector2f Panel::getSize() const
	{
		return m_shape.getGlobalBounds().size;
	}

	sf::Vector2f Panel::getScale() const
	{
		return m_shape.getScale();
	}

	sf::FloatRect Panel::getBounds() const
	{
		return m_shape.getGlobalBounds();
	}

	void Panel::render(sf::RenderTarget& target)
	{
		if (!m_visible)
			return;
		target.draw(m_shape);
	}
}
