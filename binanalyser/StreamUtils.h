#pragma once

#include <fstream>
#include <cassert>

namespace StreamUtils
{
	template<typename T>
	static inline constexpr void reverseEndianness(T& word)
	{
		assert(false);
	}

	template<>
	static inline constexpr void reverseEndianness(uint32_t& word)
	{
		word = ((word & 0xFF000000) >> 24) | ((word & 0x00FF0000) >> 8) | ((word & 0x0000FF00) << 8) | ((word & 0x000000FF) << 24);
	}

	template<>
	static inline constexpr void reverseEndianness(int32_t& word)
	{
		// static_cast to a reference didn't seem to work.
		reverseEndianness<uint32_t>(*reinterpret_cast<uint32_t*>(&word));
	}

	template<>
	static inline constexpr void reverseEndianness(uint16_t& word)
	{
		word = ((word & 0xFF00) >> 8) | ((word & 0x00FF) << 8);
	}

	template<>
	static inline constexpr void reverseEndianness(int16_t& word)
	{
		// static_cast to a reference didn't seem to work.
		reverseEndianness<uint16_t>(*reinterpret_cast<uint16_t*>(&word));
	}

	template<typename T>
	static inline std::istream& readBigEndianWord(std::istream& stream, T& word)
	{
		stream.read(reinterpret_cast<char*>(&word), sizeof(word));
		reverseEndianness(word);
		return stream;
	}
}
