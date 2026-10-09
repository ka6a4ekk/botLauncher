#pragma once

#include "Widget.hpp"

#include <string>

namespace gui
{
	class TextBox : public Widget
	{
	private:
		sf::RectangleShape m_box;
		sf::Text m_text;
		sf::Text m_caret;
		std::string m_value;
		bool m_focused;
		bool m_prevFocused;
		bool m_caretVisible;
		float m_caretTimer;
		float m_caretPeriod;
		bool m_hovered;

		sf::Color m_boxIdleColor;
		sf::Color m_boxHoverColor;
		sf::Color m_boxActiveColor;
		sf::Color m_outlineIdleColor;
		sf::Color m_outlineHoverColor;
		sf::Color m_outlineActiveColor;
		sf::Color m_textIdleColor;
		sf::Color m_textHoverColor;
		sf::Color m_textActiveColor;
		sf::Color m_caretIdleColor;
		sf::Color m_caretHoverColor;
		sf::Color m_caretActiveColor;

		void applyDisplayColors();

	public:
		TextBox(float x, float y, float width, float height, sf::Font& font, unsigned characterSize);
		const std::string& getValue() const;
		void setValue(const std::string& value);
		void setBoxIdleColor(const sf::Color& color);
		void setBoxHoverColor(const sf::Color& color);
		void setBoxActiveColor(const sf::Color& color);
		sf::Color getBoxIdleColor() const;
		sf::Color getBoxHoverColor() const;
		sf::Color getBoxActiveColor() const;
		void setOutlineIdleColor(const sf::Color& color);
		void setOutlineHoverColor(const sf::Color& color);
		void setOutlineActiveColor(const sf::Color& color);
		sf::Color getOutlineIdleColor() const;
		sf::Color getOutlineHoverColor() const;
		sf::Color getOutlineActiveColor() const;
		void setTextIdleColor(const sf::Color& color);
		void setTextHoverColor(const sf::Color& color);
		void setTextActiveColor(const sf::Color& color);
		sf::Color getTextIdleColor() const;
		sf::Color getTextHoverColor() const;
		sf::Color getTextActiveColor() const;
		void setCaretIdleColor(const sf::Color& color);
		void setCaretHoverColor(const sf::Color& color);
		void setCaretActiveColor(const sf::Color& color);
		sf::Color getCaretIdleColor() const;
		sf::Color getCaretHoverColor() const;
		sf::Color getCaretActiveColor() const;
		void setBoxColor(const sf::Color& color);
		void setTextColor(const sf::Color& color);
		void setCaretColor(const sf::Color& color);
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
		void handleEvent(const sf::Event& event) override;
		void render(sf::RenderTarget& target) override;
	};
}
