#include <iostream>
#include <iomanip>

#include "Info.h"
#include "../BinaryFileCollection.h"

namespace Commands
{
	namespace Info
	{
		static constexpr const char* const OPTION_COMMON = "common";

		static void printCommonInfo()
		{
			const BinaryFileCommon& commonFile = BinaryFileCollection::Instance.common();
			const size_t entryCount = commonFile.entryCount();

			std::cout << "Dumping info for common file (" << entryCount << " entries):" << std::endl;

			for ( uint32_t index = 0; index < entryCount; ++index )
			{
				const BinaryFileCommon::Entry& entry = commonFile.entry(index);

				std::cout
					<< "[" << std::dec << std::setfill('0') << std::setw(2) << index << "] "
					<< "Data archive: 0x" << std::setfill('0') << std::setw(8) << std::hex << entry.dataArchive << ".bin "
					<< "Meta archive: 0x" << std::setfill('0') << std::setw(8) << std::hex << entry.metaArchive << ".bin"
					<< std::dec << std::endl;
			}
		}

		void invoke(const std::string& name, const std::deque<std::string>& args)
		{
			if ( args.size() != 1 )
			{
				std::cout << "Usage: " << name << " <" << OPTION_COMMON << ">" << std::endl;
				return;
			}

			const std::string& option = args[0];

			if ( option == OPTION_COMMON )
			{
				printCommonInfo();
			}
			else
			{
				std::cout << "Unrecognised option: " << option << std::endl;
			}
		}
	}
}
