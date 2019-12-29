#pragma once

#include <Menu/Actions/BaseAction.hpp>


class ReadGraphFromFile : public BaseAction
{
    public:
    ReadGraphFromFile(const std::string& actionName);

    void run();
};
