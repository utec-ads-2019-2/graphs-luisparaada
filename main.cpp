#include <iostream>
#include "CGraph.h"
#include "CJASON.h"

using namespace std;

// print all neighboring vertices of given vertex
void printList(Node* ptr, int i)
{
    while (ptr != nullptr)
    {
        cout << "(" << i << ", " << ptr->val
             << ", " << ptr->cost << ") ";

        ptr = ptr->next;
    }

    cout << endl;
}

int main()
{
    CJASON airport("JSON/airports.json");
    //airport.print();

    //airport.printIDandDestination();
    Graph graph(airport.generateEdges(), airport.getNumberAirports());


    // print adjacency list representation of graph

    for (int i = 0; i < airport.getNumberAirports(); i++)
    {
        // print all neighboring vertices of vertex i
        printList(graph.head[i], i);
    }


    return 0;
}