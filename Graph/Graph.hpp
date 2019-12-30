#pragma once

#include <vector>
#include <Miscellanous/ParametricArray.hpp>
#include <Graph/GraphMatrix.hpp>


class Graph
{
    public:
        Graph() = default;
        ~Graph() = default;
        static void randomGenerateFullGraph(GraphMatrix &graph, unsigned maxWeight);
        static std::vector<unsigned> travellingSalesmanBruteForce(GraphMatrix &graph);
        static std::vector<unsigned> travellingSalesmanBranchAndBound(GraphMatrix &graph);
};
