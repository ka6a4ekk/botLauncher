#pragma once

#include "Widget.hpp"

#include <functional>
#include <string>
#include <vector>

namespace gui
{
	class List : public Widget
	{
	private:
		sf::RectangleShape m_bounds;
		std::reference_wrapper<sf::Font> m_font;
		std::vector<std::string> m_items;
		float m_itemHeight;
		int m_selectedIndex;
		float m_scroll01;
		ButtonState m_state;

		sf::Color m_boundsIdleColor;
		sf::Color m_boundsHoverColor;
		sf::Color m_boundsActiveColor;
		sf::Color m_outlineIdleColor;
		sf::Color m_outlineHoverColor;
		sf::Color m_outlineActiveColor;
		sf::Color m_textIdleColor;
		sf::Color m_textHoverColor;
		sf::Color m_textActiveColor;
		sf::Color m_highlightIdleColor;
		sf::Color m_highlightHoverColor;
		sf::Color m_highlightActiveColor;

		void applyDisplayColors();

	public:
		List(float x, float y, float width, float height, float itemHeight, sf::Font& font, const std::vector<std::string>& items);
		void addItem(const std::string& item);
		void clear();
		void setItems(const std::vector<std::string>& items);
		void setScroll(float t01);
		const int getSelectedIndex() const;
		void setSelectedIndex(int index);
		int hitTest(const sf::Vector2f& pos) const;
		int getItemCount() const;
		float getItemHeight() const;
		const std::string& getItem(std::size_t index) const;
		void setBoundsIdleColor(const sf::Color& color);
		void setBoundsHoverColor(const sf::Color& color);
		void setBoundsActiveColor(const sf::Color& color);
		sf::Color getBoundsIdleColor() const;
		sf::Color getBoundsHoverColor() const;
		sf::Color getBoundsActiveColor() const;
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
		void setHighlightIdleColor(const sf::Color& color);
		void setHighlightHoverColor(const sf::Color& color);
		void setHighlightActiveColor(const sf::Color& color);
		sf::Color getHighlightIdleColor() const;
		sf::Color getHighlightHoverColor() const;
		sf::Color getHighlightActiveColor() const;
		void setBoundsColor(const sf::Color& color);
		void setTextColor(const sf::Color& color);
		void setHighlightColor(const sf::Color& color);
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
