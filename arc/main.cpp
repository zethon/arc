#include <iostream>

#include <boost/program_options.hpp>

#include <fmt/core.h>

#include "core.h"
#include "ArcApp.h"

namespace po = boost::program_options;

// void welcome()
// {
//     mvprintw(0, 0, "Welcome to the Arc game!");
//     mvprintw(1, 0, "Press any key to start.");
//     refresh();
//     getch();
// }

int main(int argc, char *argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,?", "print help message")
        ("version,v", "print version string")
        ;

    po::variables_map vm;

    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    }
    catch(const po::error& e)
    {
        std::cerr << e.what();
        return 1;
    }

    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return 0;
    }
    else if (vm.count("version"))
    {
        std::cout << fmt::format("{}\n", APP_TITLE);
        std::cout << fmt::format("build-date : {}\n", BUILDTIMESTAMP);
        return 0;
    }

    arc::App app;
    app.run();

    // initscr();
    // rectangle(0, 0, LINES-1, COLS-1);
    // printw("Hello World !!!");
    // refresh();
    // getch();
    // endwin();

    return 0;
}