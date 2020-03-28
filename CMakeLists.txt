cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME "SnakeGame")
set(SFML_PATH "external/SFML")
set(RESOURCES_PATH "driver/resources")

project(${PROJECT_NAME} CXX)

# Copy the dlls to the main folder
file(GLOB SFML_DLL "${SFML_PATH}/bin/*.dll")
file(COPY ${SFML_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Copy the resources folder
file(COPY ${RESOURCES_PATH} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_GENERATOR_PLATFORM Win32 CACHE INTERNAL "")

file(GLOB_RECURSE SRC_FILES "inc/*.h*" "src/*.c*")

include_directories("inc/")
include_directories("${SFML_PATH}/include/")
link_directories("${SFML_PATH}/lib/")

add_executable(${PROJECT_NAME} ${SRC_FILES} driver/main.cpp )
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Use different libraries for different configs
target_link_libraries(${PROJECT_NAME} debug sfml-graphics-d sfml-audio-d sfml-network-d sfml-window-d sfml-system-d)
target_link_libraries(${PROJECT_NAME} optimized sfml-graphics sfml-audio sfml-network sfml-window sfml-system)
