set(SOURCE_FILES
    main.cpp

    ArcApp.cpp
    StatusLine.cpp
    UrlBar.cpp
)

set(HEADER_FILES
    ArcApp.h
    Arcutils.h
    StatusLine.h
    UrlBar.h
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

target_link_libraries(arc
    PUBLIC
        ${CONAN_LIBS}
        ${CURSES_LIBS}
)
