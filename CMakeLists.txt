cmake_minimum_required(VERSION 3.6)

project(FinalProject)

macro(copy_directory _src _dst)
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${_src} ${_dst}
        RESULT_VARIABLE _res
        OUTPUT_VARIABLE _out
        ERROR_VARIABLE  _err
    )
    if(_err)
        message(FATAL_ERROR "ERROR ---> could not be copied: ${_err}")
    endif()
endmacro()

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

copy_directory(${CMAKE_CURRENT_SOURCE_DIR}/configs configs)
