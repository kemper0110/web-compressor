#include <iostream>
#include <ranges>
#include <vector>
#include <sstream>

#include <emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;

#include "LZSSCompressor.h"
#include "LZSSDecompressor.h"
#include "HuffmanCompressor.h"
#include "HuffmanDecompressor.h"

std::string compress_result;
std::string decompress_result;

template<typename T>
void timed(T&& function) {
    const auto begin = std::chrono::steady_clock::now();
    function();
    const auto end = std::chrono::steady_clock::now();
    std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << '\n';
}


val HSCompress(const std::string& input, int dict_size, int buffer_size){
    std::stringstream iss(input), pss, oss;
    timed([dict_size, buffer_size, &iss, &pss, &oss] {
        Huffman::HuffmanCompressor().compress(iss, pss);
        LZSS::LZSSCompressor(dict_size, buffer_size).compress(pss, oss);
    });
    compress_result = oss.str();
    return val(typed_memory_view(compress_result.size(), compress_result.data()));
}
val HSDecompress(const std::string& input){
    std::stringstream iss(input), pss, oss;
    timed([&iss, &pss, &oss] {
        LZSS::LZSSDecompressor().decompress(iss, pss);
        Huffman::HuffmanDecompressor().decompress(pss, oss);
    });
    decompress_result = oss.str();
    return val(typed_memory_view(decompress_result.size(), decompress_result.data()));
}

val HuffmanDecompress(std::string input){
    std::stringstream iss(input);
    std::stringstream oss;
    timed([&iss, &oss] {
        Huffman::HuffmanDecompressor().decompress(iss, oss);
    });
    decompress_result = oss.str();
    return val(typed_memory_view(decompress_result.size(), decompress_result.data()));
}

val HuffmanCompress(std::string input){
    std::stringstream iss(input);
    std::stringstream oss;
    timed([&iss, &oss] {
        Huffman::HuffmanCompressor().compress(iss, oss);
    });
    compress_result = oss.str();
    return val(typed_memory_view(compress_result.size(), compress_result.data()));
}

val LZSSCompress(std::string input, int dict_size, int buffer_size) {
    std::stringstream iss(input);
    std::stringstream oss;
    timed([dict_size, buffer_size, &iss, &oss] {
        LZSS::LZSSCompressor(dict_size, buffer_size).compress(iss, oss);
    });
    compress_result = oss.str();
    return val(typed_memory_view(compress_result.size(), compress_result.data()));
}

val LZSSDecompress(std::string input) {
    std::stringstream iss(input);
    std::stringstream oss;
    timed([&iss, &oss] {
        LZSS::LZSSDecompressor().decompress(iss, oss);
    });
    decompress_result = oss.str();
    return val(typed_memory_view(decompress_result.size(), decompress_result.data()));
}

std::string to_upper(std::string input) {
    std::string output;
    for (const auto c: input)
        if (c >= 'a' and c <= 'z')
            output.push_back(std::toupper(c));

    return output;
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("toupper", &to_upper);
    function("LZSSCompress", &LZSSCompress);
    function("LZSSDecompress", &LZSSDecompress);
    function("HuffmanCompress", &HuffmanCompress);
    function("HuffmanDecompress", &HuffmanDecompress);
    function("HSCompress", &HSCompress);
    function("HSDecompress", &HSDecompress);
}