#include "stdafx.h"
#include "Image.hpp"

#include "GuiCommon.hpp"

namespace gui
{
	Image::Image(float x, float y, sf::Texture& texture, const sf::IntRect& rect)
		: m_sprite(texture)
		, m_outlineVisible(false)
	{
		if (rect.size.x > 0 && rect.size.y > 0)
			m_sprite.setTextureRect(rect);
		m_sprite.setPosition({x, y});
		const auto bounds = m_sprite.getGlobalBounds();
		m_outline.setPosition(bounds.position);
		m_outline.setSize(bounds.size);
		m_outline.setFillColor(sf::Color::Transparent);
		m_outline.setOutlineThickness(0.f);
		m_outline.setOutlineColor(sf::Color::Transparent);
	}

	void Image::setPosition(float x, float y)
	{
		m_sprite.setPosition({x, y});
		m_outline.setPosition({x, y});
	}

	void Image::move(float dx, float dy)
	{
		m_sprite.move({dx, dy});
		m_outline.move({dx, dy});
	}

	void Image::setSize(float width, float height)
	{
		const auto rect = m_sprite.getTextureRect();
		if (rect.size.x == 0 || rect.size.y == 0)
			return;
		m_sprite.setScale({width / static_cast<float>(rect.size.x), height / static_cast<float>(rect.size.y)});
		m_outline.setSize({width, height});
	}

	void Image::setScale(float scaleX, float scaleY)
	{
		m_sprite.setScale({scaleX, scaleY});
		m_outline.setScale({scaleX, scaleY});
	}

	void Image::setFillColor(const sf::Color& color)
	{
		m_sprite.setColor(color);
	}

	sf::Color Image::getFillColor() const
	{
		return m_sprite.getColor();
	}

	void Image::setOutlineColor(const sf::Color& color)
	{
		m_outline.setOutlineColor(color);
		m_outlineVisible = (color.a > 0 || m_outline.getOutlineThickness() > 0.f);
	}

	sf::Color Image::getOutlineColor() const
	{
		return m_outline.getOutlineColor();
	}

	void Image::setOutlineThickness(float thickness)
	{
		m_outline.setOutlineThickness(thickness);
		m_outlineVisible = (m_outline.getOutlineColor().a > 0 || thickness > 0.f);
	}

	float Image::getOutlineThickness() const
	{
		return m_outline.getOutlineThickness();
	}

	void Image::setRotation(float degrees)
	{
		m_sprite.setRotation(sf::degrees(degrees));
		m_outline.setRotation(sf::degrees(degrees));
	}

	float Image::getRotation() const
	{
		return m_sprite.getRotation().asDegrees();
	}

	void Image::setOpacity(std::uint8_t alpha)
	{
		m_opacity = alpha;
		m_sprite.setColor(detail::withAlpha(m_sprite.getColor(), alpha));
		m_outline.setOutlineColor(detail::withAlpha(m_outline.getOutlineColor(), alpha));
	}

	std::uint8_t Image::getOpacity() const
	{
		return m_sprite.getColor().a;
	}

	sf::Vector2f Image::getPosition() const
	{
		return m_sprite.getPosition();
	}

	sf::Vector2f Image::getSize() const
	{
		return m_sprite.getGlobalBounds().size;
	}

	sf::Vector2f Image::getScale() const
	{
		return m_sprite.getScale();
	}

	sf::FloatRect Image::getBounds() const
	{
		return m_sprite.getGlobalBounds();
	}

	void Image::render(sf::RenderTarget& target)
	{
		if (!m_visible)
			return;
		target.draw(m_sprite);
		if (m_outlineVisible)
			target.draw(m_outline);
	}
}
