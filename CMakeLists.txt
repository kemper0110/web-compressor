
cmake_minimum_required(VERSION 3.23)
project(web_cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXECUTABLE_SUFFIX .js)

#add_compile_options(-sEXPORTED_RUNTIME_METHODS=[ccall])
#set(CMAKE_CXX_FLAGS "-s EXPORTED_RUNTIME_METHODS=[ccall] -s ALLOW_MEMORY_GROWTH=1")
set(CMAKE_CXX_FLAGS_RELEASE  "-l embind -s ENVIRONMENT=web -sASSERTIONS -O3 -s FILESYSTEM=0 -sALLOW_MEMORY_GROWTH -s WASM=1")
#-s MODULARIZE=1 -s EXPORT_NAME='createCompressorModule'
#-flto --closure 1
#-s DEMANGLE_SUPPORT=1
#-s EXPORT_ES6=1 -s USE_ES6_IMPORT_META=0
#-s MODULARIZE=1 -s EXPORT_NAME='createCompressorModule'
#-s ERROR_ON_UNDEFINED_SYMBOLS=0
#  --no-entry -s STANDALONE_WASM

#-s EXPORTED_FUNCTIONS=\"['_malloc']\" -s EXPORTED_RUNTIME_METHODS=[ccall] -s FORCE_FILESYSTEM
#-sEXCEPTION_CATCHING_ALLOWED=[..] -fexceptions -pthread -sPTHREAD_POOL_SIZE=8

add_executable(web_cpp main.cpp
        HuffmanCompressor.cpp HuffmanDecompressor.cpp HuffmanTree.cpp
        LZSSCompressor.cpp LZSSDecompressor.cpp
        BitWriter.cpp BitReader.cpp
        )
