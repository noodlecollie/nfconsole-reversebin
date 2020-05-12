#include <iostream>
#include <string>
#include <exception>
#include <fstream>

#include "BinaryFileCollection.h"
#include "CommandInterpreter.h"
#include "Commands.h"

static void runTask(const std::string& directoryPath)
{
	std::cout
		<< "==============================" << std::endl
		<< "         " BINARY_NAME "          " << std::endl
		<< "==============================" << std::endl
		;

	BinaryFileCollection::Instance.initialise(directoryPath);

	CommandInterpreter interpreter;
	Commands::addAllCommands(interpreter);
	interpreter.run();
}

int main(int argc, char** argv)
{
	if ( argc != 2 )
	{
		std::cerr << "Usage: " BINARY_NAME " <path to binary files>" << std::endl;
		return 1;
	}

	try
	{
		runTask(std::string(argv[1]));
	}
	catch ( const std::exception& ex )
	{
		std::cerr << "An error occurred during execution. " << ex.what() << std::endl;
		return 1;
	}
	catch ( ... )
	{
		std::cerr << "An unhandled error occurred during execution. " << std::endl;
		return 1;
	}

	return 0;
}
