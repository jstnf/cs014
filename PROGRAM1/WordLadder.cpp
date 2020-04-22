#include "WordLadder.h"

#include <fstream>
#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::queue;

WordLadder::WordLadder(const string &fileName)
{
    // Attempt to open the file
    ifstream inFS(fileName);
    if (!inFS.is_open())
    {
        // File opened unsuccessfully
        cout << "Error opening file " << fileName << endl;
        return;
    }

    // Create list
    dict = list<string>();

    string inputDict;
    while (getline(inFS, inputDict))
    {
        // Verify not empty string
        if (!inputDict.empty())
        {
            // Check character count
            if (inputDict.size() != 5)
            {
                // Word was not 5 letters
                cout << "Error: word " << inputDict << " not 5 characters long" << endl;
                return;
            }

            dict.push_back(inputDict);
        }
    }

    inFS.close();
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile)
{
    /* --- start == end case --- */

    if (start == end)
    {
        stack<string> oneWordStack = stack<string>();
        oneWordStack.push(start);
        outputLadder(outputFile, oneWordStack);
        return;
    }

    /* --- start == end case --- */

    /* --- Error Check START --- */

    bool startInDict = false;
    bool endInDict = false;

    list<string>::iterator it = dict.begin();
    while (it != dict.end())
    {
        if (*it == start)
        {
            startInDict = true;
        }

        if (*it == end)
        {
            endInDict = true;
        }

        it++;
    }

    if (!startInDict)
    {
        // Starting word not in dictionary
        cout << "The first word was not in the dictionary." << endl;
        return;
    }

    if (!endInDict)
    {
        cout << "The last word was not in the dictionary." << endl;
    }

    /* --- Error Check END --- */

    /* --- Find Ladder START --- */

    stack<string> initStack = stack<string>();
    initStack.push(start);

    queue<stack<string>> wordQueue = queue<stack<string>>();
    wordQueue.push(initStack);

    while (!wordQueue.empty())
    {
        stack<string> currStack = wordQueue.front();
        string topWord = currStack.top();

        it = dict.begin();

        while (it != dict.end())
        {
            string s = *it;

            int misMatches = 0;
            for (unsigned j = 0; j < s.size(); ++j)
            {
                if (topWord.at(j) != s.at(j))
                {
                    misMatches++;
                }
            }

            if (misMatches == 1)
            {
                // Copy currStack and put word
                stack<string> newLadder = stack<string>(currStack);
                newLadder.push(s);
                wordQueue.push(newLadder);

                // Remove word from dictionary
                it = dict.erase(it);

                if (s == end)
                {
                    outputLadder(outputFile, newLadder);
                    return;
                }
            }
            else
            {
                it++;
            }
        }

        wordQueue.pop();
    }

    /* --- Find Ladder END --- */

    // Did not find a ladder
    outputNoLadder(outputFile);
}

void WordLadder::outputNoLadder(const string &outputFile)
{
    ofstream outFS(outputFile);

    if (!outFS.is_open())
    {
        cout << "Error opening output file " << outputFile << endl;
        return;
    }

    outFS << "No Word Ladder Found." << endl;
    outFS.close();
}

void WordLadder::outputLadder(const string &outputFile, stack<string> ladder)
{
    ofstream outFS(outputFile);

    if (!outFS.is_open())
    {
        cout << "Error opening output file " << outputFile << endl;
        return;
    }

    stack<string> reverse = stack<string>();
    while (!ladder.empty())
    {
        reverse.push(ladder.top());
        ladder.pop();
    }

    while (!reverse.empty())
    {
        outFS << reverse.top() << endl;
        reverse.pop();
    }

    outFS.close();
    return;
}
