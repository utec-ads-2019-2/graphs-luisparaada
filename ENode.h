//
// Created by Christian Ledgard on 10/18/19.
//

#ifndef GRAPHS_LUISPARAADA_ENODE_H
#define GRAPHS_LUISPARAADA_ENODE_H

// Data structure to store Adjacency list nodes
struct Node {
    int val, cost;
    Node* next;
};

// Data structure to store graph edges
struct Edge {
    int src, dest, weight;
};

#endif //GRAPHS_LUISPARAADA_ENODE_H
