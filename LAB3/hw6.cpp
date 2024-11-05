#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to preprocess the pattern and compute the longest prefix suffix (LPS) array
void computeLPSArray(const string &pattern, vector<int> &lps) {
    int length = 0; // Length of the previous longest prefix suffix
    lps[0] = 0; // The first element of lps is always 0
    int i = 1;

    while (i < pattern.length()) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1]; // Use the previous LPS value
            } else {
                lps[i] = 0; // No prefix found
                i++;
            }
        }
    }
}

// Function to perform KMP search on the given text using the specified pattern
void KMPStringSearch(const string &text, const string &pattern) {
    vector<int> lps(pattern.length());
    computeLPSArray(pattern, lps); // Compute the LPS array

    int textIndex = 0; // Index for the text
    int patternIndex = 0; // Index for the pattern

    while (textIndex < text.length()) {
        if (pattern[patternIndex] == text[textIndex]) {
            textIndex++;
            patternIndex++;
        }

        if (patternIndex == pattern.length()) {
            cout << "Pattern found at index " << (textIndex - patternIndex) << "\n";
            patternIndex = lps[patternIndex - 1]; // Set patternIndex to the last matched position
        } else if (textIndex < text.length() && pattern[patternIndex] != text[textIndex]) {
            if (patternIndex != 0) {
                patternIndex = lps[patternIndex - 1]; // Use the previous LPS value
            } else {
                textIndex++; // Move to the next character in the text
            }
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB"; // Text to search
    string pattern = "ABABCABAB"; // Pattern to find
    KMPStringSearch(text, pattern); // Perform the KMP search
    return 0;
}
