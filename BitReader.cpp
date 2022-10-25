//
// Created by danil on 20.10.2022.
//
#include <iostream>
#include "BitReader.h"

BitReader::BitReader(std::istream& istream) : istream(istream) {
}

std::optional<uint64_t> BitReader::read(const uint8_t how_much) {
    while (bitcount < how_much) {
        char c;
        if (not istream.get(c))
            return std::nullopt;
        assert(64 - bitcount >= 8); // there is a space for bits
        uint8_t uc = c;
        bitbuffer |= (uint64_t)uc << bitcount;
        bitcount += 8;
    }
    const auto res = bitbuffer & ((1 << how_much) - 1);
    bitbuffer >>= how_much;
    bitcount -= how_much;
    return res;
}