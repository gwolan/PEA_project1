#include <iostream>
#include <Menu/Actions/ReadGraphFromFile.hpp>
#include <Graph/GraphAsArray.hpp>


ReadGraphFromFile::ReadGraphFromFile(const std::string& actionName)
    : BaseAction(actionName)
    , graph(nullptr)
    , tspDataFileContent()
    , tspDataFile()
    , vertexCount(0)
{ }

void ReadGraphFromFile::init(std::unique_ptr<GraphAsArray>& graphAsArray)
{
    graph = &graphAsArray;

    tspDataFile.open("tsp_data.txt");
    readVertexCountIfPossible();
}

void ReadGraphFromFile::run()
{
    if(tspDataFile.is_open())
    {
        // if Graph is initialized, reset it to default
        *graph = std::make_unique<GraphAsArray>(vertexCount);

        fillGraphAdjacencyMatrix();
        tspDataFile.close();

        std::cout << "Graf pomyslnie wczytany z pliku. Liczba wezlow: " << vertexCount << std::endl;
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Plik \"tsp_data.txt\" nie istnieje!" << std::endl;
        std::cout << std::endl;
    }
}

void ReadGraphFromFile::readVertexCountIfPossible()
{
    if(tspDataFile.is_open())
    {
        tspDataFile >> tspDataFileContent;
        vertexCount = atoi(tspDataFileContent.c_str());
    }
}

void ReadGraphFromFile::fillGraphAdjacencyMatrix()
{
    for(std::size_t i = 0; i < vertexCount; i++)
    {
        for(std::size_t j = 0; j < vertexCount; j++)
        {
            tspDataFile >> tspDataFileContent;
            uint32_t weight = atoi(tspDataFileContent.c_str());

            if(i != j)
            {
                (*graph)->addEdge(i, j, weight);
            }
        }
    }
}
