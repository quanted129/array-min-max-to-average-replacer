#pragma once

#include <vector>
#include <thread>
using namespace std;

struct ArrayValue
{
    int* array;
    int size;
    int min;
    int max;
    double averageValue;
    vector<int> minIndexes;
    vector<int> maxIndexes;

    ArrayValue();
    ArrayValue(int arrSize);
    ~ArrayValue();

    void replaceMinMaxWithAverage();
};

void MinMaxThread(ArrayValue* data);
void AverageThread(ArrayValue* data);

void findMinMax(ArrayValue* data);
void calculateAverage(ArrayValue* data);