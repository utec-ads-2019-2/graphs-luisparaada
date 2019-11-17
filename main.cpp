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
    /*CJSON airport("JSON/airports.json", mode);

    //airport.print();

    DirectedGraph graph(airport.getDocument());
    graph.printAdjecentList();
    std::cout << "nodos: "<< graph.getNumberNodes() << std::endl;
    std::cout  << "edges: "<< graph.getNumberEdges() << std::endl;
    std::cout  << "density: "<< graph.getDensity() << std::endl;

    printCondition(graph.is_convex(), "Convexo");
    printCondition(graph.isBipartite(), "Bipartito");


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

    //printCondition(graph.is_convex(), "Convexo");


    //g2.printAdjecentList();
    //printEdgesFromVector(g2.kruskal());
*/

    UndirectedGraph dg;
    dg.insert_Node(0,0,1);
    dg.insert_Node(0,0,2);
    dg.insert_Node(0,0,3);
    dg.insert_Node(0,0,4);
    dg.insert_Node(0,0,5);
    dg.insert_Node(0,0,6);
    dg.insert_Node(0,0,7);
    dg.insert_Node(0,0,8);
    dg.insert_Node(0,0,9);
    dg.insert_Node(0,0,10);

    dg.insert_Edge(2,10,15);
    dg.insert_Edge(10,4,15);
    dg.insert_Edge(4,8,5);
    dg.insert_Edge(8,2,29);
    dg.insert_Edge(10,8,15);
    dg.insert_Edge(7,2,2);
    dg.insert_Edge(5,2,24);
    dg.insert_Edge(5,8,19);
    dg.insert_Edge(5,1,13);
    dg.insert_Edge(1,4,13);
    dg.insert_Edge(1,3,4);
    dg.insert_Edge(4,3,39);
    dg.insert_Edge(3,6,9);
    dg.insert_Edge(6,9,7);
    dg.insert_Edge(9,1,11);
    dg.insert_Edge(9,3,37);
    dg.insert_Edge(9,5,26);
    dg.insert_Edge(9,7,39);
    dg.insert_Edge(7,5,2);
    dg.insert_Edge(8,1,5);

    auto temporal=dg.DFS(4);
    for (auto it:temporal){
        cout<<"("<<it.idfrom<<" "<<it.idto<<", "<<it.weight<<") "<<endl;
    }

    /*auto temporal=dg.BFS(4);
    for (auto it:temporal){
        cout<<"("<<it.idfrom<<" "<<it.idto<<", "<<it.weight<<") "<<endl;
    }
    */cout<<"NOW ADJACENCY LIST"<<endl;



    //printEdgesFromVector(dg.kruskal());
    dg.printAdjecentList();
    dg.get_prim2(1).printAdjecentList();
    std::cout<<"PRIM"<<std::endl;



    /*dg.insert_Edge(4,1,2);
    dg.insert_Edge(2,4,2);
    dg.insert_Edge(3,2,3);
    dg.insert_Edge(4,2,3);
*/
    //dg.insert_Edge(3,4,2);

    UndirectedGraph ga;
    ga.insert_Node(0,0,1);
    ga.insert_Node(0,0,2);
    ga.insert_Edge(2,1,2);
    
    //printEdgesFromVector(ga.kruskal());

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
