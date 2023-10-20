cmake_minimum_required(VERSION 3.19)

project(nes_simulator)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

include_directories(include)

add_library(log
    src/log.c
)

add_library(cpu6502
    src/bus.c
    src/nes6502.c
)
add_library(nes
    src/rom.c
    # src/ppu.c
)

add_executable(Main src/main.c)
target_link_libraries(Main 
    ${CURSES_LIBRARIES}
    log
    cpu6502
    nes
)

add_executable(GtkUI src/ui.c)
target_link_libraries(GtkUI
    ${GTK4_LIBRARIES}
    log
    cpu6502
    nes
)

enable_testing()

add_executable(unit_tests test/test.c)
target_link_libraries(unit_tests
    log
    cpu6502
    nes
)

add_subdirectory(test)
