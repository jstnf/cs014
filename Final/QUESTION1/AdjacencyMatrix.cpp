#include "AdjacencyMatrix.h"

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
using std::to_string;
using std::vector;

AdjacencyMatrix::AdjacencyMatrix(std::string filename)
{
    numEdges = 0;
    _distances = vector<int>();
    _previous = vector<int>();

    ifstream inFS(filename);

    if (!inFS.is_open())
    {
        cout << "Error reading file " << filename << endl;
        return;
    }

    inFS >> numVertices;
    adjMatrix = new int*[numVertices];
    edgesAtVertex = new int[numVertices];

    for (int i = 0; i < numVertices; i++)
    {
        edgesAtVertex[i] = 0;
        adjMatrix[i] = new int[numVertices];
        _distances.push_back(-1);
        _previous.push_back(-1);
    }

    int source;
    int sink;

    while (inFS >> source >> sink)
    {
        adjMatrix[source][sink] = edgesAtVertex[source] + 1;
        edgesAtVertex[source]++;
        numEdges++;
    }

    inFS.close();
}

int AdjacencyMatrix::vertices() const
{
    return numVertices;
}

int AdjacencyMatrix::edges() const
{
    return numEdges;
}

int AdjacencyMatrix::distance(int i) const
{
    return _distances.at(i);
}

std::string AdjacencyMatrix::path(int target) const
{
    int currVert = target;
    istringstream inSS("}");

    while (_previous.at(currVert) != -1)
    {
        inSS.str("->" + to_string(currVert) + inSS.str());
        currVert = _previous.at(currVert);
    }

    inSS.str("{" + to_string(currVert) + inSS.str());
    return inSS.str();
}

// Overall runtime complexity: O(n^2) n = numVertices
// Overall space complexity: O(n) n = numVertices
void AdjacencyMatrix::bfs(int start)
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

        for (int i = 0; i < numVertices; ++i) // O(n)
        {
            if (adjMatrix[currVert][i] > 0) // O(1)
            {
                if (discovered.find(i) == discovered.end()) // O(1)
                {
                    frontier.push(i); // O(1)
                    discovered.insert(i); // O(1)

                    _previous.at(i) = currVert; // O(1)
                    _distances.at(i) = _distances.at(currVert) + 1; // O(1)
                }
            }
        }

        frontier.pop(); // O(1)
    }
}

// Overall runtime complexity: O(n*m) n = numVertices, m = numEdges
// Overall space complexity: O(n + m) n = numVertices, m = numEdges (at highest)
void AdjacencyMatrix::dfs(int start)
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

        if (visited.find(currVert) == visited.end()) // O(1)
        {
            visited.insert(currVert); // O(1)

            // /* Doesn't work (not doing paths in order)
            // cout << "Visited " << currVert << endl;

            for (unsigned i = numVertices; i > 0; --i) // O(p) p = numEdges at current vertex
            {
                if (adjMatrix[currVert][i - 1] > 0)
                {
                    processStack.push(i - 1); // O(1)
                    if (visited.find(i - 1) == visited.end()) // O(1)
                    {
                        _distances.at(i - 1) = _distances.at(currVert) + 1; // O(1)
                        _previous.at(i - 1) = currVert; // O(1)
                    }
                }
            }
            // */

            /* This solution is weird...
            int* edges = new int[numVertices]; // O(p(n)) space complexity [multiple of n, p(n) being edges at vertex] space complexity, simplify to O(n) I believe

            for (int i = 0; i < numVertices; ++i)  // O(n)
            {
                if (adjMatrix[currVert][i] > 0) // O(1)
                {
                    edges[adjMatrix[currVert][i] - 1] = i; // O(1) // Put the edges in order in the array
                }
            }

            // Try flipping?
            // for (int e = edgesAtVertex[currVert]; e > 0 ; --e) // O(p) p = numEdges at current vertex
            for (int e = 0; e < edgesAtVertex[currVert]; ++e) // O(p) p = numEdges at current vertex
            {
                int sink = edges[e];

                processStack.push(sink); // O(1)
                if (visited.find(sink) == visited.end()) // O(1)
                {
                    _distances.at(sink) = _distances.at(currVert) + 1; // O(1)
                    _previous.at(sink) = currVert; // O(1)
                }
            }

            delete[] edges;
            */
        }
    }
}

void AdjacencyMatrix::display() const
{
    cout << "VERTICES: " << numVertices << " | EDGES: " << numEdges << endl;
    cout << "Adjacency Matrix: (row is source, column is sink)" << endl;
    cout << " ";
    for (int i = 0; i < numVertices; ++i)
    {
        cout << " " << i % 10;
    }
    cout << endl;

    for (int i = 0; i < numVertices; ++i)
    {
        cout << i << " ";

        for (int j = 0; j < numVertices; ++j)
        {
            if (adjMatrix[i][j] > 0) // We're asking for truth, not nullptr status
            {
                cout << adjMatrix[i][j] << " ";
            }
            else
            {
                cout << "  ";
            }
        }

        cout << endl;
    }
}