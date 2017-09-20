cmake_minimum_required(VERSION 3.7)
project(Battleship)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -D_GNU_SOURCE -I/usr/include/ncursesw")


set(EXTRA_LIBS ${EXTRA_LIBS} ncurses++w formw menuw panelw ncursesw tinfo)

add_subdirectory(${PROJECT_SOURCE_DIR}/ai)
add_subdirectory(${PROJECT_SOURCE_DIR}/model)
add_subdirectory(${PROJECT_SOURCE_DIR}/ui)
add_subdirectory(${PROJECT_SOURCE_DIR}/controller)


configure_file(battleship.txt battleship.txt COPYONLY)

#set(SOURCE_FILES main.cpp model/Grid.cpp ui/Menu.cpp model/Game.cpp model/Player.cpp ui/GameWindow.cpp ui/GridWindow.cpp)
add_executable(Battleship main.cpp)

target_link_libraries(Battleship LINK_PUBLIC  ui controller model ai ${EXTRA_LIBS} )
