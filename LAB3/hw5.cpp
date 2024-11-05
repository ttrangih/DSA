//SId: 22521514
//Nguyen Thuy Trang
//Homework 5

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct StockPrice {
    string ticker;
    double price;
    long timestamp;

    bool operator<(const StockPrice &other) const {
        return timestamp > other.timestamp; // For priority queue (min-heap)
    }
};

class StockMarket {
    priority_queue<StockPrice> prices;

public:
    void updatePrice(const string &ticker, double price, long timestamp) {
        prices.push({ticker, price, timestamp});
    }

    void printLatestPrices() {
        while (!prices.empty()) {
            StockPrice sp = prices.top();
            cout << "Ticker: " << sp.ticker << ", Price: " << sp.price << "\n";
            prices.pop();
        }
    }
};

int main() {
    StockMarket market;
    market.updatePrice("AAPL", 150.25, 1);
    market.updatePrice("GOOGL", 2800.75, 2);
    market.updatePrice("AMZN", 3400.50, 3);

    cout << "Latest Stock Prices:\n";
    market.printLatestPrices();
    return 0;
}
