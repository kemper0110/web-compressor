#pragma once
#include <numeric>
#include <boost/circular_buffer.hpp>


namespace LZSS {

	struct LZSSHeader {
		char type[2]{ 'S', 'S' };
		uint32_t byte_size{};
		uint32_t dict_size{};
		uint32_t buffer_size{};
		uint8_t pos_width{};
		uint8_t len_width{};
	};

}
