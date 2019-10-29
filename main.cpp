#include <iostream>
#include "CGraph.h"
#include "CJSON.h"

using namespace std;

const char *const mode = "r"; // rb for windows

template <class T>
void printEdgesFromVector(const vector<T> &vec);


int main()
{
    //CJSON airport("JSON/airports.json", mode);

    //airport.print();

    //DirectedGraph graph(airport.getDocument());

   //DirectedGraph g1;
    //g1.insert_Node(0,0,0);

    UndirectedGraph g2;
    g2.insert_Node(0,0,0);
    g2.insert_Node(0,0,1);
    g2.insert_Node(0,0,2);
    g2.insert_Node(0,0,3);

    g2.insert_Edge(0,1,10);//
    g2.insert_Edge(1,3,15);//
    g2.insert_Edge(3,2,4);//
    g2.insert_Edge(2,0,6);//
    g2.insert_Edge(0,3,5);//

    g2.printAdjecentList();

    printEdgesFromVector(g2.kruskal());

//    graph.insert_Node(5,5,1);
//    graph.insert_Node(10,10,2);
//
//    graph.insert_Edge(2,1,6);

    //graph.remove(1,5);
    //graph.remove(1,2);
    //graph.remove(1,4);
    //graph.remove(1,3);
    //graph.remove(10,5446);

/*    std::cout << "nodos: "<< graph.getNumberNodes() << std::endl;
    std::cout  << "edges: "<< graph.getNumberEdges() << std::endl;
    std::cout  << "density: "<< graph.getDensity() << std::endl;

    //graph.printAdjecentList();
    std::cout<<std::endl<<std::endl;
    //graph.delete_Node(7275);
    graph.printAdjecentList();
    if (graph.know_if_convex()){
        cout<<"NICE"<<endl;

    }else{
        cout<<"F"<<endl;
    }*/

    return 0;
}


template <class T>
void printEdgesFromVector(const vector<T> &vec) {
    cout << "MST" << endl;
    for(auto elemento : vec){
        cout <<"("<< elemento.idto<<", " <<elemento.idfrom << ", " <<elemento.weight << ")" << endl;
    }
}
