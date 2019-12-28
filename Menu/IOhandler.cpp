#include <Menu/IOhandler.hpp>
#include <iostream>


IOhandler::IOhandler(const std::string& menuContent)
    : currentSelection(0)
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

bool IOhandler::readMenuSelection()
{
    std::cin >> currentSelection;

    return validateInput();
}

bool IOhandler::validateInput()
{
    switch(currentSelection)
    {
        case '1':
        {
        }
        break;
        case '2':
        {
        }
        break;
        case '3':
        {
        }
        break;
        case '4':
        {
        }
        break;
        case '5':
        {
        }
        break;
        case '6':
        {
        }
        break;
        case '7':
        {
        }
        break;
        default:
        {
            std::cout << "Wybrana opcja nie istnieje." << std::endl << std::endl;
            return false;
        }
    }

    return true;
}
