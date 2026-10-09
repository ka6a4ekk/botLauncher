#pragma once

#include "Widget.hpp"

#include <optional>

namespace gui
{
	class Slider : public Widget
	{
	private:
		Orientation m_orientation;
		float m_minValue;
		float m_maxValue;
		float m_value;
		bool m_dragging;
		bool m_hovered;
		sf::RectangleShape m_track;
		sf::RectangleShape m_knob;
		std::optional<std::reference_wrapper<const sf::Texture>> m_trackTexture;
		std::optional<std::reference_wrapper<const sf::Texture>> m_knobTexture;
		sf::Vector2f m_anchorPos;

		sf::Color m_trackIdleColor;
		sf::Color m_trackHoverColor;
		sf::Color m_trackActiveColor;
		sf::Color m_knobIdleColor;
		sf::Color m_knobHoverColor;
		sf::Color m_knobActiveColor;
		sf::Color m_trackOutlineIdleColor;
		sf::Color m_trackOutlineHoverColor;
		sf::Color m_trackOutlineActiveColor;
		sf::Color m_knobOutlineIdleColor;
		sf::Color m_knobOutlineHoverColor;
		sf::Color m_knobOutlineActiveColor;

		void applyDisplayColors();
		void updateKnobFromValue();
		void setValueFromMouse(const sf::Vector2i& mousePosWindow);
		void updateTrackPosition();

	public:
		Slider(float x, float y, float length, float thickness, Orientation orientation,
			float minValue, float maxValue, float value);
		void setTextures(const sf::Texture& trackTexture, const sf::Texture& knobTexture);
		void setTrackIdleColor(const sf::Color& color);
		void setTrackHoverColor(const sf::Color& color);
		void setTrackActiveColor(const sf::Color& color);
		sf::Color getTrackIdleColor() const;
		sf::Color getTrackHoverColor() const;
		sf::Color getTrackActiveColor() const;
		void setKnobIdleColor(const sf::Color& color);
		void setKnobHoverColor(const sf::Color& color);
		void setKnobActiveColor(const sf::Color& color);
		sf::Color getKnobIdleColor() const;
		sf::Color getKnobHoverColor() const;
		sf::Color getKnobActiveColor() const;
		void setTrackOutlineIdleColor(const sf::Color& color);
		void setTrackOutlineHoverColor(const sf::Color& color);
		void setTrackOutlineActiveColor(const sf::Color& color);
		sf::Color getTrackOutlineIdleColor() const;
		sf::Color getTrackOutlineHoverColor() const;
		sf::Color getTrackOutlineActiveColor() const;
		void setKnobOutlineIdleColor(const sf::Color& color);
		void setKnobOutlineHoverColor(const sf::Color& color);
		void setKnobOutlineActiveColor(const sf::Color& color);
		sf::Color getKnobOutlineIdleColor() const;
		sf::Color getKnobOutlineHoverColor() const;
		sf::Color getKnobOutlineActiveColor() const;
		void setTrackColor(const sf::Color& color);
		void setKnobColor(const sf::Color& color);
		void setScale(float scaleX, float scaleY) override;
		void setScale(float scale) { setScale(scale, scale); }
		const float getValue() const;
		void setValue(float newValue);
		void setPosition(float x, float y) override;
		void move(float dx, float dy) override;
		void setSize(float width, float height) override;
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
