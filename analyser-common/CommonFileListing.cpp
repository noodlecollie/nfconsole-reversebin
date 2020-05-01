#include "CommonFileListing.h"

size_t CommonFileListing::entryCount() const
{
	return m_EntryList.size();
}

const CommonFileListing::EntryList::const_iterator CommonFileListing::begin() const
{
	return m_EntryList.begin();
}

const CommonFileListing::EntryList::const_iterator CommonFileListing::end() const
{
	return m_EntryList.end();
}

const CommonFileListing::Entry& CommonFileListing::entry(uint32_t index) const
{
	return m_EntryList[index];
}

size_t CommonFileListing::fileLength() const
{
	return m_FileLength;
}

void CommonFileListing::read(std::ifstream& input)
{
	m_EntryList.clear();

	Entry workingEntry;

	while ( readEntry(input, workingEntry) )
	{
		m_EntryList.push_back(workingEntry);
	}
}

bool CommonFileListing::readEntry(std::ifstream& input, Entry& entry)
{
	input >> entry.dataArchive >> entry.metaArchive;

	// Final entry in the common file listing is an all-zero word.
	return input.good() && entry.dataArchive != 0;
}
