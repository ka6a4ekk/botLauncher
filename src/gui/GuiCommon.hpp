#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>

namespace gui
{
	const float p2pX(const float perc, const sf::VideoMode& vm);
	const float p2pY(const float perc, const sf::VideoMode& vm);
	const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);
	void beginFrame();
	void captureMouse();
	bool isMouseCaptured();

	enum class ButtonState
	{
		IDLE = 0,
		HOVER,
		ACTIVATE
	};

	enum class Orientation
	{
		HORIZONTAL,
		VERTICAL
	};

	namespace detail
	{
		inline sf::Color withAlpha(sf::Color color, std::uint8_t alpha)
		{
			color.a = alpha;
			return color;
		}
	}
}
