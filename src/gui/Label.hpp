#pragma once

#include "Widget.hpp"

#include <string>

namespace gui
{
	class Label : public Widget
	{
	private:
		sf::Text m_text;

	public:
		Label(sf::Font& font, const std::string& value = "", unsigned characterSize = 20, sf::Color color = sf::Color::White);
		Label(float x, float y, const std::string& value, sf::Font& font, unsigned characterSize, sf::Color color);
		void setText(const std::string& value);
		void setString(const std::string& value);
		void setCharacterSize(unsigned characterSize);
		void setTextColor(const sf::Color& color);
		void setPosition(float x, float y) override;
		void setPosition(const sf::Vector2f& position);
		void move(float dx, float dy) override;
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
		void render(sf::RenderTarget& target) override;
	};
}
