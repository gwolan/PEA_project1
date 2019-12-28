#include <fstream>
#include <iostream>
#include <cstdlib>
#include <Miscellanous/Timer.hpp>
#include <Miscellanous/ParametricArray.hpp>
#include <Graph/ArrayGraph.hpp>
#include <Graph/ListGraph.hpp>

using namespace std;

// USTAWIENIA
// Ilosc miast w kazdym z automatycznych pomiarow dla problemu komiwojazera
// Przeglad zupelny - pierwsze 4, podzial i ograniczenia - wszystkie
const int measureSalesmanCities[7] = {4, 6, 8, 11, 14, 18, 22};
// Maksymalna odleglosc miast (nie ma wplywu na pomiary)
const int measureSalesmanDistance = 400;
// Przy ILOSCI pomiarow nie majstrowac - chyba ze wiemy, gdzie jeszcze poprawic kod
// Inaczej mozemy sie spodziewac "cudu nad klawiatura" ;-)

// Wykorzystanie reprezentacji grafu w postaci list sasiedztwa...
// ...zamiast (domyslnie) macierzy sasiedztwa
// (wolniejsze obliczenia, mniejsze uzycie pamieci)
const bool useListGraph = false;

int main()
{
    Timer timer;                // czasomierz
    char menuSelection;
    Graph *graph = NULL;            // <- tu bedziemy zapisywac adresy przez caly program

    cout << "PEA Projekt 1 v1.0" << endl;
    cout << "Jan Potocki 2017" << endl;
    cout << "(beerware)" << endl;
    if(useListGraph)
        cout << "Uzycie listowej reprezentacji grafu" << endl;
    else
        cout << "Uzycie macierzowej reprezentacji grafu" << endl;
    cout << endl;

    char salesmanSelection;
    while(salesmanSelection != '0')
    {
        cout << "1 - wygeneruj losowe dane" << endl;
        cout << "2 - wyswietl dane" << endl;
        cout << "3 - przeglad zupelny (brute force)" << endl;
        cout << "4 - podzial i ograniczenia" << endl;
        cout << "5 - automatyczne pomiary (przeglad zupelny)" << endl;
        cout << "6 - automatyczne pomiary (podzial i ograniczenia)" << endl;
        cout << "7 - wczytaj dane z tsp_data.txt" << endl;
        cout << "Aby zakonczyc - 0" << endl;
        cout << "Wybierz: ";
        cin >> salesmanSelection;
        cout << endl;

        switch(salesmanSelection)
        {
            case '1':
            {
                int vertex;
                cout << "Liczba miast: ";
                cin >> vertex;
                cout << endl;

                if(graph != NULL)
                    delete graph;

                if(useListGraph)
                    graph = new ListGraph(vertex);
                else
                    graph = new ArrayGraph(vertex);

                Graph::randomGenerateFullGraph(*graph, measureSalesmanDistance);
            }
            break;
            case '2':
            {
                if(graph != NULL)
                    graph->displayGraph();
                else
                    cout << "Brak wygenerowanych danych" << endl;
                cout << endl;
            }
            break;
            case '3':
            {
                if(graph != NULL)
                {
                    timer.start();
                    vector<unsigned> route = Graph::travellingSalesmanBruteForce(*graph);
                    timer.stop();

                    // Wyswietlenie trasy
                    unsigned distFromStart = 0;
                    unsigned length = 0;
                    cout << route.at(0) << '\t' << length << '\t' << distFromStart << endl;
                    for(int i = 1; i < route.size(); i++)
                    {
                        length = graph->getWeight(route.at(i - 1), route.at(i));
                        distFromStart += length;

                        cout << route.at(i) << '\t' << length << '\t' << distFromStart << endl;
                    }

                    cout << "Dlugosc trasy: " << distFromStart << endl;
                    cout << endl;
                    cout << "Czas wykonania algorytmu [s]: " << timer.getTime() << endl;
                }
                else
                    cout << "Brak wygenerowanych danych" << endl;
                cout << endl;
            }
            break;
            case '4':
            {
                if(graph != NULL)
                {
                    timer.start();
                    vector<unsigned> route = Graph::travellingSalesmanBranchAndBound(*graph);
                    timer.stop();

                    // Wyswietlenie trasy
                    unsigned distFromStart = 0;
                    unsigned length = 0;
                    cout << route.at(0) << '\t' << length << '\t' << distFromStart << endl;
                    for(int i = 1; i < route.size(); i++)
                    {
                        length = graph->getWeight(route.at(i - 1), route.at(i));
                        distFromStart += length;

                        cout << route.at(i) << '\t' << length << '\t' << distFromStart << endl;
                    }

                    cout << "Dlugosc trasy: " << distFromStart << endl;
                    cout << endl;
                    cout << "Czas wykonania algorytmu [s]: " << timer.getTime() << endl;
                }
                else
                    cout << "Brak wygenerowanych danych" << endl;
                cout << endl;
            }
            break;
            case '5':
            {
                // Dla brute force tylko 3 pomiary, kolejne trwaja juz za dlugo
                double measureResults[4];
                for(int i = 0; i < 4; i++)
                {
                    measureResults[i] = 0;
                }

                cout << "Pomiary dla problemu komiwojazera, przeglad zupelny" << endl;

                // Petla pomiarowa
                for(int krok = 0; krok < 100; krok++)
                {
                    for(int i = 0; i < 4; i++)
                    {
                        if(graph != NULL)
                            delete graph;

                        cout << "Pomiar " << measureSalesmanCities[i] << " (" << krok + 1 << " ze 100)..." << endl;

                        if(useListGraph)
                            graph = new ListGraph(measureSalesmanCities[i]);
                        else
                            graph = new ArrayGraph(measureSalesmanCities[i]);

                        Graph::randomGenerateFullGraph(*graph, measureSalesmanDistance);
                        timer.start();
                        Graph::travellingSalesmanBruteForce(*graph);
                        timer.stop();
                        measureResults[i] += timer.getTime();
                    }
                }

                cout << "Opracowywanie wynikow..." << endl;

                for(int i = 0; i < 4; i++)
                {
                    measureResults[i] = measureResults[i]/100;
                }

                cout << "Zapis wynikow..." << endl;

                ofstream salesmanToFile;
                salesmanToFile.open("wyniki-komiwojazer-przeglad.txt");
                for(int i = 0; i < 4; i++)
                {
                    salesmanToFile << measureSalesmanCities[i] << " [s]: " << measureResults[i] << endl;
                }
                salesmanToFile.close();

                cout << "Gotowe!" << endl;
                cout << endl;
            }
            break;
            case '6':
            {
                double measureResults[7];
                for(int i = 0; i < 7; i++)
                {
                    measureResults[i] = 0;
                }

                cout << "Pomiary dla problemu komiwojazera, podzial i ograniczenia" << endl;

                // Petla pomiarowa
                for(int krok = 0; krok < 100; krok++)
                {
                    for(int i = 0; i < 7; i++)
                    {
                        if(graph != NULL)
                            delete graph;

                        cout << "Pomiar " << measureSalesmanCities[i] << " (" << krok + 1 << " ze 100)..." << endl;

                        if(useListGraph)
                            graph = new ListGraph(measureSalesmanCities[i]);
                        else
                            graph = new ArrayGraph(measureSalesmanCities[i]);

                        Graph::randomGenerateFullGraph(*graph, measureSalesmanDistance);
                        timer.start();
                        Graph::travellingSalesmanBranchAndBound(*graph);
                        timer.stop();
                        measureResults[i] += timer.getTime();
                    }
                }

                cout << "Opracowywanie wynikow..." << endl;

                for(int i = 0; i < 7; i++)
                {
                    measureResults[i] = measureResults[i]/100;
                }

                cout << "Zapis wynikow..." << endl;

                ofstream salesmanToFile;
                salesmanToFile.open("wyniki-komiwojazer-bnb.txt");
                for(int i = 0; i < 7; i++)
                {
                    salesmanToFile << measureSalesmanCities[i] << " [s]: " << measureResults[i] << endl;
                }
                salesmanToFile.close();

                cout << "Gotowe!" << endl;
                cout << endl;
            }
            break;
            case '7':
            {
                string fileInput;
                ifstream salesmanDataFile;

                salesmanDataFile.open("tsp_data.txt");
                if(salesmanDataFile.is_open())
                {
                    salesmanDataFile >> fileInput;
                    int vertex = atoi(fileInput.c_str());

                    if(graph != NULL)
                        delete graph;

                    if(useListGraph)
                        graph = new ListGraph(vertex);
                    else
                        graph = new ArrayGraph(vertex);

                    for(int i = 0; i < vertex; i++)
                    {
                        for(int j = 0; j < vertex; j++)
                        {
                            salesmanDataFile >> fileInput;
                            int weight = atoi(fileInput.c_str());

                            if(i != j)
                                graph->addEdge(i, j, weight);
                        }
                    }

                    salesmanDataFile.close();

                    cout << "Wczytano - liczba wierzcholkow: " << vertex << endl;
                    cout << endl;
                }
                else
                {
                    cout << "Brak pliku ts_data.txt" << endl;
                    cout << endl;
                }
            }
            break;
            case '0':
            {
            }
            break;
            default:
            {
                cout << "Nieprawidlowy wybor" << endl;
                cout << endl;
            }
        }
    }

    if(graph != NULL)
        delete graph;

    cout << "Konczenie..." << endl;
    // Easter egg :-P - ktos zna?
    cout << '"' << "...If you've just spent nearly 30 hours" << endl;
    cout << "Debugging some assembly," << endl;
    cout << "Soon you will be glad to" << endl;
    cout << "Write in C..." << '"' << endl;
    cout << "(AK2 Labs, Inc.)" << endl;
    cout << endl;

    return 0;
}
