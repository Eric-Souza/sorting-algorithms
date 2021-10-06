#include <iostream>
#include <fstream>
#include <string>

// Time measurement import
#include <chrono>

// Header file import
#include "SortingAlgorithms.h"

using namespace std;

int main (int argc, const char* argv[]) {
    string fileName = argv[1];
    string conf = argv[2];
    string lineNumber = argv[3];

    ifstream file;
    file.open(fileName);

    if (!file.is_open()) {
        cerr << "Error while opening file\n";
        return -1;
    }

    const int config = atoi(conf.c_str());
    const int linesToBeSorted = atoi(lineNumber.c_str());

    string nameData;
    int binaryData;

    NamesAndBinaryDigits** array = new NamesAndBinaryDigits*[linesToBeSorted];

    for (int index = 0; index < linesToBeSorted; index++) {
        file >> nameData;
        file >> binaryData;

        array[index] = new NamesAndBinaryDigits(nameData, binaryData);
    }

    // Quicksort and heapsort
    if (config == 1) {
        heapSort(array, linesToBeSorted);
        quickSort(array, linesToBeSorted);
    }

    // Quicksort and radix exchange sort
    else if (config == 2) {
        sort(array, 0, linesToBeSorted-1);
        quickSort(array, linesToBeSorted);
    }

    // Mergesort and heapsort
    else if (config == 3) {
        heapSort(array, linesToBeSorted);
        mergeSort(array, 0, linesToBeSorted-1);
    }

    // Mergesort and radix exchange sort
    else if (config == 4) {
        sort(array, 0, linesToBeSorted-1);
        mergeSort(array, 0, linesToBeSorted-1);
    }

    printArray(array, linesToBeSorted);

    // Cleanup
    file.close();

    for (int index = 0; index < linesToBeSorted; index++) {
        delete array[index];
        array[index] = nullptr;
    }

    delete [] array;
    array = nullptr;

    return 0;
}
