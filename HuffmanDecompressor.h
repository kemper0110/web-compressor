#pragma once

#include <filesystem>
#include <istream>
#include <ostream>
#include <algorithm>
#include <array>
#include <ranges>
#include <cassert>
#include <bitset>
#include <optional>

#include "HuffmanTree.h"

#include "BitReader.h"

namespace Huffman {
	namespace ranges = std::ranges;
	namespace fs = std::filesystem;
	class HuffmanDecompressor
	{
		//std::vector<Sign> tree;
		//std::vector<DecompressorNode> inner_nodes, leafs;
		//DecompressorNode* root;

	public:
		HuffmanDecompressor();
		void decompress(std::istream& istream, std::ostream& ostream);
	private:

		Header readHeader(std::istream& istream);
	};

}
