#include "header.h"
#include <iostream>
#include <chrono>
using namespace std;

ArrayValue::ArrayValue() : array(nullptr), size(0), min(2147483647), max(-2147483648), averageValue(0) {}
ArrayValue::ArrayValue(int arrSize) : array(new int[arrSize]), size(arrSize), min(2147483647), max(-2147483648), averageValue(0) {}
ArrayValue::~ArrayValue() { delete[] array; }

void ArrayValue::replaceMinMaxWithAverage()
{
    if (!minIndexes.empty() && !maxIndexes.empty())
    {
        int replacementValue = static_cast<int>(averageValue);
        for (int i : minIndexes) array[i] = replacementValue;
        for (int i : maxIndexes) array[i] = replacementValue;
    }
}

void findMinMax(ArrayValue* data)
{
    int* arr = data->array;
    int arrSize = data->size;

    if (arrSize == 0) return;

    data->min = 2147483647;
    data->max = -2147483648;
    data->minIndexes.clear();
    data->maxIndexes.clear();

    data->min = arr[0];
    data->max = arr[0];
    data->minIndexes.push_back(0);
    data->maxIndexes.push_back(0);

    for (int i = 1; i < arrSize; i++)
    {
        if (arr[i] < data->min)
        {
            data->min = arr[i];
            data->minIndexes.clear();
            data->minIndexes.push_back(i);
        }
        else if (arr[i] == data->min)
        {
            data->minIndexes.push_back(i);
        }
        this_thread::sleep_for(chrono::milliseconds(7));

        if (arr[i] > data->max)
        {
            data->max = arr[i];
            data->maxIndexes.clear();
            data->maxIndexes.push_back(i);
        }
        else if (arr[i] == data->max)
        {
            data->maxIndexes.push_back(i);
        }
        this_thread::sleep_for(chrono::milliseconds(7));
    }
}

void calculateAverage(ArrayValue* data)
{
    int* arr = data->array;
    int arrSize = data->size;

    if (arrSize == 0)
    {
        data->averageValue = 0;
        return;
    }

    double sum = 0;
    for (int i = 0; i < arrSize; i++)
    {
        sum += arr[i];
        this_thread::sleep_for(chrono::milliseconds(12));
    }

    data->averageValue = sum / arrSize;
}

void MinMaxThread(ArrayValue* data)
{
    findMinMax(data);
    cout << "Found min (" << data->min << ") and max (" << data->max << ").\n";
}

void AverageThread(ArrayValue* data)
{
    calculateAverage(data);
    cout << "Found average: " << data->averageValue << endl;
}