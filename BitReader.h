//
// Created by danil on 20.10.2022.
//

#ifndef SIMPLE_PROJECT_WLIB_BITREADER_H
#define SIMPLE_PROJECT_WLIB_BITREADER_H

#include <optional>
#include <istream>
#include <cassert>

class BitReader {
    std::istream& istream;
    unsigned bitcount = 0;
    uint64_t bitbuffer = 0;
public:
    BitReader(std::istream& istream);
    std::optional<uint64_t> read(const uint8_t how_much);
};

#endif //SIMPLE_PROJECT_WLIB_BITREADER_H
