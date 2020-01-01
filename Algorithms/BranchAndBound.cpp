#include <numeric>
#include <Algorithms/BranchAndBound.hpp>
#include <Graph/GraphMatrix.hpp>
#include <Miscellanous/Timer.hpp>


BranchAndBound::BranchAndBound()
    : graph(nullptr)
    , INFINITY(-1)
    , bestPathLength(INFINITY)
    , bestSequence()
{ }

std::vector<uint32_t> BranchAndBound::performBranchAndBoundOnGraph(std::unique_ptr<GraphMatrix>& graphMatrix, Timer& timer)
{
    graph = &graphMatrix;

    timer.start();
    std::vector<uint32_t> currentPath;     // Niejawne tworzenie drzewa, tu bedzie korzen
    std::vector<uint32_t> verticies((*graph)->getVertexCount());
    std::iota(verticies.begin(), verticies.end(), 0);

    PathQueue pathQueue;

    startAlgorithm(verticies, currentPath, pathQueue);

    timer.stop();
    return bestSequence;
}

void BranchAndBound::startAlgorithm(std::vector<uint32_t>& verticies,
                                    std::vector<uint32_t>& currentPath, BranchAndBound::PathQueue& pathQueue)
{
    // UMOWA
    // Pierwszy element wektora to dlugosc trasy (trzeba ustawic "z palca"!)
    // Kolejne to wierzcholki na trasie
    currentPath.push_back(0);              // Poczatkowe oszacowanie nie ma znaczenia
    currentPath.push_back(0);              // Wierzcholek startowy (korzen drzewa rozwiazan)
    pathQueue.push(currentPath);          // Dodanie do kolejki korzenia

    while(!pathQueue.empty())
    {
        // Przypisanie korzenia do dalszej roboty
        currentPath = pathQueue.top();
        pathQueue.pop();

        // Sprawdzenie, czy rozwiazanie jest warte rozwijania, czy odrzucic
        if(isGivenPathPromising(currentPath))
        {
            performCalculations(verticies, currentPath, pathQueue);
        }
        else
        {
            break;
        }
    }
}

void BranchAndBound::performCalculations(std::vector<uint32_t>& verticies,
                                         std::vector<uint32_t>& currentPath, BranchAndBound::PathQueue& pathQueue)
{
    for(auto verticiesIt = verticies.begin(); verticiesIt != verticies.end(); ++verticiesIt)
    {
        // Petla wykonywana dla kazdego potomka ropatrywanego wlasnie rozwiazania w drzewie
        // Ustalenie, czy dany wierzcholek mozna jeszcze wykorzystac, czy juz zostal uzyty
        if(wasVertexAlreadyChecked(currentPath, *verticiesIt))
        {
            continue;
        }

        // Niejawne utworzenie nowego wezla reprezuntujacego rozpatrywane rozwiazanie...
        std::vector<uint32_t> newPath = currentPath;
        newPath.push_back(*verticiesIt);

        // Dalej bedziemy postepowac roznie...
        if(isCurrentlyEvaluatedPathEnding(newPath, verticies))
        {
            finalizeCalculations(newPath);
        }
        else
        {
            performNextIteration(verticies, currentPath, newPath, *verticiesIt);

            // ...i teraz zastanawiamy sie co dalej
            if(isGivenPathPromising(newPath))
            {
                pathQueue.push(newPath);
            }
        }
    }
}

void BranchAndBound::performNextIteration(std::vector<uint32_t>& verticies, 
                                          std::vector<uint32_t>& currentPath,
                                          std::vector<uint32_t>& newPath,
                                          uint32_t currentVertex)
{
            // Liczenie tego, co juz wiemy, od nowa...
            // (dystans od poczatku)
            newPath.front() = calculatePathsCost(newPath);

            // Reszte szacujemy...
            // Pomijamy od razu wierzcholek startowy
            for(auto verticiesIt = std::next(verticies.begin()); verticiesIt != verticies.end(); ++verticiesIt)
            {
                // Odrzucenie wierzcholkow juz umieszczonych na trasie
                if(wasVertexAlreadyChecked(currentPath, *verticiesIt))
                {
                    continue;
                }

                int32_t minEdge = INFINITY;
                for(auto vertex = verticies.begin(); vertex != verticies.end(); ++vertex)
                {
                    // Odrzucenie krawedzi do wierzcholka 0 przy ostatnim wierzcholku w czesciowym rozwiazaniu
                    // Wyjatkiem jest ostatnia mozliwa krawedz
                    if(*verticiesIt == currentVertex && *vertex == 0)
                        continue;

                    // Odrzucenie krawedzi do wierzcholka umieszczonego juz na rozwazanej trasie
                    bool vertexUsed = false;
                    for(int32_t l = 2; l < newPath.size(); l++)
                    {
                        if(*vertex == newPath.at(l))
                        {
                            vertexUsed = true;
                            break;
                        }
                    }
                    if(vertexUsed)
                        continue;

                    // Odrzucenie samego siebie
                    if(*vertex == *verticiesIt)
                        continue;

                    // Znalezienie najkrotszej mozliwej jeszcze do uzycia krawedzi
                    uint32_t consideredLength = (*graph)->getWeight(*verticiesIt, *vertex);

                    if(minEdge == INFINITY)
                        minEdge = consideredLength;
                    else if(minEdge > consideredLength)
                        minEdge = consideredLength;
                }
                newPath.at(0) += minEdge;
            }
}

void BranchAndBound::finalizeCalculations(std::vector<uint32_t>& currentPath)
{
    // Doszlismy wlasnie do liscia
    // Dodajemy droge powrotna, nie musimy nic szacowac
    // (wszystko juz wiemy)
    currentPath.push_back(0);
    currentPath.front() = calculatePathsCost(currentPath);

    assignNewBestPathIfPossible(currentPath);
}

void BranchAndBound::assignNewBestPathIfPossible(std::vector<uint32_t>& possibleBestPath)
{
    if(bestPathLength == INFINITY || possibleBestPath.front() < bestPathLength)
    {
        bestPathLength = possibleBestPath.front();
        possibleBestPath.erase(possibleBestPath.begin());
        bestSequence = possibleBestPath;
    }
}

bool BranchAndBound::wasVertexAlreadyChecked(const std::vector<uint32_t>& currentPath, const uint32_t vertex)
{
    for(auto vertexIt  = std::next(currentPath.begin());
             vertexIt != currentPath.cend();
           ++vertexIt)
    {
        if(*vertexIt == vertex)
        {
            return true;
        }
    }

    return false;
}

bool BranchAndBound::isCurrentlyEvaluatedPathEnding(const std::vector<uint32_t>& evaluatedPath,
                                                    const std::vector<uint32_t>& verticies)
{
    return evaluatedPath.size() > verticies.size();
}

uint32_t BranchAndBound::calculatePathsCost(const std::vector<uint32_t>& path)
{
    // path cost = sum of all weights of the edges
    uint32_t cost = 0;

    for(auto vertexIt  = std::next(path.cbegin());
             vertexIt != std::prev(path.cend());
           ++vertexIt)
    {
        cost += (*graph)->getWeight(*vertexIt, *std::next(vertexIt));
    }

    return cost;
}

bool BranchAndBound::isGivenPathPromising(const std::vector<uint32_t>& promisingPath)
{
    return (bestPathLength == INFINITY) || (promisingPath.front() < bestPathLength);
}
