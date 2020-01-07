#include "Playlist.h"

#include <iostream>

using namespace std;

int main() {
    string title;
    cout << "Enter playlist's title:" << endl;
    getline(cin, title);
    cout << endl;

    Playlist* playlist = new Playlist();
    playlist->PrintMenu(title);

    return 0;
}