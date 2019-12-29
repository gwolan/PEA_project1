#include <iostream>
#include <Menu/IOhandler.hpp>
#include <Menu/Actions/ExitProgram.hpp>
#include <Menu/Actions/ReadGraphFromFile.hpp>


IOhandler::IOhandler(const std::string& menuContent)
    : selectedAction(nullptr)
    , currentSelection(0)
    , menu(menuContent)
{ }

void IOhandler::printMenu()
{
    std::cout << menu;
}

char IOhandler::getCurrentMenuSelection()
{
    return currentSelection;
}

BaseAction* IOhandler::getSelectedAction()
{
    return selectedAction.get();
}

bool IOhandler::readMenuSelection()
{
    std::cin >> currentSelection;

    return validateInput();
}

bool IOhandler::validateInput()
{
    switch(currentSelection)
    {
        case '0':
        {
            selectedAction = std::make_unique<ExitProgram>("");
        }
        break;
        case '1':
        {
            selectedAction = std::make_unique<ReadGraphFromFile>("Wczytanie grafu z pliku");
            std::cout << "Wybrano - " << selectedAction->getActionName() << std::endl << std::endl;
        }
        break;
        case '2':
        {
            std::cout << "Wybrano " << currentSelection << std::endl;
        }
        break;
        case '3':
        {
            std::cout << "Wybrano " << currentSelection << std::endl;
        }
        break;
        case '4':
        {
            std::cout << "Wybrano " << currentSelection << std::endl;
        }
        break;
        case '5':
        {
            std::cout << "Wybrano " << currentSelection << std::endl;
        }
        break;
        case '6':
        {
            std::cout << "Wybrano " << currentSelection << std::endl;
        }
        break;
        case '7':
        {
            std::cout << "Wybrano " << currentSelection << std::endl;
        }
        break;
        default:
        {
            return false;
        }
    }

    return true;
}
