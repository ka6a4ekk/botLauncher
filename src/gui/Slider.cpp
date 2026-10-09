#include "stdafx.h"
#include "Slider.hpp"

#include "GuiCommon.hpp"

#include <cmath>

namespace gui
{
	Slider::Slider(float x, float y, float length, float thickness, Orientation orientation,
		float minValue, float maxValue, float value)
		: m_orientation(orientation)
		, m_minValue(minValue)
		, m_maxValue(maxValue)
		, m_value(value)
		, m_dragging(false)
		, m_hovered(false)
		, m_trackTexture(std::nullopt)
		, m_knobTexture(std::nullopt)
		, m_anchorPos({x, y})
	{
		if (m_orientation == Orientation::HORIZONTAL)
		{
			m_track.setPosition({x, y});
			m_track.setSize({length, thickness});
			m_knob.setSize({thickness * 1.5f, thickness * 1.5f});
		}
		else
		{
			m_track.setPosition({x, y});
			m_track.setSize({thickness, length});
			m_knob.setSize({thickness * 1.5f, thickness * 1.5f});
		}

		m_track.setFillColor(sf::Color(60, 60, 60, 255));
		m_knob.setFillColor(sf::Color(200, 200, 200, 255));
		updateKnobFromValue();

		m_trackIdleColor = m_track.getFillColor();
		m_trackHoverColor = m_track.getFillColor();
		m_trackActiveColor = m_track.getFillColor();
		m_knobIdleColor = m_knob.getFillColor();
		m_knobHoverColor = m_knob.getFillColor();
		m_knobActiveColor = m_knob.getFillColor();
		m_trackOutlineIdleColor = m_track.getOutlineColor();
		m_trackOutlineHoverColor = m_track.getOutlineColor();
		m_trackOutlineActiveColor = m_track.getOutlineColor();
		m_knobOutlineIdleColor = m_knob.getOutlineColor();
		m_knobOutlineHoverColor = m_knob.getOutlineColor();
		m_knobOutlineActiveColor = m_knob.getOutlineColor();
	}

	void Slider::setTextures(const sf::Texture& trackTexture, const sf::Texture& knobTexture)
	{
		m_trackTexture = std::cref(trackTexture);
		m_knobTexture = std::cref(knobTexture);

		m_track.setTexture(&trackTexture, true);
		const auto trackSize = trackTexture.getSize();
		m_track.setSize({static_cast<float>(trackSize.x), static_cast<float>(trackSize.y)});
		if (m_orientation == Orientation::VERTICAL)
			m_track.setRotation(sf::degrees(90.f));
		else
			m_track.setRotation(sf::degrees(0.f));

		m_knob.setTexture(&knobTexture, true);
		const auto knobSize = knobTexture.getSize();
		m_knob.setSize({static_cast<float>(knobSize.x), static_cast<float>(knobSize.y)});

		updateTrackPosition();
		updateKnobFromValue();
	}

	void Slider::setTrackIdleColor(const sf::Color& color)
	{
		m_trackIdleColor = color;
		applyDisplayColors();
	}

	void Slider::setTrackHoverColor(const sf::Color& color)
	{
		m_trackHoverColor = color;
		applyDisplayColors();
	}

	void Slider::setTrackActiveColor(const sf::Color& color)
	{
		m_trackActiveColor = color;
		applyDisplayColors();
	}

	sf::Color Slider::getTrackIdleColor() const
	{
		return m_trackIdleColor;
	}

	sf::Color Slider::getTrackHoverColor() const
	{
		return m_trackHoverColor;
	}

	sf::Color Slider::getTrackActiveColor() const
	{
		return m_trackActiveColor;
	}

	void Slider::setKnobIdleColor(const sf::Color& color)
	{
		m_knobIdleColor = color;
		applyDisplayColors();
	}

	void Slider::setKnobHoverColor(const sf::Color& color)
	{
		m_knobHoverColor = color;
		applyDisplayColors();
	}

	void Slider::setKnobActiveColor(const sf::Color& color)
	{
		m_knobActiveColor = color;
		applyDisplayColors();
	}

	sf::Color Slider::getKnobIdleColor() const
	{
		return m_knobIdleColor;
	}

	sf::Color Slider::getKnobHoverColor() const
	{
		return m_knobHoverColor;
	}

	sf::Color Slider::getKnobActiveColor() const
	{
		return m_knobActiveColor;
	}

	void Slider::setTrackOutlineIdleColor(const sf::Color& color)
	{
		m_trackOutlineIdleColor = color;
		applyDisplayColors();
	}

	void Slider::setTrackOutlineHoverColor(const sf::Color& color)
	{
		m_trackOutlineHoverColor = color;
		applyDisplayColors();
	}

	void Slider::setTrackOutlineActiveColor(const sf::Color& color)
	{
		m_trackOutlineActiveColor = color;
		applyDisplayColors();
	}

	sf::Color Slider::getTrackOutlineIdleColor() const
	{
		return m_trackOutlineIdleColor;
	}

	sf::Color Slider::getTrackOutlineHoverColor() const
	{
		return m_trackOutlineHoverColor;
	}

	sf::Color Slider::getTrackOutlineActiveColor() const
	{
		return m_trackOutlineActiveColor;
	}

	void Slider::setKnobOutlineIdleColor(const sf::Color& color)
	{
		m_knobOutlineIdleColor = color;
		applyDisplayColors();
	}

	void Slider::setKnobOutlineHoverColor(const sf::Color& color)
	{
		m_knobOutlineHoverColor = color;
		applyDisplayColors();
	}

	void Slider::setKnobOutlineActiveColor(const sf::Color& color)
	{
		m_knobOutlineActiveColor = color;
		applyDisplayColors();
	}

	sf::Color Slider::getKnobOutlineIdleColor() const
	{
		return m_knobOutlineIdleColor;
	}

	sf::Color Slider::getKnobOutlineHoverColor() const
	{
		return m_knobOutlineHoverColor;
	}

	sf::Color Slider::getKnobOutlineActiveColor() const
	{
		return m_knobOutlineActiveColor;
	}

	void Slider::setTrackColor(const sf::Color& color)
	{
		m_trackIdleColor = color;
		m_trackHoverColor = color;
		m_trackActiveColor = color;
		applyDisplayColors();
	}

	void Slider::setKnobColor(const sf::Color& color)
	{
		m_knobIdleColor = color;
		m_knobHoverColor = color;
		m_knobActiveColor = color;
		applyDisplayColors();
	}

	void Slider::setScale(float scaleX, float scaleY)
	{
		if (scaleX <= 0.f || scaleY <= 0.f)
			return;

		m_track.setScale({scaleX, scaleY});
		m_knob.setScale({scaleX, scaleY});
		updateTrackPosition();
		updateKnobFromValue();
	}

	const float Slider::getValue() const
	{
		return m_value;
	}

	void Slider::setValue(float newValue)
	{
		if (newValue < m_minValue)
			newValue = m_minValue;
		if (newValue > m_maxValue)
			newValue = m_maxValue;
		m_value = newValue;
		updateKnobFromValue();
	}

	void Slider::setPosition(float x, float y)
	{
		m_anchorPos = {x, y};
		updateTrackPosition();
		updateKnobFromValue();
	}

	void Slider::move(float dx, float dy)
	{
		m_track.move({dx, dy});
		m_knob.move({dx, dy});
	}

	void Slider::setSize(float width, float height)
	{
		m_track.setSize({width, height});
		if (m_orientation == Orientation::HORIZONTAL)
			m_knob.setSize({height * 1.5f, height * 1.5f});
		else
			m_knob.setSize({width * 1.5f, width * 1.5f});
		updateTrackPosition();
		updateKnobFromValue();
	}

	void Slider::setFillColor(const sf::Color& color)
	{
		setTrackColor(color);
		setKnobColor(color);
	}

	sf::Color Slider::getFillColor() const
	{
		return m_track.getFillColor();
	}

	void Slider::setOutlineColor(const sf::Color& color)
	{
		m_trackOutlineIdleColor = color;
		m_trackOutlineHoverColor = color;
		m_trackOutlineActiveColor = color;
		m_knobOutlineIdleColor = color;
		m_knobOutlineHoverColor = color;
		m_knobOutlineActiveColor = color;
		applyDisplayColors();
	}

	sf::Color Slider::getOutlineColor() const
	{
		return m_track.getOutlineColor();
	}

	void Slider::setOutlineThickness(float thickness)
	{
		m_track.setOutlineThickness(thickness);
		m_knob.setOutlineThickness(thickness);
	}

	float Slider::getOutlineThickness() const
	{
		return m_track.getOutlineThickness();
	}

	void Slider::setRotation(float degrees)
	{
		float base = 0.f;
		if (m_orientation == Orientation::VERTICAL && m_trackTexture.has_value())
			base = 90.f;
		m_track.setRotation(sf::degrees(base + degrees));
		m_knob.setRotation(sf::degrees(degrees));
		updateTrackPosition();
		updateKnobFromValue();
	}

	float Slider::getRotation() const
	{
		return m_track.getRotation().asDegrees();
	}

	void Slider::setOpacity(std::uint8_t alpha)
	{
		m_opacity = alpha;
		m_track.setFillColor(detail::withAlpha(m_track.getFillColor(), alpha));
		m_track.setOutlineColor(detail::withAlpha(m_track.getOutlineColor(), alpha));
		m_knob.setFillColor(detail::withAlpha(m_knob.getFillColor(), alpha));
		m_knob.setOutlineColor(detail::withAlpha(m_knob.getOutlineColor(), alpha));
	}

	std::uint8_t Slider::getOpacity() const
	{
		return m_track.getFillColor().a;
	}

	sf::Vector2f Slider::getPosition() const
	{
		return m_track.getPosition();
	}

	sf::Vector2f Slider::getSize() const
	{
		return m_track.getGlobalBounds().size;
	}

	sf::Vector2f Slider::getScale() const
	{
		return m_track.getScale();
	}

	sf::FloatRect Slider::getBounds() const
	{
		return m_track.getGlobalBounds();
	}

	void Slider::applyDisplayColors()
	{
		const ButtonState state = m_dragging ? ButtonState::ACTIVATE : (m_hovered ? ButtonState::HOVER : ButtonState::IDLE);

		switch (state)
		{
		case ButtonState::IDLE:
			m_track.setFillColor(m_trackIdleColor);
			m_track.setOutlineColor(m_trackOutlineIdleColor);
			m_knob.setFillColor(m_knobIdleColor);
			m_knob.setOutlineColor(m_knobOutlineIdleColor);
			break;
		case ButtonState::HOVER:
			m_track.setFillColor(m_trackHoverColor);
			m_track.setOutlineColor(m_trackOutlineHoverColor);
			m_knob.setFillColor(m_knobHoverColor);
			m_knob.setOutlineColor(m_knobOutlineHoverColor);
			break;
		case ButtonState::ACTIVATE:
			m_track.setFillColor(m_trackActiveColor);
			m_track.setOutlineColor(m_trackOutlineActiveColor);
			m_knob.setFillColor(m_knobActiveColor);
			m_knob.setOutlineColor(m_knobOutlineActiveColor);
			break;
		}
	}

	void Slider::updateKnobFromValue()
	{
		const float t = (m_value - m_minValue) / (m_maxValue - m_minValue);
		if (m_orientation == Orientation::HORIZONTAL)
		{
			const auto trackBounds = m_track.getGlobalBounds();
			const auto knobBounds = m_knob.getGlobalBounds();
			const float x = trackBounds.position.x + t * trackBounds.size.x - knobBounds.size.x / 2.f;
			const float y = trackBounds.position.y + (trackBounds.size.y - knobBounds.size.y) / 2.f;
			m_knob.setPosition({x, y});
		}
		else
		{
			const auto trackBounds = m_track.getGlobalBounds();
			const auto knobBounds = m_knob.getGlobalBounds();
			const float y = trackBounds.position.y + t * trackBounds.size.y - knobBounds.size.y / 2.f;
			const float x = trackBounds.position.x + (trackBounds.size.x - knobBounds.size.x) / 2.f;
			m_knob.setPosition({x, y});
		}
	}

	void Slider::updateTrackPosition()
	{
		if (m_orientation == Orientation::VERTICAL && std::abs(m_track.getRotation().asDegrees() - 90.f) < 0.001f)
		{
			const float h = m_track.getSize().y * m_track.getScale().y;
			m_track.setPosition({m_anchorPos.x + h, m_anchorPos.y});
			return;
		}

		m_track.setPosition(m_anchorPos);
	}

	void Slider::setValueFromMouse(const sf::Vector2i& mousePosWindow)
	{
		if (m_orientation == Orientation::HORIZONTAL)
		{
			const auto trackBounds = m_track.getGlobalBounds();
			float x = static_cast<float>(mousePosWindow.x);
			if (x < trackBounds.position.x) x = trackBounds.position.x;
			if (x > trackBounds.position.x + trackBounds.size.x) x = trackBounds.position.x + trackBounds.size.x;
			const float t = (x - trackBounds.position.x) / trackBounds.size.x;
			m_value = m_minValue + t * (m_maxValue - m_minValue);
			updateKnobFromValue();
		}
		else
		{
			const auto trackBounds = m_track.getGlobalBounds();
			float y = static_cast<float>(mousePosWindow.y);
			if (y < trackBounds.position.y) y = trackBounds.position.y;
			if (y > trackBounds.position.y + trackBounds.size.y) y = trackBounds.position.y + trackBounds.size.y;
			const float t = (y - trackBounds.position.y) / trackBounds.size.y;
			m_value = m_minValue + t * (m_maxValue - m_minValue);
			updateKnobFromValue();
		}
	}

	void Slider::update(const sf::Vector2i& mousePosWindow, const float)
	{
		if (!m_enabled)
			return;
		const bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		if (!pressed)
			m_dragging = false;

		m_hovered = m_track.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)) ||
			m_knob.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow));

		if (m_knob.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)) && pressed)
			m_dragging = true;

		if (m_dragging)
			setValueFromMouse(mousePosWindow);

		applyDisplayColors();
	}

	void Slider::render(sf::RenderTarget& target)
	{
		if (!m_visible)
			return;
		target.draw(m_track);
		target.draw(m_knob);
	}
}
