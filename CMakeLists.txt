cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

#set project name and version
project(sfml_example VERSION 1.0)

#set c++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(EXIT_PARAM "Build with EXIT parameters" OFF)

# enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug
        CACHE STRING
            "Choose type of build (Debug or Release)"
            FORCE
        )
endif()

#include_directories(gameEngine PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

#set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5
             COMPONENTS
             system window graphics network audio REQUIRED)

#compile executable
#set(SOURCES
add_executable(sfml_example main.cpp)
                          #${CMAKE_CURRENT_LIST_DIR}/src/Game.cpp 
                          #${CMAKE_CURRENT_LIST_DIR}/src/window.cpp
						  #${CMAKE_CURRENT_LIST_DIR}/src/gameMap.cpp
                          #${CMAKE_CURRENT_LIST_DIR}/src/player.cpp)
#                           ${CMAKE_CURRENT_LIST_DIR}/src/Game.cpp)

#target_include_directories(gameEngine PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

message(STATUS "install prefix: ${CMAKE_INSTALL_PREFIX}")


#set include directory search paths 
target_include_directories(sfml_example
                           PUBLIC
                               "${PROJECT_BINARY_DIR}")
#                               "${CMAKE_CURRENT_SOURCE_DIR}/include/")

message(STATUS "current_source_dir: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "project_binary_dir: ${PROJECT_BINARY_DIR}")
message(sfml_example)

target_link_libraries(sfml_example PUBLIC sfml-graphics)
get_target_property(OUT sfml_example LINK_LIBRARIES)
message(STATUS ${OUT})

install(TARGETS sfml_example DESTINATION bin)

