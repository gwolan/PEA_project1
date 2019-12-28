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
        case '0':
        {
            std::cout << "Wybrano " << currentSelection << std::endl;
        }
        break;
        case '1':
        {
            std::cout << "Wybrano " << currentSelection << std::endl;
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
            std::cout << "Wybrano " << currentSelection << std::endl;
            std::cout << "Wybrana opcja nie istnieje." << std::endl << std::endl;
            return false;
        }
    }

    return true;
}
