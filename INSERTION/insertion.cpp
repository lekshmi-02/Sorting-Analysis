#include <bits/stdc++.h>
using namespace std;
#include <chrono>

int comparisons;

void insertionSort(int arr[], int n) {
    comparisons = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j;
        for (j = i - 1; j >= 0; j--) {
            comparisons++;
            if (key < arr[j]) {
                arr[j + 1] = arr[j];
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

// Run sorting 3 times and calculate average time in microseconds
long long sortAndAverage(int arr[], int n) {
    long long totalTime = 0;
    int tempComparisons = 0;

    for (int run = 0; run < 3; run++) {
        int* copyArr = new int[n];
        memcpy(copyArr, arr, n * sizeof(int));

        auto start = chrono::high_resolution_clock::now();
        insertionSort(copyArr, n);
        auto end = chrono::high_resolution_clock::now();

        long long elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
        totalTime += elapsed;

        tempComparisons = comparisons; // comparisons same each run
        delete[] copyArr;
    }

    comparisons = tempComparisons;
    return totalTime / 3; // average microseconds
}

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
    ofstream resultFile("insertion_sort_results.txt");
    resultFile << "Type\tSize\tAverageTime(microsec)\tComparisons\n";

    runOnFile("random_all.txt", "random", resultFile);
    runOnFile("increasing_all.txt", "increasing", resultFile);
    runOnFile("decreasing_all.txt", "decreasing", resultFile);

    resultFile.close();
    cout << "All sorting done! Results saved in insertion_sort_results.txt" << endl;

    return 0;
}
