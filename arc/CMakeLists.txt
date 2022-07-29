set(SOURCE_FILES
    main.cpp

    ArcApp.cpp
    ArcUtils.cpp
    Canvas.cpp
    StatusLine.cpp
    UrlBar.cpp

    ${CMAKE_SOURCE_DIR}/md4c/src/md4c.c
)

set(HEADER_FILES
    ArcApp.h
    ArcUtils.h
    Canvas.h
    NCursesUtils.h
    StatusLine.h
    UrlBar.h

    ${CMAKE_SOURCE_DIR}/md4c/src/md4c.h
)

if (WIN32)
    set(CURSES_LIBS ${CMAKE_SOURCE_DIR}/PDCurses/pdcurses.lib)
else()
    set(CURSES_LIBS
        ${CMAKE_SOURCE_DIR}/ncurses/lib/libform.a
        ${CMAKE_SOURCE_DIR}/ncurses/lib/libmenu.a
        ${CMAKE_SOURCE_DIR}/ncurses/lib/libncurses++.a
        ${CMAKE_SOURCE_DIR}/ncurses/lib/libncurses.a
        ${CMAKE_SOURCE_DIR}/ncurses/lib/libpanel.a
    )
endif()

add_executable(arc ${SOURCE_FILES} ${HEADER_FILES})

if(APPLE)
    # utils.h/.cpp needs these two libraries if curl
    # is not included
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
    find_library(CARBON_LIBRARY Carbon)
endif()

target_link_libraries(arc
    PUBLIC
        ${CONAN_LIBS}
        ${CURSES_LIBS}
        ${COREFOUNDATION_LIBRARY}
        ${CARBON_LIBRARY}
)

add_executable(example example.cpp)
target_link_libraries(example
    PUBLIC
        ${CONAN_LIBS}
        ${CURSES_LIBS}
        ${COREFOUNDATION_LIBRARY}
        ${CARBON_LIBRARY}
)

z_compile_resources(RESOURCE_FILES
    pages/home.md
)
