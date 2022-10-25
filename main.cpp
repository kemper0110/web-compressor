#include <iostream>
#include <ranges>
#include <algorithm>
#include <set>
#include <vector>
#include <utility>
#include <map>
#include <array>
#include <execution>
#include <thread>
#include <sstream>

#include <fstream>
#include <optional>

#include <span>

#include <emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;

#include "LZSSCompressor.h"
#include "LZSSDecompressor.h"
#include "HuffmanCompressor.h"
#include "HuffmanDecompressor.h"

// emcc -std=c++2b chess_to_wasm.cpp Bishop.cpp Board.cpp Figure.cpp FigureMoves.cpp King.cpp Knight.cpp Pawn.cpp Queen.cpp Rook.cpp --bind -o example.js
// python -m http.server 8080

// -sEXPORTED_RUNTIME_METHODS=[ccall]


//int main() {
//    std::cout << "Hello, World2!" << std::endl;
//    return 0;
//}

std::string compress_result;
std::string decompress_result;

val HSCompress(const std::string& input, int dict_size, int buffer_size){
    std::stringstream iss(input), pss, oss;

    Huffman::HuffmanCompressor().compress(iss, pss);
    LZSS::LZSSCompressor(dict_size, buffer_size).compress(pss, oss);

    compress_result = oss.str();
    return val(typed_memory_view(compress_result.size(), compress_result.data()));
}
val HSDecompress(const std::string& input){
    std::stringstream iss(input), pss, oss;

    LZSS::LZSSDecompressor().decompress(iss, pss);
    Huffman::HuffmanDecompressor().decompress(pss, oss);

    decompress_result = oss.str();
    return val(typed_memory_view(decompress_result.size(), decompress_result.data()));
}

val HuffmanDecompress(std::string input){
    std::stringstream iss(input);
    std::stringstream oss;
    Huffman::HuffmanDecompressor().decompress(iss, oss);

    decompress_result = oss.str();
    return val(typed_memory_view(decompress_result.size(), decompress_result.data()));
}

val HuffmanCompress(std::string input){
    std::stringstream iss(input);
    std::stringstream oss;
    Huffman::HuffmanCompressor().compress(iss, oss);

    compress_result = oss.str();
    return val(typed_memory_view(compress_result.size(), compress_result.data()));
}

val LZSSCompress(std::string input, int dict_size, int buffer_size) {
    const auto begin = std::chrono::steady_clock::now();
    std::stringstream iss(input);
    std::stringstream oss;
    LZSS::LZSSCompressor(dict_size, buffer_size).compress(iss, oss);
    const auto end = std::chrono::steady_clock::now();

    compress_result = oss.str();
    std::cout << "compress size: " << compress_result.size() << '\n';
    std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << '\n';

    return val(typed_memory_view(compress_result.size(), compress_result.data()));
}

val LZSSDecompress(std::string input) {
    const auto begin = std::chrono::steady_clock::now();
    std::stringstream iss(input);
    std::stringstream oss;
    LZSS::LZSSDecompressor().decompress(iss, oss);
    const auto end = std::chrono::steady_clock::now();

    decompress_result = oss.str();
    std::cout << "decompressed size: " << decompress_result.size() << '\n';
    std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << '\n';


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

//extern "C" EMSCRIPTEN_KEEPALIVE int run(uint8_t * data, size_t size){
//
//    for(int i = 0; i < size; ++i){
//        const auto sign = data[i];
//        if(sign >= 'a' and sign <= 'z')
//            std::toupper(sign);
//    }
//
//    return 0;
//}

//struct Node {
//    uint32_t freq = 0UL;
//    const Node *children[2]{nullptr, nullptr};
//    char sign = 0;
//};
//
//extern "C" {
//
//EMSCRIPTEN_KEEPALIVE int load_file(uint8_t *buffer, size_t size) {
////    std::cout << "load_file triggered, buffer " << &buffer << " size " << size << std::endl;
//
//    try {
//        const auto time_begin = std::chrono::steady_clock::now();
//
//        uint32_t freq_dict[256]{};
//        for (int i = 0; i < size; ++i)
//            freq_dict[buffer[i]]++;
//
//        std::vector<std::pair<uint8_t, uint32_t>> sign_to_freq;
//        sign_to_freq.reserve(256);
//        for (int i = 0; i < std::size(freq_dict); ++i)
//            if (freq_dict[i])
//                sign_to_freq.emplace_back(i, freq_dict[i]);
//
//        std::sort(sign_to_freq.begin(), sign_to_freq.end(), [](const auto &p1, const auto &p2) {
//            return p1.second < p2.second;
//        });
//
//        const auto time_end = std::chrono::steady_clock::now();
//
//        for (const auto [sign, freq]: sign_to_freq)
//            std::cout << (int) sign << " : " << freq << '\n';
//
//        std::cout << "elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_begin).count()
//                  << '\n';
//
//    } catch (const std::exception &ex) {
//        std::cout << ex.what() << '\n';
//        return -1;
//    }
//
//    return 1;
//}
//
//}