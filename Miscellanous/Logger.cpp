#include <Miscellanous/Logger.hpp>


Logger::Logger(const std::string& prologue)
    : prefix(prologue)
    , logFileName("logs.txt")
    , logFile()
{
    logFile.open(logFileName);
}

Logger::~Logger()
{
    logFile.close();
}

Logger::log(const std::string& log, const std::string functionName)
{
    if(logFile.is_open())
    {
        logFile << prefix << functionName << ": " << log << "\n";
    }
}