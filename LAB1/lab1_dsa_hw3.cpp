#include <iostream>
#include <unordered_map>
using namespace std;

class AuthenticationManager {
private:
    int timeToLive;  // Time-to-live for each token in seconds
    unordered_map<string, int> tokens;  // Map to store tokens and their expiration time

public:
    // Constructor: Initialize the authentication manager with timeToLive
    AuthenticationManager(int timeToLive) {
        this->timeToLive = timeToLive;
    }

    // Generate a new token with tokenId and currentTime
    void generate(string tokenId, int currentTime) {
        tokens[tokenId] = currentTime + timeToLive;  // Store token with its expiration time
    }

    // Renew the token if it hasn't expired
    void renew(string tokenId, int currentTime) {
        // Check if token exists and if it hasn't expired
        if (tokens.find(tokenId) != tokens.end() && tokens[tokenId] > currentTime) {
            tokens[tokenId] = currentTime + timeToLive;  // Update expiration time
        }
    }

    // Count unexpired tokens at currentTime
    int countUnexpiredTokens(int currentTime) {
        int count = 0;
        // Iterate over tokens and count those with expiration time greater than currentTime
        for (auto it = tokens.begin(); it != tokens.end(); ) {
            if (it->second > currentTime) {
                count++;
                ++it;
            } else {
                // Erase expired tokens
                it = tokens.erase(it);
            }
        }
        return count;
    }
};

int main() {
    // Example usage
    AuthenticationManager* authManager = new AuthenticationManager(5);

    // Simulating the operations
    authManager->renew("aaa", 1);  // No effect, since "aaa" doesn't exist yet
    authManager->generate("aaa", 2);  // Generate token "aaa" at time 2
    cout << authManager->countUnexpiredTokens(6) << endl;  // Output: 1 (token "aaa" still valid)

    authManager->generate("bbb", 7);  // Generate token "bbb" at time 7
    authManager->renew("aaa", 8);  // "aaa" is expired, so no renewal
    authManager->renew("bbb", 10);  // Renew "bbb" at time 10, expiration extended to 15

    cout << authManager->countUnexpiredTokens(15) << endl;  // Output: 0 (all tokens expired)

    return 0;
}
