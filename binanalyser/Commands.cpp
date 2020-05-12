#include "Commands.h"
#include "commands/Info.h"

namespace Commands
{
	void addAllCommands(CommandInterpreter& interpreter)
	{
		interpreter.addCommand(Info::COMMAND_NAME, &Info::invoke);
	}
}
