#include "stdafx.h"
#include "TextureSelector.hpp"

#include "GuiCommon.hpp"

namespace gui
{
	TextureSelector::TextureSelector(float x, float y, float width, float height,
		float gridSize, const sf::Texture& textureSheet,
		sf::Font& font, std::string text)
		: m_keytime(0.f)
		, m_keytimeMax(1.f)
		, m_gridSize(gridSize)
		, m_active(false)
		, m_hidden(false)
		, m_hideButton(nullptr)
		, m_sheet(textureSheet)
	{
		float offset = gridSize;

		m_bounds.setSize(sf::Vector2f(width, height));
		m_bounds.setPosition({x + offset, y});
		m_bounds.setFillColor(sf::Color(50, 50, 50, 100));
		m_bounds.setOutlineThickness(1.f);
		m_bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

		m_sheet.setPosition({x + offset, y});

		if (m_sheet.getGlobalBounds().size.x > m_bounds.getGlobalBounds().size.x)
		{
			m_sheet.setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(m_bounds.getGlobalBounds().size.x), static_cast<int>(m_sheet.getGlobalBounds().size.y)}));
		}
		if (m_sheet.getGlobalBounds().size.y > m_bounds.getGlobalBounds().size.y)
		{
			m_sheet.setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(m_sheet.getGlobalBounds().size.x), static_cast<int>(m_bounds.getGlobalBounds().size.y)}));
		}

		m_selector.setPosition({x + offset, y});
		m_selector.setSize(sf::Vector2f(gridSize, gridSize));
		m_selector.setFillColor(sf::Color::Transparent);
		m_selector.setOutlineThickness(1.f);
		m_selector.setOutlineColor(sf::Color::Red);

		m_textureRect.size.x = static_cast<int>(gridSize);
		m_textureRect.size.y = static_cast<int>(gridSize);

		m_hideButton = std::make_unique<gui::Button>(
			y, x, 50.f, 50.f,
			font, text, 16,
			sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50),
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50)
		);
	}

	const bool& TextureSelector::getActive() const
	{
		return m_active;
	}

	const sf::IntRect& TextureSelector::getTextureRect() const
	{
		return m_textureRect;
	}

	const bool TextureSelector::getKeytime()
	{
		if (m_keytime >= m_keytimeMax)
		{
			m_keytime = 0.f;
			return true;
		}

		return false;
	}

	void TextureSelector::updateKeytime(const float& dt)
	{
		if (m_keytime < m_keytimeMax)
			m_keytime += 10.f * dt;
	}

	void TextureSelector::setSelectorFillColor(const sf::Color& color)
	{
		m_selector.setFillColor(color);
	}

	sf::Color TextureSelector::getSelectorFillColor() const
	{
		return m_selector.getFillColor();
	}

	void TextureSelector::setSelectorOutlineColor(const sf::Color& color)
	{
		m_selector.setOutlineColor(color);
	}

	sf::Color TextureSelector::getSelectorOutlineColor() const
	{
		return m_selector.getOutlineColor();
	}

	void TextureSelector::update(const sf::Vector2i& mousePosWindow, const float dt)
	{
		if (!m_enabled)
			return;
		updateKeytime(dt);
		m_hideButton->update(mousePosWindow);

		if (m_hideButton->isPressed() && getKeytime())
			m_hidden = !m_hidden;

		if (!m_hidden)
		{
			m_active = false;

			if (m_bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			{
				m_active = true;

				m_mousePosGrid.x = (mousePosWindow.x - static_cast<int>(m_bounds.getPosition().x)) / static_cast<unsigned>(m_gridSize);
				m_mousePosGrid.y = (mousePosWindow.y - static_cast<int>(m_bounds.getPosition().y)) / static_cast<unsigned>(m_gridSize);

				m_selector.setPosition({
					m_bounds.getPosition().x + m_mousePosGrid.x * m_gridSize,
					m_bounds.getPosition().y + m_mousePosGrid.y * m_gridSize
				});

				m_textureRect.position.x = static_cast<int>(m_selector.getPosition().x - m_bounds.getPosition().x);
				m_textureRect.position.y = static_cast<int>(m_selector.getPosition().y - m_bounds.getPosition().y);
			}
		}
	}

	void TextureSelector::render(sf::RenderTarget& target)
	{
		if (!m_visible)
			return;
		if (!m_hidden)
		{
			target.draw(m_bounds);
			target.draw(m_sheet);

			if (m_active)
				target.draw(m_selector);
		}

		m_hideButton->render(target);
	}

	void TextureSelector::setPosition(float x, float y)
	{
		const auto current = m_bounds.getPosition();
		const float dx = x - current.x;
		const float dy = y - current.y;
		move(dx, dy);
	}

	void TextureSelector::move(float dx, float dy)
	{
		m_bounds.move({dx, dy});
		m_sheet.move({dx, dy});
		m_selector.move({dx, dy});
		m_hideButton->move(dx, dy);
	}

	void TextureSelector::setSize(float width, float height)
	{
		m_bounds.setSize({width, height});
		if (m_sheet.getGlobalBounds().size.x > m_bounds.getGlobalBounds().size.x)
		{
			m_sheet.setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(m_bounds.getGlobalBounds().size.x), static_cast<int>(m_sheet.getGlobalBounds().size.y)}));
		}
		if (m_sheet.getGlobalBounds().size.y > m_bounds.getGlobalBounds().size.y)
		{
			m_sheet.setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(m_sheet.getGlobalBounds().size.x), static_cast<int>(m_bounds.getGlobalBounds().size.y)}));
		}
	}

	void TextureSelector::setScale(float scaleX, float scaleY)
	{
		m_bounds.setScale({scaleX, scaleY});
		m_sheet.setScale({scaleX, scaleY});
		m_selector.setScale({scaleX, scaleY});
		m_hideButton->setScale(scaleX, scaleY);
	}

	void TextureSelector::setFillColor(const sf::Color& color)
	{
		m_bounds.setFillColor(color);
	}

	sf::Color TextureSelector::getFillColor() const
	{
		return m_bounds.getFillColor();
	}

	void TextureSelector::setOutlineColor(const sf::Color& color)
	{
		m_bounds.setOutlineColor(color);
	}

	sf::Color TextureSelector::getOutlineColor() const
	{
		return m_bounds.getOutlineColor();
	}

	void TextureSelector::setOutlineThickness(float thickness)
	{
		m_bounds.setOutlineThickness(thickness);
	}

	float TextureSelector::getOutlineThickness() const
	{
		return m_bounds.getOutlineThickness();
	}

	void TextureSelector::setRotation(float degrees)
	{
		m_bounds.setRotation(sf::degrees(degrees));
		m_sheet.setRotation(sf::degrees(degrees));
		m_selector.setRotation(sf::degrees(degrees));
	}

	float TextureSelector::getRotation() const
	{
		return m_bounds.getRotation().asDegrees();
	}

	void TextureSelector::setOpacity(std::uint8_t alpha)
	{
		m_opacity = alpha;
		m_bounds.setFillColor(detail::withAlpha(m_bounds.getFillColor(), alpha));
		m_bounds.setOutlineColor(detail::withAlpha(m_bounds.getOutlineColor(), alpha));
		m_selector.setOutlineColor(detail::withAlpha(m_selector.getOutlineColor(), alpha));
	}

	std::uint8_t TextureSelector::getOpacity() const
	{
		return m_bounds.getFillColor().a;
	}

	sf::Vector2f TextureSelector::getPosition() const
	{
		return m_bounds.getPosition();
	}

	sf::Vector2f TextureSelector::getSize() const
	{
		return m_bounds.getGlobalBounds().size;
	}

	sf::Vector2f TextureSelector::getScale() const
	{
		return m_bounds.getScale();
	}

	sf::FloatRect TextureSelector::getBounds() const
	{
		return m_bounds.getGlobalBounds();
	}
}
