#pragma once

#include "Widget.hpp"

#include <string>

namespace gui
{
	class Checkbox : public Widget
	{
	private:
		sf::RectangleShape m_box;
		sf::RectangleShape m_check;
		sf::Text m_label;
		bool m_checked;
		bool m_wasPressed;
		ButtonState m_state;

		sf::Color m_boxIdleColor;
		sf::Color m_boxHoverColor;
		sf::Color m_boxActiveColor;
		sf::Color m_outlineIdleColor;
		sf::Color m_outlineHoverColor;
		sf::Color m_outlineActiveColor;
		sf::Color m_checkIdleColor;
		sf::Color m_checkHoverColor;
		sf::Color m_checkActiveColor;
		sf::Color m_labelIdleColor;
		sf::Color m_labelHoverColor;
		sf::Color m_labelActiveColor;

		void applyDisplayColors();

	public:
		Checkbox(float x, float y, float size, sf::Font& font, const std::string& text, unsigned characterSize);
		const bool isChecked() const;
		void setChecked(bool checked);

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

		void setCheckIdleColor(const sf::Color& color);
		void setCheckHoverColor(const sf::Color& color);
		void setCheckActiveColor(const sf::Color& color);
		sf::Color getCheckIdleColor() const;
		sf::Color getCheckHoverColor() const;
		sf::Color getCheckActiveColor() const;

		void setLabelIdleColor(const sf::Color& color);
		void setLabelHoverColor(const sf::Color& color);
		void setLabelActiveColor(const sf::Color& color);
		sf::Color getLabelIdleColor() const;
		sf::Color getLabelHoverColor() const;
		sf::Color getLabelActiveColor() const;
		
		void setBoxColor(const sf::Color& color);
		void setCheckColor(const sf::Color& color);
		void setLabelColor(const sf::Color& color);
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
