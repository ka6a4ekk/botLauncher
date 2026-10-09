#pragma once

#include "Button.hpp"

#include <memory>
#include <string>

namespace gui
{
	class TextureSelector : public Widget
	{
	private:
		float m_keytime;
		const float m_keytimeMax;
		float m_gridSize;
		bool m_active;
		bool m_hidden;
		std::unique_ptr<gui::Button> m_hideButton;
		sf::RectangleShape m_bounds;
		sf::Sprite m_sheet;
		sf::RectangleShape m_selector;
		sf::Vector2u m_mousePosGrid;
		sf::IntRect m_textureRect;

	public:
		TextureSelector(float x, float y, float width, float height,
			float gridSize, const sf::Texture& textureSheet,
			sf::Font& font, std::string text);

		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;

		const bool getKeytime();
		void updateKeytime(const float& dt);
		void setSelectorFillColor(const sf::Color& color);
		sf::Color getSelectorFillColor() const;
		void setSelectorOutlineColor(const sf::Color& color);
		sf::Color getSelectorOutlineColor() const;
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
		void update(const sf::Vector2i& mousePosWindow, const float dt) override;
		void render(sf::RenderTarget& target) override;
	};
}
