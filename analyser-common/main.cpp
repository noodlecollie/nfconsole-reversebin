#include <iostream>
#include <string>
#include <exception>
#include <fstream>

#include "CommonFileListing.h"
#include "KnownFiles.h"
#include "FileUtils.h"

static CommonFileListing _CommonFile;

static void printAnalysis(const std::string& directoryPath)
{
	std::cout << "Binary file directory: " << directoryPath << std::endl;

	std::string commonFilePath(FileUtils::makePath(directoryPath, KnownFiles::FILENAME_COMMON));
	std::ifstream commonFileStream;
	FileUtils::openFile(commonFileStream, commonFilePath, true);

	std::cout << "Reading common file listing..." << std::endl;
	_CommonFile.read(commonFileStream);
	std::cout << " Done." << std::endl;
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
		printAnalysis(std::string(argv[1]));
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
