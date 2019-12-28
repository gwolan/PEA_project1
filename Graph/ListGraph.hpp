#pragma once

#include <Graph/Graph.hpp>


class ListGraph : public Graph
{
    public:
        ListGraph(unsigned vertexNumber);
        virtual ~ListGraph();
        bool addEdge(unsigned v, unsigned w, unsigned weight);
        bool removeEdge(unsigned v, unsigned w);
        unsigned getWeight(unsigned v, unsigned w);
        void displayGraph();

    protected:

    private:
        struct element
        {
            unsigned vertex;
            int weight;
            element *next;
        };
        element **graphList;

};
