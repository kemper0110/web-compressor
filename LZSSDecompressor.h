#pragma once
#include <fstream>
#include <filesystem>
#include <bitset>
#include <iostream>
#include "BitReader.h"

#include "LZSSHeader.h"

namespace LZSS {
	namespace fs = std::filesystem;

	class LZSSDecompressor {

	public:
		LZSSDecompressor();
		void decompress(std::istream& istream, std::ostream& ostream);
	};
}