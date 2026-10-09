#include "stdafx.h"
#include "Button.hpp"

#include "GuiCommon.hpp"

namespace gui
{
	Button::Button(float x, float y, float width, float height, sf::Font& font, std::string text, unsigned characterSize, sf::Color textIdleColor,
		sf::Color textHoverColor, sf::Color textActiveColor, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, 
		sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor, unsigned short id)
		: m_buttonState(ButtonState::IDLE)
		, m_id(id)
		, m_toggleMode(false)
		, m_toggled(false)
		, m_justPressed(false)
		, m_font(font)
		, m_text(font, text, characterSize)
		, m_textIdleColor(textIdleColor)
		, m_textHoverColor(textHoverColor)
		, m_textActiveColor(textActiveColor)
		, m_idleColor(idleColor)
		, m_hoverColor(hoverColor)
		, m_activeColor(activeColor)
		, m_outlineIdleColor(outlineIdleColor)
		, m_outlineHoverColor(outlineHoverColor)
		, m_outlineActiveColor(outlineActiveColor)
	{
		m_shape.setPosition({x, y});
		m_shape.setSize({width, height});
		m_shape.setFillColor(m_idleColor);
		m_shape.setOutlineThickness(1.f);
		m_shape.setOutlineColor(m_outlineIdleColor);

		m_text.setFillColor(m_textIdleColor);
		updateTextPosition();
	}

	const bool Button::isPressed() const
	{
		return m_justPressed;
	}

	const std::string Button::getText() const
	{
		return m_text.getString();
	}

	const unsigned short& Button::getId() const
	{
		return m_id;
	}

	void Button::setText(const std::string text)
	{
		m_text.setString(text);
		updateTextPosition();
	}

	void Button::setId(const unsigned short id)
	{
		m_id = id;
	}

	void Button::setToggleMode(bool enabled)
	{
		m_toggleMode = enabled;
	}

	bool Button::isToggleMode() const
	{
		return m_toggleMode;
	}

	void Button::setToggled(bool toggled)
	{
		m_toggled = toggled;
		applyDisplayColors();
	}

	bool Button::isToggled() const
	{
		return m_toggled;
	}

	void Button::setTextIdleColor(const sf::Color& color)
	{
		m_textIdleColor = color;
		applyDisplayColors();
	}

	void Button::setTextHoverColor(const sf::Color& color)
	{
		m_textHoverColor = color;
		applyDisplayColors();
	}

	void Button::setTextActiveColor(const sf::Color& color)
	{
		m_textActiveColor = color;
		applyDisplayColors();
	}

	sf::Color Button::getTextIdleColor() const
	{
		return m_textIdleColor;
	}

	sf::Color Button::getTextHoverColor() const
	{
		return m_textHoverColor;
	}

	sf::Color Button::getTextActiveColor() const
	{
		return m_textActiveColor;
	}

	void Button::setIdleColor(const sf::Color& color)
	{
		m_idleColor = color;
		applyDisplayColors();
	}

	void Button::setHoverColor(const sf::Color& color)
	{
		m_hoverColor = color;
		applyDisplayColors();
	}

	void Button::setActiveColor(const sf::Color& color)
	{
		m_activeColor = color;
		applyDisplayColors();
	}

	sf::Color Button::getIdleColor() const
	{
		return m_idleColor;
	}

	sf::Color Button::getHoverColor() const
	{
		return m_hoverColor;
	}

	sf::Color Button::getActiveColor() const
	{
		return m_activeColor;
	}

	void Button::setOutlineIdleColor(const sf::Color& color)
	{
		m_outlineIdleColor = color;
		applyDisplayColors();
	}

	void Button::setOutlineHoverColor(const sf::Color& color)
	{
		m_outlineHoverColor = color;
		applyDisplayColors();
	}

	void Button::setOutlineActiveColor(const sf::Color& color)
	{
		m_outlineActiveColor = color;
		applyDisplayColors();
	}

	sf::Color Button::getOutlineIdleColor() const
	{
		return m_outlineIdleColor;
	}

	sf::Color Button::getOutlineHoverColor() const
	{
		return m_outlineHoverColor;
	}

	sf::Color Button::getOutlineActiveColor() const
	{
		return m_outlineActiveColor;
	}

	void Button::setPosition(float x, float y)
	{
		m_shape.setPosition({x, y});
		updateTextPosition();
	}

	void Button::move(float dx, float dy)
	{
		m_shape.move({dx, dy});
		m_text.move({dx, dy});
	}

	void Button::setSize(float width, float height)
	{
		m_shape.setSize({width, height});
		updateTextPosition();
	}

	void Button::setScale(float scaleX, float scaleY)
	{
		m_shape.setScale({scaleX, scaleY});
		m_text.setScale({scaleX, scaleY});
		updateTextPosition();
	}

	void Button::setFillColor(const sf::Color& color)
	{
		m_idleColor = color;
		m_hoverColor = color;
		m_activeColor = color;
		applyDisplayColors();
	}

	sf::Color Button::getFillColor() const
	{
		return m_shape.getFillColor();
	}

	void Button::setOutlineColor(const sf::Color& color)
	{
		m_outlineIdleColor = color;
		m_outlineHoverColor = color;
		m_outlineActiveColor = color;
		applyDisplayColors();
	}

	sf::Color Button::getOutlineColor() const
	{
		return m_shape.getOutlineColor();
	}

	void Button::setOutlineThickness(float thickness)
	{
		m_shape.setOutlineThickness(thickness);
	}

	float Button::getOutlineThickness() const
	{
		return m_shape.getOutlineThickness();
	}

	void Button::setRotation(float degrees)
	{
		m_shape.setRotation(sf::degrees(degrees));
		m_text.setRotation(sf::degrees(degrees));
	}

	float Button::getRotation() const
	{
		return m_shape.getRotation().asDegrees();
	}

	void Button::setOpacity(std::uint8_t alpha)
	{
		m_opacity = alpha;
		m_shape.setFillColor(detail::withAlpha(m_shape.getFillColor(), alpha));
		m_shape.setOutlineColor(detail::withAlpha(m_shape.getOutlineColor(), alpha));
		m_text.setFillColor(detail::withAlpha(m_text.getFillColor(), alpha));
	}

	std::uint8_t Button::getOpacity() const
	{
		return m_shape.getFillColor().a;
	}

	sf::Vector2f Button::getPosition() const
	{
		return m_shape.getPosition();
	}

	sf::Vector2f Button::getSize() const
	{
		return m_shape.getGlobalBounds().size;
	}

	sf::Vector2f Button::getScale() const
	{
		return m_shape.getScale();
	}

	sf::FloatRect Button::getBounds() const
	{
		return m_shape.getGlobalBounds();
	}

	void Button::updateTextPosition()
	{
		const auto bounds = m_text.getLocalBounds();
		const auto shapeBounds = m_shape.getGlobalBounds();
		const float lineSpacing = m_font.get().getLineSpacing(m_text.getCharacterSize());

		const float centeredX = shapeBounds.position.x + (shapeBounds.size.x - bounds.size.x) * 0.5f - bounds.position.x;
		const float centeredY = shapeBounds.position.y + (shapeBounds.size.y - lineSpacing) * 0.75f - bounds.position.y;

		m_text.setPosition({std::round(centeredX), std::round(centeredY)}); //to prevent blur
	}

	void Button::applyDisplayColors()
	{
		ButtonState displayState = m_buttonState;
		if(m_toggleMode && m_toggled && displayState == ButtonState::IDLE)
			displayState = ButtonState::ACTIVATE;

		switch (displayState)
		{
		case ButtonState::IDLE:
			m_shape.setFillColor(m_idleColor);
			m_text.setFillColor(m_textIdleColor);
			m_shape.setOutlineColor(m_outlineIdleColor);
			break;

		case ButtonState::HOVER:
			m_shape.setFillColor(m_hoverColor);
			m_text.setFillColor(m_textHoverColor);
			m_shape.setOutlineColor(m_outlineHoverColor);
			break;

		case ButtonState::ACTIVATE:
			m_shape.setFillColor(m_activeColor);
			m_text.setFillColor(m_textActiveColor);
			m_shape.setOutlineColor(m_outlineActiveColor);
			break;
		}
	}

	void Button::update(const sf::Vector2i& mousePosWindow, const float)
	{
		if (!m_enabled)
			return;
		const ButtonState prevState = m_buttonState;
		m_justPressed = false;
		m_buttonState = ButtonState::IDLE;

		if (m_shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			m_buttonState = ButtonState::HOVER;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				m_buttonState = ButtonState::ACTIVATE;
		}

		if (prevState != ButtonState::ACTIVATE && m_buttonState == ButtonState::ACTIVATE)
			m_justPressed = true;

		if(m_toggleMode && prevState != ButtonState::ACTIVATE && m_buttonState == ButtonState::ACTIVATE)
			m_toggled = !m_toggled;

		applyDisplayColors();
	}

	void Button::render(sf::RenderTarget& target)
	{
		if (!m_visible)
			return;
		target.draw(m_shape);
		target.draw(m_text);
	}
}
