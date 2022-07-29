#include <iostream>

#include <boost/program_options.hpp>

#include <fmt/core.h>

#include "core.h"
#include "ArcApp.h"

namespace po = boost::program_options;

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

    return 0;
}