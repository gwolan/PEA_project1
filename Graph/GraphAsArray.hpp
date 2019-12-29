#pragma once

#include <vector>


class GraphAsArray
{
    public:
    GraphAsArray(unsigned vertexNumber);
    ~GraphAsArray();

    bool addEdge(unsigned v, unsigned w, unsigned weight);
    bool removeEdge(unsigned v, unsigned w);
    unsigned getWeight(unsigned v, unsigned w);
    unsigned getVertexNumber();
    void displayGraph();

    unsigned vertexNumber;


    private:
    unsigned **graphMatrix;
    unsigned *graphArray;

};
