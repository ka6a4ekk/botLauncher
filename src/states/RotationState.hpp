#pragma once

#include "State.hpp"

#include <SFML/Graphics.hpp>

#include "gui/Button.hpp"
#include "gui/Checkbox.hpp"
#include "gui/Label.hpp"
#include "gui/List.hpp"
#include "gui/TextBox.hpp"

#include <string>
#include <vector>

class RotationState : public State
{
private:
	struct OptionData
	{
		std::string field;
		std::string condition;
		std::string value;
	};

	struct SpellData
	{
		std::string name;
		std::string spellId;
		std::string spellType;
		bool cast = false;
		bool globalCooldown = true;
		std::string priority;
		std::string optionGroupType;
		std::vector<OptionData> options;
	};

public:
	RotationState(StateStack& stack, State::Context context);
	~RotationState() override = default;

	void handleEvent(const sf::Event& event) override;
	void update(sf::Time dt) override;
	void render() override;

private:
	void handleButtons();
	void addSpellUIItem();
	void saveSpellUIItem();
	void removeSelectedSpellUIItem();
	void addOptionUIItem();
	void removeSelectedOptionUIItem();
	void saveCurrentSpellFromUI();
	void loadSpellToUI(int index);
	void saveCurrentOptionFromUI();
	void loadOptionToUI(int index);
	void refreshSpellsList();
	void refreshOptionsCenterList();
	void setSpellEditorVisible(bool visible);
	void clearSpellEditorForNewSpell();
	std::string buildOptionDisplayText(const OptionData& option) const;
	void importJson();
	void exportJson();
	static std::string getSelectedItemOrEmpty(const gui::List& list);
	static void setSelectedItem(gui::List& list, const std::string& value);

	sf::RectangleShape m_marker;

	sf::Font m_font;
	sf::RectangleShape m_background;
	sf::RectangleShape m_leftPanel;
	sf::RectangleShape m_centerPanel;
	sf::RectangleShape m_rightPanel;

	gui::Button m_importButton;
	gui::Button m_exportButton;

	gui::Label m_fileNameLabel;
	gui::TextBox m_fileNameTextBox;

	gui::Label m_gameVersionLabel;
	gui::List m_gameVersionList;

	gui::Label m_classLabel;
	gui::List m_classList;

	gui::Label m_classTypeLabel;
	gui::List m_classTypeList;

	gui::Label m_spellsLabel;
	gui::List m_spellsList;
	gui::Button m_addSpellButton;
	gui::Button m_removeSpellButton;

	gui::Label m_spellNameLabel;
	gui::TextBox m_spellNameTextBox;
	gui::Button m_saveSpellButton;

	gui::Label m_spellIdLabel;
	gui::TextBox m_spellIdTextBox;

	gui::Label m_spellTypeLabel;
	gui::List m_spellTypeList;

	gui::Checkbox m_castCheckbox;
	gui::Checkbox m_globalCooldownCheckbox;

	gui::Label m_priorityLabel;
	gui::TextBox m_priorityTextBox;

	gui::Label m_optionGroupTypeLabel;
	gui::List m_optionGroupTypeList;
	gui::Label m_optionsCenterLabel;
	gui::List m_optionsCenterList;

	gui::List m_optionList;
	gui::List m_conditionList;
	gui::TextBox m_option_textbox;
	gui::Button m_addOptionButton;
	gui::Button m_removeOptionButton;

	std::vector<SpellData> m_spellsData;
	int m_currentSpellIndex;
	int m_currentOptionIndex;

	bool m_addSpellPressed;
	bool m_saveSpellPressed;
	bool m_removeSpellPressed;
	bool m_addOptionPressed;
	bool m_removeOptionPressed;
	bool m_importPressed;
	bool m_exportPressed;
	bool m_requestImportDialog;
	bool m_requestExportDialog;
	bool m_isSpellEditorVisible;
	bool m_isCreatingSpell;
};
