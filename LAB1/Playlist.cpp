#include "Playlist.h"

#include <iostream>

using namespace std;

PlaylistNode::PlaylistNode() : uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr)
{ }

PlaylistNode::PlaylistNode(string uniqueID, string songName, string artistName, int songLength)
{
    this->uniqueID = uniqueID;
    this->songName = songName;
    this->artistName = artistName;
    this->songLength = songLength;
    nextNodePtr = nullptr;
}

void PlaylistNode::InsertAfter(PlaylistNode* node)
{
    PlaylistNode* temp = nextNodePtr;
    nextNodePtr = node;
    node->SetNext(temp);
}

void PlaylistNode::SetNext(PlaylistNode* node)
{
    nextNodePtr = node;
}

string PlaylistNode::GetID() const
{
    return uniqueID;
}

string PlaylistNode::GetSongName() const
{
    return songName;
}

string PlaylistNode::GetArtistName() const
{
    return artistName;
}

int PlaylistNode::GetSongLength() const
{
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const
{
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() const
{
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}

Playlist::Playlist() : head(nullptr), tail(nullptr)
{ }

void Playlist::PrintMenu(string title)
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
        push_back(newNode);
        cout << endl;
        PrintMenu(title);
    }
    else if (choice == "d") // Remove song
    {
        cout << "REMOVE SONG" << endl;
        cout << "Enter song's unique ID:" << endl;
        string id;
        getline(cin, id);
        PlaylistNode* removed = remove(id);
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

        changePos(initial, newPos);
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
        printByArtist(artist);
        PrintMenu(title);
    }
    else if (choice == "t") // Output total time of playlist (in seconds)
    {
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
        cout << "Total time: " << totalTimeSeconds() << " seconds" << endl;
        cout << endl;
        PrintMenu(title);
    }
    else if (choice == "o") // Output full playlist
    {
        print(title);
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

void Playlist::print(string title) const
{
    cout << title << " - OUTPUT FULL PLAYLIST" << endl;
    if (empty())
    {
        cout << "Playlist is empty" << endl;
        cout << endl;
    }
    else
    {
        int counter = 1;
        PlaylistNode* node = head;
        while (node)
        {
            cout << counter << "." << endl;
            node->PrintPlaylistNode();
            cout << endl;

            counter++;
            node = node->GetNext();
        }
    }
}

bool Playlist::empty() const
{
    return head == nullptr;
}

void Playlist::push_back(PlaylistNode * node)
{
    if (empty())
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->SetNext(node);
        tail = node;
    }
}

PlaylistNode* Playlist::remove(string id)
{
    PlaylistNode* prevPointer = nullptr;
    PlaylistNode* currPointer = head;

    while (currPointer && currPointer->GetID() != id)
    {
        prevPointer = currPointer;
        currPointer = currPointer->GetNext();
    }

    if (currPointer)
    {
        if (prevPointer)
        {
            prevPointer->SetNext(currPointer->GetNext());
        }
        else
        {
            head = currPointer->GetNext();
        }

        if (!currPointer->GetNext())
        {
            tail = prevPointer;
        }

        return currPointer;
    }
    else
    {
        return nullptr;
    }
}

void Playlist::changePos(int initial, int newPos)
{
    int initialIndex = 1;
    PlaylistNode* prev = nullptr;
    PlaylistNode* curr = head;

    if (initial < 1)
    {
        cout << "Invalid current position." << endl;
        return;
    }

    // Get a pointer to the node to move
    while (initialIndex < initial)
    {
        if (curr)
        {
            prev = curr;
            curr = curr->GetNext();
            initialIndex++;
        }
        else
        {
            cout << "Invalid current position." << endl;
            return;
        }
    }

    // Remove the node from the list, make prev's next point to curr's next
    // Or make head point to curr's next if prev is nullptr (curr is first node in the list)
    if (prev)
    {
        prev->SetNext(curr->GetNext());
    }
    else
    {
        head = curr->GetNext();
    }

    // If curr was the last element in the list, make tail point to previous node
    if (curr == tail)
    {
        tail = prev;
    }

    // Place the node at the new position
    if (newPos <= 1) // Node is inserted at the head
    {
        if (empty())
        {
            tail = curr;
        }

        curr->SetNext(head);
        head = curr;
        cout << '"' << curr->GetSongName() << '"' << " moved to position 1" << endl;
    }
    else // Node is inserted after the head
    {
        int newPosIndex = 2;
        PlaylistNode* prevNode = head;
        PlaylistNode* afterNode = head->GetNext();
        while (newPosIndex < newPos && afterNode)
        {
            prevNode = afterNode;
            afterNode = afterNode->GetNext();
            newPosIndex++;
        }

        curr->SetNext(prevNode->GetNext());
        prevNode->SetNext(curr);

        if (!afterNode) // the node is being inserted at the tail
        {
            tail = curr;
        }
        cout << '"' << curr->GetSongName() << '"' << " moved to position " << newPosIndex << endl;
    }
}

void Playlist::printByArtist(string artist) const
{
    int positionCounter = 1;
    PlaylistNode* node = head;
    while (node)
    {
        if (node->GetArtistName() == artist)
        {
            cout << positionCounter << "." << endl;
            node->PrintPlaylistNode();
            cout << endl;
        }

        positionCounter++;
        node = node->GetNext();
    }
}

int Playlist::totalTimeSeconds() const
{
    int total = 0;
    PlaylistNode* node = head;
    while (node)
    {
        total += node->GetSongLength();
        node = node->GetNext();
    }
    return total;
}