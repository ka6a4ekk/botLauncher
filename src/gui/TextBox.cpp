#include "stdafx.h"
#include "TextBox.hpp"

#include "GuiCommon.hpp"

namespace gui
{
	TextBox::TextBox(float x, float y, float width, float height, sf::Font& font, unsigned characterSize)
		: m_text(font, "", characterSize)
		, m_caret(font, "|", characterSize)
		, m_value("")
		, m_focused(false)
		, m_prevFocused(false)
		, m_caretVisible(false)
		, m_caretTimer(0.f)
		, m_caretPeriod(0.6f)
		, m_hovered(false)
	{
		m_box.setPosition({x, y});
		m_box.setSize({width, height});
		m_box.setFillColor(sf::Color(40, 40, 40, 255));
		m_box.setOutlineThickness(1.f);
		m_box.setOutlineColor(sf::Color(120, 120, 120, 255));

		m_text.setFillColor(sf::Color(230, 230, 230, 255));
		m_text.setPosition({x + 6.f, y + 4.f});
		m_caret.setFillColor(m_text.getFillColor());

		m_boxIdleColor = m_box.getFillColor();
		m_boxHoverColor = m_box.getFillColor();
		m_boxActiveColor = m_box.getFillColor();
		m_outlineIdleColor = m_box.getOutlineColor();
		m_outlineHoverColor = m_box.getOutlineColor();
		m_outlineActiveColor = m_box.getOutlineColor();
		m_textIdleColor = m_text.getFillColor();
		m_textHoverColor = m_text.getFillColor();
		m_textActiveColor = m_text.getFillColor();
		m_caretIdleColor = m_caret.getFillColor();
		m_caretHoverColor = m_caret.getFillColor();
		m_caretActiveColor = m_caret.getFillColor();
	}

	const std::string& TextBox::getValue() const
	{
		return m_value;
	}

	void TextBox::setValue(const std::string& value)
	{
		m_value = value;
		m_text.setString(m_value);
		m_caretVisible = true;
		m_caretTimer = 0.f;
	}

	void TextBox::setBoxIdleColor(const sf::Color& color)
	{
		m_boxIdleColor = color;
		applyDisplayColors();
	}

	void TextBox::setBoxHoverColor(const sf::Color& color)
	{
		m_boxHoverColor = color;
		applyDisplayColors();
	}

	void TextBox::setBoxActiveColor(const sf::Color& color)
	{
		m_boxActiveColor = color;
		applyDisplayColors();
	}

	sf::Color TextBox::getBoxIdleColor() const
	{
		return m_boxIdleColor;
	}

	sf::Color TextBox::getBoxHoverColor() const
	{
		return m_boxHoverColor;
	}

	sf::Color TextBox::getBoxActiveColor() const
	{
		return m_boxActiveColor;
	}

	void TextBox::setOutlineIdleColor(const sf::Color& color)
	{
		m_outlineIdleColor = color;
		applyDisplayColors();
	}

	void TextBox::setOutlineHoverColor(const sf::Color& color)
	{
		m_outlineHoverColor = color;
		applyDisplayColors();
	}

	void TextBox::setOutlineActiveColor(const sf::Color& color)
	{
		m_outlineActiveColor = color;
		applyDisplayColors();
	}

	sf::Color TextBox::getOutlineIdleColor() const
	{
		return m_outlineIdleColor;
	}

	sf::Color TextBox::getOutlineHoverColor() const
	{
		return m_outlineHoverColor;
	}

	sf::Color TextBox::getOutlineActiveColor() const
	{
		return m_outlineActiveColor;
	}

	void TextBox::setTextIdleColor(const sf::Color& color)
	{
		m_textIdleColor = color;
		applyDisplayColors();
	}

	void TextBox::setTextHoverColor(const sf::Color& color)
	{
		m_textHoverColor = color;
		applyDisplayColors();
	}

	void TextBox::setTextActiveColor(const sf::Color& color)
	{
		m_textActiveColor = color;
		applyDisplayColors();
	}

	sf::Color TextBox::getTextIdleColor() const
	{
		return m_textIdleColor;
	}

	sf::Color TextBox::getTextHoverColor() const
	{
		return m_textHoverColor;
	}

	sf::Color TextBox::getTextActiveColor() const
	{
		return m_textActiveColor;
	}

	void TextBox::setCaretIdleColor(const sf::Color& color)
	{
		m_caretIdleColor = color;
		applyDisplayColors();
	}

	void TextBox::setCaretHoverColor(const sf::Color& color)
	{
		m_caretHoverColor = color;
		applyDisplayColors();
	}

	void TextBox::setCaretActiveColor(const sf::Color& color)
	{
		m_caretActiveColor = color;
		applyDisplayColors();
	}

	sf::Color TextBox::getCaretIdleColor() const
	{
		return m_caretIdleColor;
	}

	sf::Color TextBox::getCaretHoverColor() const
	{
		return m_caretHoverColor;
	}

	sf::Color TextBox::getCaretActiveColor() const
	{
		return m_caretActiveColor;
	}

	void TextBox::setBoxColor(const sf::Color& color)
	{
		m_boxIdleColor = color;
		m_boxHoverColor = color;
		m_boxActiveColor = color;
		applyDisplayColors();
	}

	void TextBox::setTextColor(const sf::Color& color)
	{
		m_textIdleColor = color;
		m_textHoverColor = color;
		m_textActiveColor = color;
		applyDisplayColors();
	}

	void TextBox::setCaretColor(const sf::Color& color)
	{
		m_caretIdleColor = color;
		m_caretHoverColor = color;
		m_caretActiveColor = color;
		applyDisplayColors();
	}

	void TextBox::setPosition(float x, float y)
	{
		m_box.setPosition({x, y});
		m_text.setPosition({x + 6.f, y + 4.f});
	}

	void TextBox::move(float dx, float dy)
	{
		m_box.move({dx, dy});
		m_text.move({dx, dy});
	}

	void TextBox::setSize(float width, float height)
	{
		m_box.setSize({width, height});
	}

	void TextBox::setScale(float scaleX, float scaleY)
	{
		m_box.setScale({scaleX, scaleY});
		m_text.setScale({scaleX, scaleY});
		m_caret.setScale({scaleX, scaleY});
	}

	void TextBox::setFillColor(const sf::Color& color)
	{
		setBoxColor(color);
	}

	sf::Color TextBox::getFillColor() const
	{
		return m_box.getFillColor();
	}

	void TextBox::setOutlineColor(const sf::Color& color)
	{
		m_outlineIdleColor = color;
		m_outlineHoverColor = color;
		m_outlineActiveColor = color;
		applyDisplayColors();
	}

	sf::Color TextBox::getOutlineColor() const
	{
		return m_box.getOutlineColor();
	}

	void TextBox::setOutlineThickness(float thickness)
	{
		m_box.setOutlineThickness(thickness);
	}

	float TextBox::getOutlineThickness() const
	{
		return m_box.getOutlineThickness();
	}

	void TextBox::setRotation(float degrees)
	{
		m_box.setRotation(sf::degrees(degrees));
		m_text.setRotation(sf::degrees(degrees));
	}

	float TextBox::getRotation() const
	{
		return m_box.getRotation().asDegrees();
	}

	void TextBox::setOpacity(std::uint8_t alpha)
	{
		m_opacity = alpha;
		m_box.setFillColor(detail::withAlpha(m_box.getFillColor(), alpha));
		m_box.setOutlineColor(detail::withAlpha(m_box.getOutlineColor(), alpha));
		m_text.setFillColor(detail::withAlpha(m_text.getFillColor(), alpha));
		m_caret.setFillColor(detail::withAlpha(m_caret.getFillColor(), alpha));
	}

	std::uint8_t TextBox::getOpacity() const
	{
		return m_box.getFillColor().a;
	}

	sf::Vector2f TextBox::getPosition() const
	{
		return m_box.getPosition();
	}

	sf::Vector2f TextBox::getSize() const
	{
		return m_box.getGlobalBounds().size;
	}

	sf::Vector2f TextBox::getScale() const
	{
		return m_box.getScale();
	}

	sf::FloatRect TextBox::getBounds() const
	{
		return m_box.getGlobalBounds();
	}

	void TextBox::applyDisplayColors()
	{
		const ButtonState state = m_focused ? ButtonState::ACTIVATE : (m_hovered ? ButtonState::HOVER : ButtonState::IDLE);
		switch (state)
		{
		case ButtonState::IDLE:
			m_box.setFillColor(m_boxIdleColor);
			m_box.setOutlineColor(m_outlineIdleColor);
			m_text.setFillColor(m_textIdleColor);
			m_caret.setFillColor(m_caretIdleColor);
			break;
		case ButtonState::HOVER:
			m_box.setFillColor(m_boxHoverColor);
			m_box.setOutlineColor(m_outlineHoverColor);
			m_text.setFillColor(m_textHoverColor);
			m_caret.setFillColor(m_caretHoverColor);
			break;
		case ButtonState::ACTIVATE:
			m_box.setFillColor(m_boxActiveColor);
			m_box.setOutlineColor(m_outlineActiveColor);
			m_text.setFillColor(m_textActiveColor);
			m_caret.setFillColor(m_caretActiveColor);
			break;
		}
	}

	void TextBox::update(const sf::Vector2i& mousePosWindow, const float dt)
	{
		if (!m_enabled)
			return;
		const bool hovered = m_box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow));
		m_hovered = hovered;
		if (hovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			m_focused = true;
		else if (!hovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			m_focused = false;

		if (m_focused != m_prevFocused)
		{
			m_caretTimer = 0.f;
			m_caretVisible = m_focused;
			m_prevFocused = m_focused;
		}

		if (m_focused && dt > 0.f)
		{
			m_caretTimer += dt;
			if (m_caretTimer >= m_caretPeriod)
			{
				m_caretTimer = 0.f;
				m_caretVisible = !m_caretVisible;
			}
		}

		applyDisplayColors();
	}

	void TextBox::handleEvent(const sf::Event& event)
	{
		if (!m_focused || !m_enabled)
			return;

		if (event.is<sf::Event::TextEntered>())
		{
			const auto* textEntered = event.getIf<sf::Event::TextEntered>();
			if (!textEntered)
				return;
			if (textEntered->unicode == 8)
			{
				if (!m_value.empty())
					m_value.pop_back();
			}
			else if (textEntered->unicode >= 32 && textEntered->unicode < 127)
			{
				m_value.push_back(static_cast<char>(textEntered->unicode));
			}
			m_text.setString(m_value);
			m_caretTimer = 0.f;
			m_caretVisible = true;
		}
	}

	void TextBox::render(sf::RenderTarget& target)
	{
		if (!m_visible)
			return;
		target.draw(m_box);
		target.draw(m_text);
		if (m_focused && m_caretVisible)
		{
			const sf::FloatRect textBounds = m_text.getLocalBounds();
			const sf::Vector2f textPos = m_text.getPosition();
			m_caret.setPosition({textPos.x + textBounds.position.x + textBounds.size.x + 2.f, textPos.y});
			target.draw(m_caret);
		}
	}
}
