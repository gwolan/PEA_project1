#pragma once

#include <memory>
#include <vector>
#include <map>
#include <fstream>
#include <cstdint>
#include <Menu/Actions/BaseAction.hpp>
#include <Algorithms/BranchAndBound.hpp>
#include <Miscellanous/Timer.hpp>
#include <Miscellanous/Dice.hpp>


class GraphMatrix;

class MeasureBranchAndBound : public BaseAction
{
    public:
    MeasureBranchAndBound(const std::string& actionName);
    ~MeasureBranchAndBound();

    void run();
    void init(std::unique_ptr<GraphMatrix>& graphMatrix);


    private:
    void performMeasurements();
    void calculateResults();
    void saveResultsToFile();
    void initializeConfiguration();
    void readConfigFile();
    void setDefaultValues();
    void fillGraphAdjacencyMatrix();

    std::unique_ptr<GraphMatrix> graph;
    BranchAndBound branchAndBound;
    Timer timer;
    Dice dice;

    std::map<uint32_t, double> citiesCountToSolvingTimeMap;
    uint32_t measurementsCount;
    std::ifstream configurationFile;
    std::string configurationFileName;
    std::string configurationFileContent;
    std::ofstream resultsFile;
    std::string resultsFileName;

    const std::vector<uint32_t> DEFAULT_PROBLEM_SIZES;
    const uint32_t DEFAULT_MEASUREMENTS_COUNT;
};
