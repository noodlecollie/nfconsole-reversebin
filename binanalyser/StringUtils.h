#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <sstream>

namespace StringUtils
{
	template<typename CONTAINER>
	inline void splitString(const std::string& str, CONTAINER& container, char delim = ' ')
	{
		std::stringstream ss(str);
		std::string token;

		while ( std::getline(ss, token, delim) )
		{
			container.push_back(token);
		}
	}

	std::string& trimStart(std::string& s)
	{
		auto it = std::find_if(s.begin(), s.end(), [](char c)
		{
			return !std::isspace<char>(c, std::locale::classic());
		});

		s.erase(s.begin(), it);
		return s;
	}

	std::string& trimEnd(std::string& s)
	{
		auto it = std::find_if(s.rbegin(), s.rend(), [](char c)
		{
			return !std::isspace<char>(c, std::locale::classic());
		});

		s.erase(it.base(), s.end());
		return s;
	}

	std::string& trim(std::string& s)
	{
		return trimStart(trimEnd(s));
	}
}
