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

    airport.print();
    //airport.printIDandDestination();
    Graph graph(airport.generateEdges(), airport.getNumberAirports());


    // print adjacency list representation of graph
    int contador=0;
    for (auto it=graph.AdjacencyList.begin(); it != graph.AdjacencyList.end(); it++)
    {
        cout<<"HOLA"<<endl;
        // print all neighboring vertices of vertex i
        printList(it->second, contador);
        contador++;
    }


    return 0;
}