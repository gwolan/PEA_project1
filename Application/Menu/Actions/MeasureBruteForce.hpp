#pragma once

#include <memory>
#include <vector>
#include <map>
#include <fstream>
#include <cstdint>
#include <Application/Menu/Actions/BaseAction.hpp>
#include <Algorithms/BruteForce.hpp>
#include <Miscellanous/Timer.hpp>
#include <Miscellanous/Dice.hpp>


class GraphMatrix;

class MeasureBruteForce : public BaseAction
{
    public:
    MeasureBruteForce(const std::string& actionName);
    ~MeasureBruteForce();

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
    BruteForce bruteForce;
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
