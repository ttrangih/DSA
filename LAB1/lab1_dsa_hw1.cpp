#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class Node {
public:
    string song;
    Node* prev;
    Node* next;

    Node(string songName) : song(songName), prev(nullptr), next(nullptr) {}
};

class MusicPlayer {
private:
    Node* head;
    Node* tail;
    Node* current;
    unordered_map<string, Node*> songMap;

public:
    MusicPlayer() : head(nullptr), tail(nullptr), current(nullptr) {}

    // Add song to the end of the playlist
    void addSong(string songName) {
        Node* newSong = new Node(songName);
        songMap[songName] = newSong;

        if (!head) {
            head = tail = current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
    }

    // Play next song, loop to the start if at the end
    void playNext() {
        if (!current) return;
        if (current->next) {
            current = current->next;
        } else {
            current = head;  // loop back to first song
        }
    }

    // Play previous song, loop to the end if at the start
    void playPrev() {
        if (!current) return;
        if (current->prev) {
            current = current->prev;
        } else {
            current = tail;  // loop back to last song
        }
    }

    // Remove a song by its name
    void removeSong(string songName) {
        if (songMap.find(songName) == songMap.end()) return;  // song not found

        Node* songToRemove = songMap[songName];

        if (songToRemove->prev) songToRemove->prev->next = songToRemove->next;
        if (songToRemove->next) songToRemove->next->prev = songToRemove->prev;

        if (songToRemove == head) head = songToRemove->next;
        if (songToRemove == tail) tail = songToRemove->prev;
        if (songToRemove == current) current = (current->next) ? current->next : head;

        songMap.erase(songName);
        delete songToRemove;
    }

    // Display the current playlist
    void displayPlaylist() {
        Node* temp = head;
        while (temp) {
            cout << temp->song << (temp->next ? " " : "");
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    MusicPlayer player;
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string command;
        cin >> command;

        if (command == "ADD") {
            string songName;
            cin >> songName;
            player.addSong(songName);
        } else if (command == "NEXT") {
            player.playNext();
        } else if (command == "PREV") {
            player.playPrev();
        } else if (command == "REMOVE") {
            string songName;
            cin >> songName;
            player.removeSong(songName);
        } else if (command == "DISPLAY") {
            player.displayPlaylist();
        }
    }

    return 0;
}
