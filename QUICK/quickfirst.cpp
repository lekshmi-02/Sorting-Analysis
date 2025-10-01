#include <bits/stdc++.h>
using namespace std;
#include <chrono>

long long firstcompCount = 0; // total comparisons

// Partition using first element as pivot
int partition_first(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low + 1, j = high;

    while (true) {
        while (i <= high && (++firstcompCount && arr[i] <= pivot)) i++;
        while (j >= low && (++firstcompCount && arr[j] > pivot)) j--;
        if (i >= j) break;
        swap(arr[i], arr[j]);
    }

    swap(arr[low], arr[j]);
    return j;
}

// Quicksort using first element as pivot
void quicksort_first(vector<int>& arr, int low, int high) {
    if (low < high) {
        int p = partition_first(arr, low, high);
        quicksort_first(arr, low, p - 1);
        quicksort_first(arr, p + 1, high);
    }
}

// Wrapper to reset comparisons
void quicksort_first_with_count(vector<int>& arr) {
    firstcompCount = 0;
    quicksort_first(arr, 0, arr.size() - 1);
}

// Run sorting 3 times and calculate average time in microseconds
long long sortAndAverage(vector<int> arr) {
    long long totalTime = 0;
    long long tempComp = 0;

    for (int run = 0; run < 3; run++) {
        vector<int> copyArr = arr;

        auto start = chrono::high_resolution_clock::now();
        quicksort_first_with_count(copyArr);
        auto end = chrono::high_resolution_clock::now();

        auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
        totalTime += elapsed;

        tempComp = firstcompCount; // comparisons same each run
    }

    firstcompCount = tempComp;
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
    int maxSize = (type == "random") ? 100000 : 20000; // Random up to 1,00,000; others up to 20,000

    while (inFile >> n) {
        if (n > maxSize) {  
            cout << "Skipping " << n << " elements (" << type << ") to avoid slow quicksort." << endl;
            break;
        }

        vector<int> arr(n);
        for (int i = 0; i < n; i++) inFile >> arr[i];

        cout << "Sorting " << n << " elements (" << type << ")..." << endl;

        long long avgTime = sortAndAverage(arr);

        resultFile << type << "\t" << n << "\t"
                   << avgTime << "\t" << firstcompCount << "\n";
    }

    inFile.close();
}

int main() {
    ofstream resultFile("quicksort_first_results.txt");
    resultFile << "Type\tSize\tAverageTime(microsec)\tComparisons\n";

    runOnFile("random_all.txt", "random", resultFile);
    runOnFile("increasing_all.txt", "increasing", resultFile);
    runOnFile("decreasing_all.txt", "decreasing", resultFile);

    resultFile.close();
    cout << "All sorting done! Results saved in quicksort_first_results.txt" << endl;

    return 0;
}
