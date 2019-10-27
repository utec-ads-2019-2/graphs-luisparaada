#include <iostream>
#include "CGraph.h"
#include "CJSON.h"

using namespace std;

const char *const mode = "r"; // rb for windows

int main()
{
    CJSON airport("JSON/airports.json", mode);

    //airport.print();

    DirectedGraph graph(airport.getDocument());


//    graph.insert_Node(5,5,1);
//    graph.insert_Node(10,10,2);
//
//    graph.insert_Edge(2,1,6);

    //graph.remove(1,5);
    //graph.remove(1,2);
    //graph.remove(1,4);
    //graph.remove(1,3);
    //graph.remove(10,5446);

    std::cout << "nodos: "<< graph.getNumberNodes() << std::endl;
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

    }

    return 0;
}