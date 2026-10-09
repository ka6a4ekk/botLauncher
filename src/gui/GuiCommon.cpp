#include "GuiCommon.hpp"
#include "stdafx.h"

#include <cmath>

const float gui::p2pX(const float perc, const sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.size.x) * (perc / 100.f));
}

const float gui::p2pY(const float perc, const sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.size.y) * (perc / 100.f));
}

const unsigned gui::calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
	return static_cast<unsigned>((vm.size.x + vm.size.y) / modifier);
}

static bool g_mouseCaptured = false;

void gui::beginFrame()
{
	g_mouseCaptured = false;
}

void gui::captureMouse()
{
	g_mouseCaptured = true;
}

bool gui::isMouseCaptured()
{
	return g_mouseCaptured;
}
