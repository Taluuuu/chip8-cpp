cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(chip8-cpp)

add_executable(
    chip8-cpp 

    src/main.cpp

    src/emulator.cpp
    src/memory.cpp
    src/screen.cpp
)
set_target_properties(chip8-cpp PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(chip8-cpp PRIVATE src lib/SFML/include)

set(BUILD_SHARED_LIBS False)
add_subdirectory(lib/SFML)
target_link_libraries(chip8-cpp sfml-graphics)