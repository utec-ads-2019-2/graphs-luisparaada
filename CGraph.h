//
// Created by Christian Ledgard on 10/18/19.
//

#ifndef GRAPHS_LUISPARAADA_CGRAPH_H
#define GRAPHS_LUISPARAADA_CGRAPH_H


#include "ENode.h"
#include <map>
#include <algorithm>
void printList(Node* ptr, int i);

class DirectedGraph
{
private:
    std::map<tipoEntero, Node*> AdjacencyList;

    unsigned long numberNodes;
    unsigned long numberEdges;

    // Function to allocate new node of Adjacency List
    Edge* getAdjListNode(tipoEntero value, tipoDouble weight, Edge* head)//TO DO
    {
        Edge* newNode = new Edge(value, weight, head);
        //test++;
        return newNode;
    }


public:
    // An array of pointers to Edge to represent
    // adjacency list
    //Edge **head;
    unsigned long getNumberNodes() const {
        return numberNodes;
    }

    unsigned long getNumberEdges() const {
        return numberEdges;
    }


    DirectedGraph(Edge2 edges[], unsigned long n, unsigned long numberNodes)//TODO
    {
        // allocate memory
        //head = new Edge*[numberNodes]();
        this->numberNodes = numberNodes;

        // initialize head pointer for all vertices
        /*for (int i = 0; i < numberNodes; ++i)
            head[i] = nullptr;*/

        // add edges to the directed graph
        for (unsigned long i = 0; i < n; i++){
            tipoEntero src = edges[i].src;
            tipoEntero dest = edges[i].dest;
            tipoDouble weight = edges[i].weight;

            // insert in the beginning
            Edge* newNode = getAdjListNode(dest, weight, AdjacencyList[i]);
            // point head pointer to new node
            AdjacencyList[src] = newNode;
        }
    }

    DirectedGraph(const std::vector<Edge2*>& ptrVec)//TO DO
    {
        numberEdges = 0;
        for(auto &elem :ptrVec)
            insert(elem->src, elem->dest, elem->weight);

    }

    void insert_Edge(tipoEntero idto,tipoEntero idfrom,tipoDouble weight){
        if (AdjacencyList.find(idfrom)==AdjacencyList.end() or AdjacencyList.find(idto)==AdjacencyList.end()){
            std::cout<<"nodo inicial y/o final no existen"<<std::endl;
        }else{
            AdjacencyList[idfrom]->vector_de_edges.emplace_back(new Edge(AdjacencyList[idfrom],AdjacencyList[idto],weight,idfrom,idto));
            std::cout<<"edge creado"<<std::endl;
        }
        numberEdges++;
    }

    void insert_node(tipoEntero x, tipoEntero y, int id){
        if(AdjacencyList.find(id)==AdjacencyList.end()){
            AdjacencyList[id] = new Node(x, y, id);
            numberNodes++;
        }else{
            std::cout<<"este nodo ya existe"<<std::endl;
        }
    }

    void delete_node(tipoEntero val) {
        if (AdjacencyList.find(val) != AdjacencyList.end()) {


            for (auto it = AdjacencyList.begin(); it != AdjacencyList.end(); it++) {
                if (it->first == val) {
                    continue;
                } else {
                    auto temp = it->second->vector_de_edges;
                    for (auto it2 = temp.begin(); it2 != temp.end(); it2++) {
                        if (it2->idto == val) {
                            temp.erase(it2);
                            numberEdges--;// se remueven los edges de todos los nodos que apuntan al que queremos eliminar y se disminuye en 1 cada vez que se hace esto

                            break;
                        }
                    }

                }
            }
            auto temporal = AdjacencyList[val];
            numberEdges -= temporal->vector_de_edges.size(); //se disminuye una cantidad N que es el size de los edges que contenia el nodo que se quiere eliminar
            temporal->vector_de_edges.clear();
            AdjacencyList.erase(val);
            numberNodes--; // se elimina el nodo y se disminuye en 1 el contador;
            std::cout << "nodo eliminado" << std::endl;
        }else{
            std::cout<<"nodo no encontrado"<<std::endl;
        }

    }

    void remove_edge(tipoEntero idfrom, tipoEntero idto){
        if (AdjacencyList.find(idfrom)==AdjacencyList.end()){
            std::cout<<"No existe el nodo from"<<std::endl;
        }else{
            if(AdjacencyList[idfrom]->vector_de_edges.empty()){
                std::cout<<"no hay ningun edge en el nodo from"<<std::endl;

            }else{
                for (auto it=AdjacencyList[idfrom]->vector_de_edges.begin();it!=AdjacencyList[idfrom]->vector_de_edges.end();it++){
                    if (it->idto==idto){
                        AdjacencyList[idfrom]->vector_de_edges.erase(it);
                        numberEdges--;
                        std::cout<<"edge removido"<<std::endl;
                        return;
                    }
                }
                std::cout<<"edge no encontrado"<<std::endl;

            }
        }

    }

    void clear(){
        for(auto it : AdjacencyList){
            it.second->vector_de_edges.clear();

        }
        AdjacencyList.clear();
        numberNodes = numberEdges = 0;
    }

    void printAdjecentList(){
        for (auto  it : AdjacencyList)
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
    for (auto it=ptr->vector_de_edges.begin();it!=ptr->vector_de_edges.end();it++)
    {
        std::cout << "(" << i << ", " << it->idto
             << ", " << it->weight << ") ";
    }

    std::cout << std::endl;
}

#endif //GRAPHS_LUISPARAADA_CGRAPH_H
