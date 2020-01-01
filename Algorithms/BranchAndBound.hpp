#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include <queue>
#include <Algorithms/Utils/GreaterPathComparator.hpp>


class GraphMatrix;
class Timer;

class BranchAndBound
{
    public:
    BranchAndBound();
    ~BranchAndBound() = default;

    std::vector<uint32_t> performBranchAndBoundOnGraph(std::unique_ptr<GraphMatrix>& graphMatrix, Timer& timer);


    private:
    using PathQueue = std::priority_queue<std::vector<uint32_t>, std::vector<std::vector<uint32_t>>, GreaterPathComparator>;

    // general algorithm steps
    void startAlgorithm(std::vector<uint32_t>& verticies, 
                        std::vector<uint32_t>& currentPath, PathQueue& pathQueue);

    void performCalculations(std::vector<uint32_t>& verticies, 
                             std::vector<uint32_t>& currentPath, PathQueue& pathQueue);

    void performNextIteration(std::vector<uint32_t>& verticies, 
                              std::vector<uint32_t>& currentPath,
                              std::vector<uint32_t>& newPath,
                              uint32_t currentVertex);

    void finalizeCalculations(std::vector<uint32_t>& currentPath);

    // helpers
    bool wasVertexAlreadyChecked(const std::vector<uint32_t>& currentPath, const uint32_t vertex);
    bool isCurrentlyEvaluatedPathEnding(const std::vector<uint32_t>& evaluatedPath,
                                        const std::vector<uint32_t>& verticies);
    uint32_t calculatePathsCost(const std::vector<uint32_t>& path);
    void assignNewBestPathIfPossible(std::vector<uint32_t>& possibleBestPath);
    bool isGivenPathPromising(const std::vector<uint32_t>& promisingPath);


    std::unique_ptr<GraphMatrix>* graph;
    const int32_t INFINITY;
    uint32_t bestPathLength;
    std::vector<uint32_t> bestSequence;
};
