#include "stdafx.h"
#include "Label.hpp"

#include "GuiCommon.hpp"

namespace gui
{
	Label::Label(sf::Font& font, const std::string& value, unsigned characterSize, sf::Color color)
		: m_text(font, value, characterSize)
	{
		m_text.setPosition({0.f, 0.f});
		m_text.setFillColor(color);
	}

	Label::Label(float x, float y, const std::string& value, sf::Font& font, unsigned characterSize, sf::Color color)
		: m_text(font, value, characterSize)
	{
		m_text.setPosition({x, y});
		m_text.setFillColor(color);
	}

	void Label::setText(const std::string& value)
	{
		m_text.setString(value);
	}

	void Label::setString(const std::string& value)
	{
		setText(value);
	}

	void Label::setCharacterSize(unsigned characterSize)
	{
		m_text.setCharacterSize(characterSize);
	}

	void Label::setTextColor(const sf::Color& color)
	{
		m_text.setFillColor(color);
	}

	void Label::setPosition(float x, float y)
	{
		m_text.setPosition({x, y});
	}

	void Label::setPosition(const sf::Vector2f& position)
	{
		m_text.setPosition(position);
	}

	void Label::move(float dx, float dy)
	{
		m_text.move({dx, dy});
	}

	void Label::setScale(float scaleX, float scaleY)
	{
		m_text.setScale({scaleX, scaleY});
	}

	void Label::setFillColor(const sf::Color& color)
	{
		m_text.setFillColor(color);
	}

	sf::Color Label::getFillColor() const
	{
		return m_text.getFillColor();
	}

	void Label::setOutlineColor(const sf::Color& color)
	{
		m_text.setOutlineColor(color);
	}

	sf::Color Label::getOutlineColor() const
	{
		return m_text.getOutlineColor();
	}

	void Label::setOutlineThickness(float thickness)
	{
		m_text.setOutlineThickness(thickness);
	}

	float Label::getOutlineThickness() const
	{
		return m_text.getOutlineThickness();
	}

	void Label::setRotation(float degrees)
	{
		m_text.setRotation(sf::degrees(degrees));
	}

	float Label::getRotation() const
	{
		return m_text.getRotation().asDegrees();
	}

	void Label::setOpacity(std::uint8_t alpha)
	{
		m_opacity = alpha;
		m_text.setFillColor(detail::withAlpha(m_text.getFillColor(), alpha));
		m_text.setOutlineColor(detail::withAlpha(m_text.getOutlineColor(), alpha));
	}

	std::uint8_t Label::getOpacity() const
	{
		return m_text.getFillColor().a;
	}

	sf::Vector2f Label::getPosition() const
	{
		return m_text.getPosition();
	}

	sf::Vector2f Label::getSize() const
	{
		return m_text.getGlobalBounds().size;
	}

	sf::Vector2f Label::getScale() const
	{
		return m_text.getScale();
	}

	sf::FloatRect Label::getBounds() const
	{
		return m_text.getGlobalBounds();
	}

	void Label::render(sf::RenderTarget& target)
	{
		if (!m_visible)
			return;
		target.draw(m_text);
	}
}
