#include <bits/stdc++.h>
using namespace std;

int main() {

    srand(time(0));

    vector<int> sizes;
    for (int n = 0; n <= 20000; n += 100)
        sizes.push_back(n);

    ofstream randomFile("random_all.txt");
    ofstream incFile("increasing_all.txt");
    ofstream decFile("decreasing_all.txt");

    for (int n : sizes) {
        if (n == 0) continue; // skip size 0

        // generating random input
        randomFile << n << endl;  
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

    randomFile.close();
    incFile.close();
    decFile.close();

    cout << "Generated three types of` input files for all sizes!" << endl;
    return 0;
}
