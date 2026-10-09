#pragma once

#include "Widget.hpp"

namespace gui
{
	class Image : public Widget
	{
	private:
		sf::Sprite m_sprite;
		sf::RectangleShape m_outline;
		bool m_outlineVisible;

	public:
		Image(float x, float y, sf::Texture& texture, const sf::IntRect& rect = sf::IntRect());
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
		void render(sf::RenderTarget& target) override;
	};
}
