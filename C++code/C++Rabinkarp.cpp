#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define d 10

void rabinKarp(const string& pattern, const string& input, int p) {
    int m = pattern.length();
    int n = input.length();
    int i, j;
    int ph = 0;
    int th = 0;
    int hash = 1;

    for (i = 0; i < m - 1; i++)
        hash = (hash * d) % p;

    // Calculate hash value for pattern and text
    for (i = 0; i < m; i++) {
        ph = (d * ph + pattern[i]) % p;
        th = (d * th + input[i]) % p;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= n - m; i++) {
        // Check the hash values of current substring of input
        // and pattern. If the hash values match then only
        // check for characters one by one
        if (ph == th) {
            //Check for characters one by one 
            for (j = 0; j < m; j++) {
                if (input[i + j] != pattern[j])
                    break;
            }

            if (j == m)
                cout << "Pattern is found at position: " << i + 1 << endl;
        }
        // Calculate hash value for next substring of input:
        // Remove leading digit, add trailing digit

        if (i < n - m) {
            th = (d * (th - input[i] * hash) + input[i + m]) % p;
            // We might get negative value of t, converting
            // it to positive 
            if (th < 0)
                th = (th + p);
        }
    }
}

int main() {
    ifstream inputFile("input2.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    string input, pattern;
    int p = 13;

    // Read input string
    if (getline(inputFile, input)) {
        // Read pattern string
        if (getline(inputFile, pattern)) {
            rabinKarp(pattern, input, p);
        } else {
            cout << "Failed to read pattern from file." << endl;
            return 1;
        }
    } else {
        cout << "Failed to read input from file." << endl;
        return 1;
    }

    inputFile.close();

    return 0;
}

