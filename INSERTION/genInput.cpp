#include <bits/stdc++.h>
using namespace std;

int main() {

    srand(time(0));

    // Generate sizes from 0 to 100000 with step 1000
    vector<int> sizes;
    for (int n = 0; n <= 20000; n += 100)
        sizes.push_back(n);

    // Open combined files for all sizes
    ofstream randomFile("random_all.txt");
    ofstream incFile("increasing_all.txt");
    ofstream decFile("decreasing_all.txt");

    for (int n : sizes) {
        if (n == 0) continue; // skip size 0

        // generating random input
        randomFile << n << endl;  // first line = size
        for (int i = 0; i < n; i++)
            randomFile << rand() % n + 1 << endl;

        // generating sorted input in increasing order
        incFile << n << endl;
        int val = 1;
        for (int i = 0; i < n; i++) {
            val += rand() % 10;
            incFile << val << endl;
        }

        // generating sorted input in decreasing order
        decFile << n << endl;
        val = n * 20;
        for (int i = 0; i < n; i++) {
            val -= rand() % 10;
            decFile << val << endl;
        }

        cout << "Generated inputs for size " << n << "..." << endl;
        cout << "--------------------------------------" << endl;
    }

    // Close files
    randomFile.close();
    incFile.close();
    decFile.close();

    cout << "Generated combined input files for all sizes!" << endl;
    return 0;
}
