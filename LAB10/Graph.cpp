#include "Graph.h"

#include <iostream>

Graph::Graph() { }

Graph::Graph(ifstream& fN)
{
    map<string, int> graph;
    string temp;

    int nodes;
    int edges;
	
	fN >> nodes >> edges;
	
	for (int i = 0; i < nodes; ++i)
    {
		fN >> temp;
		Vertex tempVertex;
		tempVertex.label = temp;
		vertices.push_back(tempVertex);
		graph[temp] = i;
	}
	
    string initVertex;
    string sinkVertex;

    int cost;
    int index;
	
	for (int i = 0; i < edges; ++i)
    {
		fN >> initVertex >> sinkVertex >> cost;
		index = graph[initVertex];
		pair<int, int> p(graph[sinkVertex], cost);
		vertices.at(index).neighbors.push_back(p);
	}
}

Graph::~Graph()
{
    while (!vertices.empty())
    {
        vertices.pop_back();
    }
}

void Graph::output_graph(const string &fN)
{
    ofstream outFS(fN.c_str());

    if (!outFS.is_open())
    {
        cout << "Error" << endl;
        return;
    }

    outFS << "digraph G {" << endl;

    for (unsigned i = 0; i < vertices.size(); ++i)
    {
    	if (vertices.at(i).distance != INT_MAX)
        {
            outFS << vertices.at(i).label << "[label = \"" << vertices.at(i).label << ", " << vertices.at(i).distance << "\"]" << endl;
    	}

     	if (!vertices.at(i).neighbors.empty())
        {
     	    list<pair<int, int> >::iterator it = vertices.at(i).neighbors.begin();
     		while (it != vertices.at(i).neighbors.end())
            {
     			if (vertices.at(i).distance!= INT_MAX)
                {
     		        outFS << vertices.at(i).label << " -> " << vertices.at(it->first).label << endl;
     			}

     		    ++it;
     		}
     	}	    
    }

    outFS << "}";
    outFS.close();

    string fNjpg = fN.substr(0, fN.size()-4) + ".jpg";

    string command = "dot -Tpng " + fN + " -o " + fNjpg;
    system(command.c_str());
}

void Graph::bfs()
{
    for (unsigned i = 0; i < vertices.size(); ++i)
    {
        vertices.at(i).color = "WHITE";
        vertices.at(i).distance = INT_MAX;
        vertices.at(i).prev = 0;
    }

    vertices.at(0).color = "GRAY";
    vertices.at(0).distance = 0;
    queue<Vertex*> queue;

    queue.push(&vertices.at(0));
    Vertex* currVertex;

    while (!queue.empty())
    {
        currVertex = queue.front();
        auto it = currVertex->neighbors.begin();

        while (it != currVertex->neighbors.end())
        {
            if (vertices.at(it->first).color == "WHITE")
            {
                vertices.at(it->first).color = "GRAY";
                vertices.at(it->first).distance = currVertex->distance + it->second;
                vertices.at(it->first).prev = currVertex;
                queue.push(&vertices.at(it->first));
            }

            ++it;
        }

        currVertex->color = "BLACK";

        queue.pop();
    }
}

int Graph::distance(const std::string& key) const
{
    auto it = vertices.begin();

    while (it != vertices.end())
    {
        if (it->label == key)
        {
            return it->distance;
        }

        it++;
    }

    return INT_MAX;
}

std::string Graph::previous(const std::string& key) const
{
    auto it = vertices.begin();

    while (it != vertices.end())
    {
        if (it->label == key)
        {
            if (it->prev)
            {
                return it->prev->label;
            }
            else
            {
                return "";
            }
        }

        it++;
    }

    return "";
}

void Graph::print_all() const
{
    cout << "Printing all!" << endl;
    cout << "Vertices size: " << vertices.size() << endl;

    auto it = vertices.begin();

    while (it != vertices.end())
    {
        cout << "Printing something..." << endl;
        cout << it->label << " " << (it->prev == nullptr ? "nullptr (0)" : it->prev->label) << " " << it->distance << endl;

        it++;
    }
}