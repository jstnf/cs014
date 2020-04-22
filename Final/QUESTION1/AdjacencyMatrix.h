#ifndef __ADJACENCYMATRIX_H__
#define __ADJACENCYMATRIX_H__

#include "Graph.h"

#include <string>
#include <vector>

class AdjacencyMatrix : public Graph
{
  private:
    int* edgesAtVertex;
    int** adjMatrix;
    int numVertices;
    int numEdges;
  public:
    AdjacencyMatrix(std::string filename);

    int vertices() const; // from Graph.h
    int edges() const; // from Graph.h
    int distance(int i) const; // from Graph.h
    std::string path(int target) const;
    void bfs(int); // from Graph.h
    void dfs(int); // from Graph.h
    void display() const; // from Graph.h
};

#endif // __ADJACENCYMATRIX_H__
