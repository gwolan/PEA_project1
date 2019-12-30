#pragma once

#include <fstream>
#include <memory>
#include <Menu/Actions/BaseAction.hpp>


class GraphAsArray;

class ReadGraphFromFile : public BaseAction
{
    public:
    ReadGraphFromFile(const std::string& actionName);

    void run();
    void init(std::unique_ptr<GraphAsArray>& graphAsArray);


    private:
    void readVertexCountIfPossible();
    void fillGraphAdjacencyMatrix();

    std::unique_ptr<GraphAsArray>* graph;
    std::string tspDataFileContent;
    std::ifstream tspDataFile;
    uint32_t vertexCount;
};
