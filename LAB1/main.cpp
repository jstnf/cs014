#include "Playlist.h"

#include <iostream>

using namespace std;

Playlist* playlist;

void PrintMenu(string);

int main() {
    string title;
    cout << "Enter playlist's title:" << endl;
    getline(cin, title);
    cout << endl;

    playlist = new Playlist();
    PrintMenu(title);

    return 0;
}

void PrintMenu(string title)
{
    cout << title << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:";
    cout << endl;

    string choice;
    getline(cin, choice);

    if (choice == "a") // Add song
    {
        cout << "ADD SONG" << endl;
        string id;
        string name;
        string artist;
        int length;

        cout << "Enter song's unique ID:" << endl;
        getline(cin, id);
        cout << "Enter song's name:" << endl;
        getline(cin, name);
        cout << "Enter artist's name:" << endl;
        getline(cin, artist);
        cout << "Enter song's length (in seconds):" << endl;
        cin >> length;
        cin.ignore();

        PlaylistNode* newNode = new PlaylistNode(id, name, artist, length);
        playlist->push_back(newNode);
        cout << endl;
        PrintMenu(title);
    }
    else if (choice == "d") // Remove song
    {
        cout << "REMOVE SONG" << endl;
        cout << "Enter song's unique ID:" << endl;
        string id;
        getline(cin, id);
        PlaylistNode* removed = playlist->remove(id);
        if (removed)
        {
            cout << '"' << removed->GetSongName() << '"' << " removed." << endl;
        }
        else
        {
            cout << "Song with unique ID " << id << " not found!" << endl;
        }
        cout << endl;
        PrintMenu(title);
    }
    else if (choice == "c") // Change position of song
    {
        cout << "CHANGE POSITION OF SONG" << endl;
        int initial;
        int newPos;
        cout << "Enter song's current position:" << endl;
        cin >> initial;
        cout << "Enter new position for song:" << endl;
        cin >> newPos;
        cin.ignore();

        playlist->changePos(initial, newPos);
        cout << endl;
        PrintMenu(title);
    }
    else if (choice == "s") // Output songs by specific artist
    {
        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
        cout << "Enter artist's name:" << endl;
        string artist;
        getline(cin, artist);
        cout << endl;
        playlist->printByArtist(artist);
        PrintMenu(title);
    }
    else if (choice == "t") // Output total time of playlist (in seconds)
    {
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
        cout << "Total time: " << playlist->totalTimeSeconds() << " seconds" << endl;
        cout << endl;
        PrintMenu(title);
    }
    else if (choice == "o") // Output full playlist
    {
        playlist->print(title);
        PrintMenu(title);
    }
    else if (choice == "q") // Quit
    {
        // Do nothing
    }
    else
    {
        cout << "Invalid selection." << endl;
        PrintMenu(title);
    }
}