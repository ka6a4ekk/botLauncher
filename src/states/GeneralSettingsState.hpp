#pragma once

#include "State.hpp"

#include <SFML/Graphics.hpp>

#include "gui/Checkbox.hpp"
#include "gui/Button.hpp"
#include "gui/Label.hpp"
#include "gui/Slider.hpp"
#include "gui/TextBox.hpp"

#include <string>

class GeneralSettingsState : public State
{
public:
	GeneralSettingsState(StateStack& stack, State::Context context);
	~GeneralSettingsState() override = default;

	void handleEvent(const sf::Event& event) override;
	void update(sf::Time dt) override;
	void render() override;

private:
	void updateLabels();
	void importJson();
	void exportJson() const;
	static int toIntValue(float value);

	sf::Font m_font;
	sf::RectangleShape m_background;
	sf::RectangleShape m_panel;

	gui::Label m_keyLabel;
	gui::TextBox m_keyTextBox;

	gui::Checkbox m_lootCheckBox;
	gui::Checkbox m_skinningCheckBox;
	gui::Checkbox m_mountCheckBox;

	gui::Label m_searchDistanceLabel;
	gui::Slider m_searchDistanceSlider;
	gui::Label m_searchDistanceValue;

	gui::Label m_dejunkLabel;
	gui::Slider m_dejunkSlider;
	gui::Label m_dejunkValue;

	gui::Label m_repairLabel;
	gui::Slider m_repairSlider;
	gui::Label m_repairValue;
};
