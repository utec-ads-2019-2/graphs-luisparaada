//
// Created by Christian Ledgard on 10/18/19.
//

#ifndef GRAPHS_LUISPARAADA_CGRAPH_H
#define GRAPHS_LUISPARAADA_CGRAPH_H


#include "ENode.h"
#include <map>

void printList(Edge* ptr, int i);

class DirectedGraph
{
private:
    std::map<tipoEntero, Node*> AdjacencyList;

    unsigned long numberNodes;
    unsigned long numberEdges;

    // Function to allocate new node of Adjacency List
    Edge* getAdjListNode(tipoEntero value, tipoDouble weight, Edge* head)
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


    DirectedGraph(Edge2 edges[], unsigned long n, unsigned long numberNodes)
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

    DirectedGraph(const std::vector<Edge2*>& ptrVec)
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

    void delete_node(tipoEntero val){
        for (auto it=AdjacencyList.begin();it!=AdjacencyList.end();it++){
            if (it->first==val){
                continue;
            }else {
                std::cout<<"WTF"<<std::endl;
                auto temporal = it->second;
                if(temporal->next==nullptr && temporal->val==val){
                    AdjacencyList[val]=nullptr;
                    delete temporal;
                    continue;
                }
                if (temporal->next!=nullptr &&temporal->val==val){
                    AdjacencyList[val]=temporal->next;
                    delete temporal;
                    continue;
                }
                Edge* temporal2=temporal->next;
                while (temporal2!= nullptr) {
                    if (temporal2->val==val){
                        temporal->next=temporal2->next;
                        delete temporal2;
                        break;
                    }else{
                        temporal=temporal2;
                        temporal2=temporal2->next;
                    }
                    std::cout<<"WTF"<<std::endl;

                }
            }
        }
        auto temporal =AdjacencyList[val]->next;
        while (temporal!=nullptr){
            auto temporal2= temporal->next;
            delete temporal;
            temporal=temporal2;
        }
        AdjacencyList.erase(val);
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
                        std::cout<<"edge removido"<<std::endl;
                        return;
                    }
                }
                std::cout<<"edge no encontrado"<<std::endl;

            }
        }

    }

    void clear(){
        for(auto &it : AdjacencyList){
            Edge* current = it.second;
            Edge* next = nullptr;

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
void printList(Edge* ptr, int i)
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
