#include "BinaryFileCommon.h"
#include "StreamUtils.h"

size_t BinaryFileCommon::entryCount() const
{
	return m_EntryList.size();
}

const BinaryFileCommon::EntryList::const_iterator BinaryFileCommon::begin() const
{
	return m_EntryList.begin();
}

const BinaryFileCommon::EntryList::const_iterator BinaryFileCommon::end() const
{
	return m_EntryList.end();
}

const BinaryFileCommon::Entry& BinaryFileCommon::entry(uint32_t index) const
{
	return m_EntryList[index];
}

size_t BinaryFileCommon::fileLength() const
{
	return m_FileLength;
}

void BinaryFileCommon::read(std::ifstream& input)
{
	m_EntryList.clear();

	Entry workingEntry;

	while ( readEntry(input, workingEntry) )
	{
		m_EntryList.push_back(workingEntry);
	}
}

bool BinaryFileCommon::readEntry(std::ifstream& input, Entry& entry)
{
	StreamUtils::readBigEndianWord(input, entry.dataArchive);

	// Final entry in the common file listing is a single all-zero word.
	// Check for this first.
	if ( entry.dataArchive == 0 )
	{
		return false;
	}

	StreamUtils::readBigEndianWord(input, entry.metaArchive);

	return input.good();
}
