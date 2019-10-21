//
// Created by Christian Ledgard on 10/18/19.
//

#ifndef GRAPHS_LUISPARAADA_CGRAPH_H
#define GRAPHS_LUISPARAADA_CGRAPH_H

#include <vector>
#include "ENode.h"
#include <map>

void printList(Node* ptr, int i);

class DirectedGraph
{
private:
    std::map<tipoEntero, Node*> AdjacencyList;

    unsigned long numberNodes;
    unsigned long numberEdges;

    // Function to allocate new node of Adjacency List
    Node* getAdjListNode(tipoEntero value, tipoWeight weight, Node* head)
    {
        Node* newNode = new Node(value, weight, head);
        //test++;
        return newNode;
    }


public:
    // An array of pointers to Node to represent
    // adjacency list
    //Node **head;
    unsigned long getNumberNodes() const {
        return numberNodes;
    }

    unsigned long getNumberEdges() const {
        return numberEdges;
    }


    DirectedGraph(Edge edges[], unsigned long n, unsigned long numberNodes)
    {
        // allocate memory
        //head = new Node*[numberNodes]();
        this->numberNodes = numberNodes;

        // initialize head pointer for all vertices
        /*for (int i = 0; i < numberNodes; ++i)
            head[i] = nullptr;*/

        // add edges to the directed graph
        for (unsigned long i = 0; i < n; i++){
            tipoEntero src = edges[i].src;
            tipoEntero dest = edges[i].dest;
            tipoWeight weight = edges[i].weight;

            // insert in the beginning
            Node* newNode = getAdjListNode(dest, weight, AdjacencyList[i]);
            // point head pointer to new node
            AdjacencyList[src] = newNode;
        }
    }

    DirectedGraph(const std::vector<Edge*>& ptrVec)
    {
        numberEdges = 0;
        for(auto &elem :ptrVec)
            insert(elem->src, elem->dest, elem->weight);

    }

    void insert(tipoEntero src, tipoEntero dest, tipoWeight weight){
        // insert in the beginning
        Node* newNode = getAdjListNode(dest, weight, AdjacencyList[src]);
        // point head pointer to new node
        AdjacencyList[src] = newNode;
        numberNodes = AdjacencyList.size();
        numberEdges++;
    }

    void remove(tipoEntero src, tipoEntero dest){
        Node* temp = AdjacencyList[src];
        Node* prev = nullptr;

        if(temp != nullptr and temp->val == dest){
            AdjacencyList[src] = temp->next;
            delete temp;

        } else {

            while(temp!= nullptr and temp->val != dest){
                prev = temp;
                temp = temp->next;
            }
            if (temp == nullptr) return;
            if(prev != nullptr)
                prev->next = temp->next;
            delete temp;
        }

        if(AdjacencyList[src] == nullptr){
            AdjacencyList.erase(src);
            --numberNodes;
        }
        numberEdges--;
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
        numberNodes = numberEdges = 0;
    }

    void printAdjecentList(){
        for (auto & it : AdjacencyList)
        {
            // print all neighboring vertices of vertex i
            printList(it.second, it.first);
        }
    }



    long double getDensity(){
        long double e = numberEdges/1.;
        long double n = numberNodes/1.;
        return e/(n*(n-1.0));
    }

    // Destructor
    virtual ~DirectedGraph() {
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
