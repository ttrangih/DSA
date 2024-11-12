#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int SIZE = 1000;

// Hàm tạo danh sách ngẫu nhiên
void generateRandomList(list<int>& lst, int size) {
    for (int i = 0; i < size; ++i) {
        lst.push_back(rand() % 10000);
    }
}

// Bubble Sort cho Linked List
void bubbleSort(list<int>& lst) {
    bool swapped;
    do {
        swapped = false;
        for (auto it = lst.begin(); it != --lst.end(); ++it) {
            auto next = it;
            ++next;
            if (*it > *next) {
                swap(*it, *next);
                swapped = true;
            }
        }
    } while (swapped);
}

// Selection Sort cho Linked List
void selectionSort(list<int>& lst) {
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        auto minIt = it;
        for (auto jt = next(it); jt != lst.end(); ++jt) {
            if (*jt < *minIt) {
                minIt = jt;
            }
        }
        if (minIt != it) {
            swap(*it, *minIt);
        }
    }
}

// Quick Sort cho Linked List (sử dụng đệ quy)
list<int> quickSort(const list<int>& lst) {
    if (lst.size() <= 1) return lst;

    auto pivot = lst.begin();
    list<int> less, equal, greater;

    for (const auto& val : lst) {
        if (val < *pivot) less.push_back(val);
        else if (val > *pivot) greater.push_back(val);
        else equal.push_back(val);
    }

    less = quickSort(less);
    greater = quickSort(greater);

    less.splice(less.end(), equal);
    less.splice(less.end(), greater);
    return less;
}

// Hàm sắp xếp hàng đợi bằng Bubble Sort
void bubbleSortQueue(queue<int>& q) {
    vector<int> v;
    while (!q.empty()) {
        v.push_back(q.front());
        q.pop();
    }

    // Sắp xếp vector
    for (size_t i = 0; i < v.size() - 1; ++i) {
        for (size_t j = 0; j < v.size() - i - 1; ++j) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }

    // Đưa lại vào hàng đợi
    for (auto val : v) {
        q.push(val);
    }
}

// Hàm sắp xếp ngăn xếp bằng Bubble Sort
void bubbleSortStack(stack<int>& s) {
    vector<int> v;
    while (!s.empty()) {
        v.push_back(s.top());
        s.pop();
    }

    // Sắp xếp vector
    for (size_t i = 0; i < v.size() - 1; ++i) {
        for (size_t j = 0; j < v.size() - i - 1; ++j) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }

    // Đưa lại vào ngăn xếp (theo thứ tự đảo ngược)
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        s.push(*it);
    }
}

// Hàm đo thời gian thực thi
template <typename Func, typename Container>
double measureExecutionTime(Func sortFunc, Container& container) {
    auto start = high_resolution_clock::now();
    sortFunc(container);
    auto end = high_resolution_clock::now();

    return duration<double>(end - start).count();
}

int main() {
    list<int> linkedList;
    queue<int> queueData;
    stack<int> stackData;

    // Tạo dữ liệu ngẫu nhiên cho danh sách liên kết
    generateRandomList(linkedList, SIZE);

    // Tạo hàng đợi và ngăn xếp từ danh sách liên kết
    for (const auto& val : linkedList) {
        queueData.push(val);
        stackData.push(val);
    }

    // Đo thời gian thực thi của Bubble Sort với danh sách liên kết
    list<int> linkedListCopy = linkedList;
    cout << "Bubble Sort on Linked List: " << measureExecutionTime(bubbleSort, linkedListCopy) << " seconds" << endl;

    // Đo thời gian thực thi của Selection Sort với danh sách liên kết
    linkedListCopy = linkedList;
    cout << "Selection Sort on Linked List: " << measureExecutionTime(selectionSort, linkedListCopy) << " seconds" << endl;

    // Đo thời gian thực thi của Quick Sort với danh sách liên kết
    auto start = high_resolution_clock::now();
    linkedListCopy = quickSort(linkedList);
    auto end = high_resolution_clock::now();
    cout << "Quick Sort on Linked List: " << duration<double>(end - start).count() << " seconds" << endl;

    // Đo thời gian thực thi của Bubble Sort với hàng đợi
    cout << "Bubble Sort on Queue: " << measureExecutionTime(bubbleSortQueue, queueData) << " seconds" << endl;

    // Đo thời gian thực thi của Bubble Sort với ngăn xếp
    cout << "Bubble Sort on Stack: " << measureExecutionTime(bubbleSortStack, stackData) << " seconds" << endl;

    return 0;
}
