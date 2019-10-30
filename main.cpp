#include <iostream>
#include "CGraph.h"
#include "CJSON.h"

using namespace std;

const char *const mode = "r"; // rb for windows

template <class T>
void printEdgesFromVector(const vector<T> &vec);

void printCondition(bool is, const std::string& type);

int main()
{
    CJSON airport("JSON/airports.json", mode);

    //airport.print();

    DirectedGraph graph(airport.getDocument());
    //graph.printAdjecentList();
    //std::cout << "nodos: "<< graph.getNumberNodes() << std::endl;
    //std::cout  << "edges: "<< graph.getNumberEdges() << std::endl;
    //std::cout  << "density: "<< graph.getDensity() << std::endl;



    UndirectedGraph g2;
    g2.insert_Node(0,0,0);
    g2.insert_Node(0,0,1);
    g2.insert_Node(0,0,2);
    g2.insert_Node(0,0,3);

    g2.insert_Edge(0,1,10);
    g2.insert_Edge(1,3,15);
    g2.insert_Edge(3,2,4);
    g2.insert_Edge(2,0,6);
    g2.insert_Edge(0,3,5);

    printCondition(graph.is_convex(), "Convexo");


    //g2.printAdjecentList();
    printEdgesFromVector(g2.kruskal());


    DirectedGraph dg;
    dg.insert_Node(0,0,1);
    dg.insert_Node(0,0,2);
    dg.insert_Node(0,0,3);
    dg.insert_Node(0,0,4);
    dg.insert_Edge(3,1,2);
    dg.insert_Edge(4,1,2);
    dg.insert_Edge(2,4,2);
    dg.insert_Edge(3,2,3);
    dg.insert_Edge(4,2,3);

    //dg.insert_Edge(3,4,2);

    UndirectedGraph ga;
    ga.insert_Node(0,0,1);
    ga.insert_Node(0,0,2);
    ga.insert_Edge(2,1,2);


    printCondition(ga.is_convex(), "Bipartido");

    //dg.insert_Edge(3,1,3);
    //dg.insert_Edge(3,2,3);

    printCondition(dg.isBipartite(), "Bipartido");

    return 0;
}


template <class T>
void printEdgesFromVector(const vector<T> &vec) {
    cout << "MST" << endl;
    for(auto elemento : vec){
        cout <<"("<< elemento.idto<<", " <<elemento.idfrom << ", " <<elemento.weight << ")" << endl;
    }
}

void printCondition(bool is, const std::string& type){
    if(is){
        cout<<"El Grafo es " << type <<endl;
    }else{
        cout<<"El Grafo no es " << type <<endl;
    }
}
