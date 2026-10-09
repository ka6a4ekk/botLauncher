#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace rotation
{
	enum class GameVersion : std::uint8_t
	{
		Classic,
		TBC,
		WotLK,
		Cataclysm,
		MoP
	};

	enum class ClassName : std::uint8_t
	{
		Warrior,
		Paladin,
		Hunter,
		Rogue,
		Priest,
		DeathKnight,
		Shaman,
		Mage,
		Warlock,
		Monk,
		Druid
	};

	enum class ClassType : std::uint8_t
	{
		Melee,
		Range
	};

	enum class PowerType : std::uint8_t
	{
		None,
		Rage,
		HolyPower,
		Focus,
		Energy,
		RunicPower,
		Chi
	};

	enum class SpellType : std::uint8_t
	{
		Combat,
		Heal,
		FoodDrink,
		BuffAura
	};

	enum class OptionGroupType : std::uint8_t
	{
		And,
		Or
	};

	enum class ConditionOp : std::uint8_t
	{
		Ge,
		Gt,
		Le,
		Lt,
		Eq,
		Ne
	};

	struct ClassInfo
	{
		ClassName name;
		PowerType power;
		int powerMin;
		int powerMax;
		bool usesMana;
		bool canMelee;
		bool canRange;
	};

	inline constexpr std::array<std::string_view, 5> kGameVersionNames = {
		"Classic",
		"TBC",
		"WotLK",
		"Cataclysm",
		"MoP"
	};

	inline constexpr std::array<std::string_view, 11> kClassNames = {
		"Warrior",
		"Paladin",
		"Hunter",
		"Rogue",
		"Priest",
		"Death Knight",
		"Shaman",
		"Mage",
		"Warlock",
		"Monk",
		"Druid"
	};

	inline constexpr std::array<std::string_view, 2> kClassTypeNames = {
		"Melee",
		"Range"
	};

	inline constexpr std::array<std::string_view, 4> kSpellTypeNames = {
		"Combat",
		"Heal",
		"Food/Drink",
		"Buff/Aura"
	};

	inline constexpr std::array<std::string_view, 2> kOptionGroupNames = {
		"AND",
		"OR"
	};

	inline constexpr std::array<std::string_view, 6> kConditionNames = {
		"ge",
		"gt",
		"le",
		"lt",
		"eq",
		"ne"
	};

	inline constexpr std::array<std::string_view, 7> kOptionFieldNames = {
		"Enemy Health",
		"Player Health",
		"Player Mana",
		"Distance To Enemy",
		"Power",
		"Player Aura",
		"Enemy Count"
	};

	inline constexpr std::array<ClassInfo, 11> kClassInfo = {{
		{ClassName::Warrior, PowerType::Rage, 0, 100, false, true, false},
		{ClassName::Paladin, PowerType::HolyPower, 0, 3, true, true, false},
		{ClassName::Hunter, PowerType::Focus, 0, 100, true, false, true},
		{ClassName::Rogue, PowerType::Energy, 0, 100, false, true, false},
		{ClassName::Priest, PowerType::None, 0, 0, true, false, true},
		{ClassName::DeathKnight, PowerType::RunicPower, 0, 100, false, true, false},
		{ClassName::Shaman, PowerType::None, 0, 0, true, true, true},
		{ClassName::Mage, PowerType::None, 0, 0, true, false, true},
		{ClassName::Warlock, PowerType::None, 0, 0, true, false, true},
		{ClassName::Monk, PowerType::Chi, 0, 5, false, true, false},
		{ClassName::Druid, PowerType::Energy, 0, 100, true, true, true}
	}};
}
