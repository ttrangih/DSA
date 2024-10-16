//22521514
//Nguyen Thuy Trang
//Lab2_homework_question 4
#include <iostream>
using namespace std;

const int MAX_FRUITS = 1000; // Maximum number of fruits

int minCoinsToBuyFruits(int prices[], int n) {
    int totalCoins = 0;
    int i = 0; // Start from the first fruit

    while (i < n) {
        // Buy the current fruit
        totalCoins += prices[i];

        // Calculate how many fruits can be obtained for free after buying the current one
        // We can skip the next fruit, so move the index forward by 2
        i += 2; // Move to the next fruit to buy after the free one

        // If we can afford to buy the next fruit that can be skipped,
        // check if it's cheaper than any upcoming fruits we can take for free.
        // This logic allows us to decide whether we want to skip the free fruit
        // and buy it instead.
    }

    return totalCoins;
}

int main() {
    int n;
    int prices[MAX_FRUITS]; // Declare an array for prices

    cout << "Enter the number of fruits: ";
    cin >> n;

    cout << "Enter the prices of the fruits: ";
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }

    int result = minCoinsToBuyFruits(prices, n);
    cout << "Minimum number of coins required: " << result << endl;

    return 0;
}
