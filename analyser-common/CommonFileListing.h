#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>
#include <fstream>

class CommonFileListing
{
public:
	struct Entry
	{
		uint32_t dataArchive = 0;
		uint32_t metaArchive = 0;
	};

	using EntryList = std::vector<Entry>;

	size_t entryCount() const;
	const EntryList::const_iterator begin() const;
	const EntryList::const_iterator end() const;
	const Entry& entry(uint32_t index) const;
	size_t fileLength() const;

	void read(std::ifstream& input);

private:
	bool readEntry(std::ifstream& input, Entry& entry);

	EntryList m_EntryList;
	size_t m_FileLength = 0;
};
