#pragma once

#include <string>
#include <memory>
#include <Graph/GraphMatrix.hpp>
#include <Application/Menu/IOhandler.hpp>
#include <Application/Menu/ActionStrategy.hpp>


class ApplicationFacade
{
    public:
    ApplicationFacade(const std::string& menuContent);
    ~ApplicationFacade() = default;

    void run();
    void printMenu();
    void readMenuSelection();
    char getCurrentMenuSelection();


    private:
    std::unique_ptr<GraphMatrix> graph;
    IOhandler ioHandler;
    ActionStrategy actionStrategy;
};
