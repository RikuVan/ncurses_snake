cmake_minimum_required(VERSION 3.15)
project(snake)
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/ncurses/include")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

add_executable(snake main.cpp player.cpp game.cpp ui.cpp)
target_link_libraries(snake ${CURSES_LIBRARIES})
