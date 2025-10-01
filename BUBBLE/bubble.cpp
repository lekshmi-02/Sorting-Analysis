#include <bits/stdc++.h>
using namespace std;
#include <chrono>

int comparisons;

void bubbleSort(int arr[], int n)
{
    comparisons = 0;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            comparisons++;
            if (arr[j] > arr[j + 1]) 
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void runOnFile(string fileName, string type, ofstream &resultFile)
{
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Cannot open " << fileName << endl;
        return;
    }

    int n;
    while (inFile >> n) { // read size
        int* arr = new int[n];
        for (int i = 0; i < n; i++) inFile >> arr[i];

        cout << "Sorting " << n << " elements (" << type << ")..." << endl;

        auto start = chrono::high_resolution_clock::now();
        bubbleSort(arr, n);
        auto end = chrono::high_resolution_clock::now();

        long long time_us = chrono::duration_cast<chrono::microseconds>(end - start).count();

        resultFile << type << "\t" << n << "\t" 
                   << time_us << "\t" << comparisons << "\n";

        delete[] arr;
    }

    inFile.close();
}

int main()
{
    ofstream resultFile("bubble_sort_results.txt");
    resultFile << "Type\tSize\tTime(microsec)\tComparisons\n";

    runOnFile("random_all.txt", "random", resultFile);
    runOnFile("increasing_all.txt", "increasing", resultFile);
    runOnFile("decreasing_all.txt", "decreasing", resultFile);

    resultFile.close();
    cout << "All sorting done! Results saved in bubble_sort_results.txt" << endl;

    return 0;
}
