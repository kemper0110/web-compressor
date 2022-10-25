//
// Created by danil on 20.10.2022.
//

#include "BitWriter.h"

BitWriter::BitWriter(std::ostream& ostream) : ostream(ostream) {}

void BitWriter::write(uint64_t code, uint8_t how_much) {
    assert(64 - bitcount >= how_much); // there is a space for bits
    bitbuffer |= code << bitcount;
    bitcount += how_much;

    while (bitcount >= 8) {
        ostream.put(bitbuffer & 0xff);
        bitbuffer >>= 8;
        bitcount -= 8;
    }
}

BitWriter::~BitWriter() {
    while(bitcount != 0)
        write(0, 1);
}
