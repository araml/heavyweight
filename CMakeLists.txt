cmake_minimum_required(VERSION 3.0)

project(heavyweight)
enable_testing()


if (UNIX) # This is so we get colorized output if we use ninja to build
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
           add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
          add_compile_options (-fcolor-diagnostics)
    endif ()
endif()

macro(add_files name)
    file(GLOB ${name} src/${name}/*.h src/${name}/*.cpp)
    include_directories(src/${name})
endmacro()

add_files(src/filesystem)
add_executable(heavyweight src/main.cpp ${filesystem})
set_property(TARGET heavyweight PROPERTY CXX_STANDARD 14)

