#pragma once

#include <string>
#include <functional>
#include <vector>
#include <deque>
#include <utility>

class CommandInterpreter
{
public:
	using CommandCallback = std::function<void(const std::string&, const std::deque<std::string>&)>;

	static constexpr const char* CMD_QUIT = "quit";

	explicit CommandInterpreter(const std::string& quitCommand = CMD_QUIT);

	void addCommand(const std::string& commandName, const CommandCallback& callback);
	void run();

private:
	using CommandEntry = std::pair<std::string, CommandCallback>;

	bool handleInput(std::deque<std::string>& tokens);

	std::string m_QuitCommand;
	std::vector<CommandEntry> m_CommandHandlers;
};
