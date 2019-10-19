//
// Created by Christian Ledgard on 10/18/19.
//

#ifndef GRAPHS_LUISPARAADA_CGRAPH_H
#define GRAPHS_LUISPARAADA_CGRAPH_H

#include <vector>
#include "ENode.h"
#include <map>

class Graph
{
    // Function to allocate new node of Adjacency List
    Node* getAdjListNode(int value, double weight, Node* head)
    {
        Node* newNode = new Node;
        newNode->val = value;
        newNode->cost = weight;

        // point new node to current head
        newNode->next = head;

        return newNode;
    }
    int N;  // number of nodes in the graph


public:
    // An array of pointers to Node to represent
    // adjacency list
    std::map<int, Node*> AdjacencyList;
    //Node **head;

    // Constructor

    Graph(Edge edges[], int n, int N)
    {
        // allocate memory
        //head = new Node*[N]();
        this->N = N;

        // initialize head pointer for all vertices
        /*for (int i = 0; i < N; ++i)
            head[i] = nullptr;*/

        // add edges to the directed graph
        for (unsigned i = 0; i < n; i++)
        {
            int src = edges[i].src;
            int dest = edges[i].dest;
            int weight = edges[i].weight;

            // insert in the beginning
            Node* newNode = getAdjListNode(dest, weight, AdjacencyList[i]);
            // point head pointer to new node
            AdjacencyList[src] = newNode;

        }
    }


    Graph(std::vector<Edge*> ptrVec, int N)
    {
        // allocate memory
        //head = new Node*[N]();
        this->N = N;

        // initialize head pointer for all vertices
        /*for (int i = 0; i < N; ++i)
            head[i] = nullptr;
        */
        // add edges to the directed graph
        for (auto &elem :ptrVec) {
            int src = elem->src;
            int dest = elem->dest;
            double weight = elem->weight;

            // insert in the beginning

            Node* newNode = getAdjListNode(dest, weight, AdjacencyList[src]);
            // point head pointer to new node
            AdjacencyList[src] = newNode;
        }
    }



    // Destructor
    ~Graph() {
        /*for (int i = 0; i < N; i++)
            delete[] head[i];

        delete[] head;
        */
         }
};

#endif //GRAPHS_LUISPARAADA_CGRAPH_H
