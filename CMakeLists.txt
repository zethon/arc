cmake_minimum_required(VERSION 3.0)

project(CppCursesTemplate)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MACOSX_RPATH 1)

if (MSVC)
    add_link_options(
        /NODEFAULTLIB:library 
    )
endif(MSVC)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

if (WIN32)
    set(CURSES_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    string(REPLACE "\\" "/" CURSES_SRC_DIR "${CURSES_SRC_DIR}")

    include(ExternalProject)
    ExternalProject_Add(
    pdcurses
    SOURCE_DIR ${CURSES_SRC_DIR}/PDCurses
    CONFIGURE_COMMAND  cmake -E echo "Skipping configure step."
    BUILD_COMMAND cmake -E env PDCURSES_SRCDIR=${CURSES_SRC_DIR}/PDCurses nmake -f ${CURSES_SRC_DIR}/PDCurses/wincon/Makefile.vc
    INSTALL_COMMAND cmake -E echo "Skipping install step."
    BUILD_IN_SOURCE 1
    )

    include_directories(${CURSES_SRC_DIR}/PDCurses)
else()
    include(ExternalProject)
    ExternalProject_Add(
    libncurses
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ncurses
    CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/ncurses/configure
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/ncurses
    BUILD_COMMAND make
    INSTALL_COMMAND cmake -E echo "Skipping install step."
    BUILD_IN_SOURCE 1
    )

endif()


add_subdirectory(src)
