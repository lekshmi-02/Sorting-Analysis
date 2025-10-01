#include <bits/stdc++.h>
using namespace std;
#include <chrono>

int comparisons; 

void merge(vector<int>& a, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        comparisons++; // count each comparison
        if (L[i] <= R[j]) {
            a[k++] = L[i++];
        } else {
            a[k++] = R[j++];
        }
    }

    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void mergeSort(vector<int>& a, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    merge(a, left, mid, right);
}

void mergeSortArray(int arr[], int n) {
    comparisons = 0;
    vector<int> vec(arr, arr + n);
    mergeSort(vec, 0, n - 1);
    for (int i = 0; i < n; i++) arr[i] = vec[i];
}

// Run sorting 3 times and calculate average time in microseconds
double sortAndAverage(int arr[], int n) {
    double totalTime = 0.0;
    int tempComparisons = 0;

    for (int run = 0; run < 3; run++) {
        int* copyArr = new int[n];
        memcpy(copyArr, arr, n * sizeof(int));

        auto start = chrono::high_resolution_clock::now();
        mergeSortArray(copyArr, n);
        auto end = chrono::high_resolution_clock::now();

        auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
        totalTime += elapsed;

        tempComparisons = comparisons; 
        delete[] copyArr;
    }

    comparisons = tempComparisons;
    return totalTime / 3.0; // average in microseconds
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

        double avgTime = sortAndAverage(arr, n);

        resultFile << type << "\t" << n << "\t"
                   << fixed << setprecision(0) << avgTime
                   << "\t" << comparisons << "\n";

        delete[] arr;
    }

    inFile.close();
}

int main() {
    ofstream resultFile("merge_sort_results.txt");
    resultFile << "Type\tSize\tAverageTime(us)\tComparisons\n";

    runOnFile("random_all.txt", "random", resultFile);
    runOnFile("increasing_all.txt", "increasing", resultFile);
    runOnFile("decreasing_all.txt", "decreasing", resultFile);

    resultFile.close();
    cout << "All sorting done! Results saved in merge_sort_results.txt" << endl;

    return 0;
}
