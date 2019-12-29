#include <Menu/Actions/ReadGraphfromFile.hpp>
#include <iostream>


ReadGraphFromFile::ReadGraphFromFile(const std::string& actionName)
    : BaseAction(actionName)
{ }

void ReadGraphFromFile::run()
{
    std::cout << name << "::run()" << std::endl;
}
