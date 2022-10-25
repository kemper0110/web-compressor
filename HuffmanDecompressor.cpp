#include "HuffmanDecompressor.h"


namespace Huffman {
    HuffmanDecompressor::HuffmanDecompressor() {


    }


    void HuffmanDecompressor::decompress(std::istream &istream, std::ostream &ostream) {
        const auto header = readHeader(istream);

        //std::vector<SignWidth> dict(header.dict_size);
        //if (not istream.read(reinterpret_cast<char*>(dict.data()), dict.size() * sizeof SignWidth))
        //throw std::runtime_error("Bad file structure: dictionary error");

        std::vector<SignFrequency> frequency_vec;
        frequency_vec.reserve(header.dict_size);
        for (int i = 0; i < header.dict_size; ++i) {
            SignFrequency sf;
            istream.read(reinterpret_cast<char *>(&sf.sign), sizeof sf.sign);
            istream.read(reinterpret_cast<char *>(&sf.freq), sizeof sf.freq);
            frequency_vec.push_back(sf);
        }
        auto [leafs, inner_nodes, root] = huffmanImpl(frequency_vec);
        //std::tie(leafs, inner_nodes, root) = makeDecompressorTree(dict);
        //auto [leafs, inner_nodes, root] = makeDecompressorTree(dict);
        //std::vector<bool> input;
        //input.reserve(fs::file_size(dst) * 8);
        //input.size();
        //{
        //	auto& intvec = input._Myvec;
        //	int buff;
        //	while (ifstream.read(reinterpret_cast<char*>(&buff), sizeof buff)) {
        //		intvec.push_back(buff);
        //	}
        //	//std::copy(std::istreambuf_iterator<int>(ifstream), {}, intvec.begin());
        //}

        //const auto idx = 2 * prevIdx + bit + 1;
        //if (idx >= tree.size())
        //	prevIdx = bit + 1;
        //else
        //	prevIdx = idx;

        {
            BitReader bitreader(istream);

            const auto *current = root;
            const auto isLeaf = [&root = root](const auto *node) {
                //return node->children[0] == root->children[0] or
                //	node->children[1] == root->children[1];
                return node->children[0] == nullptr or node->children[1] == nullptr;
            };
//			const auto onError = [](std::string_view message) {
//				return [=] {
//					throw std::runtime_error(message.data());
//					return std::optional<uint64_t>{};
//				};
//			};
            while (true) {
//					const auto bit = bitreader.read(1).or_else(onError("bit expected")).value();
                const auto bit_opt = bitreader.read(1);
                if (not bit_opt.has_value())
                    break;
                const auto bit = bit_opt.value();
                current = current->children[bit];
                if (isLeaf(current)) {
                    ostream.write(reinterpret_cast<const char *>(&current->sign), 1);
                    current = root;
                }
            }

        }

    }

    Header HuffmanDecompressor::readHeader(std::istream &istream) {
        Header header;
        if (not istream.read(reinterpret_cast<char *>(&header), sizeof(Header)))
            std::exit(1);
//            throw std::runtime_error("Bad file structure: header error");

        if (std::string_view(header.type, 2) != "HM")
            std::exit(1);
//            throw std::runtime_error("Bad file type: header error");

        return header;
    }
}


