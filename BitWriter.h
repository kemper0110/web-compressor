//
// Created by danil on 20.10.2022.
//
#include <ostream>
#include <cassert>

#ifndef SIMPLE_PROJECT_WLIB_BITWRITER_H
#define SIMPLE_PROJECT_WLIB_BITWRITER_H
class BitWriter
{
    std::ostream& ostream;
    uint64_t bitbuffer = 0;
    unsigned bitcount = 0;
public:
    BitWriter(std::ostream& ostream);
    void write(uint64_t code, uint8_t how_much);
    ~BitWriter();
};


#endif //SIMPLE_PROJECT_WLIB_BITWRITER_H
