#include <bits/stdc++.h>
using namespace std;
#include <chrono>

long long digitOps; // counts number of digit inspections

// Get maximum element
int getMax(vector<int> &arr){
    int mx = arr[0];
    for(int num : arr){
        digitOps++;
        if(num > mx) mx = num; // count digit read as operation
    }
    return mx;
}

// Count sort for a specific digit
void countSort(vector<int> &arr, int exp){
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    // Count occurrences of digits
    for(int i = 0; i < n; i++){
        int digit = (arr[i]/exp) % 10;
        count[digit]++;
        digitOps++; // counting digit access
    }

    // Cumulative count
    for(int i = 1; i < 10; i++){
        count[i] += count[i-1];
        digitOps++;
    }

    // Build output array (iterate n-1 → 0 for stability)
    for(int i = n-1; i >= 0; i--){
        int digit = (arr[i]/exp) % 10;
        output[count[digit]-1] = arr[i];
        count[digit]--;
        digitOps++;
    }

    // Copy output back to arr
    for(int i = 0; i < n; i++){
        arr[i] = output[i];
        digitOps++;
    }
}

// Radix sort
void radixSortArray(int arr[], int n){
    digitOps = 0;
    vector<int> vec(arr, arr + n);
    int m = *max_element(vec.begin(), vec.end());

    for(int exp = 1; m/exp > 0; exp *= 10){
        countSort(vec, exp);
    }

    // Copy back to array
    for(int i = 0; i < n; i++) arr[i] = vec[i];
}

// Run sorting 3 times and calculate average time in microseconds
long long sortAndAverage(int arr[], int n){
    long long totalTime = 0;
    long long tempOps = 0;

    for(int run = 0; run < 3; run++){
        int* copyArr = new int[n];
        memcpy(copyArr, arr, n * sizeof(int));

        auto start = chrono::high_resolution_clock::now();
        radixSortArray(copyArr, n);
        auto end = chrono::high_resolution_clock::now();

        auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
        totalTime += elapsed;

        tempOps = digitOps; // digit operations same each run
        delete[] copyArr;
    }

    digitOps = tempOps;
    return totalTime / 3;
}

// Run sorting on a file
void runOnFile(string fileName, string type, ofstream &resultFile){
    ifstream inFile(fileName);
    if(!inFile){
        cerr << "Cannot open " << fileName << endl;
        return;
    }

    int n;
    while(inFile >> n){
        int* arr = new int[n];
        for(int i = 0; i < n; i++) inFile >> arr[i];

        cout << "Sorting " << n << " elements (" << type << ")..." << endl;

        long long avgTime = sortAndAverage(arr, n);

        resultFile << type << "\t" << n << "\t"
                   << avgTime << "\t" << digitOps << "\n";

        delete[] arr;
    }

    inFile.close();
}

int main(){
    ofstream resultFile("radix_sort_results.txt");
    resultFile << "Type\tSize\tAverageTime(microsec)\tDigitOperations\n";

    runOnFile("random_all.txt", "random", resultFile);
    runOnFile("increasing_all.txt", "increasing", resultFile);
    runOnFile("decreasing_all.txt", "decreasing", resultFile);

    resultFile.close();
    cout << "All sorting done! Results saved in radix_sort_results.txt" << endl;

    return 0;
}
