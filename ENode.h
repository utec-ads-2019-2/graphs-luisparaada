//
// Created by Christian Ledgard on 10/18/19.
//

#ifndef GRAPHS_LUISPARAADA_ENODE_H
#define GRAPHS_LUISPARAADA_ENODE_H

typedef int tipoEntero; //Edges
typedef double tipoWeight; //Peso

// Data structure to store Adjacency list nodes
struct Node {
    tipoEntero val;
    tipoWeight cost;
    Node* next;
    int color;
    Node(tipoEntero val, tipoWeight cost, Node *next) : val(val), cost(cost), next(next), color(0) {}
};

// Data structure to store graph edges
struct Edge {
    tipoEntero src, dest;
    tipoWeight weight;

    Edge(std::string src, std::string dest){
        this->src = std::stoi(src);
        this->dest = std::stoi(dest);
    }

    Edge(tipoEntero src, tipoEntero dest) : src(src), dest(dest) {}
    Edge(tipoEntero src, tipoEntero dest, tipoWeight weight) : src(src), dest(dest), weight(weight) {}
};

#endif //GRAPHS_LUISPARAADA_ENODE_H
