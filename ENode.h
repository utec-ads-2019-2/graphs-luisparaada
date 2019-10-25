//
// Created by Christian Ledgard on 10/18/19.
//

#ifndef GRAPHS_LUISPARAADA_ENODE_H
#define GRAPHS_LUISPARAADA_ENODE_H
#include <vector>
typedef int tipoEntero; //Edges
typedef double tipoDouble; //Peso

// Data structure to store Adjacency list nodes
struct Edge;
struct Node;
struct Edge2;

struct Edge {
    Node* from,*to;
    tipoDouble weight;
    tipoEntero idfrom,idto;
    Edge(Node* from1, Node* to1, tipoDouble weight1,tipoEntero idfrom1,tipoEntero idto1) : from(from1), to(to1), weight(weight1),idfrom(idfrom1),idto(idto1) {};
};

// Data structure to store graph edges
struct Edge2 {
    tipoEntero src, dest;
    tipoDouble weight;

    Edge2(std::string src, std::string dest){
        this->src = std::stoi(src);
        this->dest = std::stoi(dest);
    }

    Edge2(tipoEntero src, tipoEntero deprintListst) : src(src), dest(dest) {}
    Edge2(tipoEntero src, tipoEntero dest, tipoDouble weight) : src(src), dest(dest), weight(weight) {}
};
struct Node{
    tipoDouble x;
    tipoDouble y;
    tipoEntero id;
    std::vector<Edge> vector_de_edges;
    Node (int x1,int y1,unsigned int id1):x(x1),y(y1),id(id1){};
};


#endif //GRAPHS_LUISPARAADA_ENODE_H
