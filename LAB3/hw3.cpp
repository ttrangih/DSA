//SId: 22521514
//Nguyen Thuy Trang
//Homework3

#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
using namespace std;

void performSearch(int retry) {
    // Simulated search operation
    if (retry < 3) { // Simulate failures
        throw runtime_error("Search failed");
    }
    cout << "Search successful!\n";
}

void exponentialBackoff(int maxRetries) {
    for (int retry = 0; retry < maxRetries; ++retry) {
        try {
            performSearch(retry);
            break; // Exit on success
        } catch (const runtime_error &) {
            int waitTime = pow(2, retry); // Exponential backoff
            cout << "Retrying in " << waitTime << " seconds...\n";
            this_thread::sleep_for(chrono::seconds(waitTime));
        }
    }
}

int main() {
    exponentialBackoff(5);
    return 0;
}
