//SId: 22521514
//Nguyen Thuy Trang
//Homework 4

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
};

double distance(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// KNN search function that calculates distances and finds the k nearest neighbors
void knnSearch(const vector<Point> &dataset, const Point &query, int k, int start, int end, vector<Point> &results, mutex &m) {
    vector<pair<double, Point>> distances;

    // Calculate distances from the query point
    for (int i = start; i < end; ++i) {
        double dist = distance(dataset[i], query);
        distances.emplace_back(dist, dataset[i]);
    }

    // Sort distances based on the distance value
    sort(distances.begin(), distances.end(),
         [](const pair<double, Point> &a, const pair<double, Point> &b) {
             return a.first < b.first; // Sort by the distance value
         });

    // Lock and store k nearest neighbors
    for (int i = 0; i < k && i < distances.size(); ++i) {
        lock_guard<mutex> lock(m);
        results.push_back(distances[i].second);
    }
}

int main() {
    vector<Point> dataset = { {1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10} };
    Point query = {5, 5};
    int k = 3;
    int numThreads = 2;
    vector<thread> threads;
    vector<Point> results;
    mutex m;

    int chunkSize = dataset.size() / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? dataset.size() : (i + 1) * chunkSize;
        threads.emplace_back(knnSearch, ref(dataset), query, k, start, end, ref(results), ref(m));
    }

    for (auto &t : threads) {
        t.join();
    }

    cout << "K Nearest Neighbors:\n";
    for (const auto &p : results) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}
