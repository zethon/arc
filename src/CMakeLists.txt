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

add_executable(main main.cpp)


target_link_libraries(main
    PUBLIC
        ${CONAN_LIBS}
        ${CURSES_LIBS}
)
