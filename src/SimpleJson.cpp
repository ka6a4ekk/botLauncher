#include "stdafx.h"
#include "SimpleJson.hpp"

#include <cctype>

namespace
{
	bool isWs(char c)
	{
		return c == ' ' || c == '\n' || c == '\t' || c == '\r';
	}

	std::size_t skipWs(const std::string& s, std::size_t i)
	{
		while(i < s.size() && isWs(s[i]))
			++i;
		return i;
	}

	std::optional<std::size_t> findKeyPos(const std::string& text, const std::string& key)
	{
		const std::string needle = "\"" + key + "\"";
		const std::size_t pos = text.find(needle);
		if(pos == std::string::npos)
			return std::nullopt;
		std::size_t colon = text.find(':', pos + needle.size());
		if(colon == std::string::npos)
			return std::nullopt;
		return skipWs(text, colon + 1);
	}
}

namespace simplejson
{
	std::string escape(const std::string& value)
	{
		std::string out;
		out.reserve(value.size());
		for(char c : value)
		{
			switch(c)
			{
			case '\\': out += "\\\\"; break;
			case '"': out += "\\\""; break;
			case '\n': out += "\\n"; break;
			case '\r': out += "\\r"; break;
			case '\t': out += "\\t"; break;
			default: out += c; break;
			}
		}
		return out;
	}

	std::optional<std::string> findString(const std::string& text, const std::string& key)
	{
		auto p = findKeyPos(text, key);
		if(!p || *p >= text.size() || text[*p] != '"')
			return std::nullopt;

		std::string out;
		for(std::size_t i = *p + 1; i < text.size(); ++i)
		{
			char c = text[i];
			if(c == '\\' && i + 1 < text.size())
			{
				char n = text[++i];
				switch(n)
				{
				case 'n': out += '\n'; break;
				case 'r': out += '\r'; break;
				case 't': out += '\t'; break;
				case '"': out += '"'; break;
				case '\\': out += '\\'; break;
				default: out += n; break;
				}
				continue;
			}
			if(c == '"')
				return out;
			out += c;
		}
		return std::nullopt;
	}

	std::optional<bool> findBool(const std::string& text, const std::string& key)
	{
		auto p = findKeyPos(text, key);
		if(!p)
			return std::nullopt;
		if(text.compare(*p, 4, "true") == 0)
			return true;
		if(text.compare(*p, 5, "false") == 0)
			return false;
		return std::nullopt;
	}

	std::optional<double> findNumber(const std::string& text, const std::string& key)
	{
		auto p = findKeyPos(text, key);
		if(!p)
			return std::nullopt;
		std::size_t i = *p;
		if(i < text.size() && (text[i] == '-' || text[i] == '+'))
			++i;
		while(i < text.size() && (std::isdigit(static_cast<unsigned char>(text[i])) || text[i] == '.'))
			++i;
		if(i == *p)
			return std::nullopt;
		try
		{
			return std::stod(text.substr(*p, i - *p));
		}
		catch(...)
		{
			return std::nullopt;
		}
	}
}
