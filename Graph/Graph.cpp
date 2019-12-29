#include <Graph/Graph.hpp>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <iostream>

void Graph::randomGenerateFullGraph(GraphAsArray &graph, unsigned maxWeight)
{
    srand(time(NULL));

    for(int i = 0; i < graph.vertexNumber; i++)
    {
        for(int j = 0; j < graph.vertexNumber; j++)
        {
            if(i != j)
            {
                // Bez warunku na krawedzie juz wygenerowane...
                // ...z tym radzi sobie juz metoda addEdge
                int randomWeight = rand()%maxWeight + 1;
                graph.addEdge(i, j, randomWeight);
            }
        }
    }
}

std::vector<unsigned> Graph::travellingSalesmanBruteForce(GraphAsArray &graph)
{
    // ALGORYTM przegladu zupelnego
    // Implementacja: Jan Potocki 2017
    std::vector<ParametricArray*> combinationsArray;
    std::vector<unsigned> vertexArray;
    ParametricArray *combination;

    // Generowanie "spisu" wierzcholkow
    // (od razu w odpowiedniej kolejnosci dla next_permutation)
    for(int i = 1; i < graph.vertexNumber; i++)
        vertexArray.push_back(i);

    // Petla dodajaca kolejne permutacje do tablicy
    do
    {
        int distance;

        // Dodanie wierzcholka startowego i pierwszego na trasie
        combination = new ParametricArray;
        combination->add(0, 0);
        distance = graph.getWeight(0, vertexArray.front());
        combination->add(vertexArray.front(), distance);

        // W petli reszta wiercholkow
        for(int i = 1; i < vertexArray.size(); i++)
        {
            distance = graph.getWeight(vertexArray.at(i - 1), vertexArray.at(i));
            combination->add(vertexArray.at(i), distance);
        }

        // Powrot do wierzcholka startowego
        distance = graph.getWeight(vertexArray.back(), 0);
        combination->add(0, distance);
        combinationsArray.push_back(combination);
    }
    while(next_permutation(vertexArray.begin(), vertexArray.end()));

    // Wyszukiwanie najlepszej permutacji
    ParametricArray *minCombination = combinationsArray.front();
    int minRoute = minCombination->sumParameters();

    for(int i = 0; i < combinationsArray.size(); i++)
    {
        int route = combinationsArray.at(i)->sumParameters();

        if(route < minRoute)
        {
            minRoute = route;
            minCombination = combinationsArray.at(i);
        }
    }

    std::vector<unsigned> optimal;

    for(int i = 0; i < minCombination->getLength(); i++)
        optimal.push_back(minCombination->getValue(i));

    for(int i = 0; i < combinationsArray.size(); i++)
        delete combinationsArray.at(i);

    return optimal;
}

std::vector<unsigned> Graph::travellingSalesmanBranchAndBound(GraphAsArray &graph)
{
    // ALGORYTM pracujacy w oparciu o kolejke priorytetowa i niejawnie utworzone drzewo
    // Zrodlo: www.ii.uni.wroc.pl/~prz/2011lato/ah/opracowania/met_podz_ogr.opr.pdf
    // Autor: Mateusz Lyczek 2011
    // Implementacja: Jan Potocki 2017

    struct RouteComparison
    {
        bool operator() (const std::vector<unsigned>& lhs, const std::vector<unsigned>& rhs) const
        {
            return (lhs.at(0) > rhs.at(0));
        }
    };

    std::priority_queue<std::vector<unsigned>, std::vector<std::vector<unsigned> >, RouteComparison> routeQueue;
    std::vector<unsigned> optimalRoute;     // Tu bedziemy zapisywac optymalne (w danej chwili) rozwiazanie
    int optimalRouteLength = -1;            // -1 - bedziemy odtad uznawac, ze to jest nieskonczonosc ;-)

    // UMOWA
    // Pierwszy element wektora to dlugosc trasy (trzeba ustawic "z palca"!)
    // Kolejne to wierzcholki na trasie
    std::vector<unsigned> currentRoute;     // Niejawne tworzenie drzewa, tu bedzie korzen
    currentRoute.push_back(0);              // Poczatkowe oszacowanie nie ma znaczenia
    currentRoute.push_back(0);              // Wierzcholek startowy (korzen drzewa rozwiazan)
    routeQueue.push(currentRoute);          // Dodanie do kolejki korzenia

    while(!routeQueue.empty())
    {
        // Przypisanie korzenia do dalszej roboty
        currentRoute = routeQueue.top();
        routeQueue.pop();

        // Sprawdzenie, czy rozwiazanie jest warte rozwijania, czy odrzucic
        if(optimalRouteLength == -1 || currentRoute.at(0) < optimalRouteLength)
        {
            for(int i = 0; i < graph.vertexNumber; i++)
            {
                // Petla wykonywana dla kazdego potomka ropatrywanego wlasnie rozwiazania w drzewie
                // Ustalenie, czy dany wierzcholek mozna jeszcze wykorzystac, czy juz zostal uzyty
                bool vertexUsed = false;
                for(int j = 1; j < currentRoute.size(); j++)
                {
                    if(currentRoute.at(j) == i)
                    {
                        vertexUsed = true;
                        break;
                    }
                }
                if(vertexUsed)
                    continue;

                // Niejawne utworzenie nowego wezla reprezuntujacego rozpatrywane rozwiazanie...
                std::vector<unsigned> nextRoute = currentRoute;
                unsigned nextLength = graph.getWeight(nextRoute.back(), i);
                nextRoute.push_back(i);

                // Dalej bedziemy postepowac roznie...
                if(nextRoute.size() > graph.vertexNumber)
                {
                    // Doszlismy wlasnie do liscia
                    // Dodajemy droge powrotna, nie musimy nic szacowac
                    // (wszystko juz wiemy)
                    nextRoute.push_back(0);

                    nextRoute.at(0) = 0;

                    for(int j = 1; j < nextRoute.size() - 1; j++)
                    {
                        // Liczymy dystans od poczatku do konca
                        nextRoute.at(0) += graph.getWeight(nextRoute.at(j), nextRoute.at(j+ 1));
                    }
                    if(optimalRouteLength == -1 || nextRoute.at(0) < optimalRouteLength)
                    {
                        optimalRouteLength = nextRoute.at(0);
                        nextRoute.erase(nextRoute.begin());
                        optimalRoute = nextRoute;
                    }
                }
                else
                {
                    // Liczenie tego, co juz wiemy, od nowa...
                    // (dystans od poczatku)
                    nextRoute.at(0) = 0;
                    for(int j = 1; j < nextRoute.size() - 1; j++)
                    {
                        nextRoute.at(0) += graph.getWeight(nextRoute.at(j), nextRoute.at(j + 1));
                    }

                    // Reszte szacujemy...
                    // Pomijamy od razu wierzcholek startowy
                    for(int j = 1; j < graph.vertexNumber; j++)
                    {
                        // Odrzucenie wierzcholkow juz umieszczonych na trasie
                        bool vertexUsed = false;
                        for(int k = 1; k < currentRoute.size(); k++)
                        {
                            if(j == currentRoute.at(k))
                            {
                                vertexUsed = true;
                                break;
                            }
                        }
                        if(vertexUsed)
                            continue;

                        int minEdge = -1;
                        for(int k = 0; k < graph.vertexNumber; k++)
                        {
                            // Odrzucenie krawedzi do wierzcholka 0 przy ostatnim wierzcholku w czesciowym rozwiazaniu
                            // Wyjatkiem jest ostatnia mozliwa krawedz
                            if(j == i && k == 0)
                                continue;

                            // Odrzucenie krawedzi do wierzcholka umieszczonego juz na rozwazanej trasie
                            bool vertexUsed = false;
                            for(int l = 2; l < nextRoute.size(); l++)
                            {
                                if(k == nextRoute.at(l))
                                {
                                    vertexUsed = true;
                                    break;
                                }
                            }
                            if(vertexUsed)
                                continue;

                            // Odrzucenie samego siebie
                            if(k == j)
                                continue;

                            // Znalezienie najkrotszej mozliwej jeszcze do uzycia krawedzi
                            unsigned consideredLength = graph.getWeight(j, k);

                            if(minEdge == -1)
                                minEdge = consideredLength;
                            else if(minEdge > consideredLength)
                                minEdge = consideredLength;
                        }
                        nextRoute.at(0) += minEdge;
                    }

                    // ...i teraz zastanawiamy sie co dalej
                    if(optimalRouteLength == -1 || nextRoute.at(0) < optimalRouteLength)
                    {
                        routeQueue.push(nextRoute);
                    }
                }
            }
        }
        else
        {
            break;
        }
    }

    return optimalRoute;
}
