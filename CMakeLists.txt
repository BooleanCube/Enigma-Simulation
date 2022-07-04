cmake_minimum_required(VERSION 3.22)
project(enigma)

set(CMAKE_CXX_STANDARD 14)

add_executable(enigma src/enigma/enigma.cpp src/enigma/components/rotor.cpp src/enigma/tools/tools.cpp src/enigma/components/reflector.cpp src/enigma/components/plugboard.cpp)
