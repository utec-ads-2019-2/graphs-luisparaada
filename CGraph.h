//
// Created by Christian Ledgard on 10/18/19.
//

#ifndef GRAPHS_LUISPARAADA_CGRAPH_H
#define GRAPHS_LUISPARAADA_CGRAPH_H

#include <map>
#include <algorithm>
#include <vector>
#include <stack>
#include "ENode.h"
#include "HaversineEquation.h"
#include "rapidjson/document.h"
#include <queue>
//JSON Compatibility
bool check_nodos_prioridad(int node,std::vector< int> prioridades);
int get_last_value_of_id(int node, std::vector<nodo_dijkstra>& prioridades);
int get_index_with_node(int node,std::vector<int> vector2);
void delete_every_repeated(std::vector<int>usados,std::vector<nodo_prioridad>& priorityqeue);
using namespace std;
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
    int get_weight(int idfrom,int idto ){
        auto temp=AdjacencyList[idfrom]->vector_de_edges;
        for (auto it:temp){
            if (it.idto==idto){
                int temporal=it.weight;
                return temporal;
            }
        }
        return -1;
    }

    std::vector<int> get_nodes(){
        std::vector<int> retorno;
        for (auto it:AdjacencyList){
            retorno.push_back(it.first);
        }
        return retorno;
    }
    //used for the convex function
        bool BFS(Node* nodo,std::vector<tipoEntero > &missing){
        std::vector<tipoEntero > checked;
        checked.push_back(nodo->id);
        int contador=0;
        int limit=checked.size();
        while (contador<limit){
            //std::cout<<"checking"<<checked[contador]<<std::endl;
            Node* temporal=AdjacencyList[checked[contador]];
            for (auto it2=temporal->vector_de_edges.begin();it2!=temporal->vector_de_edges.end();it2++){
                auto temporal2=std::find(checked.begin(),checked.end(),it2->idto);
                //std::cout<<"edge: "<<it2->idfrom<<" to "<<it2->idto<<std::endl;
                if (temporal2!=checked.end()){
                    continue;
                }else{
                    //std::cout<<"added "<<it2->idto<<std::endl;
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
    //used for the real deapth search
    std::vector<Edge> BFS(int nodo){
        std::vector<tipoEntero > checked;
        auto missing=get_nodes();
        std::vector<Edge> retorno;
        checked.push_back(nodo);
        int contador=0;
        int limit=checked.size();
        while (contador<limit){
            //std::cout<<"checking"<<checked[contador]<<std::endl;
            Node* temporal=AdjacencyList[checked[contador]];
            for (auto it2=temporal->vector_de_edges.begin();it2!=temporal->vector_de_edges.end();it2++){
                auto temporal2=std::find(checked.begin(),checked.end(),it2->idto);
                //std::cout<<"edge: "<<it2->idfrom<<" to "<<it2->idto<<std::endl;
                if (temporal2!=checked.end()){
                    continue;
                }else{
                    //std::cout<<"added "<<it2->idto<<std::endl;
                    checked.push_back(it2->idto);
                    retorno.emplace_back(Edge(it2->from,it2->to,it2->weight,it2->idfrom,it2->idto));
                }
            }
            limit=checked.size();
            contador++;
        }
        if(checked.size()!= missing.size()){
            std::vector<Edge> nulo;
            return nulo;
        }else{
            std::sort(checked.begin(),checked.end());
            return retorno;
        }
    }

    void deepen(int nodo,std::vector<Edge>& retorno, std::map<int,bool>& marcados){
        marcados[nodo]=true;
        for (auto it:AdjacencyList[nodo]->vector_de_edges){
            if (!marcados[it.idto]){
                retorno.emplace_back(Edge(AdjacencyList[nodo],AdjacencyList[it.idto],it.weight,it.idfrom,it.idto));
                deepen(it.idto,retorno,marcados);
            }
        }


    }

    std::vector<Edge> DFS(int node){
        std::vector<int> missing=get_nodes();
        std::vector<Edge> retorno;
        std::map<int,bool> marcados;
        for (auto it:missing ){
            marcados[it]=false;
        }
        deepen(node,retorno,marcados);
        std::cout<<"HOLA"<<std::endl;
        if (retorno.size()!=missing.size()-1){
            std::cout<<missing.size()<<std::endl;
            std::cout<<retorno.size()<<std::endl;
            for (auto it:retorno){
                std::cout<<"("<<it.idfrom<<" "<<it.idto<<", "<<it.weight<<") "<<std::endl;
            }
            retorno.clear();
            std::cout<<"BFS did not work"<<std::endl;
            return retorno;
        }else{
            return retorno;
        }

    }


    std::vector<Edge> Dijkstra(int node) {
        auto vector2=get_nodes();
        int** matriz;
        vector<int> orden;
        vector<int> usados;
        vector<nodo_prioridad> priority_qeue;
        matriz=new int*[vector2.size()];
        for (int i=0;i<vector2.size();i++){
            matriz[i]=new int[vector2.size()];
            for (int j=0;j<vector2.size();j++){
                matriz[i][j]=-1;
            }
        }
        usados.push_back(node);
        for (int i=0;i<vector2.size();i++){
            matriz[0][i]=get_weight(usados[0],vector2[i]);
            if (get_weight(usados[0],vector2[i])!=-1){
                priority_qeue.emplace_back(nodo_prioridad(node,vector2[i],get_weight(usados[0],vector2[i])));
            }
        }

        int contador=0;
        while (!priority_qeue.empty() ){
            int contador2=0;
            nodo_prioridad a=priority_qeue[0];
            for (int i=0;i<priority_qeue.size();i++ ){
                if (priority_qeue[i].costo<a.costo && check_nodos_prioridad(priority_qeue[i].idto,usados)){
                    a=priority_qeue[i];
                    contador2=i;
                }
            }
            cout<<"CHECKING"<<endl;
            cout<<a.idfrom<<" "<<a.idto<<" "<<a.costo<<endl;
            usados.push_back(a.idto);
            for (auto it:usados){
                cout<<it<<" "<<endl;
            }
            for (int i=0;i<vector2.size();i++){
                if (matriz[contador][i]==-1 && get_weight(a.idto,vector2[i])){
                    matriz[contador+1][i]=get_weight(a.idto,vector2[i]);
                }else{
                    if (matriz[contador][i]!=-1 && get_weight(a.idto,vector2[i])+matriz[contador][get_index_with_node(a.idto,vector2)]<matriz[contador][i]  &&get_weight(a.idto,vector2[i])!=-1){
                        matriz[contador+1][i]=get_weight(a.idto,vector2[i])+matriz[contador][get_index_with_node(a.idto,vector2)]<matriz[contador][i];
                        cout<<"LLEGO ACA con i="<<i<<endl;
                    }else{
                        matriz[contador+1][i]=matriz[contador][i];

                    }
                }
            }
            for(auto it:AdjacencyList[a.idto]->vector_de_edges){
                if (!check_nodos_prioridad(it.idto,usados)){
                    priority_qeue.emplace_back(nodo_prioridad(it.idfrom,it.idto,it.weight));
                }
            }
            delete_every_repeated(usados,priority_qeue);
            contador++;

        }
        for (int i=0;i<vector2.size();i++){
            for (int j=0;j<vector2.size();j++){
                cout<<matriz[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"NOW PARENTS"<<endl;
        for (auto it:orden){
            cout<<it<<" ";
        }cout<<endl;
        cout<<"now retorno"<<endl;
        std::vector<Edge> retorno;
        if (is_bidirectional()){
            for (int i=1;i<orden.size();i++){
                retorno.emplace_back(Edge(AdjacencyList[vector2[i]],AdjacencyList[orden[i]],get_weight( vector2[i],orden[i]),vector2[i],orden[i]));
                retorno.emplace_back(Edge(AdjacencyList[orden[i]],AdjacencyList[vector2[i]],get_weight( vector2[i],orden[i]),orden[i],vector2[i]));
            }
        }else{
            for (int i=1;i<orden.size();i++){
                retorno.emplace_back(Edge(AdjacencyList[orden[i]],AdjacencyList[vector2[i]],get_weight( orden[i],vector2[i]),orden[i],vector2[i]));
            }
        }
        for (auto it:retorno){
            cout<<"( "<<it.idfrom<<", "<<it.idto<<", "<<it.weight<<")"<<endl;
        }
        return retorno;
    }


    std::pair <std::vector<std::vector<tipoDouble>>*,std::vector<std::vector<tipoDouble>>*>* FloydWarshall(){

        auto AdjencyMatrix = new std::vector<std::vector<tipoDouble>>(numberNodes, std::vector<tipoDouble>(numberNodes, 0.0));

        for (auto  it : AdjacencyList)
            for (auto iter=(it.second)->vector_de_edges.begin();iter!=it.second->vector_de_edges.end();iter++)
                (*AdjencyMatrix)[(iter->idto) - 1][(it.first) - 1] = iter->weight;


        auto distanceMatrix = new std::vector<std::vector<tipoDouble>>(numberNodes, std::vector<tipoDouble>(numberNodes, 0.0));
        auto secuenceMatrix = new std::vector<std::vector<tipoDouble>>(numberNodes, std::vector<tipoDouble>(numberNodes, 0.0));

        for (int l = 0; l < numberNodes; ++l)
            for (int i = 0; i < numberNodes; ++i)
                (*distanceMatrix)[l][i] = (*AdjencyMatrix)[l][i];


        for (int k = 0; k < numberNodes; ++k)
            for (int i = 0; i < numberNodes; ++i)
                if((*distanceMatrix)[k][i] == 0 and k != i)
                    (*distanceMatrix)[k][i] = MAXFLOAT;
                else if(k == i) //DIAGONAL = 0 POR PROPIEDAD
                    (*distanceMatrix)[k][i] = 0.0;

        for (int n = 0; n < numberNodes; ++n)
            for (int i = 0; i < numberNodes; ++i)
                if(n == i) //DIAGONAL = 0 POR PROPIEDAD
                    (*secuenceMatrix)[n][i] = 0.0;
                else
                    (*secuenceMatrix)[n][i] = i + 1;


        for (int k = 0; k < numberNodes; ++k)
            for (int i = 0; i < numberNodes; ++i)
                for (int j = 0; j < numberNodes; ++j)
                    if((*distanceMatrix)[i][k] + (*distanceMatrix)[k][j] < (*distanceMatrix)[i][j]){
                        (*distanceMatrix)[i][j] = (*distanceMatrix)[i][k] + (*distanceMatrix)[k][j];
                        (*secuenceMatrix)[i][j] = k + 1;
                    }


        cout <<"Matriz de Distancias de los Caminos más Cortos" << endl;


        for (int m = 0; m < numberNodes; ++m) {
            for (int i = 0; i < numberNodes; ++i) {
                cout << (*distanceMatrix)[m][i] << " ";
            }
            cout << endl;
        }

        cout <<"Matriz de Secuencia" << endl;

        for (int m = 0; m < numberNodes; ++m) {
            for (int i = 0; i < numberNodes; ++i) {
                cout << (*secuenceMatrix)[m][i] << " ";
            }
            cout << endl;
        }

        auto result = new pair<std::vector<std::vector<tipoDouble>>*,std::vector<std::vector<tipoDouble>>*>;
        result->first = distanceMatrix;
        result->second = secuenceMatrix;


        return result;
    }

    vector<SimpleEdge> BellmanFord(int startNode, int endNode){
        //map<tipoEntero,tipoDouble> distanceOfNodes;

        map<tipoEntero,pair<tipoDouble,pair<tipoDouble,tipoDouble>>> distanceOfNodesWithPrev;


        for (auto  &it : AdjacencyList){
            distanceOfNodesWithPrev[it.first].first = MAXFLOAT;
        }

        //distanceOfNodes[startNode] = 0;
        distanceOfNodesWithPrev[startNode] = make_pair(0, make_pair(startNode,0));

        for (int j = 0; j < numberNodes - 1 ; ++j)
            for (auto  it : AdjacencyList)
                for (auto iter=(it.second)->vector_de_edges.begin();iter!=it.second->vector_de_edges.end();iter++)
                    if (distanceOfNodesWithPrev[iter->idto].first != MAXFLOAT && distanceOfNodesWithPrev[iter->idto].first + iter->weight < distanceOfNodesWithPrev[it.first].first){
                        distanceOfNodesWithPrev[it.first].first = distanceOfNodesWithPrev[iter->idto].first + iter->weight;
                        distanceOfNodesWithPrev[it.first].second.first = iter->idto;
                        distanceOfNodesWithPrev[it.first].second.second = iter->weight;
                    }


        for (auto  it : AdjacencyList)
            for (auto iter=(it.second)->vector_de_edges.begin();iter!=it.second->vector_de_edges.end();iter++)
                if (distanceOfNodesWithPrev[iter->idto].first != MAXFLOAT && distanceOfNodesWithPrev[iter->idto].first + iter->weight < distanceOfNodesWithPrev[it.first].first)
                    throw std::invalid_argument("El grafo contiene ciclos negativos");



        for(auto &elemento : distanceOfNodesWithPrev){
            cout << "The distance from node " << startNode << " to node " << elemento.first << " is: " << distanceOfNodesWithPrev[elemento.first].first << endl;
            int currnode = elemento.first;
            cout << "The path is: " << currnode;
            while(currnode != startNode)
            {
                currnode = distanceOfNodesWithPrev[currnode].second.first;
                cout << " <- " << currnode;
            }
            cout << endl << endl;
        }

//        for (int i = 1; i <= distanceOfNodesWithPrev.size(); ++i) {
//            cout << "The distance from node " << startNode << " to node " << i << " is: " << distanceOfNodesWithPrev[i].first << endl;
//            int currnode = i;
//            cout << "The path is: " << currnode;
//            while(currnode != startNode)
//            {
//                currnode = distanceOfNodesWithPrev[currnode].second.first;
//                cout << " <- " << currnode;
//            }
//            cout << endl << endl;
//        }


        vector <tipoDouble> nodesShortPathTrail;
        vector<SimpleEdge> result;

        cout << "The distance from node " << startNode << " to node " << endNode << " is: " << distanceOfNodesWithPrev[endNode].first << endl;

        int prevnode = endNode;
        int currnode = prevnode;

        while(currnode != startNode)
        {
            currnode = distanceOfNodesWithPrev[currnode].second.first;
            result.emplace(result.begin(),distanceOfNodesWithPrev[prevnode].second.second,currnode,prevnode);
            prevnode = currnode;
        }

        return result;

    }

    tipoDouble calcularEuristica(Node a, Node b){
        return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
    }



    bool is_bidirectional(){
        for (auto it:AdjacencyList){
            for (auto it2:it.second->vector_de_edges){
                bool check=false;
                for (auto it3:AdjacencyList[it2.idto]->vector_de_edges){
                    if(it3.idto==it2.idfrom){
                        check=true;
                        break;
                    }
                }
                if ( !check){
                    return false;
                }
            }
        }
        return true;
    }

    bool isBipartite()
    {
        std::stack<Node*> stack1;
        std::stack<Node*> stack2;
        std::map<int,Node*>::iterator temporal;
        for (auto it2=AdjacencyList.begin();it2!=AdjacencyList.end();it2++){
            if(it2->second->vector_de_edges.size()!=0){
                temporal=it2;
                break;
            }
        }
        temporal->second->color=1;
        for (auto it=temporal->second->vector_de_edges.begin();it!=temporal->second->vector_de_edges.end();it++){
            it->to->color=2;
            stack1.push(it->to);
        }
        int colorear=1;
        //std::cout<<"HOLA"<<std::endl;
        while (!stack1.empty() ){
            auto temporal2=stack1.top();
            //std::cout<<stack1.top()->id<<" "<<stack1.top()->color<<std::endl;
            stack1.pop();
            for (auto it=temporal2->vector_de_edges.begin();it!=temporal2->vector_de_edges.end();it++){
                //std::cout<<"checkeando "<<it->idto<<" con color "<<it->to->color<<std::endl;
                if(it->to->color==colorear || it->to->color==0){
                    it->to->color=colorear;
                    //std::cout<<"el nodo "<<it->idto<<" tiene color "<<it->to->color<<std::endl;
                    if (it->to->color==0){
                        stack2.push(it->to);
                    }
                }else{
                    return false;
                }
            }
            if (stack1.empty()){
                auto temp=stack1;
                stack1=stack2;
                stack2=temp;
                if(colorear==1){
                    colorear=2;
                }else{
                    colorear=1;
                }
            }




        }

        return true;
    }

    bool is_convex(){
        auto vector=get_nodes();
        for (auto it:AdjacencyList){
            //std::cout<<"hola"<<std::endl;
            if(!BFS(it.second,vector)){
                return false;
            }
        }
        return true;
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

    DirectedGraph() {}
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


};


class UndirectedGraph : public Graph
{
private:
    std::vector<SimpleEdge> sortedEdges;

    void sortByWeight(){
        for (auto  it : AdjacencyList)
        {
            // print all neighboring vertices of vertex i
            for (auto iter=(it.second)->vector_de_edges.begin();iter!=it.second->vector_de_edges.end();iter++)
            {
                auto from = it.first;
                auto to = iter->idto;

                auto iterador = std::find_if(sortedEdges.begin(),sortedEdges.end(),[from,to](const SimpleEdge &a)-> bool{ return (from == a.idto) and (to == a.idfrom) ;});

                if(iterador == sortedEdges.end()){
                    sortedEdges.emplace_back(iter->weight,from,to);
                }
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


public:


    void insert_Edge(tipoEntero id1, tipoEntero id2, tipoDouble weight) override{
        if ((AdjacencyList.find(id2) == AdjacencyList.end() or AdjacencyList.find(id1) == AdjacencyList.end())or(AdjacencyList.find(id1) == AdjacencyList.end() or AdjacencyList.find(id2) == AdjacencyList.end())){
            std::cout<<"nodo inicial y/o final no existen"<<std::endl;
        }else{
            AdjacencyList[id2]->vector_de_edges.emplace_back(AdjacencyList[id2], AdjacencyList[id1], weight, id2, id1);
            AdjacencyList[id1]->vector_de_edges.emplace_back(AdjacencyList[id1], AdjacencyList[id2], weight, id1, id2);
        }
        numberEdges++;
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


    DirectedGraph get_prim2(int key){
        if (AdjacencyList.find(key)!=AdjacencyList.end()){
            if(!is_bidirectional() || !is_convex()){
                std::cout<<"este grafo no es bidireccional o no es conexo, por lo que no se le puede sacar prim"<<std::endl;
                DirectedGraph retorno;
                return retorno;
            }else {
                std::vector<tipoEntero> nodes_checked;
                std::vector<tipoEntero> All_nodes = get_nodes();
                nodes_checked.push_back(key);
                DirectedGraph retorno;
                Node *temporalx = AdjacencyList[key];
                retorno.insert_Node(temporalx->x, temporalx->y, temporalx->id);
                int contador = 0;
                while (nodes_checked.size() != All_nodes.size() && contador < 10) {
                    Edge temporal(100000);
                    for(auto it:nodes_checked){
                        auto temporal2=AdjacencyList[it]->vector_de_edges;
                        for(auto it2:temporal2){
                            auto idfrom_found=find(nodes_checked.begin(),nodes_checked.end(),it2.idfrom);
                            auto idto_found=find(nodes_checked.begin(),nodes_checked.end(),it2.idto);
                            if ((idfrom_found==nodes_checked.end() || idto_found==nodes_checked.end()) && it2.weight<temporal.weight){
                                temporal=it2;
                            }
                        }
                    }
                    auto idfrom_found=find(nodes_checked.begin(),nodes_checked.end(),temporal.idfrom);
                    if (idfrom_found==nodes_checked.end()){
                        nodes_checked.push_back(temporal.idfrom);
                        retorno.insert_Node(temporal.from->x,temporal.from->y,temporal.from->id);
                    }else{
                        nodes_checked.push_back(temporal.idto);
                        retorno.insert_Node(temporal.to->x,temporal.to->y,temporal.to->id);
                    }
                    retorno.insert_Edge(temporal.idto,temporal.idfrom,temporal.weight);
                    retorno.insert_Edge(temporal.idfrom,temporal.idto,temporal.weight);
                    contador++;
                }
                retorno.printAdjecentList();
                std::cout<<"PRIM"<<std::endl;
                return retorno;


            }
            }else{
            std::cout<<"id no encontrado"<<std::endl;
        }

    }




};

bool check_nodos_prioridad(int node,std::vector< int> usados){
    for (auto it:usados){
        if (it==node){
            return true;
        }
    }
    return false;
}

int get_last_value_of_id(int node, std::vector<nodo_dijkstra>& prioridades){
    for (auto it:prioridades[prioridades.size()-2].valores){
        if (it.first==node){
            return it.second;
        }
    }
}

int get_index_with_node(int node,std::vector<int> vector2){
    for (int i=0;i<vector2.size();i++){
        if (vector2[i]==node){
            return i;
        }
    }
}

void delete_every_repeated(std::vector<int>usados,std::vector<nodo_prioridad>& priorityqeue){
    std::vector<nodo_prioridad> temporal;
    for (int i=0;i<priorityqeue.size();i++){
        if (!check_nodos_prioridad(priorityqeue[i].idto,usados)){
            temporal.emplace_back(nodo_prioridad(priorityqeue[i].idfrom,priorityqeue[i].idto,priorityqeue[i].costo));
            cout<<priorityqeue[i].idfrom<<" "<<priorityqeue[i].idto<<" "<<priorityqeue[i].costo<<"WA HELLO THERE"<<endl;
            for (auto it:usados){
                cout<<it<<" ";

            }
        }
    }
    priorityqeue.clear();
    for (int i=0;i<temporal.size();i++){
        priorityqeue.emplace_back(temporal[i].idfrom,temporal[i].idto,temporal[i].costo);
    }
}
#endif //GRAPHS_LUISPARAADA_CGRAPH_H
