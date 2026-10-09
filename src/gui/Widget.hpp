#pragma once

#include "GuiCommon.hpp"

namespace gui
{
	class Widget
	{
	protected:
		bool m_visible;
		bool m_enabled;
		int m_zIndex;
		std::uint8_t m_opacity;

	public:
		Widget()
			: m_visible(true)
			, m_enabled(true)
			, m_zIndex(0)
			, m_opacity(255)
		{
		}
		virtual ~Widget() = default;
		virtual void update(const sf::Vector2i& mousePosWindow, const float dt = 0.f) { (void)mousePosWindow; (void)dt; }
		virtual void handleEvent(const sf::Event& event) { (void)event; }
		virtual void render(sf::RenderTarget& target) = 0;

		virtual void setPosition(float x, float y) { (void)x; (void)y; }
		virtual void move(float dx, float dy) { (void)dx; (void)dy; }

		virtual void setSize(float width, float height) { (void)width; (void)height; }
		virtual void setScale(float scaleX, float scaleY) { (void)scaleX; (void)scaleY; }

		virtual sf::Vector2f getPosition() const { return {0.f, 0.f}; }
		virtual sf::Vector2f getSize() const { return {0.f, 0.f}; }
		virtual sf::Vector2f getScale() const { return {1.f, 1.f}; }
		virtual sf::FloatRect getBounds() const { return {}; }

		virtual void setFillColor(const sf::Color& color) { (void)color; }
		virtual sf::Color getFillColor() const { return sf::Color::Transparent; }
		virtual void setOutlineColor(const sf::Color& color) { (void)color; }
		virtual sf::Color getOutlineColor() const { return sf::Color::Transparent; }
		virtual void setOutlineThickness(float thickness) { (void)thickness; }
		virtual float getOutlineThickness() const { return 0.f; }
		virtual void setRotation(float degrees) { (void)degrees; }
		virtual float getRotation() const { return 0.f; }
		virtual void setOpacity(std::uint8_t alpha) { this->m_opacity = alpha; }
		virtual std::uint8_t getOpacity() const { return this->m_opacity; }

		void setVisible(bool value) { this->m_visible = value; }
		const bool isVisible() const { return this->m_visible; }
		void setEnabled(bool value) { this->m_enabled = value; }
		const bool isEnabled() const { return this->m_enabled; }
		void setZIndex(int value) { this->m_zIndex = value; }
		int getZIndex() const { return this->m_zIndex; }
	};
}
