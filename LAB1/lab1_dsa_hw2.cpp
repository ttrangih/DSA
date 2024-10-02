#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BrowserHistory {
private:
    vector<string> history;  // To store the URLs visited
    int current;  // Index of the current page in the history

public:
    // Constructor to initialize with the homepage
    BrowserHistory(string homepage) {
        history.push_back(homepage);
        current = 0;  // Start at the homepage
    }

    // Visit a new URL, and clear any forward history
    void visit(string url) {
        // Remove any forward history if we visit a new URL
        history.resize(current + 1);
        history.push_back(url);
        current++;
    }

    // Move back by 'steps' in history, returning the new current page
    string back(int steps) {
        current = max(0, current - steps);  // Move back as much as possible
        return history[current];
    }

    // Move forward by 'steps' in history, returning the new current page
    string forward(int steps) {
        current = min((int)history.size() - 1, current + steps);  // Move forward as much as possible
        return history[current];
    }
};

int main() {
    // Example usage
    BrowserHistory* browser = new BrowserHistory("uit.edu.vn");

    browser->visit("google.com");
    browser->visit("facebook.com");
    browser->visit("youtube.com");

    cout << browser->back(1) << endl;   // Should print "facebook.com"
    cout << browser->back(1) << endl;   // Should print "google.com"
    cout << browser->forward(1) << endl; // Should print "facebook.com"

    browser->visit("linkedin.com");
    cout << browser->forward(2) << endl; // Should print "linkedin.com" (no forward history)
    cout << browser->back(2) << endl;    // Should print "google.com"
    cout << browser->back(7) << endl;    // Should print "uit.edu.vn" (as far back as possible)

    return 0;
}
