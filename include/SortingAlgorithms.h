#include <string>
#include <iostream>
#include <math.h>

using namespace std;

// Class for both names and binary digits
class NamesAndBinaryDigits {
    public:
        NamesAndBinaryDigits(const string name, const int binaryDigits) {
            this -> name = name;
            this -> binaryDigits = binaryDigits;
        }

        ~NamesAndBinaryDigits() {}

        void print() const {
            printf("%s %08d\n", this -> name.c_str(), this -> binaryDigits);
        }

        string name;
        int binaryDigits;
};

// Runs list separating elements according to the pivot, necessary for quicksort method
void partArray(int leftHead, int rightHead, int *i, int *j, NamesAndBinaryDigits **A)  {
    NamesAndBinaryDigits* x;
    NamesAndBinaryDigits* w;

    *i = leftHead;
    *j = rightHead;

    // pivot
    x = A[(*i + *j) / 2];

    do {
        while (x -> name > A[*i] -> name) (*i)++;
        while (x -> name < A[*j] -> name) (*j)--;

        // If not yet crossed
        if (*i <= *j) {
            w = A[*i];
            A[*i] = A[*j];
            A[*j] = w;

            // After exchange, sum the values
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

// Implements "divide and conquer" logic
void orderArray(int leftHead, int rightHead, NamesAndBinaryDigits **A) {
    int i, j;

    partArray(leftHead, rightHead, &i, &j, A);

    if (leftHead < j) orderArray(leftHead, j, A);
    if (i < rightHead) orderArray(i, rightHead, A);
}

// Orders entire array
void quickSort(NamesAndBinaryDigits **A, int n) {
    orderArray(0, n - 1, A);
}

// Merges sub arrays
void merge(NamesAndBinaryDigits **array, int leftHead, int arrayMiddle, int rightHead) {
    int const firstSubArray = arrayMiddle - leftHead + 1;
    int const secondSubArray = rightHead - arrayMiddle;

    // Creates temporary arrays
    NamesAndBinaryDigits **leftArray = new NamesAndBinaryDigits*[firstSubArray], **rightArray = new NamesAndBinaryDigits*[secondSubArray];

    // Copies data
    for (int i = 0; i < firstSubArray; i++)
        leftArray[i] = array[leftHead + i];

    for (int j = 0; j < secondSubArray; j++)
        rightArray[j] = array[arrayMiddle + 1 + j];

    // Initial index of first and second sub arrays
    auto firstSubArrayIndex = 0, secondSubArrayIndex = 0;

    // Initial index of merged array
    int mergedArrayIndex = leftHead;

    // Merge the temporary arrays back into original array[left ... right]
    while (firstSubArrayIndex < firstSubArray && secondSubArrayIndex < secondSubArray) {
        if (leftArray[firstSubArrayIndex] -> name <= rightArray[secondSubArrayIndex] -> name) {
            array[mergedArrayIndex] = leftArray[firstSubArrayIndex];
            firstSubArrayIndex++;
        }

        else {
            array[mergedArrayIndex] = rightArray[secondSubArrayIndex];
            secondSubArrayIndex++;
        }

        mergedArrayIndex++;
    }

    // Copies remaining elements from left head
    while (firstSubArrayIndex < firstSubArray) {
        array[mergedArrayIndex] = leftArray[firstSubArrayIndex];

        firstSubArrayIndex++;
        mergedArrayIndex++;
    }

    // Copies remaining elements from right head
    while (secondSubArrayIndex < secondSubArray) {
        array[mergedArrayIndex] = rightArray[secondSubArrayIndex];

        secondSubArrayIndex++;
        mergedArrayIndex++;
    }
}

// Main mergesort function
template<class T = string>
void mergeSort(T *array, int arrayStart, int arrayEnd) {
    if (arrayStart >= arrayEnd) return; // Returns using recursive logic

    int middle = arrayStart + (arrayEnd - arrayStart) / 2;

    mergeSort(array, arrayStart, middle);
    mergeSort(array, middle + 1, arrayEnd);
    merge(array, arrayStart, middle, arrayEnd);
}

// Remakes a heap (tree), allocations biggest and smallest in 2n and 2n + 1 indexes
void heap(NamesAndBinaryDigits **array, int n, int i) {
    int largest = i; // Initialize largest as root

    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is bigger than parent
    if (l < n && array[l] -> binaryDigits > array[largest] -> binaryDigits) largest = l;

    // If right child is bigger than parent
    if (r < n && array[r] -> binaryDigits > array[largest] -> binaryDigits) largest = r;

    // If largest is not index
    if (largest != i) {
        swap(array[i], array[largest]);

        // Recursively rearranges heap with bigger children
        heap(array, n, largest);
    }
}

// Main heapsort function
void heapSort(NamesAndBinaryDigits **array, int n) {
    // Constructs or rearranges heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heap(array, n, i);

    // Extracts each heap element
    for (int i = n - 1; i > 0; i--) {
        // Moves current root to array end
        swap(array[0], array[i]);

        heap(array, i, 0);
    }
}

// Gets an integer's n bit
int digit(NamesAndBinaryDigits *x, int n) {
    int b = (x -> binaryDigits / (int) pow(2, n)) % 2;
    return b;
}

// Implements quicksort logic to sort using radix (bit by bit)
void radixQuickSort(NamesAndBinaryDigits **a, int l, int r, int w) {
    int i = l, j = r;

    // Calls default case
    if (r <= l || w < 0) return;

    while(j != i) {
        while(digit(a[i], w) == 0 && (i < j)) i++;
        while(digit(a[j], w) == 1 && (j > i)) j--;

        swap(a[i], a[j]);
    }

    if (digit(a[r], w) == 0) j++;

    radixQuickSort(a, l, j-1, w-1);
    radixQuickSort(a, j, r, w-1);
}

void sort(NamesAndBinaryDigits **a, int l, int r) {
    radixQuickSort(a, l, r, 31);
}

// Prints array elements
void printArray(NamesAndBinaryDigits **array, int n) {
    for (int i = 0; i < n; ++i)
        array[i] -> print();

    cout << "\n";
}