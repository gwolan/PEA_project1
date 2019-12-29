#pragma once

#include <string>


class BaseAction
{
    public:
    BaseAction(const std::string& actionName);

    virtual void run() = 0;
    std::string getActionName();


    protected:
    std::string name;
};
