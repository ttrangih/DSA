//SId: 22520422
//Name: Nguyen Thuy Trang
//Lab_2 Homework question 3

#include <iostream>

using namespace std;

const int MAX_N = 100000;
int heights[MAX_N];
int result[MAX_N];

int main() {
    int n; // Number of people in the queue

    // Input the number of people
    cout << "Enter the number of people: ";
    cin >> n;

    // Input the heights of people
    cout << "Enter the heights of the people: ";
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }

    // Calculate the number of visible people for each person
    for (int i = 0; i < n; ++i) {
        result[i] = 0; // Initialize the count for each person
        for (int j = i + 1; j < n; ++j) {
            if (heights[j] < heights[i]) {
                result[i]++;
            }
            else {
                // If a taller person is encountered, stop checking
                break;
            }
        }
    }

    // Output the result
    cout << "Output: [";
    for (int i = 0; i < n; ++i) {
        cout << result[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}

