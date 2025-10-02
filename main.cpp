#include "header.h"
#include <iostream>
using namespace std;

int main()
{
    int size;
    cout << "Enter array size: ";
    cin >> size;

    if (size < 1)
    {
        cout << "Size must be positive"
                "!" << endl;
        return 1;
    }

    ArrayValue arr(size);

    for (int i = 0; i < size; i++)
    {
        cout << "Element " << i + 1 << ": ";
        cin >> arr.array[i];
    }

    thread minMaxThread(MinMaxThread, &arr);
    thread averageThread(AverageThread, &arr);

    minMaxThread.join();
    averageThread.join();

    arr.replaceMinMaxWithAverage();

    cout << "\nMin element: " << arr.min << endl;
    cout << "Max element: " << arr.max << endl;
    cout << "Average value: " << arr.averageValue << " (applied as " << static_cast<int>(arr.averageValue) << ")\n";
    cout << "New array: { ";
    for (int i = 0; i < size; i++) cout << arr.array[i] << " ";
    cout << "}\n";
    return 0;
}