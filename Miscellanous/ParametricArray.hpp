#pragma once


class ParametricArray
{
    public:
        ParametricArray();
        ~ParametricArray();
        void add(int value, int parameter);
        void removeIndex(int index);
        void clearArray();
        void displayArray();
        int getValue(int index);
        int getParameter(int index);
        int sumValues();
        int sumParameters();
        int getLength();
    protected:
    private:
        int length;
        int *tab;
        int *param;
};
