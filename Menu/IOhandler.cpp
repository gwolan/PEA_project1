#include <iostream>
#include <Menu/IOhandler.hpp>
#include <Menu/Actions/ExitProgram.hpp>
#include <Menu/Actions/ReadGraphFromFile.hpp>
#include <Menu/Actions/DisplayGraph.hpp>
#include <Menu/Actions/GenerateRandomGraph.hpp>


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
            selectedAction = std::make_unique<ExitProgram>("Wyjście z programu");
        }
        break;
        case '1':
        {
            selectedAction = std::make_unique<ReadGraphFromFile>("Wczytanie grafu z pliku");
        }
        break;
        case '2':
        {
            selectedAction = std::make_unique<GenerateRandomGraph>("Wygenerowanie losowego grafu");
        }
        break;
        case '3':
        {
            selectedAction = std::make_unique<DisplayGraph>("Wyświetlenie grafu (macierz sasiedztwa)");
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
            std::cout << "Wybrana opcja nie istnieje." << std::endl;
            return false;
        }
    }

    std::cout << "Wybrano - " << selectedAction->getActionName() << std::endl << std::endl;
    return true;
}
