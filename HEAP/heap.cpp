#include <bits/stdc++.h>
using namespace std;
#include <chrono>

int comparisons; // global counter

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        comparisons++; // count comparison
        if (arr[left] > arr[largest]) largest = left;
    }

    if (right < n) {
        comparisons++; // count comparison
        if (arr[right] > arr[largest]) largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Heap sort wrapper for int arrays
void heapSortArray(int arr[], int n) {
    comparisons = 0;
    vector<int> vec(arr, arr + n);

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(vec, n, i);
    }

    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(vec[0], vec[i]);
        heapify(vec, i, 0);
    }

    // Copy back to array
    for (int i = 0; i < n; i++) arr[i] = vec[i];
}

// Run sorting 3 times and calculate average time in microseconds
long long sortAndAverage(int arr[], int n) {
    long long totalTime = 0;
    int tempComparisons = 0;

    for (int run = 0; run < 3; run++) {
        int* copyArr = new int[n];
        memcpy(copyArr, arr, n * sizeof(int));

        auto start = chrono::high_resolution_clock::now();
        heapSortArray(copyArr, n);
        auto end = chrono::high_resolution_clock::now();

        auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
        totalTime += elapsed;

        tempComparisons = comparisons; // comparisons same each run
        delete[] copyArr;
    }

    comparisons = tempComparisons;
    return totalTime / 3;
}

// Run sorting on a file
void runOnFile(string fileName, string type, ofstream &resultFile) {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Cannot open " << fileName << endl;
        return;
    }

    int n;
    while (inFile >> n) {
        int* arr = new int[n];
        for (int i = 0; i < n; i++) inFile >> arr[i];

        cout << "Sorting " << n << " elements (" << type << ")..." << endl;

        long long avgTime = sortAndAverage(arr, n);

        resultFile << type << "\t" << n << "\t"
                   << avgTime << "\t" << comparisons << "\n";

        delete[] arr;
    }

    inFile.close();
}

int main() {
    ofstream resultFile("heap_sort_results.txt");
    resultFile << "Type\tSize\tAverageTime(microsec)\tComparisons\n";

    runOnFile("random_all.txt", "random", resultFile);
    runOnFile("increasing_all.txt", "increasing", resultFile);
    runOnFile("decreasing_all.txt", "decreasing", resultFile);

    resultFile.close();
    cout << "All sorting done! Results saved in heap_sort_results.txt" << endl;

    return 0;
}
