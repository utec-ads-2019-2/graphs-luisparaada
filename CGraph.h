//
// Created by Christian Ledgard on 10/18/19.
//

#ifndef GRAPHS_LUISPARAADA_CGRAPH_H
#define GRAPHS_LUISPARAADA_CGRAPH_H

#include <map>
#include <algorithm>
#include <vector>
#include "ENode.h"
#include "HaversineEquation.h"
#include "rapidjson/document.h" //JSON Compatibility

class Graph
{
protected:
    std::map<tipoEntero, Node*> AdjacencyList;

    unsigned long numberNodes;
    unsigned long numberEdges;

public:
    Graph() {
        numberEdges=numberNodes=0;
    }

    void insert_Node(tipoEntero x, tipoEntero y, tipoID id){
        if(AdjacencyList.find(id)==AdjacencyList.end()){
            AdjacencyList[id] = new Node(x, y, id);
            numberNodes++;
        }else{
            std::cout<<"este nodo ya existe"<<std::endl;
        }
    }

    virtual void insert_Edge(tipoEntero idto,tipoEntero idfrom,tipoDouble weight) = 0;

    long double getDensity(){
        long double e = numberEdges/1.;
        long double n = numberNodes/1.;
        return e/(n*(n-1.0));
    }

    void printAdjecentList(){
        for (auto  it : AdjacencyList)
        {
            // print all neighboring vertices of vertex i
            for (auto iter=(it.second)->vector_de_edges.begin();iter!=it.second->vector_de_edges.end();iter++)
            {
                std::cout << "(" << it.first << ", " << iter->idto
                          << ", " << iter->weight << ") ";
            }

            std::cout << std::endl;
        }
    }

    unsigned long getNumberNodes() const {
        return numberNodes;
    }

    unsigned long getNumberEdges() const {
        return numberEdges;
    }

    std::vector<int> get_nodes(){
        std::vector<int> retorno;
        for (auto it:AdjacencyList){
            retorno.push_back(it.first);
        }
        return retorno;
    }



    void clear(){
        for(auto it : AdjacencyList){
            it.second->vector_de_edges.clear();

        }
        AdjacencyList.clear();
        numberNodes = numberEdges = 0;
    }




    virtual ~Graph() {
        clear();
    }

};

class DirectedGraph : public Graph
{
public:
/*    DirectedGraph(Edge2 edges[], unsigned long n, unsigned long numberNodes)//TODO
    {
        // allocate memory
        //head = new Edge*[numberNodes]();
        this->numberNodes = numberNodes;

        // initialize head pointer for all vertices
        *//*for (int i = 0; i < numberNodes; ++i)
            head[i] = nullptr;*//*

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
    }*/

/*    DirectedGraph(const std::vector<Edge2*>& ptrVec)//TO DO
    {
        numberEdges = 0;
        for(auto &elem :ptrVec)
            insert(elem->src, elem->dest, elem->weight);

    }*/


    explicit DirectedGraph(const rapidjson::Document& d) {
        numberEdges=numberNodes=0;

        std::map<tipoID, std::pair<tipoDouble, tipoDouble>> coordenates;

        for(auto itr = d.Begin(); itr != d.End() ; ++itr){
            if (itr->HasMember("Id")) {
                auto id = (*itr)["Id"].GetString();
                std::string latitude = (*itr)["Latitude"].GetString();
                std::string longitude = (*itr)["Longitude"].GetString();

                insert_Node(std::stod(latitude), std::stod(longitude), std::stoi(id));

                coordenates[std::stoi(id)] = std::make_pair(std::stod(latitude),std::stod(longitude));

            } else {
                throw std::invalid_argument( "NO existe el campo Id en un objeto del JASON" );
            }
        }

        for(auto itr = d.Begin(); itr != d.End() ; ++itr){
            if (itr->HasMember("Id")) {
                tipoID idFrom = std::stoi((*itr)["Id"].GetString());

                const rapidjson::Value& a = (*itr)["destinations"];
                for (rapidjson::SizeType i = 0; i < a.Size(); i++){
                    tipoID idTo = std::stoi(a[i].GetString());
                    tipoDouble weight = getDistanceFromCoordenatesHaversine(coordenates[idFrom].first,coordenates[idFrom].second,coordenates[idTo].first,coordenates[idTo].second);

                    insert_Edge(idTo,idFrom,weight);
                }
            } else {
                throw std::invalid_argument( "NO existe el campo Id en un objeto del JASON" );
            }
        }

    }



    void insert_Edge(tipoEntero idto,tipoEntero idfrom,tipoDouble weight) override{
        if (AdjacencyList.find(idfrom)==AdjacencyList.end() or AdjacencyList.find(idto)==AdjacencyList.end()){
            std::cout<<"nodo inicial y/o final no existen"<<std::endl;
        }else{
            AdjacencyList[idfrom]->vector_de_edges.emplace_back(AdjacencyList[idfrom],AdjacencyList[idto],weight,idfrom,idto);
            //std::cout<<"edge creado"<<std::endl;
        }
        numberEdges++;
    }


    void delete_Node(tipoEntero val) {
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

    void remove_Edge(tipoEntero idfrom, tipoEntero idto){
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
    bool know_if_convex(){
        auto vector=get_nodes();
        for (auto it:AdjacencyList){
            std::cout<<"hola"<<std::endl;
            if(!deapth_search(it.second,vector)){
                return false;
            }
        }
        return true;
    }

    bool deapth_search(Node* nodo,std::vector<tipoEntero > &missing){
        std::vector<tipoEntero > checked;
        checked.push_back(nodo->id);
        int contador=0;
        int limit=checked.size();
        while (contador<limit){
            std::cout<<"checking"<<checked[contador]<<std::endl;
            Node* temporal=AdjacencyList[checked[contador]];
            for (auto it2=temporal->vector_de_edges.begin();it2!=temporal->vector_de_edges.end();it2++){
                auto temporal2=std::find(checked.begin(),checked.end(),it2->idto);
                std::cout<<"edge: "<<it2->idfrom<<" to "<<it2->idto<<std::endl;
                if (temporal2!=checked.end()){
                    continue;
                }else{
                    std::cout<<"added "<<it2->idto<<std::endl;
                    checked.push_back(it2->idto);
                }
            }
            limit=checked.size();
            contador++;
        }
        if(checked.size()!= missing.size()){
            return false;
        }else{
            std::sort(checked.begin(),checked.end());
            return checked == missing;
        }
    }



};


class UndirectedGraph : public Graph
{
private:
    std::vector<SimpleEdge> sortedEdges;


public:


    void insert_Edge(tipoEntero id1, tipoEntero id2, tipoDouble weight) override{
        if ((AdjacencyList.find(id2) == AdjacencyList.end() or AdjacencyList.find(id1) == AdjacencyList.end())or(AdjacencyList.find(id1) == AdjacencyList.end() or AdjacencyList.find(id2) == AdjacencyList.end())){
            std::cout<<"nodo inicial y/o final no existen"<<std::endl;
        }else{
            AdjacencyList[id2]->vector_de_edges.emplace_back(AdjacencyList[id2], AdjacencyList[id1], weight, id2, id1);
            //AdjacencyList[id1]->vector_de_edges.emplace_back(AdjacencyList[id1], AdjacencyList[id2], weight, id1, id2);
        }
        numberEdges++;
    }


    void sortByWeight(){
        for (auto  it : AdjacencyList)
        {
            // print all neighboring vertices of vertex i
            for (auto iter=(it.second)->vector_de_edges.begin();iter!=it.second->vector_de_edges.end();iter++)
            {
                sortedEdges.emplace_back(iter->weight,it.first,iter->idto);
            }
        }
        std::sort(sortedEdges.begin(), sortedEdges.end(), [](const SimpleEdge &a, const SimpleEdge &b) -> bool {return a.weight < b.weight;});
    }

    static tipoDouble findinSubset(subset subsets[], int i){
        if(subsets[i].parent != i)
            subsets[i].parent = findinSubset(subsets,subsets[i].parent);
        return subsets[i].parent;
    }

    static void Union(subset subsets[], tipoDouble x, tipoDouble y) {
        int xroot = findinSubset(subsets, x);
        int yroot = findinSubset(subsets, y);

        if(subsets[xroot].rank < subsets[yroot].rank)
            subsets[xroot].parent = yroot;
        else if (subsets[xroot].rank > subsets[yroot].rank)
            subsets[yroot].parent = xroot;
        else{
            subsets[yroot].parent = xroot;
            subsets[xroot].rank++;
        }

    }

    std::vector<SimpleEdge> kruskal(){
        std::vector<SimpleEdge> result;
        auto kruskalResult = new SimpleEdge[numberNodes];
        int indexEdges = 0, indexSorted = 0;

        sortByWeight();

        auto *subsets = new subset[numberNodes];

        for (int i = 0; i < numberNodes; ++i) {
            subsets[i].parent = i;
            subsets[i].rank = 0;
        }

        while(indexEdges < numberNodes-1 and indexSorted < numberEdges){

            SimpleEdge nextEdge = sortedEdges[indexSorted++];

            tipoDouble x = findinSubset(subsets, nextEdge.idfrom);
            tipoDouble y = findinSubset(subsets, nextEdge.idto);

            if(x != y){
                kruskalResult[indexEdges] = nextEdge;
                result.emplace_back(kruskalResult[indexEdges].weight,kruskalResult[indexEdges].idfrom,kruskalResult[indexEdges].idto);
                ++indexEdges;
                Union(subsets, x, y);
            }
        }
        return result;
    }






};


#endif //GRAPHS_LUISPARAADA_CGRAPH_H
