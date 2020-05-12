#include <iostream>

#include "BinaryFileCollection.h"
#include "FileUtils.h"
#include "KnownFiles.h"

BinaryFileCollection BinaryFileCollection::Instance;

const BinaryFileCommon& BinaryFileCollection::common() const
{
	return m_CommonFile;
}

void BinaryFileCollection::initialise(const std::string& rootDir)
{
	m_RootDir = rootDir;

	readCommonFile();
}

void BinaryFileCollection::readCommonFile()
{
	std::string path = FileUtils::makePath(m_RootDir, KnownFiles::FILENAME_COMMON);
	std::ifstream stream;

	FileUtils::openBinaryFile(stream, path, true);
	m_CommonFile.read(stream);

	std::cout << "Common file read successfully." << std::endl;
}
