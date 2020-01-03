#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include <queue>
#include <Algorithms/Utils/GreaterPathComparator.hpp>


class GraphMatrix;

class BranchAndBound
{
    public:
    BranchAndBound();
    ~BranchAndBound() = default;

    std::vector<uint32_t> performBranchAndBoundOnGraph(std::unique_ptr<GraphMatrix>& graphMatrix);


    private:
    using PathQueue = std::priority_queue<std::vector<uint32_t>, std::vector<std::vector<uint32_t>>, GreaterPathComparator>;

    // general algorithm steps
    void startAlgorithm(std::vector<uint32_t>& verticies, 
                        std::vector<uint32_t>& currentBestPartialPath, PathQueue& pathQueue);

    void performCalculations(std::vector<uint32_t>& verticies, 
                             std::vector<uint32_t>& currentBestPartialPath, PathQueue& pathQueue);

    void performNextIteration(std::vector<uint32_t>& verticies, 
                              std::vector<uint32_t>& currentBestPartialPath,
                              std::vector<uint32_t>& newPartialPath);

    void finalizeCalculations(std::vector<uint32_t>& pathWithSolution);

    // helpers
    template<class Iterator>
    bool wasVertexAlreadyChecked(Iterator begin, Iterator end, const uint32_t vertex);
    bool isCurrentlyEvaluatedPathEnding(const std::vector<uint32_t>& evaluatedPath,
                                        const std::vector<uint32_t>& verticies);
    uint32_t calculatePathsCost(const std::vector<uint32_t>& path);
    void assignNewBestPathIfPossible(std::vector<uint32_t>& possibleBestPath);
    bool isGivenPathPromising(const uint32_t currentCost, const uint32_t upperBound);
    bool isEvaluatedEdgeClosingHamiltonCycle(const uint32_t edgeBegin, const uint32_t edgeEnd, const uint32_t lastVertexInPartialPath);
    bool doVerticiesCreateEdge(const uint32_t edgeBegin, const uint32_t edgeEnd);


    std::unique_ptr<GraphMatrix>* graph;
    const int32_t INFINITY;
    const int32_t STARTING_VERTEX;
    uint32_t bestPathLength;
    std::vector<uint32_t> bestSequence;
};
