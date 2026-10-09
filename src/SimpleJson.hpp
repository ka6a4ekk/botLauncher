#pragma once

#include <optional>
#include <string>

namespace simplejson
{
	std::string escape(const std::string& value);
	std::optional<std::string> findString(const std::string& text, const std::string& key);
	std::optional<bool> findBool(const std::string& text, const std::string& key);
	std::optional<double> findNumber(const std::string& text, const std::string& key);
}
