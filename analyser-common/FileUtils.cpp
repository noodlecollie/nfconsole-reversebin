#include <iostream>

#include "FileUtils.h"

namespace FileUtils
{
	size_t fileLength(std::ifstream& stream)
	{
		std::streampos origPos = stream.tellg();

		stream.seekg(std::ios_base::end, 0);
		std::streampos endPos = stream.tellg();
		stream.seekg(std::ios_base::beg);

		return endPos;
	}

	void openFile(std::ifstream& stream, const std::string& path, bool log)
	{
		if ( log )
		{
			std::cout << "Opening file: " << path << std::endl;
		}

		stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			stream.open(path);
		}
		catch ( const std::ifstream::failure ex )
		{
			// Make the message a bit nicer.
			throw std::runtime_error("Failed to open file " + path);
		}
	}
}
