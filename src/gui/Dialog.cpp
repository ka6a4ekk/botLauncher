#include "stdafx.h"
#include "Dialog.hpp"

#include "GuiCommon.hpp"

namespace gui
{
	Dialog::Dialog(float x, float y, float width, float height, sf::Font& font, const std::string& titleText, const std::string& messageText)
		: m_window(x, y, width, height, font, titleText)
		, m_message(font, messageText, 16)
		, m_messageOffset({10.f, 38.f})
	{
		m_message.setFillColor(sf::Color(220, 220, 220, 255));
		m_message.setPosition({x + m_messageOffset.x, y + m_messageOffset.y});
	}

	void Dialog::setMessageColor(const sf::Color& color)
	{
		m_message.setFillColor(color);
	}

	sf::Color Dialog::getMessageColor() const
	{
		return m_message.getFillColor();
	}

	void Dialog::setPosition(float x, float y)
	{
		m_window.setPosition(x, y);
		m_message.setPosition({x + m_messageOffset.x, y + m_messageOffset.y});
	}

	void Dialog::move(float dx, float dy)
	{
		m_window.move(dx, dy);
		m_message.move({dx, dy});
	}

	void Dialog::setSize(float width, float height)
	{
		m_window.setSize(width, height);
	}

	void Dialog::setScale(float scaleX, float scaleY)
	{
		m_window.setScale(scaleX, scaleY);
		m_message.setScale({scaleX, scaleY});
	}

	void Dialog::setFillColor(const sf::Color& color)
	{
		m_window.setFillColor(color);
	}

	sf::Color Dialog::getFillColor() const
	{
		return m_window.getFillColor();
	}

	void Dialog::setOutlineColor(const sf::Color& color)
	{
		m_window.setOutlineColor(color);
	}

	sf::Color Dialog::getOutlineColor() const
	{
		return m_window.getOutlineColor();
	}

	void Dialog::setOutlineThickness(float thickness)
	{
		m_window.setOutlineThickness(thickness);
	}

	float Dialog::getOutlineThickness() const
	{
		return m_window.getOutlineThickness();
	}

	void Dialog::setRotation(float degrees)
	{
		m_window.setRotation(degrees);
		m_message.setRotation(sf::degrees(degrees));
	}

	float Dialog::getRotation() const
	{
		return m_window.getRotation();
	}

	void Dialog::setOpacity(std::uint8_t alpha)
	{
		m_opacity = alpha;
		m_window.setOpacity(alpha);
		m_message.setFillColor(detail::withAlpha(m_message.getFillColor(), alpha));
	}

	std::uint8_t Dialog::getOpacity() const
	{
		return m_window.getOpacity();
	}

	sf::Vector2f Dialog::getPosition() const
	{
		return m_window.getPosition();
	}

	sf::Vector2f Dialog::getSize() const
	{
		return m_window.getSize();
	}

	sf::Vector2f Dialog::getScale() const
	{
		return m_window.getScale();
	}

	sf::FloatRect Dialog::getBounds() const
	{
		return m_window.getBounds();
	}

	void Dialog::render(sf::RenderTarget& target)
	{
		if (!m_visible)
			return;
		m_window.render(target);
		target.draw(m_message);
	}
}
