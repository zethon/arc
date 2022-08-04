#include <iostream>

#include <boost/algorithm/string/trim.hpp>
#include <boost/program_options.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/common.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <fmt/core.h>

#include "core.h"
#include "ArcApp.h"
#include "ArcLogger.h"
#include "OSUtils.h"

namespace po = boost::program_options;

void initLogging(std::string_view logfile)
{
    // create the root logger
    spdlog::stdout_color_mt(arc::log::GLOBAL_LOGGER);

#ifdef RELEASE
    spdlog::set_level(spdlog::level::info);
#else
    spdlog::set_level(spdlog::level::trace);
#endif

    if (logfile.size() > 0)
    {
        auto logger = arc::log::rootLogger();
        auto rotating = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            logfile.data(), 1024 * 1024 * 5, 3);

        logger->sinks().push_back(rotating);
    }
}

int main(int argc, char *argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,?", "print help message")
        ("logfile,l", po::value<std::string>(), "path of logfile")
        ("loglevel", po::value<std::string>(), "trace,debug,info,warning,error,critical,off")
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

    std::string logfile;
    if (vm.count("logfile"))
    {
        logfile = vm["logfile"].as<std::string>();

        // leading spaces can cause problems on macOS
        boost::algorithm::trim(logfile);
    }

    initLogging(logfile);
    auto logger = arc::log::rootLogger();
    if (vm.count("loglevel"))
    {
        const auto configLevel = spdlog::level::from_str(vm["loglevel"].as<std::string>());
        logger->set_level(configLevel);
    }

    logger->info("Starting {} v{}",APP_NAME_LONG, VERSION);
    logger->info("built on {} for {}", BUILDTIMESTAMP, os::utils::getOsString());


    arc::App app;
    app.run();

    return 0;
}