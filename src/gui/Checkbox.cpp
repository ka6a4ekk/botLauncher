#include "stdafx.h"
#include "Checkbox.hpp"

#include "GuiCommon.hpp"

namespace gui
{
	Checkbox::Checkbox(float x, float y, float size, sf::Font& font, const std::string& text, unsigned characterSize)
		: m_label(font, text, characterSize)
		, m_checked(false)
		, m_wasPressed(false)
		, m_state(ButtonState::IDLE)
	{
		m_box.setPosition({x, y});
		m_box.setSize({size, size});
		m_box.setFillColor(sf::Color(50, 50, 50, 200));
		m_box.setOutlineColor(sf::Color(200, 200, 200, 200));
		m_box.setOutlineThickness(1.f);

		m_check.setPosition({x + 4.f, y + 4.f});
		m_check.setSize({size - 8.f, size - 8.f});
		m_check.setFillColor(sf::Color(170, 170, 170, 220));

		m_label.setFillColor(sf::Color(220, 220, 220, 255));
		m_label.setPosition({x + size + 10.f, y - 2.f});

		m_boxIdleColor = m_box.getFillColor();
		m_boxHoverColor = m_box.getFillColor();
		m_boxActiveColor = m_box.getFillColor();
		m_outlineIdleColor = m_box.getOutlineColor();
		m_outlineHoverColor = m_box.getOutlineColor();
		m_outlineActiveColor = m_box.getOutlineColor();
		m_checkIdleColor = m_check.getFillColor();
		m_checkHoverColor = m_check.getFillColor();
		m_checkActiveColor = m_check.getFillColor();
		m_labelIdleColor = m_label.getFillColor();
		m_labelHoverColor = m_label.getFillColor();
		m_labelActiveColor = m_label.getFillColor();
	}

	const bool Checkbox::isChecked() const
	{
		return m_checked;
	}

	void Checkbox::setChecked(bool checked)
	{
		m_checked = checked;
	}

	void Checkbox::setBoxIdleColor(const sf::Color& color)
	{
		m_boxIdleColor = color;
		applyDisplayColors();
	}

	void Checkbox::setBoxHoverColor(const sf::Color& color)
	{
		m_boxHoverColor = color;
		applyDisplayColors();
	}

	void Checkbox::setBoxActiveColor(const sf::Color& color)
	{
		m_boxActiveColor = color;
		applyDisplayColors();
	}

	sf::Color Checkbox::getBoxIdleColor() const
	{
		return m_boxIdleColor;
	}

	sf::Color Checkbox::getBoxHoverColor() const
	{
		return m_boxHoverColor;
	}

	sf::Color Checkbox::getBoxActiveColor() const
	{
		return m_boxActiveColor;
	}

	void Checkbox::setOutlineIdleColor(const sf::Color& color)
	{
		m_outlineIdleColor = color;
		applyDisplayColors();
	}

	void Checkbox::setOutlineHoverColor(const sf::Color& color)
	{
		m_outlineHoverColor = color;
		applyDisplayColors();
	}

	void Checkbox::setOutlineActiveColor(const sf::Color& color)
	{
		m_outlineActiveColor = color;
		applyDisplayColors();
	}

	sf::Color Checkbox::getOutlineIdleColor() const
	{
		return m_outlineIdleColor;
	}

	sf::Color Checkbox::getOutlineHoverColor() const
	{
		return m_outlineHoverColor;
	}

	sf::Color Checkbox::getOutlineActiveColor() const
	{
		return m_outlineActiveColor;
	}

	void Checkbox::setCheckIdleColor(const sf::Color& color)
	{
		m_checkIdleColor = color;
		applyDisplayColors();
	}

	void Checkbox::setCheckHoverColor(const sf::Color& color)
	{
		m_checkHoverColor = color;
		applyDisplayColors();
	}

	void Checkbox::setCheckActiveColor(const sf::Color& color)
	{
		m_checkActiveColor = color;
		applyDisplayColors();
	}

	sf::Color Checkbox::getCheckIdleColor() const
	{
		return m_checkIdleColor;
	}

	sf::Color Checkbox::getCheckHoverColor() const
	{
		return m_checkHoverColor;
	}

	sf::Color Checkbox::getCheckActiveColor() const
	{
		return m_checkActiveColor;
	}

	void Checkbox::setLabelIdleColor(const sf::Color& color)
	{
		m_labelIdleColor = color;
		applyDisplayColors();
	}

	void Checkbox::setLabelHoverColor(const sf::Color& color)
	{
		m_labelHoverColor = color;
		applyDisplayColors();
	}

	void Checkbox::setLabelActiveColor(const sf::Color& color)
	{
		m_labelActiveColor = color;
		applyDisplayColors();
	}

	sf::Color Checkbox::getLabelIdleColor() const
	{
		return m_labelIdleColor;
	}

	sf::Color Checkbox::getLabelHoverColor() const
	{
		return m_labelHoverColor;
	}

	sf::Color Checkbox::getLabelActiveColor() const
	{
		return m_labelActiveColor;
	}

	void Checkbox::setBoxColor(const sf::Color& color)
	{
		m_boxIdleColor = color;
		m_boxHoverColor = color;
		m_boxActiveColor = color;
		applyDisplayColors();
	}

	void Checkbox::setCheckColor(const sf::Color& color)
	{
		m_checkIdleColor = color;
		m_checkHoverColor = color;
		m_checkActiveColor = color;
		applyDisplayColors();
	}

	void Checkbox::setLabelColor(const sf::Color& color)
	{
		m_labelIdleColor = color;
		m_labelHoverColor = color;
		m_labelActiveColor = color;
		applyDisplayColors();
	}

	void Checkbox::setPosition(float x, float y)
	{
		const auto size = m_box.getSize();
		m_box.setPosition({x, y});
		m_check.setPosition({x + 4.f, y + 4.f});
		m_label.setPosition({x + size.x + 10.f, y - 2.f});
	}

	void Checkbox::move(float dx, float dy)
	{
		m_box.move({dx, dy});
		m_check.move({dx, dy});
		m_label.move({dx, dy});
	}

	void Checkbox::setSize(float width, float height)
	{
		m_box.setSize({width, height});
		m_check.setSize({width - 8.f, height - 8.f});
		const auto pos = m_box.getPosition();
		m_check.setPosition({pos.x + 4.f, pos.y + 4.f});
	}

	void Checkbox::setScale(float scaleX, float scaleY)
	{
		m_box.setScale({scaleX, scaleY});
		m_check.setScale({scaleX, scaleY});
		m_label.setScale({scaleX, scaleY});
	}

	void Checkbox::setFillColor(const sf::Color& color)
	{
		setBoxColor(color);
	}

	sf::Color Checkbox::getFillColor() const
	{
		return m_box.getFillColor();
	}

	void Checkbox::setOutlineColor(const sf::Color& color)
	{
		m_outlineIdleColor = color;
		m_outlineHoverColor = color;
		m_outlineActiveColor = color;
		applyDisplayColors();
	}

	sf::Color Checkbox::getOutlineColor() const
	{
		return m_box.getOutlineColor();
	}

	void Checkbox::setOutlineThickness(float thickness)
	{
		m_box.setOutlineThickness(thickness);
	}

	float Checkbox::getOutlineThickness() const
	{
		return m_box.getOutlineThickness();
	}

	void Checkbox::setRotation(float degrees)
	{
		m_box.setRotation(sf::degrees(degrees));
		m_check.setRotation(sf::degrees(degrees));
		m_label.setRotation(sf::degrees(degrees));
	}

	float Checkbox::getRotation() const
	{
		return m_box.getRotation().asDegrees();
	}

	void Checkbox::setOpacity(std::uint8_t alpha)
	{
		m_opacity = alpha;
		m_box.setFillColor(detail::withAlpha(m_box.getFillColor(), alpha));
		m_box.setOutlineColor(detail::withAlpha(m_box.getOutlineColor(), alpha));
		m_check.setFillColor(detail::withAlpha(m_check.getFillColor(), alpha));
		m_label.setFillColor(detail::withAlpha(m_label.getFillColor(), alpha));
	}

	std::uint8_t Checkbox::getOpacity() const
	{
		return m_box.getFillColor().a;
	}

	sf::Vector2f Checkbox::getPosition() const
	{
		return m_box.getPosition();
	}

	sf::Vector2f Checkbox::getSize() const
	{
		return m_box.getGlobalBounds().size;
	}

	sf::Vector2f Checkbox::getScale() const
	{
		return m_box.getScale();
	}

	sf::FloatRect Checkbox::getBounds() const
	{
		return m_box.getGlobalBounds();
	}

	void Checkbox::applyDisplayColors()
	{
		switch (m_state)
		{
		case ButtonState::IDLE:
			m_box.setFillColor(m_boxIdleColor);
			m_box.setOutlineColor(m_outlineIdleColor);
			m_check.setFillColor(m_checkIdleColor);
			m_label.setFillColor(m_labelIdleColor);
			break;
		case ButtonState::HOVER:
			m_box.setFillColor(m_boxHoverColor);
			m_box.setOutlineColor(m_outlineHoverColor);
			m_check.setFillColor(m_checkHoverColor);
			m_label.setFillColor(m_labelHoverColor);
			break;
		case ButtonState::ACTIVATE:
			m_box.setFillColor(m_boxActiveColor);
			m_box.setOutlineColor(m_outlineActiveColor);
			m_check.setFillColor(m_checkActiveColor);
			m_label.setFillColor(m_labelActiveColor);
			break;
		}
	}

	void Checkbox::update(const sf::Vector2i& mousePosWindow, const float)
	{
		if (!m_enabled)
			return;
		const bool hovered = m_box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow));
		const bool pressed = hovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

		if (pressed)
			m_state = ButtonState::ACTIVATE;
		else if (hovered)
			m_state = ButtonState::HOVER;
		else
			m_state = ButtonState::IDLE;

		if (pressed && !m_wasPressed)
			m_checked = !m_checked;
		m_wasPressed = pressed;

		applyDisplayColors();
	}

	void Checkbox::render(sf::RenderTarget& target)
	{
		if (!m_visible)
			return;
		target.draw(m_box);
		if (m_checked)
			target.draw(m_check);
		target.draw(m_label);
	}
}
