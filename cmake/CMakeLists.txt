cmake_minimum_required(VERSION 3.7)

project(game)

set(SRC "../src")
set(ENGSRC "../src/engine")
set(GAMESRC "../src/game")

find_package(SDL2 REQUIRED)
include_directories(${SDL_INCLUDE_DIRS})
set(SDL_LIBS SDL2 SDL2_image SDL2_ttf SDL2_mixer)

add_executable(a 
${GAMESRC}/main.cpp

${GAMESRC}/levels/demo.h
${GAMESRC}/levels/demo.cpp

${GAMESRC}/levels/level01.h
${GAMESRC}/levels/level01.cpp

)

add_library(engine

${ENGSRC}/core.cpp
${ENGSRC}/texture.cpp
${ENGSRC}/timer.cpp

${ENGSRC}/common.h
${ENGSRC}/engine.h
${ENGSRC}/core.h
${ENGSRC}/texture.h
${ENGSRC}/timer.h

${ENGSRC}/level.h
${ENGSRC}/level.cpp

${ENGSRC}/ecs/entity.h
${ENGSRC}/ecs/entity.cpp

${ENGSRC}/ecs/entities/button.h
${ENGSRC}/ecs/entities/button.cpp

)
target_link_libraries(engine ${SDL_LIBS})


target_link_libraries(a engine ${SDL_LIBS})
include_directories(a ${ENGSRC})