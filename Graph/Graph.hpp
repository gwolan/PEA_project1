#pragma once

#include <vector>
#include <Miscellanous/ParametricArray.hpp>
#include <Graph/GraphAsArray.hpp>


class Graph
{
    public:
        Graph() = default;
        ~Graph() = default;
        static void randomGenerateFullGraph(GraphAsArray &graph, unsigned maxWeight);
        static std::vector<unsigned> travellingSalesmanBruteForce(GraphAsArray &graph);
        static std::vector<unsigned> travellingSalesmanBranchAndBound(GraphAsArray &graph);
};
