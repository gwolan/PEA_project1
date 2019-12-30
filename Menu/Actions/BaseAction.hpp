#pragma once

#include <string>
#include <memory>


class GraphAsArray;

class BaseAction
{
    public:
    BaseAction(const std::string& actionName);

    virtual void run() = 0;
    virtual void init(std::unique_ptr<GraphAsArray>& graphAsArray) = 0;
    std::string getActionName();


    protected:
    std::string name;
};
