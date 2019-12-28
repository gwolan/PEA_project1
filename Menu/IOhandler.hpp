#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Menu/Actions/BaseAction.hpp>


class IOhandler
{
    public:
    IOhandler(const std::string& menuContent);

    void printMenu();
    bool readMenuSelection();
    char getCurrentMenuSelection();


    private:
    bool validateInput();

    std::shared_ptr<BaseAction> selectedAction;
    char currentSelection;
    const std::string menu;
};
