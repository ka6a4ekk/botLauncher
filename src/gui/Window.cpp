#include "stdafx.h"
#include "Window.hpp"

#include "GuiCommon.hpp"

namespace gui
{
	Window::Window(float x, float y, float width, float height, sf::Font& font, const std::string& titleText)
		: m_title(font, titleText, 16)
	{
		m_frame.setPosition({x, y});
		m_frame.setSize({width, height});
		m_frame.setFillColor(sf::Color(40, 40, 40, 255));
		m_frame.setOutlineThickness(1.f);
		m_frame.setOutlineColor(sf::Color(160, 160, 160, 255));

		m_titleBar.setPosition({x, y});
		m_titleBar.setSize({width, 28.f});
		m_titleBar.setFillColor(sf::Color(60, 60, 60, 255));

		m_title.setFillColor(sf::Color(220, 220, 220, 255));
		m_title.setPosition({x + 8.f, y + 4.f});
	}

	void Window::setTitleBarColor(const sf::Color& color)
	{
		m_titleBar.setFillColor(color);
	}

	sf::Color Window::getTitleBarColor() const
	{
		return m_titleBar.getFillColor();
	}

	void Window::setTitleTextColor(const sf::Color& color)
	{
		m_title.setFillColor(color);
	}

	sf::Color Window::getTitleTextColor() const
	{
		return m_title.getFillColor();
	}

	void Window::setPosition(float x, float y)
	{
		m_frame.setPosition({x, y});
		m_titleBar.setPosition({x, y});
		m_title.setPosition({x + 8.f, y + 4.f});
	}

	void Window::move(float dx, float dy)
	{
		m_frame.move({dx, dy});
		m_titleBar.move({dx, dy});
		m_title.move({dx, dy});
	}

	void Window::setSize(float width, float height)
	{
		m_frame.setSize({width, height});
		m_titleBar.setSize({width, 28.f});
	}

	void Window::setScale(float scaleX, float scaleY)
	{
		m_frame.setScale({scaleX, scaleY});
		m_titleBar.setScale({scaleX, scaleY});
		m_title.setScale({scaleX, scaleY});
	}

	void Window::setFillColor(const sf::Color& color)
	{
		m_frame.setFillColor(color);
	}

	sf::Color Window::getFillColor() const
	{
		return m_frame.getFillColor();
	}

	void Window::setOutlineColor(const sf::Color& color)
	{
		m_frame.setOutlineColor(color);
	}

	sf::Color Window::getOutlineColor() const
	{
		return m_frame.getOutlineColor();
	}

	void Window::setOutlineThickness(float thickness)
	{
		m_frame.setOutlineThickness(thickness);
	}

	float Window::getOutlineThickness() const
	{
		return m_frame.getOutlineThickness();
	}

	void Window::setRotation(float degrees)
	{
		m_frame.setRotation(sf::degrees(degrees));
		m_titleBar.setRotation(sf::degrees(degrees));
		m_title.setRotation(sf::degrees(degrees));
	}

	float Window::getRotation() const
	{
		return m_frame.getRotation().asDegrees();
	}

	void Window::setOpacity(std::uint8_t alpha)
	{
		m_opacity = alpha;
		m_frame.setFillColor(detail::withAlpha(m_frame.getFillColor(), alpha));
		m_frame.setOutlineColor(detail::withAlpha(m_frame.getOutlineColor(), alpha));
		m_titleBar.setFillColor(detail::withAlpha(m_titleBar.getFillColor(), alpha));
		m_title.setFillColor(detail::withAlpha(m_title.getFillColor(), alpha));
	}

	std::uint8_t Window::getOpacity() const
	{
		return m_frame.getFillColor().a;
	}

	sf::Vector2f Window::getPosition() const
	{
		return m_frame.getPosition();
	}

	sf::Vector2f Window::getSize() const
	{
		return m_frame.getGlobalBounds().size;
	}

	sf::Vector2f Window::getScale() const
	{
		return m_frame.getScale();
	}

	sf::FloatRect Window::getBounds() const
	{
		return m_frame.getGlobalBounds();
	}

	void Window::render(sf::RenderTarget& target)
	{
		if (!m_visible)
			return;
		target.draw(m_frame);
		target.draw(m_titleBar);
		target.draw(m_title);
	}
}
