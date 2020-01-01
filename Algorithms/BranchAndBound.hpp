#pragma once

#include <vector>
#include <memory>
#include <cstdint>


class GraphMatrix;
class Timer;

class BranchAndBound
{
    public:
    BranchAndBound();
    ~BranchAndBound() = default;

    std::vector<uint32_t> performBranchAndBoundOnGraph(std::unique_ptr<GraphMatrix>& graphMatrix, Timer& timer);


    private:
    std::unique_ptr<GraphMatrix>* graph;
};
