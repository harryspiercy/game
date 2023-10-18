cmake_minimum_required(VERSION 3.7)

project(cmakeTest)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDL2")
set(GAMESRC "../src")

find_package(SDL2 REQUIRED)
include_directories(${SDL_INCLUDE_DIRS})

add_executable(game 
${GAMESRC}/main.cpp
)

add_library(engine
${GAMESRC}/button.cpp
${GAMESRC}/core.cpp
${GAMESRC}/texture.cpp
${GAMESRC}/timer.cpp

${GAMESRC}/common.h
${GAMESRC}/engine.h
${GAMESRC}/button.h
${GAMESRC}/core.h
${GAMESRC}/texture.h
${GAMESRC}/timer.h
)
target_link_libraries(engine SDL2 SDL2_image SDL2_ttf SDL2_mixer)


target_link_libraries(game engine SDL2 SDL2_image SDL2_ttf SDL2_mixer)