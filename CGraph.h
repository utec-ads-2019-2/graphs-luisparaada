//
// Created by Christian Ledgard on 10/18/19.
//

#ifndef GRAPHS_LUISPARAADA_CGRAPH_H
#define GRAPHS_LUISPARAADA_CGRAPH_H

#include <vector>
#include "ENode.h"
#include <map>

void printList(Node* ptr, int i);

class Graph
{
private:
    // Function to allocate new node of Adjacency List
    static Node* getAdjListNode(tipoEntero value, tipoWeight weight, Node* head)
    {
        Node* newNode = new Node(value, weight, head);
        return newNode;
    }

    size_t N;  // number of nodes in the graph

public:
    // An array of pointers to Node to represent
    // adjacency list
    std::map<tipoEntero, Node*> AdjacencyList;
    //Node **head;

    Graph(Edge edges[], size_t n, size_t N)
    {
        // allocate memory
        //head = new Node*[N]();
        this->N = N;

        // initialize head pointer for all vertices
        /*for (int i = 0; i < N; ++i)
            head[i] = nullptr;*/

        // add edges to the directed graph
        for (size_t i = 0; i < n; i++)
        {
            tipoEntero src = edges[i].src;
            tipoEntero dest = edges[i].dest;
            tipoWeight weight = edges[i].weight;

            // insertEdges in the beginning
            Node* newNode = getAdjListNode(dest, weight, AdjacencyList[i]);
            // point head pointer to new node
            AdjacencyList[src] = newNode;

        }
    }

    Graph(const std::vector<Edge*>& ptrVec, size_t N)
    {
<<<<<<< Updated upstream
        // allocate memory
        //head = new Node*[N]();
        this->N = N;
=======
        numberEdges = 0;
        for(auto &elem :ptrVec)
            insertEdges(elem->src, elem->dest, elem->weight);
>>>>>>> Stashed changes

        // initialize head pointer for all vertices
        /*for (int i = 0; i < N; ++i)
            head[i] = nullptr;
        */
        // add edges to the directed graph
        for (auto &elem :ptrVec)
            insert(elem->src, elem->dest, elem->weight);
    }

    void insertEdges(tipoEntero src, tipoEntero dest, tipoWeight weight){
        // insertEdges in the beginning
        Node* newNode = getAdjListNode(dest, weight, AdjacencyList[src]);
        // point head pointer to new node
        AdjacencyList[src] = newNode;
    }

    void removeEdges(tipoEntero src, tipoEntero dest){
        Node* temp = AdjacencyList[src];
        Node* prev = nullptr;

        if(temp != nullptr and temp->val == dest){
            AdjacencyList[src] = nullptr;
            AdjacencyList.erase(src);
            delete temp;
            return;
        }

        while(temp!= nullptr and temp->val != dest){
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) return;
        if(prev != nullptr)
            prev->next = temp->next;
        delete temp;

    }

    void clear(){
        for(auto &it : AdjacencyList){
            Node* current = it.second;
            Node* next = nullptr;

            while(current != nullptr){
                next = current->next;
                delete current;
                current = next;
            }
            it.second = nullptr;
        }
        AdjacencyList.clear();
    }

    void printAdjecentList(){
        for (auto & it : AdjacencyList)
        {
            // print all neighboring vertices of vertex i
            printList(it.second, it.first);
        }
    }


    // Destructor
    virtual ~Graph() {
        clear();
    }
};

// print all neighboring vertices of given vertex
void printList(Node* ptr, int i)
{
    while (ptr != nullptr)
    {
        std::cout << "(" << i << ", " << ptr->val
             << ", " << ptr->cost << ") ";

        ptr = ptr->next;
    }

    std::cout << std::endl;
}

#endif //GRAPHS_LUISPARAADA_CGRAPH_H
