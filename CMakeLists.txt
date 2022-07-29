cmake_minimum_required(VERSION 3.0)

project(arc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
include(CMake/ZCompileResource.cmake)

# initialize conan libs
include(CMake/conan.cmake)
conan_cmake_run(REQUIRES
    boost/1.79.0
    spdlog/1.9.2
    fmt/8.1.1
    libcurl/7.84.0
    zlib/1.2.12
    BASIC_SETUP CMAKE_TARGETS
    GENERATORS cmake_find_package cmake_paths
    BUILD missing
    OPTIONS 
        boost:shared=False 
        boost:without_test=False 
        boost:without_program_options=False 
        boost:without_filesystem=False 
        boost:without_system=False  
        boost:without_exception=False
        boost:without_contract=False
)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS KEEP_RPATHS)

if (MSVC)
    add_link_options(
        /IGNORE:4099
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

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/md4c/src)

add_subdirectory(arc)
