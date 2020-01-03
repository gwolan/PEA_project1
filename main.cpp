#include <Menu/IOhandler.hpp>
#include <Graph/GraphMatrix.hpp>


int main()
{
    std::unique_ptr<GraphMatrix> graphMatrix(nullptr);
    std::string menuContent(std::string("\n====================\n") +
                            std::string("PEA Projekt nr 1: Travelling Salesman Problem\n") +
                            std::string("Autor: Grzegorz Wolanski\n\n") +
                            std::string("Menu:\n") +
                            std::string("1. Wczytaj graf z pliku.\n") +
                            std::string("2. Wygeneruj losowy graf.\n") +
                            std::string("3. Wyświetl graf.\n") +
                            std::string("4. Wykonaj przegląd zupełny.\n") +
                            std::string("5. Wykonaj algorytm podzialu i ograniczen.\n") +
                            std::string("6. Testy dla przegladu zupelnego.\n") +
                            std::string("7. Testy dla Branch & Bound.\n") +
                            std::string("0. Wyjscie.\n\n") +
                            std::string("Wybor: "));


    IOhandler ioHandler(menuContent);

    while(ioHandler.getCurrentMenuSelection() != '0')
    {
        ioHandler.printMenu();

        if(ioHandler.readMenuSelection())
        {
            ioHandler.getSelectedAction()->init(graphMatrix);
            ioHandler.getSelectedAction()->run();
        }
    }

    return 0;
}
