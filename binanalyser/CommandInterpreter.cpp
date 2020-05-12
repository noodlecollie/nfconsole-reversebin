#include <iostream>

#include "CommandInterpreter.h"
#include "StringUtils.h"

CommandInterpreter::CommandInterpreter(const std::string& helpCommand, const std::string& quitCommand) :
	m_HelpCommand(helpCommand),
	m_QuitCommand(quitCommand)
{
	StringUtils::trim(m_HelpCommand);
	StringUtils::trim(m_QuitCommand);

	if ( m_HelpCommand.size() < 1 )
	{
		throw std::runtime_error("Help command string must not be empty.");
	}

	if ( m_QuitCommand.size() < 1 )
	{
		throw std::runtime_error("Quit command string must not be empty.");
	}
}

void CommandInterpreter::addCommand(const std::string& commandName, const CommandCallback& callback)
{
	std::string name = commandName;
	StringUtils::trim(name);

	if ( name.size() < 1 )
	{
		throw std::invalid_argument("Command name was not valid.");
	}

	if ( !callback )
	{
		throw std::invalid_argument("Command callback was not valid.");
	}

	m_CommandHandlers.push_back(CommandEntry(name, callback));
}

void CommandInterpreter::run()
{
	std::cout << "Type '" << m_HelpCommand << "' for help, or '" << m_QuitCommand << "' to quit." << std::endl;

	std::string line;
	std::deque<std::string> tokens;

	while ( std::getline(std::cin, line) )
	{
		StringUtils::trim(line);

		tokens.clear();
		StringUtils::splitString(line, tokens);

		if ( !handleInput(tokens) )
		{
			break;
		}
	}
}

bool CommandInterpreter::handleInput(std::deque<std::string>& tokens)
{
	if ( tokens.size() < 1 )
	{
		return true;
	}

	if ( tokens[0] == m_QuitCommand )
	{
		std::cout << "Quitting." << std::endl;
		return false;
	}

	if ( tokens[0] == m_HelpCommand )
	{
		printHelp();
		return true;
	}

	for ( const CommandEntry& entry : m_CommandHandlers )
	{
		if ( entry.first == tokens[0] )
		{
			tokens.pop_front();
			entry.second(entry.first, tokens);
			return true;
		}
	}

	std::cout << "Unrecognised command: " << tokens[0] << std::endl;
	return true;
}

void CommandInterpreter::printHelp()
{
	std::cout << (m_CommandHandlers.size() + 2) << " available commands:" << std::endl;

	for ( const CommandEntry& entry : m_CommandHandlers )
	{
		std::cout << "  " << entry.first << std::endl;
	}

	std::cout << "  " << m_HelpCommand << std::endl;
	std::cout << "  " << m_QuitCommand << std::endl;
}
