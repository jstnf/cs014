#include "AdjacencyList.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::queue;
using std::set;
using std::stack;
using std::string;
using std::to_string;
using std::vector;

AdjacencyList::AdjacencyList(std::string filename)
{
    numEdges = 0;

    ifstream inFS(filename);

    if (!inFS.is_open())
    {
        cout << "Error reading file " << filename << endl;
        return;
    }

    inFS >> numVertices;
    adjList = new vector<int>[numVertices];

    _distances = vector<int>();
    _previous = vector<int>();

    for (int i = 0; i < numVertices; i++)
    {
        _distances.push_back(-1);
        _previous.push_back(-1);
    }

    int source;
    int sink;

    while (inFS >> source >> sink)
    {
        adjList[source].push_back(sink);
        numEdges++;
    }

    inFS.close();
}

int AdjacencyList::vertices() const
{
    return numVertices;
}

int AdjacencyList::edges() const
{
    return numEdges;
}

int AdjacencyList::distance(int i) const
{
    return _distances.at(i);
}

std::string AdjacencyList::path(int target) const
{
    int currVect = target;
    istringstream inSS("}");

    while (_previous.at(currVect) != -1)
    {
        inSS.str("->" + to_string(currVect) + inSS.str());
        currVect = _previous.at(currVect);
    }

    inSS.str("{" + to_string(currVect) + inSS.str());
    return inSS.str();
}

// Overall runtime complexity: O(m + n) m = numEdges, n = numNodes (roughly, each edge will be processed once)
// Overall space complexity: O(n) n = numVertices
void AdjacencyList::bfs(int start)
{
    set<int> discovered = set<int>(); // Will reach O(n) space complexity at end
    queue<int> frontier = queue<int>(); // Will never be above O(n) due to check against discovered

    frontier.push(start); // O(1)
    discovered.insert(start); // O(1)

    _distances.at(start) = 0; // O(1)
    _previous.at(start) = -1; // O(1)

    while (!frontier.empty()) // O(n) n = numVertices (frontier will contain only vertices not visited)
    {
        int currVert = frontier.front(); // O(1)

        for (int sink : adjList[currVert]) // O(p) p = numNeighbors in the current vertex
        {
            if (discovered.find(sink) == discovered.end()) // O(1)
            {
                frontier.push(sink); // O(1)
                discovered.insert(sink); // O(1)

                _previous.at(sink) = currVert; // O(1)
                _distances.at(sink) = _distances.at(currVert) + 1; // O(1)
            }
        }

        frontier.pop(); // O(1)
    }
}

// Overall runtime complexity: O(m) m being the numEdges
// Overall space complexity: O(n + m) n = numVertices, m = numEdges (at highest)
void AdjacencyList::dfs(int start)
{
    set<int> visited = set<int>(); // Will reach O(n) space complexity at end
    stack<int> processStack = stack<int>(); // At max, O(m) space complexity, m being the numEdges

    processStack.push(start); // O(1)

    _distances.at(start) = 0; // O(1)
    _previous.at(start) = -1; // O(1)

    while (!processStack.empty()) // O(m) m = numEdges since it follows the stack space complexity and repetitive edges may be added
    {
        int currVert = processStack.top(); // O(1)
        processStack.pop(); // O(1)

        // Check if the node being processed has already been visited
        // This check means that roughly, the processing of each edge depends on order of visitation; max would be all nodes if path not optimized
        // Sum of all p(n) = m so this whole loop is a rough runtime of m
        if (visited.find(currVert) == visited.end()) // O(1)
        {
            visited.insert(currVert); // O(1)

            for (unsigned i = adjList[currVert].size(); i > 0; --i) // O(p) p = numEdges at current vertex
            {
                int sink = adjList[currVert].at(i - 1); // O(1)

                processStack.push(sink); // O(1)
                if (visited.find(sink) == visited.end()) // O(1)
                {
                    _distances.at(sink) = _distances.at(currVert) + 1; // O(1)
                    _previous.at(sink) = currVert; // O(1)
                }
            }
        }
    }
}

void AdjacencyList::display() const
{
    cout << "VERTICES: " << numVertices << endl;
    cout << "Adjacency List: " << endl;
    for (int i = 0; i < numVertices; i++)
    {
        cout << i << "\t" << "|";
        for (unsigned j = 0; j < adjList[i].size(); ++j)
        {
            cout << " " << adjList[i].at(j);
        }
        cout << endl;
    }
}