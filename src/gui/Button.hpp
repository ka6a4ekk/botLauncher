#pragma once

#include "Widget.hpp"

#include <functional>
#include <string>

namespace gui
{
	class Button : public Widget
	{
	private:
		ButtonState m_buttonState;
		unsigned short m_id;
		bool m_toggleMode;
		bool m_toggled;
		bool m_justPressed;

		sf::RectangleShape m_shape;
		std::reference_wrapper<sf::Font> m_font;
		sf::Text m_text;

		sf::Color m_textIdleColor;
		sf::Color m_textHoverColor;
		sf::Color m_textActiveColor;

		sf::Color m_idleColor;
		sf::Color m_hoverColor;
		sf::Color m_activeColor;

		sf::Color m_outlineIdleColor;
		sf::Color m_outlineHoverColor;
		sf::Color m_outlineActiveColor;

		void applyDisplayColors();
		void updateTextPosition();

	public:
		Button(float x, float y, float width, float height,
			sf::Font& font, std::string text, unsigned characterSize,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color outlineIdleColor = sf::Color::Transparent, sf::Color outlineHoverColor = sf::Color::Transparent, sf::Color outlineActiveColor = sf::Color::Transparent,
			unsigned short id = 0);

		const bool isPressed() const;
		const std::string getText() const;
		const unsigned short& getId() const;

		void setText(const std::string text);
		void setId(const unsigned short id);
		void setToggleMode(bool enabled);
		bool isToggleMode() const;
		void setToggled(bool toggled);
		bool isToggled() const;
		void setTextIdleColor(const sf::Color& color);
		void setTextHoverColor(const sf::Color& color);
		void setTextActiveColor(const sf::Color& color);
		sf::Color getTextIdleColor() const;
		sf::Color getTextHoverColor() const;
		sf::Color getTextActiveColor() const;
		void setIdleColor(const sf::Color& color);
		void setHoverColor(const sf::Color& color);
		void setActiveColor(const sf::Color& color);
		sf::Color getIdleColor() const;
		sf::Color getHoverColor() const;
		sf::Color getActiveColor() const;
		void setOutlineIdleColor(const sf::Color& color);
		void setOutlineHoverColor(const sf::Color& color);
		void setOutlineActiveColor(const sf::Color& color);
		sf::Color getOutlineIdleColor() const;
		sf::Color getOutlineHoverColor() const;
		sf::Color getOutlineActiveColor() const;
		void setPosition(float x, float y) override;
		void move(float dx, float dy) override;
		void setSize(float width, float height) override;
		void setScale(float scaleX, float scaleY) override;
		void setFillColor(const sf::Color& color) override;
		sf::Color getFillColor() const override;
		void setOutlineColor(const sf::Color& color) override;
		sf::Color getOutlineColor() const override;
		void setOutlineThickness(float thickness) override;
		float getOutlineThickness() const override;
		void setRotation(float degrees) override;
		float getRotation() const override;
		void setOpacity(std::uint8_t alpha) override;
		std::uint8_t getOpacity() const override;
		sf::Vector2f getPosition() const override;
		sf::Vector2f getSize() const override;
		sf::Vector2f getScale() const override;
		sf::FloatRect getBounds() const override;

		void update(const sf::Vector2i& mousePosWindow, const float dt = 0.f) override;
		void render(sf::RenderTarget& target) override;
	};
}
