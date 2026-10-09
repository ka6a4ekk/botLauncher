#include "stdafx.h"
#include "ConfigParser.hpp"

#include <cctype>
#include <fstream>

std::string ConfigParser::toUpper(std::string value)
{
	for (char& ch : value)
		ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
	return value;
}

std::string ConfigParser::stripComment(const std::string& line)
{
	const size_t pos = line.find("//");
	if (pos == std::string::npos)
		return line;
	return line.substr(0, pos);
}

std::vector<std::string> ConfigParser::splitTokens(const std::string& line)
{
	std::vector<std::string> tokens;
	std::string current;
	bool inQuotes = false;

	for (char ch : line)
	{
		if (ch == '\"')
		{
			inQuotes = !inQuotes;
			continue;
		}

		if (!inQuotes && std::isspace(static_cast<unsigned char>(ch)))
		{
			if (!current.empty())
			{
				tokens.push_back(current);
				current.clear();
			}
			continue;
		}

		current.push_back(ch);
	}

	if (!current.empty())
		tokens.push_back(current);

	return tokens;
}

ConfigParser::LoadResult ConfigParser::load(const std::string& path, Data& out) const
{
	std::ifstream ifs(path);
	if (!ifs)
	{
		if (tryGenerateConfig(path))
		{
			return LoadResult::MISSING;
		}
		return LoadResult::ERROR;
	}

	std::string line;
	while (std::getline(ifs, line))
	{
		line = stripComment(line);
		if (line.empty())
			continue;

		const auto tokens = splitTokens(line);
		if (tokens.empty())
			continue;

		const std::string cmd = toUpper(tokens[0]);

		if ((cmd == "SETA") && tokens.size() >= 3)
		{
			std::string value;
			for (size_t i = 2; i < tokens.size(); ++i)
			{
				if (i > 2)
					value += " ";
				value += tokens[i];
			}
			out.m_cvars[tokens[1]] = value;
		}
		else if (cmd == "BIND")
		{
			// later
		}
	}

	return LoadResult::OK;
}

bool ConfigParser::tryGenerateConfig(const std::string& path)
{
	std::ofstream ofs(path);
	if (!ofs)
		return false;

	ofs << "seta r_width 1280\n";
	ofs << "seta r_height 800\n";
	ofs << "seta r_fps 144\n";
	ofs << "seta r_vsync 0\n";
	return true;
}
