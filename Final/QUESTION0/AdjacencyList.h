#ifndef __ADJACENCYLIST_H__
#define __ADJACENCYLIST_H__

#include "Graph.h"

#include <string>
#include <vector>

class AdjacencyList : public Graph
{
  private:
    std::vector<int>* adjList;
    int numVertices;
    int numEdges;
  public:
    AdjacencyList(std::string filename);
    int vertices() const; // from Graph.h
    int edges() const; // from Graph.h
    int distance(int i) const; // from Graph.h
    std::string path(int target) const;
    void bfs(int); // from Graph.h
    void dfs(int); // from Graph.h
    void display() const; // from Graph.h
};

#endif // __ADJACENCYLIST_H__

