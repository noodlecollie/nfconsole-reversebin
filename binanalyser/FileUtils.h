#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace FileUtils
{
	size_t fileLength(std::ifstream& stream);
	void openFile(std::ifstream& stream, const std::string& path, bool log = false);

	template<typename... ARGS>
	std::string makePath(ARGS... pathSegments)
	{
		const std::vector<std::string> segmentList({pathSegments...});
		std::stringstream stream;
		bool firstSegment = true;

		for ( const std::string& segment : segmentList )
		{
			if ( !firstSegment )
			{
				stream << PATH_SEP;
			}

			stream << segment;
			firstSegment = false;
		}

		return stream.str();
	}
}
