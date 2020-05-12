#pragma once

#include <string>
#include <deque>

namespace Commands
{
	namespace Info
	{
		static constexpr const char* const COMMAND_NAME = "info";

		void invoke(const std::string& name, const std::deque<std::string>& args);
	}
}
