cmake_minimum_required(VERSION 3.6)

project(FinalProject)

# Lookup for pre-built gtest
# find_package(GTest)

add_executable(
    bat
    src/main.cpp
    src/lexer.cpp
    src/printer.cpp
    src/lang/c_printer.cpp
)

target_include_directories(bat PRIVATE include)

set_target_properties(bat PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(bat PRIVATE fmt::fmt)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(bat PRIVATE nlohmann_json nlohmann_json::nlohmann_json)


set(CMAKE_BUILD_TYPE Debug)

