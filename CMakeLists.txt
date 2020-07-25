# CMakeList.txt : CMake project for Gameboy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Gameboy")

set(SFML_DIR "")
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)
# Add source to this project's executable.
add_executable (Gameboy "Gameboy.cpp" "Gameboy.h" "GBDef.h"   "Emulator.cpp" "Emulator.h"  "GBUtil.cpp" "GBUtil.h")


target_link_libraries(Gameboy sfml-audio sfml-graphics sfml-window sfml-system)

# TODO: Add tests and install targets if needed.
