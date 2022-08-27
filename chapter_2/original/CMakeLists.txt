cmake_minimum_required(VERSION 3.22)
project(game)

set(CMAKE_CXX_STANDARD 20)

add_executable(game main.cpp Math.h Game.cpp Game.h Actor.cpp Actor.h Component.cpp Component.h SpriteComponent.cpp SpriteComponent.h AnimSpriteComponent.cpp AnimSpriteComponent.h BGSpriteComponent.cpp BGSpriteComponent.h Ship.cpp Ship.h)

# For finding our SDL2 package!
INCLUDE(FindPkgConfig)

# Searching SDL2 package.
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)

# Including our external library's directory for header files!
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

# Linking SDL2 library with our project.
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
