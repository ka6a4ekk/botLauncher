#include "stdafx.h"
#include "states/GeneralSettingsState.hpp"
#include "Json.hpp"

#include <cmath>
#include <fstream>
#include <stdexcept>

static sf::Font loadFont()
{
	sf::Font font;
	if(!font.openFromFile("res/fonts/font.ttf"))
		throw std::runtime_error("Failed to load font");
	return font;
}

GeneralSettingsState::GeneralSettingsState(StateStack& stack, State::Context context)
	: State(stack, context)
	, m_font(loadFont())
	, m_keyLabel(0.f, 0.f, "Key", m_font, 18, sf::Color(220, 220, 220))
	, m_keyTextBox(0.f, 0.f, 200.f, 30.f, m_font, 18)
	, m_lootCheckBox(0.f, 0.f, 20.f, m_font, "Loot", 18)
	, m_skinningCheckBox(0.f, 0.f, 20.f, m_font, "Skinning", 18)
	, m_mountCheckBox(0.f, 0.f, 20.f, m_font, "Mount", 18)
	, m_searchDistanceLabel(0.f, 0.f, "Search Distance", m_font, 18, sf::Color(220, 220, 220))
	, m_searchDistanceSlider(0.f, 0.f, 200.f, 8.f, gui::Orientation::HORIZONTAL, 10.f, 100.f, 10.f)
	, m_searchDistanceValue(0.f, 0.f, "", m_font, 18, sf::Color(200, 200, 200))
	, m_dejunkLabel(0.f, 0.f, "Dejunk", m_font, 18, sf::Color(220, 220, 220))
	, m_dejunkSlider(0.f, 0.f, 200.f, 8.f, gui::Orientation::HORIZONTAL, 0.f, 128.f, 0.f)
	, m_dejunkValue(0.f, 0.f, "", m_font, 18, sf::Color(200, 200, 200))
	, m_repairLabel(0.f, 0.f, "Repair", m_font, 18, sf::Color(220, 220, 220))
	, m_repairSlider(0.f, 0.f, 200.f, 8.f, gui::Orientation::HORIZONTAL, 0.f, 100.f, 0.f)
	, m_repairValue(0.f, 0.f, "", m_font, 18, sf::Color(200, 200, 200))
{
	const auto backgroundSize = mContext.window->getSize();
	m_background.setSize(sf::Vector2f(static_cast<float>(backgroundSize.x), static_cast<float>(backgroundSize.y)));
	m_background.setFillColor(sf::Color(20, 20, 20));

	const auto windowSize = mContext.window->getSize();
	m_panel.setPosition(sf::Vector2f(10.f, 60.f));
	m_panel.setSize(sf::Vector2f(static_cast<float>(windowSize.x) - 20.f, static_cast<float>(windowSize.y) - 70.f));
	m_panel.setFillColor(sf::Color(28, 28, 28));
	m_panel.setOutlineThickness(1.f);
	m_panel.setOutlineColor(sf::Color(70, 70, 70));

	const float left = 20.f;
	const float top = 70.f;
	const float labelWidth = 280.f;
	const float inputWidth = 260.f;
	const float inputHeight = 30.f;
	const float rowGap = 35.f;
	const float valueGap = 16.f;
	const float checkboxSize = 20.f;
	const float sliderThickness = 8.f;

	float y = top;

	m_keyLabel.setPosition(left, y);
	m_keyTextBox.setPosition(left + labelWidth, y - 4.f);
	m_keyTextBox.setSize(inputWidth, inputHeight);
	y += rowGap;
	m_lootCheckBox.setPosition(left, y);
	m_lootCheckBox.setSize(checkboxSize, checkboxSize);
	y += rowGap;

	m_skinningCheckBox.setPosition(left, y);
	m_skinningCheckBox.setSize(checkboxSize, checkboxSize);
	y += rowGap;

	m_mountCheckBox.setPosition(left, y);
	m_mountCheckBox.setSize(checkboxSize, checkboxSize);
	y += rowGap;

	const float sliderY = y + (inputHeight - sliderThickness) * 0.5f;

	m_searchDistanceLabel.setPosition(left, y);
	m_searchDistanceSlider.setPosition(left + labelWidth, sliderY);
	m_searchDistanceSlider.setSize(inputWidth, sliderThickness);
	m_searchDistanceValue.setPosition(left + labelWidth + inputWidth + valueGap, y - 2.f);
	y += rowGap;

	m_dejunkLabel.setPosition(left, y);
	m_dejunkSlider.setPosition(left + labelWidth, sliderY + rowGap);
	m_dejunkSlider.setSize(inputWidth, sliderThickness);
	m_dejunkValue.setPosition(left + labelWidth + inputWidth + valueGap, y - 2.f);
	y += rowGap;

	m_repairLabel.setPosition(left, y);
	m_repairSlider.setPosition(left + labelWidth, sliderY + rowGap * 2.f);
	m_repairSlider.setSize(inputWidth, sliderThickness);
	m_repairValue.setPosition(left + labelWidth + inputWidth + valueGap, y - 2.f);

	updateLabels();
	importJson();
	updateLabels();
	exportJson();
}

void GeneralSettingsState::handleEvent(const sf::Event& event)
{
	if(event.is<sf::Event::Closed>())
		mContext.window->close();
	m_keyTextBox.handleEvent(event);
}

void GeneralSettingsState::update(sf::Time dt)
{
	const sf::Vector2i mousePos = sf::Mouse::getPosition(*mContext.window);
	const float dtSeconds = dt.asSeconds();

	m_keyTextBox.update(mousePos, dtSeconds);
	m_lootCheckBox.update(mousePos, dtSeconds);
	m_skinningCheckBox.update(mousePos, dtSeconds);
	m_mountCheckBox.update(mousePos, dtSeconds);
	m_searchDistanceSlider.update(mousePos, dtSeconds);
	m_dejunkSlider.update(mousePos, dtSeconds);
	m_repairSlider.update(mousePos, dtSeconds);
	// m_importButton.update(m_mousePosWindow, dt);
	// m_exportButton.update(m_mousePosWindow, dt);

	if(m_keyTextBox.getValue().size() > 16)
		m_keyTextBox.setValue(m_keyTextBox.getValue().substr(0, 16));

	updateLabels();
	exportJson();
}

void GeneralSettingsState::render()
{
	mContext.window->draw(m_background);
	mContext.window->draw(m_panel);

	m_keyLabel.render(*mContext.window);
	m_keyTextBox.render(*mContext.window);
	m_lootCheckBox.render(*mContext.window);
	m_skinningCheckBox.render(*mContext.window);
	m_mountCheckBox.render(*mContext.window);
	m_searchDistanceLabel.render(*mContext.window);
	m_searchDistanceSlider.render(*mContext.window);
	m_searchDistanceValue.render(*mContext.window);
	m_dejunkLabel.render(*mContext.window);
	m_dejunkSlider.render(*mContext.window);
	m_dejunkValue.render(*mContext.window);
	m_repairLabel.render(*mContext.window);
	m_repairSlider.render(*mContext.window);
	m_repairValue.render(*mContext.window);
}

void GeneralSettingsState::updateLabels()
{
	m_searchDistanceValue.setText(std::to_string(toIntValue(m_searchDistanceSlider.getValue())));
	m_dejunkValue.setText(std::to_string(toIntValue(m_dejunkSlider.getValue())));
	m_repairValue.setText(std::to_string(toIntValue(m_repairSlider.getValue())) + "%");
}

int GeneralSettingsState::toIntValue(float value)
{
	return static_cast<int>(std::round(value));
}

void GeneralSettingsState::importJson()
{
	std::ifstream in("general_settings.json");
	if(!in.is_open())
		return;

	nlohmann::json json;
	try { in >> json; } catch(...) { return; }

	if(json.contains("key") && json["key"].is_string())
		m_keyTextBox.setValue(json["key"].get<std::string>());
	if(json.contains("loot") && json["loot"].is_boolean())
		m_lootCheckBox.setChecked(json["loot"].get<bool>());
	if(json.contains("skinning") && json["skinning"].is_boolean())
		m_skinningCheckBox.setChecked(json["skinning"].get<bool>());
	if(json.contains("mount") && json["mount"].is_boolean())
		m_mountCheckBox.setChecked(json["mount"].get<bool>());
	if(json.contains("search_distance") && json["search_distance"].is_number())
		m_searchDistanceSlider.setValue(static_cast<float>(json["search_distance"].get<double>()));
	if(json.contains("dejunk_when_free_bag_slots_lt") && json["dejunk_when_free_bag_slots_lt"].is_number())
		m_dejunkSlider.setValue(static_cast<float>(json["dejunk_when_free_bag_slots_lt"].get<double>()));
	if(json.contains("repair_when_durability_lt") && json["repair_when_durability_lt"].is_number())
		m_repairSlider.setValue(static_cast<float>(json["repair_when_durability_lt"].get<double>()));
}

void GeneralSettingsState::exportJson() const
{
	nlohmann::json json;
	json["schema_version"] = 1;
	json["key"] = m_keyTextBox.getValue();
	json["loot"] = m_lootCheckBox.isChecked();
	json["skinning"] = m_skinningCheckBox.isChecked();
	json["mount"] = m_mountCheckBox.isChecked();
	json["search_distance"] = toIntValue(m_searchDistanceSlider.getValue());
	json["dejunk_when_free_bag_slots_lt"] = toIntValue(m_dejunkSlider.getValue());
	json["repair_when_durability_lt"] = toIntValue(m_repairSlider.getValue());

	std::ofstream out("general_settings.json");
	if(out.is_open())
		out << json.dump(2);
}
