cmake_minimum_required(VERSION 3.22)
project(game)

set(CMAKE_CXX_STANDARD 20)

add_executable(game main.cpp Game.cpp Game.h Actor.cpp Actor.h Animal.cpp Animal.h Bear.cpp Bear.h Hippo.cpp Hippo.h Pig.cpp Pig.h Narwhal.cpp Narwhal.h Penguin.cpp Penguin.h Walrus.cpp Walrus.h Car.cpp Car.h)

# For finding our SDL2 package!
INCLUDE(FindPkgConfig)

# Searching SDL2 package.
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)

# Including our external library's directory for header files!
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})

# Linking SDL2 library with our project.
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
