#include <queue>
#include <Algorithms/BranchAndBound.hpp>
#include <Graph/GraphMatrix.hpp>
#include <Miscellanous/Timer.hpp>


BranchAndBound::BranchAndBound()
    : graph(nullptr)
{ }

std::vector<uint32_t> BranchAndBound::performBranchAndBoundOnGraph(std::unique_ptr<GraphMatrix>& graphMatrix, Timer& timer)
{
    graph = &graphMatrix;

    timer.start();

    struct RouteComparison
    {
        bool operator() (const std::vector<unsigned>& lhs, const std::vector<unsigned>& rhs) const
        {
            return (lhs.at(0) > rhs.at(0));
        }
    };

    std::priority_queue<std::vector<unsigned>, std::vector<std::vector<unsigned> >, RouteComparison> routeQueue;
    std::vector<unsigned> bestSequence;     // Tu bedziemy zapisywac optymalne (w danej chwili) rozwiazanie
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
            for(int i = 0; i < (*graph)->getVertexCount(); i++)
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
                unsigned nextLength = (*graph)->getWeight(nextRoute.back(), i);
                nextRoute.push_back(i);

                // Dalej bedziemy postepowac roznie...
                if(nextRoute.size() > (*graph)->getVertexCount())
                {
                    // Doszlismy wlasnie do liscia
                    // Dodajemy droge powrotna, nie musimy nic szacowac
                    // (wszystko juz wiemy)
                    nextRoute.push_back(0);

                    nextRoute.at(0) = 0;

                    for(int j = 1; j < nextRoute.size() - 1; j++)
                    {
                        // Liczymy dystans od poczatku do konca
                        nextRoute.at(0) += (*graph)->getWeight(nextRoute.at(j), nextRoute.at(j+ 1));
                    }
                    if(optimalRouteLength == -1 || nextRoute.at(0) < optimalRouteLength)
                    {
                        optimalRouteLength = nextRoute.at(0);
                        nextRoute.erase(nextRoute.begin());
                        bestSequence = nextRoute;
                    }
                }
                else
                {
                    // Liczenie tego, co juz wiemy, od nowa...
                    // (dystans od poczatku)
                    nextRoute.at(0) = 0;
                    for(int j = 1; j < nextRoute.size() - 1; j++)
                    {
                        nextRoute.at(0) += (*graph)->getWeight(nextRoute.at(j), nextRoute.at(j + 1));
                    }

                    // Reszte szacujemy...
                    // Pomijamy od razu wierzcholek startowy
                    for(int j = 1; j < (*graph)->getVertexCount(); j++)
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
                        for(int k = 0; k < (*graph)->getVertexCount(); k++)
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
                            unsigned consideredLength = (*graph)->getWeight(j, k);

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

    timer.stop();
    return bestSequence;
}
