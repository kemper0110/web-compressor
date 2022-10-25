#include "HuffmanCompressor.h"


namespace Huffman {


	HuffmanCompressor::HuffmanCompressor() {
	}

	void HuffmanCompressor::compress(std::istream& istream, std::ostream& ostream)
	{
		auto [frequency_vec, codemap] = makeCompressorTree(istream);

		istream.seekg(0, istream.beg);
		//std::tie(frequency_vec, codemap) = makeCompressorTree(istream);

		//for (int i = 0; i < codemap.size(); ++i) 
		//	std::cout << (char)i << " : " << codemap[i].size() << '\n';
		//std::cout << '\n';

		Header header = {
			.dict_size = (decltype(Header::dict_size))frequency_vec.size(),
			.byte_size = 0
		};
		std::cout << "dict size: " << frequency_vec.size() << '\n';
		ostream.write(reinterpret_cast<const char*>(&header), sizeof header);

		for (const auto& sf : frequency_vec) {
			ostream.write(reinterpret_cast<const char*>(&sf.sign), sizeof sf.sign);
			ostream.write(reinterpret_cast<const char*>(&sf.freq), sizeof sf.freq);
		}

		{
			BitWriter bitwriter(ostream);
			std::for_each(std::istreambuf_iterator<char>(istream), {}, [&codemap = codemap, &bitwriter](char c) {
				const auto sign = static_cast<Sign>(c);
				const auto& code = codemap[sign];
				for (const auto bit : code)
					bitwriter.write(bit, 1);
				});
		}


		//std::vector<SignWidth> output_dict;
		//output_dict.reserve(frequency_vec.size());
		//for (const auto& sf : frequency_vec) {
		//	const auto code_width = codemap[sf.sign].size();
		//	output_dict.emplace_back(sf.sign, code_width);
		//}
		//ostream.write(reinterpret_cast<const char*>(output_dict.data()), output_dict.size() * sizeof SignWidth);


	}
	//std::vector<SignFrequency> frequency_vec;
	//frequency_vec.reserve(codemap.size());
	//for (auto i = 0UL; i < codemap.size(); ++i)
	//	if (codemap[i].size())
	//		frequency_vec.emplace_back(i, codemap[i]);


}

