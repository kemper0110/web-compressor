#pragma once

#include <filesystem>
#include <fstream>
#include <algorithm>
#include <array>
#include <ranges>
#include <cassert>

#include <istream>
#include <ostream>

#include "HuffmanTree.h"

#include "BitWriter.h"

namespace Huffman {
	namespace ranges = std::ranges;
	namespace fs = std::filesystem;


	class HuffmanCompressor
	{
		//std::vector<SignFrequency> frequency_vec;
		//std::array<std::vector<bool>, MAX_SIGN_VALUE> codemap;
	public:
		HuffmanCompressor();
		void compress(std::istream& istream, std::ostream& ostream);
	private:
	};
}

