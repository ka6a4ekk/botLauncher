#include "stdafx.h"
#include "states/RotationState.hpp"
#include "Json.hpp"
#include <tinyfiledialogs.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

static sf::Font loadFont()
{
	sf::Font font;
	if(!font.openFromFile("res/fonts/font.ttf"))
		throw std::runtime_error("Failed to load font");
	return font;
}

RotationState::RotationState(StateStack& stack, State::Context context)
	: State(stack, context)
	, m_marker({2000.f, 2000.f})
	, m_font(loadFont())
	, m_background()
	, m_leftPanel()
	, m_centerPanel()
	, m_rightPanel()
	, m_importButton(0.f, 0.f, 135.f, 24.f, m_font, "Import", 16,
		sf::Color(240, 240, 240), sf::Color(255, 255, 255), sf::Color(255, 255, 255),
		sf::Color(85, 85, 85), sf::Color(105, 105, 105), sf::Color(70, 70, 70),
		sf::Color(130, 130, 130), sf::Color(150, 150, 150), sf::Color(115, 115, 115))
	, m_exportButton(0.f, 0.f, 135.f, 24.f, m_font, "Save", 16,
		sf::Color(240, 240, 240), sf::Color(255, 255, 255), sf::Color(255, 255, 255),
		sf::Color(85, 85, 85), sf::Color(105, 105, 105), sf::Color(70, 70, 70),
		sf::Color(130, 130, 130), sf::Color(150, 150, 150), sf::Color(115, 115, 115))
	, m_fileNameLabel(0.f, 0.f, "File Name", m_font, 18, sf::Color(220, 220, 220))
	, m_fileNameTextBox(0.f, 0.f, 280.f, 30.f, m_font, 18)
	, m_gameVersionLabel(0.f, 0.f, "Game Version", m_font, 18, sf::Color(220, 220, 220))
	, m_gameVersionList(0.f, 0.f, 280.f, 24.f * 5, 24.f, m_font, {"Classic", "TBC", "WotLK", "Cataclysm", "MoP"})
	, m_classLabel(0.f, 0.f, "Class", m_font, 18, sf::Color(220, 220, 220))
	, m_classList(0.f, 0.f, 280.f, 24.f * 4, 24.f, m_font,
		{"Warrior", "Paladin", "Hunter", "Rogue", "Priest", "Death Knight", "Shaman", "Mage", "Warlock", "Monk", "Druid"})
	, m_classTypeLabel(0.f, 0.f, "Class Type", m_font, 18, sf::Color(220, 220, 220))
	, m_classTypeList(0.f, 0.f, 280.f, 24.f * 2, 24.f, m_font, {"Melee", "Range"})
	, m_spellsLabel(0.f, 0.f, "Spells", m_font, 18, sf::Color(220, 220, 220))
	, m_spellsList(0.f, 0.f, 280.f, 24.f * 6, 24.f, m_font, {})
	, m_addSpellButton(0.f, 0.f, 135.f, 32.f, m_font, "Add Spell", 16,
		sf::Color(240, 240, 240), sf::Color(255, 255, 255), sf::Color(255, 255, 255),
		sf::Color(85, 85, 85), sf::Color(105, 105, 105), sf::Color(70, 70, 70),
		sf::Color(130, 130, 130), sf::Color(150, 150, 150), sf::Color(115, 115, 115))
	, m_removeSpellButton(0.f, 0.f, 135.f, 32.f, m_font, "Remove", 16,
		sf::Color(240, 240, 240), sf::Color(255, 255, 255), sf::Color(255, 255, 255),
		sf::Color(85, 85, 85), sf::Color(105, 105, 105), sf::Color(70, 70, 70),
		sf::Color(130, 130, 130), sf::Color(150, 150, 150), sf::Color(115, 115, 115))
	, m_spellNameLabel(0.f, 0.f, "Spell Name", m_font, 18, sf::Color(220, 220, 220))
	, m_spellNameTextBox(0.f, 0.f, 420.f, 30.f, m_font, 18)
	, m_saveSpellButton(0.f, 0.f, 135.f, 24.f, m_font, "Save", 16,
		sf::Color(240, 240, 240), sf::Color(255, 255, 255), sf::Color(255, 255, 255),
		sf::Color(85, 85, 85), sf::Color(105, 105, 105), sf::Color(70, 70, 70),
		sf::Color(130, 130, 130), sf::Color(150, 150, 150), sf::Color(115, 115, 115))
	, m_spellIdLabel(0.f, 0.f, "Spell ID", m_font, 18, sf::Color(220, 220, 220))
	, m_spellIdTextBox(0.f, 0.f, 420.f, 30.f, m_font, 18)
	, m_spellTypeLabel(0.f, 0.f, "Spell Type", m_font, 18, sf::Color(220, 220, 220))
	, m_spellTypeList(0.f, 0.f, 220.f, 24.f * 4, 24.f, m_font, {"Combat", "Heal", "Food/Drink", "Buff/Aura"})
	, m_castCheckbox(0.f, 0.f, 20.f, m_font, "Cast", 18)
	, m_globalCooldownCheckbox(0.f, 0.f, 20.f, m_font, "Global Cooldown", 18)
	, m_priorityLabel(0.f, 0.f, "Priority", m_font, 18, sf::Color(220, 220, 220))
	, m_priorityTextBox(0.f, 0.f, 180.f, 30.f, m_font, 18)
	, m_optionGroupTypeLabel(0.f, 0.f, "Option Group Type", m_font, 18, sf::Color(220, 220, 220))
	, m_optionGroupTypeList(0.f, 0.f, 180.f, 24.f * 2, 24.f, m_font, {"AND", "OR"})
	, m_optionsCenterLabel(0.f, 0.f, "Options", m_font, 18, sf::Color(220, 220, 220))
	, m_optionsCenterList(0.f, 0.f, 180.f, 200.f, 24.f, m_font, {})
	, m_optionList(0.f, 0.f, 220.f, 24.f * 8, 24.f, m_font,
		{"Enemy health", "Player health", "Player mana", "Distance to enemy", "Power", "Player aura", "Enemy count"})
	, m_conditionList(0.f, 0.f, 110.f, 24.f * 6, 24.f, m_font, {"greater or equal", "greater than", "less or equal", "less than", "equal", "not equal"})
	, m_option_textbox(0.f, 0.f, 110.f, 30.f, m_font, 18)
	, m_addOptionButton(0.f, 0.f, 155.f, 32.f, m_font, "Add Option", 16,
		sf::Color(240, 240, 240), sf::Color(255, 255, 255), sf::Color(255, 255, 255),
		sf::Color(85, 85, 85), sf::Color(105, 105, 105), sf::Color(70, 70, 70),
		sf::Color(130, 130, 130), sf::Color(150, 150, 150), sf::Color(115, 115, 115))
	, m_removeOptionButton(0.f, 0.f, 155.f, 32.f, m_font, "Remove", 16, //rightContentWidth 314
		sf::Color(240, 240, 240), sf::Color(255, 255, 255), sf::Color(255, 255, 255),
		sf::Color(85, 85, 85), sf::Color(105, 105, 105), sf::Color(70, 70, 70),
		sf::Color(130, 130, 130), sf::Color(150, 150, 150), sf::Color(115, 115, 115))
	, m_spellsData()
	, m_currentSpellIndex(-1)
	, m_currentOptionIndex(-1)
	, m_addSpellPressed(false)
	, m_saveSpellPressed(false)
	, m_removeSpellPressed(false)
	, m_addOptionPressed(false)
	, m_removeOptionPressed(false)
	, m_importPressed(false)
	, m_exportPressed(false)
	, m_requestImportDialog(false)
	, m_requestExportDialog(false)
	, m_isSpellEditorVisible(false)
	, m_isCreatingSpell(false)
{
	m_marker.setFillColor(sf::Color({255, 0, 0, 60}));
	m_marker.setPosition(sf::Vector2f(0.f, 800.f));

	const auto size = mContext.window->getSize();
	m_background.setSize(sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y)));
	m_background.setFillColor(sf::Color(18, 18, 18));

	const float top = 60.f;
	const float panelGap = 8.f;
	const float leftX = 10.f;
	const float leftW = 320.f;
	const float rightW = 360.f;
	const float centerX = leftX + leftW + panelGap;
	const float centerW = size.x - leftW - rightW - panelGap * 2.f - 10.f;
	const float rightX = centerX + centerW + panelGap;

	m_leftPanel.setPosition(sf::Vector2f(leftX, top));
	m_leftPanel.setSize(sf::Vector2f(leftW, static_cast<float>(size.y) - top - panelGap));
	m_leftPanel.setFillColor(sf::Color(28, 28, 28));
	m_leftPanel.setOutlineThickness(1.f);
	m_leftPanel.setOutlineColor(sf::Color(70, 70, 70));

	m_centerPanel.setPosition(sf::Vector2f(centerX, top));
	m_centerPanel.setSize(sf::Vector2f(centerW, static_cast<float>(size.y) - top - panelGap));
	m_centerPanel.setFillColor(sf::Color(28, 28, 28));
	m_centerPanel.setOutlineThickness(1.f);
	m_centerPanel.setOutlineColor(sf::Color(70, 70, 70));

	m_rightPanel.setPosition(sf::Vector2f(rightX, top));
	m_rightPanel.setSize(sf::Vector2f(rightW - panelGap, static_cast<float>(size.y) - top - panelGap));
	m_rightPanel.setFillColor(sf::Color(28, 28, 28));
	m_rightPanel.setOutlineThickness(1.f);
	m_rightPanel.setOutlineColor(sf::Color(70, 70, 70));

	float leftY = 70.f;
	const float leftPadding = 20.f;
	const float leftContentX = m_leftPanel.getPosition().x + leftPadding;
	const float leftContentWidth = m_leftPanel.getSize().x - leftPadding * 2.f;
	const float gap = 8.f;

	m_importButton.setPosition(leftContentX, leftY);
	m_exportButton.setPosition(leftContentX + leftContentWidth - 135.f, leftY);
	leftY += m_importButton.getSize().y + gap * 2;

	m_fileNameLabel.setPosition(leftContentX, leftY);
	leftY += m_fileNameLabel.getSize().y + gap;
	m_fileNameTextBox.setPosition(leftContentX, leftY);
	m_fileNameTextBox.setSize(leftContentWidth, 30.f);
	leftY += m_fileNameTextBox.getSize().y + gap * 2;

	m_gameVersionLabel.setPosition(leftContentX, leftY);
	leftY += m_gameVersionLabel.getSize().y + gap;
	m_gameVersionList.setPosition(leftContentX, leftY);
	leftY += m_gameVersionList.getSize().y + gap * 2;

	m_classLabel.setPosition(leftContentX, leftY);
	leftY += m_classLabel.getSize().y + gap;
	m_classList.setPosition(leftContentX, leftY);
	leftY += m_classList.getSize().y + gap * 2;

	m_classTypeLabel.setPosition(leftContentX, leftY);
	leftY += m_classTypeLabel.getSize().y + gap;
	m_classTypeList.setPosition(leftContentX, leftY);
	leftY += m_classTypeList.getSize().y + gap * 2;

	m_spellsLabel.setPosition(leftContentX, leftY);
	leftY += m_spellsLabel.getSize().y + gap;
	m_spellsList.setPosition(leftContentX, leftY);
	leftY += m_spellsList.getSize().y + gap * 2;
	m_addSpellButton.setPosition(leftContentX, leftY);
	m_removeSpellButton.setPosition(leftContentX + leftContentWidth - 135.f, leftY);

	const float centerPadding = 18.f;
	const float centerContentX = m_centerPanel.getPosition().x + centerPadding;
	const float centerContentWidth = m_centerPanel.getSize().x - centerPadding * 2.f;
	float centerY = 95.f;

	m_saveSpellButton.setPosition(centerContentX + centerContentWidth - 135.f, 70.f);

	m_spellNameLabel.setPosition(centerContentX, centerY);
	centerY += m_spellNameLabel.getSize().y + gap;
	m_spellNameTextBox.setPosition(centerContentX, centerY);
	m_spellNameTextBox.setSize(centerContentWidth, 30.f);
	centerY += m_spellNameTextBox.getSize().y + gap * 2;

	m_spellIdLabel.setPosition(centerContentX, centerY);
	centerY += m_spellIdLabel.getSize().y + gap;
	m_spellIdTextBox.setPosition(centerContentX, centerY);
	m_spellIdTextBox.setSize(centerContentWidth, 30.f);
	centerY += m_spellIdTextBox.getSize().y + gap * 2;

	m_spellTypeLabel.setPosition(centerContentX, centerY);
	centerY += m_spellTypeLabel.getSize().y + gap;
	m_spellTypeList.setPosition(centerContentX, centerY);
	m_castCheckbox.setPosition(centerContentX + 260.f, centerY + 32.f);
	m_globalCooldownCheckbox.setPosition(centerContentX + 260.f, centerY + 66.f);
	centerY += m_spellTypeList.getSize().y + gap * 2;

	m_priorityLabel.setPosition(centerContentX, centerY);
	m_priorityTextBox.setPosition(centerContentX + 100.f, centerY - 4.f);
	centerY += std::max(m_priorityLabel.getSize().y, m_priorityTextBox.getSize().y) + gap * 2;

	m_optionGroupTypeLabel.setPosition(centerContentX, centerY);
	centerY += m_optionGroupTypeLabel.getSize().y + gap;
	m_optionGroupTypeList.setPosition(centerContentX, centerY);
	centerY += m_optionGroupTypeList.getSize().y + gap * 2;

	m_optionsCenterLabel.setPosition(centerContentX, centerY);
	centerY += m_optionsCenterLabel.getSize().y + gap;
	m_optionsCenterList.setPosition(centerContentX, centerY);
	m_optionsCenterList.setSize(centerContentWidth, 24.f * 9);

	const float rightPadding = 18.f;
	const float rightContentX = m_rightPanel.getPosition().x + rightPadding;
	const float rightContentWidth = m_rightPanel.getSize().x - rightPadding * 2.f;
	float rightY = 70.f;

	m_optionList.setPosition(rightContentX, rightY);
	m_optionList.setSize(rightContentWidth, 24.f * 7.f);
	rightY += m_optionList.getSize().y + gap * 2;

	m_conditionList.setPosition(rightContentX, rightY);
	m_conditionList.setSize(rightContentWidth, 24.f * 6.f);
	rightY += m_conditionList.getSize().y + gap * 2;

	m_option_textbox.setPosition(rightContentX, rightY);
	m_option_textbox.setSize(rightContentWidth, 30.f);
	rightY += m_option_textbox.getSize().y + gap * 2;

	m_addOptionButton.setPosition(rightContentX, rightY);
	m_removeOptionButton.setPosition(rightContentX + rightContentWidth - 150.f, rightY);

	m_gameVersionList.setSelectedIndex(0);
	m_classList.setSelectedIndex(0);
	m_classTypeList.setSelectedIndex(0);
	m_spellTypeList.setSelectedIndex(0);
	m_optionGroupTypeList.setSelectedIndex(0);
	m_optionList.setSelectedIndex(0);
	m_conditionList.setSelectedIndex(0);
	m_globalCooldownCheckbox.setChecked(true);
	setSpellEditorVisible(false);
}

void RotationState::handleEvent(const sf::Event& event)
{
	if(event.is<sf::Event::Closed>())
		mContext.window->close();

	m_fileNameTextBox.handleEvent(event);
	m_gameVersionList.handleEvent(event);
	m_classList.handleEvent(event);
	m_classTypeList.handleEvent(event);
	m_spellsList.handleEvent(event);
	if(m_isSpellEditorVisible)
	{
		m_spellNameTextBox.handleEvent(event);
		m_spellIdTextBox.handleEvent(event);
		m_spellTypeList.handleEvent(event);
		m_priorityTextBox.handleEvent(event);
		m_optionGroupTypeList.handleEvent(event);
		m_optionsCenterList.handleEvent(event);
		m_optionList.handleEvent(event);
		m_conditionList.handleEvent(event);
		m_option_textbox.handleEvent(event);
	}
}

void RotationState::update(sf::Time dt)
{
	const sf::Vector2i mousePos = sf::Mouse::getPosition(*mContext.window);
	const float dtSeconds = dt.asSeconds();

	m_importButton.update(mousePos, dtSeconds);
	m_exportButton.update(mousePos, dtSeconds);
	m_fileNameTextBox.update(mousePos, dtSeconds);
	m_gameVersionList.update(mousePos, dtSeconds);
	m_classList.update(mousePos, dtSeconds);
	m_classTypeList.update(mousePos, dtSeconds);
	m_spellsList.update(mousePos, dtSeconds);
	m_addSpellButton.update(mousePos, dtSeconds);
	m_removeSpellButton.update(mousePos, dtSeconds);
	if(m_isSpellEditorVisible)
	{
		m_saveSpellButton.update(mousePos, dtSeconds);
		m_spellNameTextBox.update(mousePos, dtSeconds);
		m_spellIdTextBox.update(mousePos, dtSeconds);
		m_spellTypeList.update(mousePos, dtSeconds);
		m_castCheckbox.update(mousePos, dtSeconds);
		m_globalCooldownCheckbox.update(mousePos, dtSeconds);
		m_priorityTextBox.update(mousePos, dtSeconds);
		m_optionGroupTypeList.update(mousePos, dtSeconds);
		m_optionsCenterList.update(mousePos, dtSeconds);
		m_optionList.update(mousePos, dtSeconds);
		m_conditionList.update(mousePos, dtSeconds);
		m_option_textbox.update(mousePos, dtSeconds);
		m_addOptionButton.update(mousePos, dtSeconds);
		m_removeOptionButton.update(mousePos, dtSeconds);
	}

	const int selectedSpell = m_spellsList.getSelectedIndex();
	if(selectedSpell != m_currentSpellIndex && selectedSpell >= 0)
	{
		m_isCreatingSpell = false;
		saveCurrentOptionFromUI();
		saveCurrentSpellFromUI();
		m_currentSpellIndex = selectedSpell;
		setSpellEditorVisible(true);
		loadSpellToUI(m_currentSpellIndex);
	}

	if(m_isSpellEditorVisible)
	{
		const int selectedOption = m_optionsCenterList.getSelectedIndex();
		if(selectedOption != m_currentOptionIndex)
		{
			saveCurrentOptionFromUI();
			m_currentOptionIndex = selectedOption;
			loadOptionToUI(m_currentOptionIndex);
		}
	}

	handleButtons();
}

void RotationState::render()
{
	mContext.window->draw(m_background);
	mContext.window->draw(m_leftPanel);
	mContext.window->draw(m_centerPanel);
	mContext.window->draw(m_rightPanel);

	m_importButton.render(*mContext.window);
	m_exportButton.render(*mContext.window);
	m_fileNameLabel.render(*mContext.window);
	m_fileNameTextBox.render(*mContext.window);
	m_gameVersionLabel.render(*mContext.window);
	m_gameVersionList.render(*mContext.window);
	m_classLabel.render(*mContext.window);
	m_classList.render(*mContext.window);
	m_classTypeLabel.render(*mContext.window);
	m_classTypeList.render(*mContext.window);
	m_spellsLabel.render(*mContext.window);
	m_spellsList.render(*mContext.window);
	m_addSpellButton.render(*mContext.window);
	m_removeSpellButton.render(*mContext.window);

	if(m_isSpellEditorVisible)
	{
		m_saveSpellButton.render(*mContext.window);
		m_spellNameLabel.render(*mContext.window);
		m_spellNameTextBox.render(*mContext.window);
		m_spellIdLabel.render(*mContext.window);
		m_spellIdTextBox.render(*mContext.window);
		m_spellTypeLabel.render(*mContext.window);
		m_spellTypeList.render(*mContext.window);
		m_castCheckbox.render(*mContext.window);
		m_globalCooldownCheckbox.render(*mContext.window);
		m_priorityLabel.render(*mContext.window);
		m_priorityTextBox.render(*mContext.window);
		m_optionGroupTypeLabel.render(*mContext.window);
		m_optionGroupTypeList.render(*mContext.window);
		m_optionsCenterLabel.render(*mContext.window);
		m_optionsCenterList.render(*mContext.window);
		m_addOptionButton.render(*mContext.window);
		m_removeOptionButton.render(*mContext.window);
		m_optionList.render(*mContext.window);
		m_conditionList.render(*mContext.window);
		m_option_textbox.render(*mContext.window);
	}

	mContext.window->draw(m_marker);
}

void RotationState::handleButtons()
{
	if(m_importButton.isPressed())
		importJson();
	if(m_exportButton.isPressed())
		exportJson();
	if(m_addSpellButton.isPressed())
		addSpellUIItem();
	if(m_removeSpellButton.isPressed())
		removeSelectedSpellUIItem();
	if(m_isSpellEditorVisible && m_saveSpellButton.isPressed())
		saveSpellUIItem();
	if(m_isSpellEditorVisible && m_addOptionButton.isPressed())
		addOptionUIItem();
	if(m_isSpellEditorVisible && m_removeOptionButton.isPressed())
		removeSelectedOptionUIItem();
}

void RotationState::addSpellUIItem()
{
	setSpellEditorVisible(true);
	m_isCreatingSpell = true;
	m_currentSpellIndex = -1;
	m_currentOptionIndex = -1;
	m_spellsList.setSelectedIndex(-1);
	clearSpellEditorForNewSpell();
	refreshOptionsCenterList();
	m_optionsCenterList.setSelectedIndex(-1);
	loadOptionToUI(-1);
}

void RotationState::saveSpellUIItem()
{
	if(m_currentSpellIndex < 0)
	{
		SpellData spell;
		spell.name = m_spellNameTextBox.getValue();
		if(spell.name.empty())
			spell.name = "Spell";
		spell.spellId = m_spellIdTextBox.getValue();
		spell.spellType = getSelectedItemOrEmpty(m_spellTypeList);
		spell.cast = m_castCheckbox.isChecked();
		spell.globalCooldown = m_globalCooldownCheckbox.isChecked();
		spell.priority = m_priorityTextBox.getValue();
		spell.optionGroupType = getSelectedItemOrEmpty(m_optionGroupTypeList);
		m_spellsData.push_back(spell);
		m_currentSpellIndex = static_cast<int>(m_spellsData.size()) - 1;
		m_isCreatingSpell = false;
		m_spellsList.setSelectedIndex(m_currentSpellIndex);
		saveCurrentOptionFromUI();
		refreshSpellsList();
		m_spellsList.setSelectedIndex(m_currentSpellIndex);
		return;
	}

	saveCurrentOptionFromUI();
	saveCurrentSpellFromUI();
}

void RotationState::removeSelectedSpellUIItem()
{
	const int selected = m_spellsList.getSelectedIndex();
	if(selected < 0 || selected >= static_cast<int>(m_spellsData.size()))
		return;

	m_spellsData.erase(m_spellsData.begin() + selected);
	refreshSpellsList();

	if(m_spellsData.empty())
	{
		m_currentSpellIndex = -1;
		m_currentOptionIndex = -1;
		loadSpellToUI(-1);
		setSpellEditorVisible(false);
		return;
	}

	m_currentSpellIndex = std::clamp(selected, 0, static_cast<int>(m_spellsData.size()) - 1);
	m_spellsList.setSelectedIndex(m_currentSpellIndex);
	loadSpellToUI(m_currentSpellIndex);
}

void RotationState::addOptionUIItem()
{
	if(m_currentSpellIndex < 0 || m_currentSpellIndex >= static_cast<int>(m_spellsData.size()))
		return;

	OptionData option;
	option.field = getSelectedItemOrEmpty(m_optionList);
	option.condition = getSelectedItemOrEmpty(m_conditionList);
	option.value = m_option_textbox.getValue();
	if(option.field.empty())
		option.field = "Enemy Health";
	if(option.condition.empty())
		option.condition = "greater or equal";
	if(option.value.empty())
		option.value = "0";

	m_spellsData[static_cast<std::size_t>(m_currentSpellIndex)].options.push_back(option);
	refreshOptionsCenterList();
	m_currentOptionIndex = static_cast<int>(m_spellsData[static_cast<std::size_t>(m_currentSpellIndex)].options.size()) - 1;
	m_optionsCenterList.setSelectedIndex(m_currentOptionIndex);
	loadOptionToUI(m_currentOptionIndex);
}

void RotationState::removeSelectedOptionUIItem()
{
	if(m_currentSpellIndex < 0 || m_currentSpellIndex >= static_cast<int>(m_spellsData.size()))
		return;

	auto& options = m_spellsData[static_cast<std::size_t>(m_currentSpellIndex)].options;
	int selected = m_optionsCenterList.getSelectedIndex();
	if(selected < 0)
		selected = m_currentOptionIndex;
	if(selected < 0 || selected >= static_cast<int>(options.size()))
		return;

	options.erase(options.begin() + selected);
	refreshOptionsCenterList();

	if(options.empty())
	{
		m_currentOptionIndex = -1;
		m_optionsCenterList.setSelectedIndex(-1);
		loadOptionToUI(-1);
		return;
	}

	m_currentOptionIndex = std::clamp(selected, 0, static_cast<int>(options.size()) - 1);
	m_optionsCenterList.setSelectedIndex(m_currentOptionIndex);
	loadOptionToUI(m_currentOptionIndex);
}

void RotationState::saveCurrentSpellFromUI()
{
	if(m_currentSpellIndex < 0 || m_currentSpellIndex >= static_cast<int>(m_spellsData.size()))
		return;

	saveCurrentOptionFromUI();

	SpellData& spell = m_spellsData[static_cast<std::size_t>(m_currentSpellIndex)];
	spell.name = m_spellNameTextBox.getValue();
	if(spell.name.empty())
		spell.name = "Spell";
	spell.spellId = m_spellIdTextBox.getValue();
	spell.spellType = getSelectedItemOrEmpty(m_spellTypeList);
	spell.cast = m_castCheckbox.isChecked();
	spell.globalCooldown = m_globalCooldownCheckbox.isChecked();
	spell.priority = m_priorityTextBox.getValue();
	spell.optionGroupType = getSelectedItemOrEmpty(m_optionGroupTypeList);

	refreshSpellsList();
	m_spellsList.setSelectedIndex(m_currentSpellIndex);
}

void RotationState::loadSpellToUI(int index)
{
	if(index < 0 || index >= static_cast<int>(m_spellsData.size()))
	{
		m_spellNameTextBox.setValue("");
		m_spellIdTextBox.setValue("");
		m_priorityTextBox.setValue("");
		m_castCheckbox.setChecked(false);
		m_globalCooldownCheckbox.setChecked(true);
		m_spellTypeList.setSelectedIndex(0);
		m_optionGroupTypeList.setSelectedIndex(0);
		m_optionsCenterList.clear();
		m_currentOptionIndex = -1;
		loadOptionToUI(-1);
		return;
	}

	const SpellData& spell = m_spellsData[static_cast<std::size_t>(index)];
	m_spellNameTextBox.setValue(spell.name);
	m_spellIdTextBox.setValue(spell.spellId);
	setSelectedItem(m_spellTypeList, spell.spellType);
	m_castCheckbox.setChecked(spell.cast);
	m_globalCooldownCheckbox.setChecked(spell.globalCooldown);
	m_priorityTextBox.setValue(spell.priority);
	setSelectedItem(m_optionGroupTypeList, spell.optionGroupType);

	refreshOptionsCenterList();
	if(spell.options.empty())
	{
		m_currentOptionIndex = -1;
		m_optionsCenterList.setSelectedIndex(-1);
		loadOptionToUI(-1);
	}
	else
	{
		m_currentOptionIndex = 0;
		m_optionsCenterList.setSelectedIndex(0);
		loadOptionToUI(0);
	}
}

void RotationState::saveCurrentOptionFromUI()
{
	if(m_currentSpellIndex < 0 || m_currentSpellIndex >= static_cast<int>(m_spellsData.size()))
		return;
	if(m_currentOptionIndex < 0)
		return;

	auto& options = m_spellsData[static_cast<std::size_t>(m_currentSpellIndex)].options;
	if(m_currentOptionIndex >= static_cast<int>(options.size()))
		return;

	OptionData& option = options[static_cast<std::size_t>(m_currentOptionIndex)];
	option.field = getSelectedItemOrEmpty(m_optionList);
	option.condition = getSelectedItemOrEmpty(m_conditionList);
	option.value = m_option_textbox.getValue();

	refreshOptionsCenterList();
	m_optionsCenterList.setSelectedIndex(m_currentOptionIndex);
}

void RotationState::loadOptionToUI(int index)
{
	if(m_currentSpellIndex < 0 || m_currentSpellIndex >= static_cast<int>(m_spellsData.size()))
	{
		m_optionList.setSelectedIndex(0);
		m_conditionList.setSelectedIndex(0);
		m_option_textbox.setValue("");
		return;
	}

	const auto& options = m_spellsData[static_cast<std::size_t>(m_currentSpellIndex)].options;
	if(index < 0 || index >= static_cast<int>(options.size()))
	{
		m_optionList.setSelectedIndex(0);
		m_conditionList.setSelectedIndex(0);
		m_option_textbox.setValue("");
		return;
	}

	const OptionData& option = options[static_cast<std::size_t>(index)];
	setSelectedItem(m_optionList, option.field);
	setSelectedItem(m_conditionList, option.condition);
	m_option_textbox.setValue(option.value);
}

void RotationState::refreshSpellsList()
{
	std::vector<std::string> items;
	items.reserve(m_spellsData.size());
	for(std::size_t i = 0; i < m_spellsData.size(); ++i)
	{
		const std::string& name = m_spellsData[i].name;
		items.push_back(name.empty() ? "Spell" : name);
	}
	m_spellsList.setItems(items);
}

void RotationState::refreshOptionsCenterList()
{
	if(m_currentSpellIndex < 0 || m_currentSpellIndex >= static_cast<int>(m_spellsData.size()))
	{
		m_optionsCenterList.clear();
		return;
	}

	const auto& options = m_spellsData[static_cast<std::size_t>(m_currentSpellIndex)].options;
	std::vector<std::string> items;
	items.reserve(options.size());
	for(const OptionData& option : options)
		items.push_back(buildOptionDisplayText(option));
	m_optionsCenterList.setItems(items);
}

std::string RotationState::buildOptionDisplayText(const OptionData& option) const
{
	const std::string field = option.field.empty() ? "?" : option.field;
	const std::string condition = option.condition.empty() ? "?" : option.condition;
	const std::string value = option.value.empty() ? "?" : option.value;
	return field + " " + condition + " " + value;
}

std::string RotationState::getSelectedItemOrEmpty(const gui::List& list)
{
	const int index = list.getSelectedIndex();
	if(index < 0)
		return "";
	return list.getItem(static_cast<std::size_t>(index));
}

void RotationState::setSelectedItem(gui::List& list, const std::string& value)
{
	for(int i = 0; i < list.getItemCount(); ++i)
	{
		if(list.getItem(static_cast<std::size_t>(i)) == value)
		{
			list.setSelectedIndex(i);
			return;
		}
	}
	list.setSelectedIndex(0);
}



void RotationState::setSpellEditorVisible(bool visible)
{
	m_isSpellEditorVisible = visible;

	auto setWidgetState = [visible](gui::Widget& widget)
	{
		widget.setVisible(visible);
		widget.setEnabled(visible);
	};

	setWidgetState(m_saveSpellButton);
	setWidgetState(m_spellNameLabel);
	setWidgetState(m_spellNameTextBox);
	setWidgetState(m_spellIdLabel);
	setWidgetState(m_spellIdTextBox);
	setWidgetState(m_spellTypeLabel);
	setWidgetState(m_spellTypeList);
	setWidgetState(m_castCheckbox);
	setWidgetState(m_globalCooldownCheckbox);
	setWidgetState(m_priorityLabel);
	setWidgetState(m_priorityTextBox);
	setWidgetState(m_optionGroupTypeLabel);
	setWidgetState(m_optionGroupTypeList);
	setWidgetState(m_optionsCenterLabel);
	setWidgetState(m_optionsCenterList);
	setWidgetState(m_addOptionButton);
	setWidgetState(m_removeOptionButton);
	setWidgetState(m_optionList);
	setWidgetState(m_conditionList);
	setWidgetState(m_option_textbox);
}

void RotationState::clearSpellEditorForNewSpell()
{
	m_spellNameTextBox.setValue("");
	m_spellIdTextBox.setValue("");
	m_spellTypeList.setSelectedIndex(0);
	m_castCheckbox.setChecked(false);
	m_globalCooldownCheckbox.setChecked(true);
	m_priorityTextBox.setValue("");
	m_optionGroupTypeList.setSelectedIndex(0);
	m_optionList.setSelectedIndex(0);
	m_conditionList.setSelectedIndex(0);
	m_option_textbox.setValue("");
}

void RotationState::importJson()
{
	const char* patterns[] = {"*.json"};
	const char* filePath = tinyfd_openFileDialog("Import rotation JSON", "data/rotations", 1, patterns, "JSON files", 0);
	if(!filePath)
		return;

	std::ifstream in(filePath);
	if(!in.is_open())
		return;

	nlohmann::json json;
	try { in >> json; } catch(...) { return; }

	if(json.contains("file_name") && json["file_name"].is_string())
		m_fileNameTextBox.setValue(json["file_name"].get<std::string>());
	if(json.contains("game_version") && json["game_version"].is_string())
		setSelectedItem(m_gameVersionList, json["game_version"].get<std::string>());
	if(json.contains("class") && json["class"].is_string())
		setSelectedItem(m_classList, json["class"].get<std::string>());
	if(json.contains("class_type") && json["class_type"].is_string())
		setSelectedItem(m_classTypeList, json["class_type"].get<std::string>());

	m_spellsData.clear();
	if(json.contains("spells") && json["spells"].is_array())
	{
		for(const auto& spellJson : json["spells"])
		{
			SpellData spell;
			if(spellJson.contains("name") && spellJson["name"].is_string())
				spell.name = spellJson["name"].get<std::string>();
			if(spellJson.contains("spell_id"))
			{
				if(spellJson["spell_id"].is_string())
					spell.spellId = spellJson["spell_id"].get<std::string>();
				else if(spellJson["spell_id"].is_number_integer())
					spell.spellId = std::to_string(spellJson["spell_id"].get<int>());
			}
			if(spellJson.contains("spell_type") && spellJson["spell_type"].is_string())
				spell.spellType = spellJson["spell_type"].get<std::string>();
			if(spellJson.contains("cast") && spellJson["cast"].is_boolean())
				spell.cast = spellJson["cast"].get<bool>();
			if(spellJson.contains("global_cooldown") && spellJson["global_cooldown"].is_boolean())
				spell.globalCooldown = spellJson["global_cooldown"].get<bool>();
			if(spellJson.contains("priority"))
			{
				if(spellJson["priority"].is_string())
					spell.priority = spellJson["priority"].get<std::string>();
				else if(spellJson["priority"].is_number_integer())
					spell.priority = std::to_string(spellJson["priority"].get<int>());
			}
			if(spellJson.contains("option_group_type") && spellJson["option_group_type"].is_string())
				spell.optionGroupType = spellJson["option_group_type"].get<std::string>();
			if(spellJson.contains("options") && spellJson["options"].is_array())
			{
				for(const auto& optionJson : spellJson["options"])
				{
					OptionData option;
					if(optionJson.contains("field") && optionJson["field"].is_string())
						option.field = optionJson["field"].get<std::string>();
					if(optionJson.contains("condition") && optionJson["condition"].is_string())
						option.condition = optionJson["condition"].get<std::string>();
					if(optionJson.contains("value"))
					{
						if(optionJson["value"].is_string())
							option.value = optionJson["value"].get<std::string>();
						else if(optionJson["value"].is_number_integer())
							option.value = std::to_string(optionJson["value"].get<int>());
					}
					spell.options.push_back(option);
				}
			}
			m_spellsData.push_back(spell);
		}
	}

	refreshSpellsList();
	if(m_spellsData.empty())
	{
		m_currentSpellIndex = -1;
		m_spellsList.setSelectedIndex(-1);
		loadSpellToUI(-1);
		setSpellEditorVisible(false);
	}
	else
	{
		setSpellEditorVisible(true);
		m_currentSpellIndex = 0;
		m_spellsList.setSelectedIndex(0);
		loadSpellToUI(0);
	}
}

void RotationState::exportJson()
{
	saveCurrentOptionFromUI();
	saveCurrentSpellFromUI();

	std::string fileName = m_fileNameTextBox.getValue();
	if(fileName.empty())
		fileName = "rotation";

	nlohmann::json json;
	json["schema_version"] = 1;
	json["file_name"] = fileName;
	json["game_version"] = getSelectedItemOrEmpty(m_gameVersionList);
	json["class"] = getSelectedItemOrEmpty(m_classList);
	json["class_type"] = getSelectedItemOrEmpty(m_classTypeList);
	json["spells"] = nlohmann::json::array();
	for(const SpellData& spell : m_spellsData)
	{
		nlohmann::json s;
		s["name"] = spell.name;
		s["spell_id"] = spell.spellId;
		s["spell_type"] = spell.spellType;
		s["cast"] = spell.cast;
		s["global_cooldown"] = spell.globalCooldown;
		s["priority"] = spell.priority;
		s["option_group_type"] = spell.optionGroupType;
		s["options"] = nlohmann::json::array();
		for(const OptionData& option : spell.options)
			s["options"].push_back({{"field", option.field}, {"condition", option.condition}, {"value", option.value}});
		json["spells"].push_back(s);
	}
	const std::filesystem::path dir = std::filesystem::path("data") / "rotations" / getSelectedItemOrEmpty(m_gameVersionList) / getSelectedItemOrEmpty(m_classList);
	std::filesystem::create_directories(dir);
	const std::filesystem::path outPath = dir / (fileName + ".json");
	std::ofstream out(outPath);
	if(out.is_open())
		out << json.dump(2);
}
