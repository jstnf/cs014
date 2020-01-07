#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

#include <string>

using namespace std;

class PlaylistNode
{
private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;
public:
    PlaylistNode();
    PlaylistNode(string, string, string, int);
    void InsertAfter(PlaylistNode*);
    void SetNext(PlaylistNode*);
    string GetID() const;
    string GetSongName() const;
    string GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext() const;
    void PrintPlaylistNode() const;
};

class Playlist
{
private:
    PlaylistNode* head;
    PlaylistNode* tail;
public:
    Playlist();
    void PrintMenu(string);
    void print(string title) const;
    bool empty() const;
    void push_back(PlaylistNode*);
    PlaylistNode* remove(string);
    void changePos(int, int);
    void printByArtist(string) const;
    int totalTimeSeconds() const;
};
#endif