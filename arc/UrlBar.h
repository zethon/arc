#pragma once

#include <string>

namespace arc
{

class UrlBar
{

public:
    void draw();

    void setLocation(const std::string& location) { _location = location; }
    std::string location() const { return _location; }

private:
    std::string _location;

};

} // namespace arc
