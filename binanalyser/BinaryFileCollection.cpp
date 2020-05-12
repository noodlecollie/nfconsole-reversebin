#include <cstdio>

#include "BinaryFileCollection.h"
#include "FileUtils.h"
#include "KnownFiles.h"

BinaryFileCollection BinaryFileCollection::Instance;

void BinaryFileCollection::initialise(const std::string& rootDir)
{
	m_RootDir = rootDir;

	readCommonFile();
}

void BinaryFileCollection::readCommonFile()
{
	std::string path = FileUtils::makePath(m_RootDir, KnownFiles::FILENAME_COMMON);
	std::ifstream stream;

	FILE* file = fopen(path.c_str(), "rb");
	if ( file )
	{
		fclose(file);
	}

	FileUtils::openBinaryFile(stream, path, true);

	volatile bool good = stream.good();

	m_CommonFile.read(stream);
}
