#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <algorithm>
#include <bit>
#include <bitset>
//#include <ranges>
#include "LZSSHeader.h"


#include "BitWriter.h"


namespace LZSS {

	namespace fs = std::filesystem;
	//namespace ranges = std::ranges;
	//namespace views = std::views;



	class LZSSCompressor
	{
		struct Ref {
			uint32_t pos{};
			uint32_t len{};
		};
		struct Literal {
			Literal(char c) : sign(c) {}
			char sign;
		};
		struct Element {
			Element(uint32_t pos, uint32_t len) : isRef(true), ref({ pos, len }) {}
			Element(char sign) : isRef(false), literal(sign) {}
			bool isRef;
			union {
				Ref ref;
				Literal literal;
			};
		};
		size_t dict_size = 0, buffer_size = 0;
	public:
		LZSSCompressor(size_t dict_size, size_t buffer_size);
		LZSSCompressor();
		LZSSCompressor& setDictSize(size_t dict_size);
		LZSSCompressor& setBufferSize(size_t buffer_size);
		size_t getDictSize();
		size_t getBufferSize();
		void compress(std::istream& istream, std::ostream& ostream);
	};
}
