cmake_minimum_required(VERSION 3.19)

project(nes_simulator)

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

add_executable(Main src/main.c)
target_link_libraries(Main 
    ${CURSES_LIBRARIES}
    log
    cpu6502
)

enable_testing()

add_executable(unit_tests test/test.c)
target_link_libraries(unit_tests
    log
    cpu6502
)

add_subdirectory(test)
