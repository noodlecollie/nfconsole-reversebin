#include <iostream>

#include "FileUtils.h"

namespace FileUtils
{
	size_t fileLength(std::ifstream& stream)
	{
		std::streampos origPos = stream.tellg();

		// stream.seekg(std::ios_base::beg, 0);
		// std::streampos beginPos = stream.tellg();
		// stream.seekg(std::ios_base::end, 0);
		// std::streampos endPos = stream.tellg();
		// stream.seekg(std::ios_base::beg, origPos);

		// return endPos - beginPos;

		std::ios_base::io_state oldExceptions = stream.exceptions();
		stream.exceptions(0);

		stream.ignore(std::numeric_limits<std::streamsize>::max());
		std::streamsize length = stream.gcount();
		stream.clear();	// Since ignore will have set eof.
		stream.seekg(origPos, std::ios_base::beg);

		stream.exceptions(oldExceptions);
		return length;
	}

	void openBinaryFile(std::ifstream& stream, const std::string& path, bool log)
	{
		if ( log )
		{
			std::cout << "Opening file: " << path << std::endl;
		}

		stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			stream.open(path, std::ios::in | std::ios::binary);
		}
		catch ( const std::ifstream::failure ex )
		{
			// Make the message a bit nicer.
			throw std::runtime_error("Failed to open file " + path);
		}
	}
}
