cmake_minimum_required(VERSION 2.9 FATAL_ERROR)
SET(projectName OutOfTheDark)

project(projectName)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_STANDARD_REQUIRED true)
set(EXECUTABLE_NAME OutOfTheDark)

find_package(SFML 2.0 REQUIRED system window graphics network audio )


file(GLOB SOURCES src/cpp/*.cpp) #stores all .cpp files in SOURCES

add_executable (${EXECUTABLE_NAME} ${SOURCES})

TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-audio sfml-network sfml-system)
