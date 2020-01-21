#include <iostream>
#include <vector>
#include <cstdint>
#include <numeric>
#include <Application/Menu/Actions/MeasureBruteForce.hpp>
#include <Graph/GraphMatrix.hpp>


MeasureBruteForce::MeasureBruteForce(const std::string& actionName)
    : BaseAction(actionName)
    , graph(nullptr)
    , bruteForce()
    , timer()
    , dice(1, 999)
    , citiesCountToSolvingTimeMap()
    , measurementsCount()
    , configurationFile()
    , configurationFileName("BruteForce_config.txt")
    , configurationFileContent()
    , resultsFile()
    , resultsFileName("BruteForce_results.txt")
    , DEFAULT_PROBLEM_SIZES( { 4, 7, 9, 11 } )
    , DEFAULT_MEASUREMENTS_COUNT(100)
{ }

MeasureBruteForce::~MeasureBruteForce()
{
    configurationFile.close();
    resultsFile.close();
}

void MeasureBruteForce::init(std::unique_ptr<GraphMatrix>& graphMatrix)
{
    configurationFile.open(configurationFileName);
    initializeConfiguration();
}

void MeasureBruteForce::initializeConfiguration()
{
    if(configurationFile.is_open())
    {
        readConfigFile();
        std::cout << "Wczytano rozmiar pomiarow z pliku konfiguracyjnego \"" << configurationFileName << "\"." << std::endl << std::endl;
    }
    else
    {
        setDefaultValues();
        std::cout << "Plik konfiguracyjny \"" << configurationFileName << "\" nie istnieje. \nWczytano rozmiar pomiarow z domyslnych wartosci." << std::endl << std::endl;
    }
}

void MeasureBruteForce::readConfigFile()
{
    configurationFile >> configurationFileContent;
    measurementsCount = std::atoi(configurationFileContent.c_str());

    while(not configurationFile.eof())
    {
        configurationFile >> configurationFileContent;
        uint32_t problemSize = std::atoi(configurationFileContent.c_str());

        citiesCountToSolvingTimeMap.insert(std::pair<uint32_t, double>(problemSize, 0));
    }

    configurationFile.close();
}

void MeasureBruteForce::setDefaultValues()
{
    measurementsCount = DEFAULT_MEASUREMENTS_COUNT;

    for(auto cities : DEFAULT_PROBLEM_SIZES)
    {
        citiesCountToSolvingTimeMap.insert(std::pair<uint32_t, double>(cities, 0));
    }
}

void MeasureBruteForce::run()
{
    performMeasurements();
    saveResultsToFile();

    std::cout << "Pomiary skonczone." << std::endl << std::endl;
}

void MeasureBruteForce::performMeasurements()
{
    std::cout << "Rozpoczecie pomiarow dla przegladu zupelnego." << std::endl;

    for(std::size_t measurementIteration = 0;
                    measurementIteration < measurementsCount; ++measurementIteration)
    {
        for(auto problem  = citiesCountToSolvingTimeMap.begin();
                 problem != citiesCountToSolvingTimeMap.end(); ++problem)
        {
            std::cout << "Pomiar dla " << problem->first << " miast. Iteracja " << measurementIteration + 1 << " ze " << measurementsCount << "..." << std::endl;

            graph = std::make_unique<GraphMatrix>(problem->first);
            fillGraphAdjacencyMatrix();

            timer.start();
            bruteForce.performBruteForceOnGraph(graph);
            timer.stop();
            problem->second += timer.getTime();
        }
    }

    calculateResults();
}

void MeasureBruteForce::calculateResults()
{
    for(auto problem  = citiesCountToSolvingTimeMap.begin();
             problem != citiesCountToSolvingTimeMap.end(); ++problem)
    {
        problem->second = problem->second / measurementsCount;
    }
}

void MeasureBruteForce::saveResultsToFile()
{
    resultsFile.open(resultsFileName);

    for(auto problem  = citiesCountToSolvingTimeMap.begin();
             problem != citiesCountToSolvingTimeMap.end(); ++problem)
    {
        resultsFile << problem->first << " [s]: " << problem->second << std::endl;
    }

    resultsFile.close();
    std::cout << "Wyniki pomyślnie zapisano do pliku." << std::endl;
}

void MeasureBruteForce::fillGraphAdjacencyMatrix()
{
    uint32_t vertexCount = graph->getVertexCount();

    for(std::size_t row = 0; row < vertexCount; ++row)
    {
        for(std::size_t column = 0; column < vertexCount; ++column)
        {
            uint32_t weight = dice.roll();
            if(row != column)
            {
                graph->addWeightToMatrix(row, column, weight);
            }
        }
    }
}
