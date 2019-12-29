#include <fstream>
#include <iostream>
#include <Menu/Actions/ReadGraphFromFile.hpp>
#include <Graph/GraphAsArray.hpp>


ReadGraphFromFile::ReadGraphFromFile(const std::string& actionName)
    : BaseAction(actionName)
{ }

void ReadGraphFromFile::init(GraphAsArray* graphToProcess)
{
    graph = graphToProcess;
}

void ReadGraphFromFile::run()
{
    std::string tspDataFileContent;
    std::ifstream tspDataFile;

    tspDataFile.open("tsp_data.txt");
    if(tspDataFile.is_open())
    {
        tspDataFile >> tspDataFileContent;
        int vertex = atoi(tspDataFileContent.c_str());

        if(graph != NULL)
            delete graph;

        graph = new GraphAsArray(vertex);

        for(int i = 0; i < vertex; i++)
        {
            for(int j = 0; j < vertex; j++)
            {
                tspDataFile >> tspDataFileContent;
                int weight = atoi(tspDataFileContent.c_str());

                if(i != j)
                    graph->addEdge(i, j, weight);
            }
        }

        tspDataFile.close();

        std::cout << "Wczytano - liczba wierzcholkow: " << vertex << std::endl;
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Brak pliku ts_data.txt" << std::endl;
        std::cout << std::endl;
    }
}
