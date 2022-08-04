#pragma once
#include <memory>

#include <spdlog/spdlog.h>

namespace arc::log
{

constexpr auto GLOBAL_LOGGER = "arc";

using SpdLogPtr = std::shared_ptr<spdlog::logger>;

[[maybe_unused]] SpdLogPtr rootLogger();
SpdLogPtr initializeLogger(const std::string& name);

} // namespace arc::log
