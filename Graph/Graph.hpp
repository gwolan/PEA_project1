#pragma once

#include <vector>
#include <Miscellanous/ParametricArray.hpp>


class Graph
{
    public:
        Graph();
        virtual ~Graph();
        virtual bool addEdge(unsigned v, unsigned w, unsigned weight) = 0;
        virtual bool removeEdge(unsigned v, unsigned w) = 0;
        virtual unsigned getWeight(unsigned v, unsigned w) = 0;
        unsigned getVertexNumber();
        virtual void displayGraph() = 0;
        static void randomGenerateFullGraph(Graph &graph, unsigned maxWeight);
        static std::vector<unsigned> travellingSalesmanBruteForce(Graph &graph);
        static std::vector<unsigned> travellingSalesmanBranchAndBound(Graph &graph);

    protected:
        unsigned vertexNumber;

    private:
        class RouteComparison
        {
            public:
                bool operator() (const std::vector<unsigned>& lhs, const std::vector<unsigned>& rhs) const
                {
                    return (lhs.at(0) > rhs.at(0));
                }
        };
};
