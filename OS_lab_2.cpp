#include <windows.h>
#include <iostream>
#include <vector>
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
    ArrayValue() : array(nullptr), size(0), averageValue(0) {}
    ~ArrayValue() { delete[] array; }
};

DWORD WINAPI MinMaxThread(LPVOID lpParam);
DWORD WINAPI AverageThread(LPVOID lpParam);

int main()
{
    int size;
    cout << "Enter array size: ";
    cin >> size;

    if (size < 1)
    {
        cout << "Size must be positive!" << endl;
        return 1;
    }

    ArrayValue arr;
    arr.size = size;
    arr.min = 2147483647;
    arr.max = -2147483648;

    int* array = new int[size];
    for (int i = 0; i < size; i++)
    {
        cout << "Element " << i + 1 << ": ";
        cin >> array[i];
    }
    arr.array = array;

    HANDLE hMinMaxThread = CreateThread(NULL, 0, MinMaxThread, &arr, 0, NULL);
    HANDLE hAverageThread = CreateThread(NULL, 0, AverageThread, &arr, 0, NULL);
    HANDLE threads[2] = { hMinMaxThread, hAverageThread };

    WaitForMultipleObjects(2, threads, TRUE, INFINITE);
    CloseHandle(hMinMaxThread);
    CloseHandle(hAverageThread);

    if (!arr.minIndexes.empty() && !arr.maxIndexes.empty())
    {
        for (int i : arr.minIndexes)
        {
            array[i] = static_cast<int>(arr.averageValue);
        }

        for (int i : arr.maxIndexes)
        {
            array[i] = static_cast<int>(arr.averageValue);
        }

        cout << "\nMin element: " << arr.min << endl;
        cout << "Max element: " << arr.max << endl;
        cout << "Average value: " << arr.averageValue << " (applied as " << static_cast<int>(arr.averageValue) << ")\n";
        cout << "New array: { ";
        for (int i = 0; i < size; i++)
        {
            cout << array[i] << " ";
        }
        cout << "}\n";
    }

    return 0;
}

DWORD WINAPI MinMaxThread(LPVOID lpParam)
{
    ArrayValue* data = static_cast<ArrayValue*>(lpParam);
    int* arr = data->array;
    int arrSize = data->size;

    if (arrSize == 0) return 0;

    data->min = arr[0];
    data->max = arr[0];
    data->minIndexes.clear();
    data->maxIndexes.clear();
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
        Sleep(7);

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
        Sleep(7);
    }

    cout << "Found min (" << data->min << ") and max (" << data->max << ").\n";

    return 0;
}

DWORD WINAPI AverageThread(LPVOID lpParam)
{
    ArrayValue* data = static_cast<ArrayValue*>(lpParam);
    int* arr = data->array;
    int arrSize = data->size;

    if (arrSize == 0)
    {
        data->averageValue = 0;
        return 0;
    }

    double sum = 0;

    for (int i = 0; i < arrSize; i++)
    {
        sum += arr[i];
        Sleep(12);
    }

    data->averageValue = sum / arrSize;

    cout << "Found average: " << data->averageValue << endl;

    return 0;
}