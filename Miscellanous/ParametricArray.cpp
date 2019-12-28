#include <Miscellanous/ParametricArray.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>


ParametricArray::ParametricArray()
{
    //ctor
    length = 0;
    tab = NULL;
    param = NULL;
}

ParametricArray::~ParametricArray()
{
    //dtor
    if(tab != NULL)
        delete [] tab;
    if(param != NULL)
        delete [] param;
}

void ParametricArray::add(int value, int parameter)
{
    length++;
    int *newTab = new int[length];
    int *newParam = new int[length];

    for(int i = 0; i < length - 1; i++)
    {
        newTab[i] = tab[i];
        newParam[i] = param[i];
    }

    newTab[length - 1] = value;
    newParam[length - 1] = parameter;

    if(tab != NULL)
        delete [] tab;
    if(param != NULL)
        delete [] param;

    tab = newTab;
    param = newParam;
}

void ParametricArray::removeIndex(int index)
{
    if(tab != NULL && param != NULL)
    {
        length--;

        int *newTab;
        int *newParam;
        if(length > 0)
        {
            newTab = new int[length];
            newParam = new int[length];

            for(int i = 0; i < index; i++)
            {
                newTab[i] = tab[i];
                newParam[i] = param[i];
            }

            for(int i = index; i < length; i++)
            {
                newTab[i] = tab[i + 1];
                newParam[i] = param[i + 1];
            }
        }
        else
        {
            newTab = NULL;
            newParam = NULL;
        }

        delete [] tab;
        delete [] param;
        tab = newTab;
        param = newParam;
    }
}

void ParametricArray::clearArray()
{
    if(tab != NULL && param != NULL)
    {
        delete [] tab;
        delete [] param;
        length = 0;
        tab = NULL;
        param = NULL;
    }
}

int ParametricArray::getValue(int index)
{
    return tab[index];
}

int ParametricArray::getParameter(int index)
{
    return param[index];
}

int ParametricArray::getLength()
{
    return length;
}

int ParametricArray::sumValues()
{
    if(length > 0)
    {
        int sum = 0;

        for(int i = 0; i < length; i++)
            sum += tab[i];

        return sum;
    }
    else
        return 0;
}

int ParametricArray::sumParameters()
{
    if(length > 0)
    {
        int sum = 0;

        for(int i = 0; i < length; i++)
            sum += param[i];

        return sum;
    }
    else
        return 0;
}

void ParametricArray::displayArray()
{
    for(int i = 0; i < length; i++)
        std::cout << tab[i] << ": " << param[i] << std::endl;
    std::cout << std::endl;
}
