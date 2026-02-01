cmake_minimum_required(VERSION 3.10)
project(HITL_Dynamics)

# Standard C++ settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler-specific flags
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/W4 /Zi /Od")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
else()
    # This covers MinGW (g++), Clang, and GCC on Linux/macOS
    add_compile_options(
        "$<$<CONFIG:Debug>:-Wall;-Wextra;-Wpedantic;-g;-O0>"
        "$<$<CONFIG:Release>:-O3;-DNDEBUG>"
    )
endif()

# Source discovery
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# Define executable
add_executable(${PROJECT_NAME} 
    main.cpp
    ${SRC_FILES}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    include 
    include/eigen-5.0.0
)