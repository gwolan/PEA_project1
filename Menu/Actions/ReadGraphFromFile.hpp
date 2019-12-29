#pragma once

#include <Menu/Actions/BaseAction.hpp>


class GraphAsArray;

class ReadGraphFromFile : public BaseAction
{
    public:
    ReadGraphFromFile(const std::string& actionName);

    void run();
    void init(GraphAsArray* graphToProcess);

    GraphAsArray* graph;
};
