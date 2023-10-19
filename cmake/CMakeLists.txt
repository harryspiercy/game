cmake_minimum_required(VERSION 3.7)

project(game)

set(SRC "../src")

find_package(SDL2 REQUIRED)
include_directories(${SDL_INCLUDE_DIRS})
set(SDL_LIBS SDL2 SDL2_image SDL2_ttf SDL2_mixer)

add_executable(a 
${SRC}/main.cpp
)

add_library(engine
${SRC}/button.cpp
${SRC}/core.cpp
${SRC}/texture.cpp
${SRC}/timer.cpp

${SRC}/common.h
${SRC}/engine.h
${SRC}/button.h
${SRC}/core.h
${SRC}/texture.h
${SRC}/timer.h
)
target_link_libraries(engine ${SDL_LIBS})


target_link_libraries(a engine ${SDL_LIBS})