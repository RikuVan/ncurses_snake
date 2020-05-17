cmake_minimum_required(VERSION 3.15)
project(snake)
set(CMAKE_CXX_STANDARD 17)

#osx
# list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/ncurses/include")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

add_executable(snake main.cpp game/player.cpp game/player.h game/game.cpp game/game.h game/ui.cpp game/ui.h db/sqlite_orm.h db/game_db.h)
target_link_libraries(snake ${CURSES_LIBRARIES} sqlite3)

