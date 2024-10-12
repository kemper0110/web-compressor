cmake_minimum_required(VERSION 3.23)
project(web-compressor)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXECUTABLE_SUFFIX .js)

set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -flto -s ASSERTIONS -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s MODULARIZE=1 -s EXPORT_NAME='MainModule' -s EXPORT_ES6=1 -s USE_ES6_IMPORT_META=0")
# -s EXPORT_NAME='createCompressorModule'
#-s DEMANGLE_SUPPORT=1
#-s ERROR_ON_UNDEFINED_SYMBOLS=0

#-sEXCEPTION_CATCHING_ALLOWED=[..] -fexceptions

add_subdirectory(compressor-cpp)

add_executable(web-compressor main.cpp)

target_include_directories(web-compressor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/compressor-cpp/include)

target_link_libraries(web-compressor PRIVATE compressor)

target_link_options(web-compressor PRIVATE --emit-tsd "web-compressor.d.ts")
target_link_options(web-compressor PRIVATE -l "embind")
target_link_options(web-compressor PRIVATE -s "ENVIRONMENT=web")