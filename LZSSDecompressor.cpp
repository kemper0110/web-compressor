#include "LZSSDecompressor.h"


namespace LZSS {
    LZSSDecompressor::LZSSDecompressor() {}

    void LZSSDecompressor::decompress(std::istream &istream, std::ostream &ostream) {

        LZSSHeader header;
        /*{
            .dict_size = 9,
            .buffer_size = 5,
            .pos_width = 4,
            .len_width = 3,
        };*/
        if (not istream.read(reinterpret_cast<char *>(&header), sizeof header)) {
            std::cout << "bad structure\n";
            std::exit(1);
//            throw std::runtime_error("Bad file structure: header error");
        }

        if (std::string_view(header.type, 2) != "SS") {
            std::cout << "bad file type\n";
            std::exit(1);
//            throw std::runtime_error("Bad file type: header error");
        }

        std::cout << "header: " << header.dict_size << ' ' << header.buffer_size << '\n';


        BitReader bitreader(istream);

        boost::circular_buffer<unsigned char> dict(header.dict_size, header.dict_size, 0);

        const auto onError = [](std::string_view reason) {
            return [=] {
//                throw std::runtime_error(reason.data());
                std::exit(1);
                return std::optional<uint64_t>{};
            };
        };

        //std::ofstream debug("LZSS_DECOMPRESSOR_DBG.txt", std::ios::trunc);

        for (auto is_ref = bitreader.read(1); is_ref.has_value(); is_ref = bitreader.read(1)) {
            switch (is_ref.value()) {
                case 0: {
//                    const auto literal = static_cast<unsigned char>(bitreader.read(8).or_else(
//                            onError("LZSS error: expected literal")).value());
                    const auto literal_opt = bitreader.read(8);
                    if(not literal_opt.has_value())
                        break;
                    const auto literal = static_cast<unsigned char>(literal_opt.value());
                    ostream.write(reinterpret_cast<const char *>(&literal), 1);
                    dict.push_back(literal);
                    //debug << literal << std::endl;
                    break;
                }
                case 1: {
//                    const auto pos = bitreader.read(header.pos_width).or_else(
//                            onError("LZSS error: expected ref position")).value();
//                    const auto len = bitreader.read(header.len_width).or_else(
//                            onError("LZSS error: expected ref length")).value();

                    const auto pos_opt = bitreader.read(header.pos_width);
                    if(not pos_opt.has_value())
                        break;
                    const auto pos = pos_opt.value();
                    const auto len_opt = bitreader.read(header.len_width);
                    if(not len_opt.has_value())
                        break;
                    const auto len = len_opt.value();
                    //debug << "pos = " << pos << " len = " << len << std::endl;

                    for (auto j = 0UL; j < len; ++j) {
                        const auto sign = dict.at(pos);
                        ostream.write(reinterpret_cast<const char *>(&sign), 1);
                        dict.push_back(sign);
                    }
                    break;
                }
            }
        }



        //std::vector<bool> output;
        /*	for (auto i = 0UL; i < input.size();) {
                const auto refbit = input[i++];
                switch (refbit) {
                case 0:
                {
                    std::bitset<8> literal_bs;
                    for (auto j = i; j < 8; ++j)
                        literal_bs[j] = input[i + j];
                    i += 8;
                    for (auto k = 0UL; k < 8; ++k)
                        output.push_back(literal_bs[k]);
                    const auto literal = static_cast<char>(literal_bs.to_ulong());
                    dict.push_back(literal);
                    break;
                }
                case 1:
                {
                    uint32_t pos, len;
                    {
                        std::bitset<32> pos_bs, len_bs;
                        for (int j = i; j < header.pos_width; ++j)
                            pos_bs[j] = input[i + j];
                        i += header.pos_width;
                        pos = pos_bs.to_ulong();
                        for (int j = i; j < header.len_width; ++j)
                            len_bs[j] = input[i + j];
                        i += header.len_width;
                        len = len_bs.to_ulong();
                    }
                    for (auto j = 0UL; j < len; ++j) {
                        const auto sign = pos;
                        const std::bitset<8> sign_bs = dict.at(sign);
                        for (auto k = 0UL; j < sign_bs.size(); ++j)
                            output.push_back(sign_bs[k]);
                        dict.push_back(sign);
                    }
                    break;
                }
                }
            }*/

        //ofs.open(dst);
        //auto& intvec = input._Myvec;
        //const auto data = reinterpret_cast<const char*>(intvec.data());
        //ofs.write(data, intvec.size() * sizeof(intvec[0]));
    }

}