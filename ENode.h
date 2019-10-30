//
// Created by Christian Ledgard on 10/18/19.
//

#ifndef GRAPHS_LUISPARAADA_ENODE_H
#define GRAPHS_LUISPARAADA_ENODE_H
#include <vector>
#include "typedef.h"

// Data structure to store Adjacency list nodes
struct Edge;
struct Node;

struct Node{
    tipoDouble x;
    tipoDouble y;
    tipoEntero id;
    std::vector<Edge> vector_de_edges;
    int color;

    Node(tipoDouble x, tipoDouble y, tipoEntero id) : x(x), y(y), id(id), color(0) {}
};


struct Edge {
    Node *from, *to;
    tipoDouble weight;
    tipoEntero idfrom, idto;

    Edge(Node *from, Node *to, tipoDouble weight, tipoEntero idfrom, tipoEntero idto) : from(from), to(to),
                                                                                        weight(weight), idfrom(idfrom),
                                                                                        idto(idto) {}
};

struct SimpleEdge{
    tipoDouble weight;
    tipoEntero idfrom, idto;

    SimpleEdge() {}

    SimpleEdge(tipoDouble weight, tipoEntero idfrom, tipoEntero idto) : weight(weight), idfrom(idfrom), idto(idto) {}
};

struct subset
{
    tipoDouble parent;
    tipoDouble rank;
};


#endif //GRAPHS_LUISPARAADA_ENODE_H
