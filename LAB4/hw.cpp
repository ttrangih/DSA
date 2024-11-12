#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;

// --- Struct Definitions ---

struct Product {
    string name;
    double price;
    double rating;
    int popularity;

    Product(string n, double p, double r, int pop)
        : name(n), price(p), rating(r), popularity(pop) {}
};

struct Post {
    string content;
    int likes;
    int shares;
    int comments;
    string time;

    Post(string c, int l, int s, int com, string t)
        : content(c), likes(l), shares(s), comments(com), time(t) {}
};

struct Student {
    string name;
    double grade;
    int age;

    Student(string n, double g, int a) : name(n), grade(g), age(a) {}
};

struct Song {
    string name;
    string artist;
    string genre;
    string mood;

    Song(string n, string a, string g, string m)
        : name(n), artist(a), genre(g), mood(m) {}
};

// --- Sorting Algorithms ---

// Quick Sort Partition for Product (sort by price)
int partition(vector<Product>& products, int low, int high) {
    double pivot = products[high].price;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (products[j].price < pivot) {
            i++;
            swap(products[i], products[j]);
        }
    }
    swap(products[i + 1], products[high]);
    return i + 1;
}

void quickSort(vector<Product>& products, int low, int high) {
    if (low < high) {
        int pi = partition(products, low, high);
        quickSort(products, low, pi - 1);
        quickSort(products, pi + 1, high);
    }
}

// Merge Sort for Products
void merge(vector<Product>& products, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Product> leftArr(n1), rightArr(n2);
    for (int i = 0; i < n1; i++) leftArr[i] = products[left + i];
    for (int i = 0; i < n2; i++) rightArr[i] = products[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].price <= rightArr[j].price) {
            products[k] = leftArr[i];
            i++;
        } else {
            products[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        products[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        products[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Product>& products, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(products, left, mid);
        mergeSort(products, mid + 1, right);
        merge(products, left, mid, right);
    }
}

// --- Performance Measurement ---

void printExecutionTime(const string& sortName, void (*sortFunc)(vector<Product>&, int, int), vector<Product>& products) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(products, 0, products.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << sortName << " took: " << duration.count() << " seconds\n";
}

void printExecutionTimeMerge(const string& sortName, void (*sortFunc)(vector<Product>&, int, int), vector<Product>& products) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(products, 0, products.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << sortName << " took: " << duration.count() << " seconds\n";
}

// --- Main function ---

int main() {
    vector<Product> products = {
        {"Laptop", 1200.0, 4.5, 300},
        {"Smartphone", 700.0, 4.2, 500},
        {"Tablet", 300.0, 3.9, 150},
        {"Headphones", 150.0, 4.8, 100},
        {"Monitor", 500.0, 4.6, 200}
    };

    vector<Product> productsCopy = products;

    // Sort by Price (Quick Sort Example)
    printExecutionTime("Quick Sort by Price", quickSort, productsCopy);

    productsCopy = products;
    printExecutionTimeMerge("Merge Sort by Price", mergeSort, productsCopy);

    return 0;
}
