cmake_minimum_required(VERSION 3.10)
project(HITL_Dynamics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/W4 /Zi /Od")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wpedantic -g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
endif()

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} 
    main.cpp
    ${SRC_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    include 
    include/eigen-5.0.0
)
