#include <bits/stdc++.h>
using namespace std;
#include <chrono>
#include <cstdlib>

long long randcompCount = 0; // total comparisons

// Partition using first element as pivot
int partition_first(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low + 1, j = high;

    while (true) {
        while (i <= high && (++randcompCount && arr[i] <= pivot)) i++;
        while (j >= low && (++randcompCount && arr[j] > pivot)) j--;
        if (i >= j) break;
        swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

// Partition using random pivot
int partition_random(vector<int>& arr, int low, int high) {
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[low], arr[pivotIndex]);
    return partition_first(arr, low, high);
}

// Quicksort using random pivot
void quicksort_random(vector<int>& arr, int low, int high) {
    if (low < high) {
        int p = partition_random(arr, low, high);
        quicksort_random(arr, low, p - 1);
        quicksort_random(arr, p + 1, high);
    }
}

// Wrapper to reset comparisons
void quicksort_random_with_count(vector<int>& arr) {
    randcompCount = 0;
    quicksort_random(arr, 0, arr.size() - 1);
}

// Run sorting 3 times and calculate average time in microseconds
long long sortAndAverage(vector<int> arr) {
    long long totalTime = 0;
    long long tempComp = 0;

    for (int run = 0; run < 3; run++) {
        vector<int> copyArr = arr;

        auto start = chrono::high_resolution_clock::now();
        quicksort_random_with_count(copyArr);
        auto end = chrono::high_resolution_clock::now();

        auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
        totalTime += elapsed;

        tempComp = randcompCount; // comparisons same each run
    }

    randcompCount = tempComp;
    return totalTime / 3;
}

// Run sorting on a file
void runOnFile(const string &fileName, const string &type, ofstream &resultFile) {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Cannot open " << fileName << endl;
        return;
    }

    int n;
    while (inFile >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) inFile >> arr[i];

        cout << "Sorting " << n << " elements (" << type << ")..." << endl;

        long long avgTime = sortAndAverage(arr);

        resultFile << type << "\t" << n << "\t"
                   << avgTime << "\t" << randcompCount << "\n";
    }

    inFile.close();
}

int main() {
    ofstream resultFile("quicksort_random_results.txt");
    resultFile << "Type\tSize\tAverageTime(microsec)\tComparisons\n";

    runOnFile("random_all.txt", "random", resultFile);
    runOnFile("increasing_all.txt", "increasing", resultFile);
    runOnFile("decreasing_all.txt", "decreasing", resultFile);

    resultFile.close();
    cout << "All sorting done! Results saved in quicksort_random_results.txt" << endl;

    return 0;
}
